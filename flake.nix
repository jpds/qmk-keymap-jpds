{
  description = "A Nix flake for building QMK firmware for custom keyboards with specific keymaps.";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

    qmk_firmware = {
      type = "git";
      url = "https://github.com/qmk/qmk_firmware";
      ref = "refs/tags/0.31.6";
      submodules = true;
      flake = false;
    };

    qmkfmt = {
      url = "github:rcorre/qmkfmt?ref=v0.3.0";
      flake = false;
    };

    getreuer_modules = {
      url = "github:getreuer/qmk-modules";
      flake = false;
    };
  };

  outputs =
    {
      self,
      nixpkgs,
      qmkfmt,
      qmk_firmware,
      getreuer_modules,
    }:
    let
      keyboards = [
        {
          keyboard = "zsa/voyager";
          name = "jpds";
          rules = ./keyboards/zsa/voyager/keymaps/jpds/rules.mk;
          rgb_matrix = ./keyboards/zsa/voyager/keymaps/jpds/rgb_matrix_user.inc;
          config = ./keyboards/zsa/voyager/keymaps/jpds/config.h;
          keymap = ./keyboards/zsa/voyager/keymaps/jpds/keymap.c;
          keymap_json = ./keyboards/zsa/voyager/keymaps/jpds/keymap.json;
        }
      ];

      pkgs = import nixpkgs {
        system = "x86_64-linux";
      };

      qmkfmtPkg = pkgs.rustPlatform.buildRustPackage {
        pname = "qmkfmt";
        version = "v0.3.0";
        src = qmkfmt;
        cargoHash = "sha256-+0tFSSZR5tBUC0WbJ1Oc3b6n5q3JkaeMnL9bzL6B3zo=";
        doCheck = false;
      };

      flash = pkgs.writeShellScriptBin "flash" ''
        set -e

        FIRMWARE_PATH="$1"
        if [ -z "$FIRMWARE_PATH" ]; then
          echo "Usage: flash <path_to_firmware>"
          exit 1
        fi

        # https://github.com/qmk/qmk_firmware/blob/master/keyboards/zsa/voyager/rules.mk
        ${pkgs.lib.getExe pkgs.dfu-util} -d 3297:0791 -a 0 -s 0x08002000:leave -D $FIRMWARE_PATH
        # QMK_HOME=${qmk_firmware} ${pkgs.qmk}/bin/qmk --config-file /dev/null flash -kb zsa/voyager "$FIRMWARE_PATH"
      '';

      firmware = pkgs.stdenv.mkDerivation {
        pname = "qmk_firmware";
        version = "v1.0";
        src = qmk_firmware;

        nativeBuildInputs = [
          pkgs.gnumake
          pkgs.qmk
        ];

        patchPhase = builtins.concatStringsSep "\n" (
          map (k: ''
            mkdir -p keyboards/${k.keyboard}/keymaps/${k.name}
            cp ${k.rgb_matrix} keyboards/${k.keyboard}/keymaps/${k.name}/rgb_matrix_user.inc
            cp ${k.rules} keyboards/${k.keyboard}/keymaps/${k.name}/rules.mk
            cp ${k.config} keyboards/${k.keyboard}/keymaps/${k.name}/config.h
            cp ${k.keymap} keyboards/${k.keyboard}/keymaps/${k.name}/keymap.c
            cp ${k.keymap_json} keyboards/${k.keyboard}/keymaps/${k.name}/keymap.json

            mkdir -p modules/getreuer/
            cp -r ${getreuer_modules}/* modules/getreuer/
          '') keyboards
        );

        buildPhase = builtins.concatStringsSep "\n" (
          map (k: ''
            SKIP_GIT=true make -r -R -f builddefs/build_keyboard.mk -s KEYBOARD=${k.keyboard} KEYMAP=${k.name} KEYBOARD_FILESAFE=${k.keyboard} TARGET=${k.name} VERBOSE=false COLOR=true SILENT=false
          '') keyboards
        );

        installPhase = ''
          mkdir -p $out/firmware
          mkdir -p $out/bin

          cp -r .build/*.bin $out/firmware/
          cp ${flash}/bin/flash $out/bin
        '';
      };
    in
    {
      packages.x86_64-linux.firmware = firmware;
      packages.x86_64-linux.default = firmware;

      devShells.x86_64-linux.default = nixpkgs.legacyPackages.x86_64-linux.mkShell {
        buildInputs = [
          qmkfmtPkg
          pkgs.qmk
          pkgs.ccls
          pkgs.clang-tools
        ];
      };
    };
}

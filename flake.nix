{
  description = "Rumble GameCube controller with ponylang.";

  outputs = { self, nixpkgs }: {

    packages.x86_64-linux =
      let pkgs = import nixpkgs { system = "x86_64-linux"; };
      in {
        listdevs = pkgs.stdenv.mkDerivation {
          name = "rumblepony";
          src = ./.;

          description = ''
            libusb example code for listing devices

            see: https://github.com/libusb/libusb/blob/4e2de881cf0f8b38b1e19c078d19b4628f38c732/examples/listdevs.c
          '';

          buildInputs = with pkgs; [ libusb libusb.dev ];

          buildPhase = ''
            gcc listdevs.c "${pkgs.libusb}/lib/libusb-1.0.so" \
              -I "${pkgs.libusb.dev}/include/libusb-1.0" \
              -o listdevs
          '';

          installPhase = ''
            mkdir -p $out/bin && cp listdevs $out/bin
          '';
        };
      };
  };
}

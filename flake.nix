{
  description = "Rumble GameCube controller with ponylang.";

  outputs = { self, nixpkgs }: {

    packages.x86_64-linux =
      let pkgs = import nixpkgs { system = "x86_64-linux"; };
      in {
        read-gcc = pkgs.stdenv.mkDerivation {
          name = "read-gcc";
          src = ./.;

          buildInputs = with pkgs; [ libusb libusb.dev ];

          buildPhase = ''
            gcc read-gcc.c "${pkgs.libusb}/lib/libusb-1.0.so" \
              -I "${pkgs.libusb.dev}/include/libusb-1.0" \
              -o read-gcc
          '';

          installPhase = ''
            mkdir -p $out/bin && cp read-gcc $out/bin
          '';
        };
      };
  };
}

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
              -Wall \
              -o read-gcc

            gcc -c read-gcc.c "${pkgs.libusb}/lib/libusb-1.0.so" \
              -I "${pkgs.libusb.dev}/include/libusb-1.0" \
              -Wall \
              -o read-gcc.o
            gcc -shared -o read-gcc.so read-gcc.o "${pkgs.libusb}/lib/libusb-1.0.so"
          '';

          installPhase = ''
            mkdir -p $out/bin && mkdir -p $out/lib \
              && cp read-gcc $out/bin \
              && cp read-gcc.so $out/lib
          '';
        };
      };
  };
}

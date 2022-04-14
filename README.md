# rumblepony

The goal: **write a Pony program that rumbles a GameCube controller (connected via USB) to rumble when the A button is held.**

# motivation

* explore `libusb` C API
* explore `rusb` Rust bindings
* practice understanding Rust FFI
* practice using Pony FFI

# usage

## running `libusb` example code from NixOS

This is example code from `libusb`:
* [https://github.com/libusb/libusb/blob/4e2de881cf0f8b38b1e19c078d19b4628f38c732/examples/listdevs.c]

```sh
; nix eval --raw .#listdevs.buildPhase
gcc listdevs.c "/nix/store/4izsgifdpqnfbwy5mlb47c7ab553gyhv-libusb-1.0.25/lib/libusb-1.0.so" \
  -I "/nix/store/y9mg8d6ic9pqa72376dkygyv2wy7bs95-libusb-1.0.25-dev/include/libusb-1.0" \
  -o listdevs
```

I added this to the flake to test using [`libusb` API functions](https://libusb.sourceforge.io/api-1.0/libusb_api.html), starting from the simplest working example:
``` shell-session
; nix build github:djanatyn/rumblepony#listdevs -o listdevs \
    && ./listdevs/bin/listdevs
1d6b:0003 (bus 4, device 1)
057e:0337 (bus 3, device 103) path: 3
1d6b:0002 (bus 3, device 1)
1d6b:0003 (bus 2, device 1)
feed:6061 (bus 1, device 90) path: 5.4
1532:0e03 (bus 1, device 89) path: 5.3
046d:c539 (bus 1, device 88) path: 5.2
1a40:0101 (bus 1, device 87) path: 5
046d:0ab7 (bus 1, device 84) path: 4
0a12:0001 (bus 1, device 75) path: 3
1d6b:0002 (bus 1, device 1)
```

## rumblepony

Slightly modified example code.
```sh
; cd rumblerust && cargo run
```

# references

* [`jam1garner/gc-adapter`](https://github.com/jam1garner/gc-adapter), a rust library for the GameCube controller adapter that uses...
* [`a1ien/rusb`](https://docs.rs/rusb/0.6.5/rusb), a safe rust wrapper for...
* [`libusb`](https://github.com/libusb/libusb), a library for USB devices written in C.

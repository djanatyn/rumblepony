# rumblepony

The goal: **write a Pony program that rumbles a GameCube controller (connected via USB) to rumble when the A button is held.**

# motivation

* explore `libusb` C API
* explore `rusb` Rust bindings
* practice understanding Rust FFI
* practice using Pony FFI

# usage

``` sh
nix build github:djanatyn/rumblepony#read-gcc -o read-gcc \
    && watch -n1 './read-gcc/bin/read-gcc | xxd'
```
```
Every 1.0s: ./read-gcc/bin/read-gcc | xxd

device found: 0x19F0FC0
00000000: 2104 0000 0000 0000 0000 1400 007a 8a78  !............z.x
00000010: 751f 2504 0000 0000 0000 0000 0400 0000  u.%.............
00000020: 0000 0000 00                             .....
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

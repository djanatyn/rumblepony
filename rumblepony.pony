use "path:/nix/store/xjfjkiqmchp40z83krkyjhx0p7mmsbg6-read-gcc/lib"
use "lib:read-gcc"

use @open_adapter[I32](adapter: Pointer[U8] tag)
use @check_controller[I32](adapter: Pointer[U8] tag, info: Pointer[ControllerInfo] tag)

struct Controller
  var a: Bool = false

struct ControllerInfo
  embed p1: Controller = Controller
  embed p2: Controller = Controller
  embed p3: Controller = Controller
  embed p4: Controller = Controller

  new create() => None

struct AdapterHandle
	var handle: Pointer[U8] tag = Pointer[U8]

actor Main
  new create(env: Env) =>
    var handle = AdapterHandle

    let result: I32 = @open_adapter(handle.handle)

    env.out.print("hello world")

use @gamecube_adapter_init[I32]()
use @gamecube_adapter_exit[None]()
use @open_adapter[I32](adapter: Pointer[None] tag)
use @check_controller[I32](adapter: Pointer[None] tag, info: Pointer[ControllerInfo] tag)

struct Controller
  var a: U8 = 0

  new create() => None

struct ControllerInfo
  embed p1: Controller = Controller
  embed p2: Controller = Controller
  embed p3: Controller = Controller
  embed p4: Controller = Controller

  new create() => None

struct AdapterHandle
  var handle: Pointer[None] tag = Pointer[None]

  new create() => None

actor Main
  new create(env: Env) =>
    var result = @gamecube_adapter_init()
    env.out.print("initialized libusb: " + result.string())

    var adapter = AdapterHandle
    result = @open_adapter(addressof adapter)
    env.out.print("opened adapter adapter: " + result.string())

    var info = ControllerInfo

    result = @check_controller(addressof adapter, addressof info)
    env.out.print("checked controller states: " + result.string())
    env.out.print(info.p2.a.string())

    @gamecube_adapter_exit()
    env.out.print("success! :)")

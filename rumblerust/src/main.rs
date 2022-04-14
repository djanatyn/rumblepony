use gc_adapter::GcAdapter;
use std::thread::sleep;
use std::time::Duration;

fn main() {
    let mut adapter = GcAdapter::from_usb().expect("could not grab adapter");

    loop {
        adapter.refresh_inputs();
        dbg!(adapter.read_controllers());

        // one second rumble
        adapter.set_rumble([true, true, true, true]);
        sleep(Duration::from_secs(1));

        // one second no rumble
        adapter.set_rumble([false, false, false, false]);
        sleep(Duration::from_secs(1));
    }
}

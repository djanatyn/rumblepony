#include "read-gcc.h"
#include "libusb.h"

int main(void)
{
    if (libusb_init(NULL) < 0) { return 1; }

    struct AdapterHandle adapter;
    int r;
    r = open_adapter(&adapter);
    switch (r) {
        case 0:
            fprintf(stderr, "device found: %p\n", adapter.handle);
            break;
        case ERR_ADAPTER_NOT_FOUND:
            fprintf(stderr, "device not found\n");
            return 1;
        default:
            fprintf(stderr, "unknown error");
            return 1;
    };

    struct ControllerInfo info;
    r = check_controller(&adapter, &info);

    printf(info.p1.a ? "p1: true\n" : "p1: false\n");
    printf(info.p2.a ? "p2: true\n" : "p2: false\n");
    printf(info.p3.a ? "p3: true\n" : "p3: false\n");
    printf(info.p4.a ? "p4: true\n" : "p4: false\n");

    libusb_exit(NULL);
    return 0;
}

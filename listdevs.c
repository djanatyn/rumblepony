#include <stdio.h>
#include "libusb.h"

int main(void)
{
	libusb_device **devs;
	int r;
	ssize_t cnt;

	// init libusb
	if (libusb_init(NULL) < 0) { return 1; }

	// get all devices
	if (libusb_get_device_list(NULL, &devs) < 0) {
		libusb_exit(NULL);
		return 1;
	}

	// does it makes sense to set this to NULL?
	libusb_device *adapter = NULL;
	libusb_device *dev;
	int i = 0;

	// look for mayflash adapter
	while ((dev = devs[i++]) != NULL) {
		struct libusb_device_descriptor desc;
		if (libusb_get_device_descriptor(dev, &desc) > 0) {
			fprintf(stderr, "failed to get device descriptor");
			continue;
		}

		// adapter vid is 0x057e
		// adapter pid is 0x0337
		if (desc.idVendor == 0x057e) {
			printf("%04x:%04x\n", desc.idVendor, desc.idProduct);
			adapter = dev;
		} else { continue; }
	}

	if (adapter != NULL) {
		printf("found adapter\n");
	} else {
		printf("adapter not found\n");
	};

	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);

	return 0;
}

#include <stdio.h>
#include "libusb.h"

int main(void)
{
	// init libusb
	if (libusb_init(NULL) < 0) { return 1; }

	// adapter vid is 0x057e
	// adapter pid is 0x0337
	libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, 0x057e, 0x0337);

	// check for handle
	if (handle != NULL) {
		printf("device found: 0x%X\n", handle);
	} else {
		printf("device not found\n");
	}

	unsigned char data;
	int ret, len;
	ret = libusb_interrupt_transfer(handle, 0x81, data, 1, &len, 0);

	if (ret != 0) {
		printf("failed\n");
		printf("ret: %d\n", ret);
		printf("len: %d\n", len);
		printf("data: %d\n", data);
	} else {
		printf("%d\n", len);
		printf("%x\n", data);
	}

	// quit
	libusb_exit(NULL);
	return 0;
}

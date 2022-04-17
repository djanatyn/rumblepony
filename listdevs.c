#include <stdio.h>
#include "libusb.h"

const int LENGTH = 37;
const int MAYFLASH_ENDPOINT = 0x81;
const int MAYFLASH_VID = 0x057e;
const int MAYFLASH_PID = 0x0337;

int main(void)
{
	// init libusb
	if (libusb_init(NULL) < 0) { return 1; }

	// get mayflash handle
	libusb_device_handle *handle =
		libusb_open_device_with_vid_pid(NULL, MAYFLASH_VID, MAYFLASH_PID);

	// abort if handle not found
	if (handle != NULL) {
		fprintf(stderr, "device found: 0x%X\n", handle);
	} else {
		fprintf(stderr, "device not found\n");
		return 1;
	}

	// prepare buffer for usb interrupt transfer
	unsigned char data[LENGTH];
	int ret, len;
	ret = libusb_interrupt_transfer(handle, MAYFLASH_ENDPOINT, data, LENGTH, &len, 0);

	if (ret != 0) {
		fprintf(stderr, "failed\n");
		fprintf(stderr, "ret: %d\n", ret);
		fprintf(stderr, "len: %d\n", len);
		fprintf(stderr, "data: %d\n", data);
	} else {
		for (int i = 0; i < LENGTH; i++) {
			printf("%c", data[i]);
		}
	}

	libusb_exit(NULL);
	return 0;
}

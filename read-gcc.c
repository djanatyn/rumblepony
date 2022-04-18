#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "libusb.h"

const int CONTROLLER_WIDTH = 9;
const int A_BUTTON_OFFSET = 1;
const int LENGTH = 37;
const int MAYFLASH_ENDPOINT = 0x81;
const int MAYFLASH_WRITE_ENDPOINT = 2;
const int MAYFLASH_VID = 0x057e;
const int MAYFLASH_PID = 0x0337;
const int MAGIC = 0x21;

struct Controller {
	bool a;
};

struct ControllerInfo {
	struct Controller p1;
	struct Controller p2;
	struct Controller p3;
	struct Controller p4;
};

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
		/* for (int i = 0; i < LENGTH; i++) { */
		/* 	putchar(data[i]); */
		/* } */

		if (*data != MAGIC)  {
			fprintf(stderr, "did not find magic number: %#x", *data);
			return 1;
		} else {
			unsigned char *startp1 = data + 1; // skip magic
			unsigned char *startp2 = startp1 + CONTROLLER_WIDTH;
			unsigned char *startp3 = startp2 + CONTROLLER_WIDTH;
			unsigned char *startp4 = startp3 + CONTROLLER_WIDTH;

			struct Controller p1, p2, p3, p4;
			memcpy(&p1.a, startp1 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&p2.a, startp2 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&p3.a, startp3 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&p4.a, startp4 + A_BUTTON_OFFSET, sizeof(bool));

			printf(p1.a ? "p1: true\n" : "p1: false\n");
			printf(p2.a ? "p2: true\n" : "p2: false\n");
			printf(p3.a ? "p3: true\n" : "p3: false\n");
			printf(p4.a ? "p4: true\n" : "p4: false\n");
		}
	}

	libusb_exit(NULL);
	return 0;
}

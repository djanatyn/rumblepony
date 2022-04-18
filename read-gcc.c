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

struct AdapterHandle {
	libusb_device_handle *handle;
};

const int ERR_ADAPTER_NOT_FOUND = 1;

// try to open mayflash adapter, setting handle
int open_adapter(struct AdapterHandle *adapter) {
	libusb_device_handle *handle =
		libusb_open_device_with_vid_pid(NULL, MAYFLASH_VID, MAYFLASH_PID);

	// abort if handle not found
	if (handle != NULL) {
		adapter->handle = handle;
		return 0;
	} else {
		return ERR_ADAPTER_NOT_FOUND;
	}
}

const int ERR_UNEXPECTED_LENGTH = 1;
const int ERR_NO_MAGIC = 2;

int check_controller(struct AdapterHandle *adapter, struct ControllerInfo *info) {
	unsigned char data[LENGTH];
	int r, len;
	r = libusb_interrupt_transfer(adapter->handle, MAYFLASH_ENDPOINT, data, LENGTH, &len, 0);

	if (r != 0) {
		fprintf(stderr, "[check_controller] failed\n");
		fprintf(stderr, "[check_controller] r: %d\n", r);
		fprintf(stderr, "[check_controller] len: %d\n", len);
		return ERR_UNEXPECTED_LENGTH;
	} else {
		/* for (int i = 0; i < LENGTH; i++) { */
		/* 	putchar(data[i]); */
		/* } */

		if (*data != MAGIC)  {
			fprintf(stderr, "[check_controller] did not find magic number: %#x", *data);
			return ERR_NO_MAGIC;
		} else {
			unsigned char *startp1 = data + 1; // skip magic
			unsigned char *startp2 = startp1 + CONTROLLER_WIDTH;
			unsigned char *startp3 = startp2 + CONTROLLER_WIDTH;
			unsigned char *startp4 = startp3 + CONTROLLER_WIDTH;

			struct Controller p1, p2, p3, p4;
			memcpy(&(info->p1.a), startp1 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&(info->p2.a), startp2 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&(info->p3.a), startp3 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&(info->p4.a), startp4 + A_BUTTON_OFFSET, sizeof(bool));

			printf(info->p1.a ? "p1: true\n" : "p1: false\n");
			printf(info->p2.a ? "p2: true\n" : "p2: false\n");
			printf(info->p3.a ? "p3: true\n" : "p3: false\n");
			printf(info->p4.a ? "p4: true\n" : "p4: false\n");

			return 0;
		}
	}

}

int main(void)
{
	// init libusb
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

	libusb_exit(NULL);
	return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "libusb.h"
#include "read-gcc.h"

int gamecube_adapter_init() {
	return libusb_init(NULL);
}

void gamecube_adapter_exit() {
	libusb_exit(NULL);
}

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

// update controller state, reading adapter's handle
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
			return ERR_BAD_MAGIC;
		} else {
			unsigned char *startp1 = data + 1; // skip magic
			unsigned char *startp2 = startp1 + CONTROLLER_WIDTH;
			unsigned char *startp3 = startp2 + CONTROLLER_WIDTH;
			unsigned char *startp4 = startp3 + CONTROLLER_WIDTH;

			memcpy(&(info->p1.a), startp1 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&(info->p2.a), startp2 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&(info->p3.a), startp3 + A_BUTTON_OFFSET, sizeof(bool));
			memcpy(&(info->p4.a), startp4 + A_BUTTON_OFFSET, sizeof(bool));

			return 0;
		}
	}

}

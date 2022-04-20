#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "libusb.h"

extern const int CONTROLLER_WIDTH = 9;
extern const int A_BUTTON_OFFSET = 1;
extern const int LENGTH = 37;
extern const int MAYFLASH_ENDPOINT = 0x81;
extern const int MAYFLASH_WRITE_ENDPOINT = 2;
extern const int MAYFLASH_VID = 0x057e;
extern const int MAYFLASH_PID = 0x0337;
extern const int MAGIC = 0x21;

extern const int ERR_ADAPTER_NOT_FOUND = 1;
extern const int ERR_UNEXPECTED_LENGTH = 1;
extern const int ERR_BAD_MAGIC = 2;

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

int open_adapter(struct AdapterHandle *adapter);
int check_controller(struct AdapterHandle *adapter, struct ControllerInfo *info);

#include "ampel-lib.h"
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/types.h>

#define ERORR_GET_LISTE -1
#define ERROR_NOFOUND -2
#define SUCCESS 0

static const short VENDOR = 0x0d50;
static const short PRODUCT_ID = 0x0008;

struct libampel_ampel_led {
  libusb_context *context;
  libusb_device_handle *handle;
};

int init() {
  libusb_context *context = NULL;
  libusb_device_handle *handle = NULL;
  int error_code;

  if ((error_code = libusb_init_context(&context, NULL, 0)) < 0) {
    perror("Cannot initialize conntext");
    return ERROR_CODE;
  }

  if ((handle = libusb_open_device_with_vid_pid(context, VENDOR, PRODUCT_ID)) ==
      NULL) {
    perror("Cannot found the usb product");
    return ERROR_NOFOUND;
  }
  return SUCCESS;
}

int enable_led(LED_COLOR led_color) { return OK; }

int disable_led(LED_COLOR led_color) { return OK; }

int get_last_state() { return OK; }

char *libampel_strerror(int error_code) { return NULL; }

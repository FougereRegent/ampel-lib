#include "ampel-lib.h"
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include <sys/types.h>

#define ERROR_MSG_INIT "libusb initialization error"
#define ERROR_MSG_NOTFOUND "Device not found"
#define ERROR_MSG_USB_TRANSFER "USB transfer error"
#define ERROR_MSG_ACCESS "No access to USB port"

static const short VENDOR = 0x0d50;
static const short PRODUCT_ID = 0x0008;

struct libampel_ampel_led {
  libusb_context *context;
  libusb_device_handle *handle;
  struct libampel_state state;
};

int init(libampel_ampel_led **ampel_led) {
  libusb_context *context = NULL;
  libusb_device_handle *handle = NULL;
  int error_code;

  if ((error_code = libusb_init(&context)) < 0) {
    return ERROR_INIT;
  }

  if ((handle = libusb_open_device_with_vid_pid(context, VENDOR, PRODUCT_ID)) ==
      NULL) {
    free(context);
    return ERROR_NOTFOUND;
  }

  if (libusb_kernel_driver_active(handle, 0) == 1 &&
      (error_code = libusb_detach_kernel_driver(handle, 0)) < 0) {
    libusb_close(handle);
    free(context);
    return ERROR_ACCESS;
  }

  *ampel_led = malloc(sizeof(struct libampel_ampel_led));
  if (ampel_led == NULL) {
    return ERROR_INIT;
  }

  (*ampel_led)->context = context;
  (*ampel_led)->handle = handle;
  return OK;
}

int libampel_apply_value(libampel_ampel_led *ampel_led,
                         struct libampel_state state) {
  const unsigned char padding = 0x00;
  const int endpoint = 0x02;
  int write_byte = ERROR_USB_TRANSFER;

  unsigned char data[] = {padding, state.color, state.state};

  libusb_interrupt_transfer(ampel_led->handle, endpoint, data, sizeof(data),
                            &write_byte, 0);
  return write_byte >= 0 ? 0 : write_byte;
}

struct libampel_state get_last_state(libampel_ampel_led *ampel_led) {
  return ampel_led->state;
}

char *libampel_strerror(int error_code) {
  switch (error_code) {
  case ERROR_INIT:
    return ERROR_MSG_INIT;
  case ERROR_NOTFOUND:
    return ERROR_MSG_NOTFOUND;
  case ERROR_USB_TRANSFER:
    return ERROR_MSG_USB_TRANSFER;
  case ERROR_ACCESS:
    return ERROR_MSG_ACCESS;
  default:
    return "Unknown message";
  }
}

void release_ampel(libampel_ampel_led *ampel_led) {
  libusb_close(ampel_led->handle);
  free(ampel_led->context);
  free(ampel_led);
}

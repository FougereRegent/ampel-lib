#include "ampel-lib.h"
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define ERORR_GET_LISTE -1
#define ERROR_NOFOUND -2
#define SUCCESS 0

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
    return ERROR_CODE;
  }

  if ((handle = libusb_open_device_with_vid_pid(context, VENDOR, PRODUCT_ID)) ==
      NULL) {
    free(context);
    return ERROR_NOFOUND;
  }

  if (libusb_kernel_driver_active(handle, 0) == 1 &&
      (error_code = libusb_detach_kernel_driver(handle, 0)) < 0) {
    printf("Erreur %d\”", error_code);
    libusb_close(handle);
    free(context);
    return ERROR_CODE;
  }

  *ampel_led = malloc(sizeof(struct libampel_ampel_led));
  if (ampel_led == NULL) {
    return ERROR_CODE;
  }

  (*ampel_led)->context = context;
  (*ampel_led)->handle = handle;
  return SUCCESS;
}

int libampel_apply_value(libampel_ampel_led *ampel_led,
                         struct libampel_state state) {
  const unsigned char padding = 0x00;
  const int endpoint = 0x02;
  int write_byte = ERROR_CODE;

  unsigned char data[] = {padding, state.color, state.state};
  printf("%02x , %02x, %02x\n", padding, state.color, state.state);

  libusb_interrupt_transfer(ampel_led->handle, endpoint, data, sizeof(data),
                            &write_byte, 0);
  printf("%d\n", write_byte);

  return write_byte >= 0;
}

struct libampel_state get_last_state(libampel_ampel_led *ampel_led) {
  return ampel_led->state;
}

char *libampel_strerror(int error_code) { return NULL; }

void release_ampel(libampel_ampel_led *ampel_led) {
  libusb_close(ampel_led->handle);
  free(ampel_led->context);
  free(ampel_led);
}

#ifndef AMPEL_LIB_H
#define AMPEL_LIB_H

#define LIBLED_VERSION_MAJOR X_MAJOR
#define LIBLED_VERSION_MINOR X_MINOR
#define LIBLED_VERSION_BUILD X_BUILD
#define LIBLED_VERSION X_VERSION

/*ERROR CODE*/
#define OK 0
#define ERROR_INIT -1
#define ERROR_NOTFOUND -2
#define ERROR_USB_TRANSFER -3
#define ERROR_ACCESS -4

#include <stdbool.h>

typedef enum {
  RED = 0x10,
  ORANGE = 0x11,
  GREEN = 0x12,
} LED_COLOR;

typedef enum {
  OFF = 0x0,
  ON = 0x01,
} LED_STATE;

typedef struct libampel_ampel_led libampel_ampel_led;

struct libampel_state {
  LED_STATE state;
  LED_COLOR color;
};

struct libampel_actual_state {
  bool red_led_activated;
  bool orange_led_activated;
  bool green_led_activated;
};

extern int init(libampel_ampel_led **ampel_led);
extern int libampel_apply_value(libampel_ampel_led *ampel_led,
                                struct libampel_state state);
extern char *libampel_strerror(int error_code);
extern struct libampel_actual_state
libampel_get_last_led(libampel_ampel_led *ampel_led);
extern void release_ampel(libampel_ampel_led *ampel_led);

#endif

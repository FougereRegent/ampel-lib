#ifndef AMPEL_LIB_H
#define AMPEL_LIB_H

/*ERROR CODE*/
#define OK 0
#define ERROR_INIT -1
#define ERROR_NOTFOUND -2
#define ERROR_USB_TRANSFER -3
#define ERROR_ACCESS -4

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

int init(libampel_ampel_led **ampel_led);
int libampel_apply_value(libampel_ampel_led *ampel_led,
                         struct libampel_state state);
char *libampel_strerror(int error_code);
struct libampel_state libampel_get_last_led(libampel_ampel_led *ampel_led);
void release_ampel(libampel_ampel_led *ampel_led);

#endif

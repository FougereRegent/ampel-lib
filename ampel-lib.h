#ifndef AMPEL_LIB_H
#define AMPEL_LIB_H

#define ERROR_CODE -1
#define OK 0

typedef enum {
  RED = 0x10,
  ORANGE = 0x11,
  GREEN = 0x12,
} LED_COLOR;

typedef enum {
  OFF = 0x00,
  ON = 0x01,
} LED_STATE;

typedef struct libampel_ampel_led libampel_ampel_led;

struct libampel_state {
  LED_STATE state;
  LED_COLOR color;
};

int libampel_enable_led(LED_COLOR);
int libample_disable_led(LED_COLOR);

char *libampel_strerror(int);

#endif

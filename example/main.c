#include "../ampel-lib.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define NO_ARGS -2
#define BAD_ARGS -3

int parse_color(char *color_str, LED_COLOR *color_enum) {
  if (strcmp(color_str, "red") == 0) {
    *color_enum = RED;
  } else if (strcmp(color_str, "orange") == 0) {
    *color_enum = ORANGE;
  } else if (strcmp(color_str, "green") == 0) {
    *color_enum = GREEN;
  } else {
    return BAD_ARGS;
  }
  return 0;
}

int parse_state(char *state_str, LED_STATE *state_enum) {
  if (strcmp(state_str, "on") == 0) {
    *state_enum = ON;
  } else if (strcmp(state_str, "off") == 0) {
    *state_enum = OFF;
  } else {
    return BAD_ARGS;
  }
  return 0;
}

int parse(char **args, struct libampel_state *state) {
  char *colorArgs = args[1];
  char *stateArgs = args[2];

  return parse_state(stateArgs, &state->state) |
         parse_color(colorArgs, &state->color);
}

void help_command_display() {
  const char *help = {
      "This command is used to enable or disable some color on light\n\
the first argurment is color and the secon argurment is state\n\
the enabled color are describe below:\n\
\tRED\n\tGREEN\n\tORANGE\n\
if you want to turn on/off an color use ON/OFF keyword\n\
example : toggle orange on"};

  printf("%s\n", help);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("use help command to show some commands\n");
    help_command_display();
    return NO_ARGS;
  }

  int error_code;
  libampel_ampel_led *led = NULL;
  if ((error_code = init(&led)) < 0 || led == NULL) {
    printf("Erreur : %s\n", libampel_strerror(error_code));
    return -1;
  }

  struct libampel_state state = {.state = OFF, .color = GREEN};
  if (parse(argv, &state) < 0) {
    printf("Parsing error\n");
    return BAD_ARGS;
  }

  if ((error_code = libampel_apply_value(led, state)) < 0) {
    printf("Error : %s\n", libampel_strerror(error_code));
    return -1;
  }

  return 0;
}

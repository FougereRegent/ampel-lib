#include "../ampel-lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  int error_code;
  libampel_ampel_led *led = NULL;
  if ((error_code = init(&led)) < 0 || led == NULL) {
    printf("Erreur : %s\n", libampel_strerror(error_code));
    return -1;
  }

  struct libampel_state state = {.state = OFF, .color = GREEN};

  if ((error_code = libampel_apply_value(led, state)) < 0) {
    printf("Error : %s\n", libampel_strerror(error_code));
    return -1;
  }

  return 0;
}

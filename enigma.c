
#include "globalFunctions.h"
#include "plugBoard.h"
#include "reflector.h"
#include "rotor.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines the Rotor Size && Width
#define ROTOR_SIZE 26
#define WIDTH 100

void enigma() {
  struct PlugBoard plugBoard;
  initializePlugBoard(&plugBoard);

  struct Rotor rotor_one = {"Rotor One", NULL, NULL, 0};
  initializeRotor(&rotor_one);

  struct Rotor rotor_two = {"Rotor Two", NULL, NULL, 0};
  initializeRotor(&rotor_two);

  struct Rotor rotor_three = {"Rotor Three", NULL, NULL, 0};
  initializeRotor(&rotor_three);

  struct Reflector reflector;
  initializeReflector(&reflector);

  char message[256];
  char *prompt;

  while (1) {
    int result = menu();

    switch (result) {
    case 1:
      outputRotors(&rotor_one, &rotor_two, &rotor_three);

      prompt = "What is your message that you want encrypted?: ";
      printf("%*s%s", format_string(prompt), "", prompt);
      if (!fgets(message, sizeof(message), stdin)) {
        break; // End of input
      }

      // Remove newline character if present
      size_t len = strlen(message);
      if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
      }

      if (strcmp(message, "exit") == 0) {
        freeRotor(&rotor_one);
        freeRotor(&rotor_two);
        freeRotor(&rotor_three);
        return;
      }

      encode(&rotor_one, &rotor_two, &rotor_three, message);
      outputRotors(&rotor_one, &rotor_two, &rotor_three);
      break;

    case 2:
      prompt = "What is your message that you want decrypted?: ";
      printf("%*s%s", format_string(prompt), "", prompt);
      if (!fgets(message, sizeof(message), stdin)) {
        break; // End of input
      }

      // Remove newline character if present
      len = strlen(message);
      if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
      }

      if (strcmp(message, "exit") == 0) {
        freeRotor(&rotor_one);
        freeRotor(&rotor_two);
        freeRotor(&rotor_three);
        return;
      }

      decode(&rotor_one, &rotor_two, &rotor_three, message);
      outputRotors(&rotor_one, &rotor_two, &rotor_three);
      break;

    case 3:
      outputPlugBoard(&plugBoard);
      changePlugBoard(&plugBoard);
      break;

    case 4:
      changeRotors(&rotor_one, &rotor_two, &rotor_three);
      break;

    case 5:
      outputRotors(&rotor_one, &rotor_two, &rotor_three);
      break;

    case 6:
      freeRotor(&rotor_one);
      freeRotor(&rotor_two);
      freeRotor(&rotor_three);
      return;

    default:
      printf("There was an error!\n");
      break;
    }
  }
}

int main() {
  enigma();
  return 0;
}


#include "globalFunctions.h"
#include "plugBoard.h"
#include "reflector.h"
#include "rotor.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Defines the Rotor Size && Width
#define ROTOR_SIZE 26
#define WIDTH 100

/**
 * @brief Runs the Enigma machine simulation.
 *
 * This function initializes the components of the Enigma machine
 * (plug board, rotors, and reflector) and provides a menu for the user
 * to interact with the machine. The user can encrypt or decrypt messages,
 * change the plug board settings, and change the rotor settings.
 */
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

  char *strang;
  while (1) {
    int result = menu();

    switch (result) {
    case 1:
      outputRotors(&rotor_one, &rotor_two, &rotor_three);

      strang = "What is your message that you want encrypted?: ";

      printf("%*s%s", format_string(strang), "", strang);
      if (!fgets(message, sizeof(message), stdin)) {
        break; // End of input
      }

      // Remove newline character if present
      size_t len = strlen(message);
      if (message[len - 1] == '\n') {
        message[len - 1] = '\0';
      }

      if (strcmp(message, "exit") == 0) {
        freeRotor(&rotor_one);
        freeRotor(&rotor_two);
        freeRotor(&rotor_three);
        freeReflector(&reflector);
        return;
      }

      encode(rotor_one.rotation_count, rotor_two.rotation_count,
             rotor_three.rotation_count, message);
      break;
    case 2:
      outputRotors(&rotor_one, &rotor_two, &rotor_three);

      strang = "What is your message that you want decrypted?: ";

      printf("%*s%s", format_string(strang), "", strang);
      if (!fgets(message, sizeof(message), stdin)) {
        break; // End of input
      }

      if (strcmp(message, "exit") == 0) {
        freeRotor(&rotor_one);
        freeRotor(&rotor_two);
        freeRotor(&rotor_three);
        freeReflector(&reflector);
        return;
      }

      decode(rotor_one.rotation_count, rotor_two.rotation_count,
             rotor_three.rotation_count, message);
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
      return;

    default:
      printf("There was an error!\n");
      break;
    }
  }
}

/**
 * @brief The main function of the program.
 *
 * This function calls the enigma function to start the Enigma machine
 * simulation.
 *
 * @return int Return status of the program (0 for success).
 */
int main() {
  enigma();
  return 0;
}


#include "plugBoard.h"
#include "reflector.h"
#include "rotor.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Defines the Rotor Size
#define ROTOR_SIZE 26
#define WIDTH 100

int format_string(char *message) {
  int str_len = strlen(message);
  int padding = (WIDTH - str_len) / 2;
  return padding;
}

int menu() {
  char *enigma_string = "-------------Enigma Machine-------------";
  int str_len = strlen(enigma_string);
  int padding = (WIDTH - str_len) / 2;

  printf("%*s%s%*s\n\n", padding, "", enigma_string, padding, "");

  char *type_message = "1. Encode Message";
  char *change_plugboard = "2. Change Plug Board";
  char *decode_message = "3. Decode Message";
  char *exit_message = "(Type 'exit' to quit)";

  printf("%*s%s\n%*s%s\n%*s%s\n%*s%s\n\n", format_string(type_message), "",
         type_message, format_string(change_plugboard) + 1, "",
         change_plugboard, format_string(decode_message), "", decode_message,
         format_string(exit_message) + 1, "", exit_message);

  char *choose_string = "Please choose a number from above: ";
  printf("%*s %s ", format_string(choose_string), "", choose_string);

  int number;
  scanf("%d", &number); // Read an integer input from the user
  getchar();

  return number; // Return the chosen number}
}

void decode(int rotor_one_number, int rotor_two_number, int rotor_three_number,
            char *message) {
  char decoded[256];
  struct PlugBoard plugBoard;
  initializePlugBoard(&plugBoard);

  struct Rotor rotor_one = {"Rotor One", NULL, NULL, rotor_one_number};
  initializeRotor(&rotor_one);
  struct Rotor rotor_two = {"Rotor Two", NULL, NULL, rotor_two_number};
  initializeRotor(&rotor_two);
  struct Rotor rotor_three = {"Rotor Three", NULL, NULL, rotor_three_number};
  initializeRotor(&rotor_three);

  struct Reflector reflector;
  initializeReflector(&reflector);

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

  // Convert entire message to uppercase
  for (size_t i = 0; i < len; i++) {
    message[i] = toupper(message[i]);
  }

  for (size_t i = 0; i < len; i++) {
    char originalChar = message[i];

    if (originalChar >= 'A' && originalChar <= 'Z') {
      char newChar = sendLetterThroughPlugBoard(&plugBoard, originalChar);
      newChar = sendLetterThroughRotor(&rotor_one, newChar, true);
      newChar = sendLetterThroughRotor(&rotor_two, newChar, true);
      newChar = sendLetterThroughRotor(&rotor_three, newChar, true);
      newChar = sendLetterThroughReflector(&reflector, newChar);
      newChar = sendLetterThroughRotor(&rotor_three, newChar, false);
      newChar = sendLetterThroughRotor(&rotor_two, newChar, false);
      newChar = sendLetterThroughRotor(&rotor_one, newChar, false);
      newChar = sendLetterThroughPlugBoard(&plugBoard, newChar);
      decoded[i] = newChar;

      // Rotate rotors
      rotateRotor(&rotor_one);
      if (rotor_one.rotation_count == 0) {
        rotateRotor(&rotor_two);
        if (rotor_two.rotation_count == 0) {
          rotateRotor(&rotor_three);
        }
      }
    } else {
      decoded[i] = originalChar; // Non-alphabetic characters are not encrypted
    }
  }
  decoded[len] = '\0';
  char *message_string = "Message";
  printf("\n%*s : %s\n", format_string(message_string), message_string,
         decoded);
}

void enigma() {
  struct PlugBoard plugBoard;
  initializePlugBoard(&plugBoard);
  // Print Plug Board
  // outputPlugBoard(&plugBoard);

  struct Rotor rotor_one = {"Rotor One", NULL, NULL, 0};
  initializeRotor(&rotor_one);

  struct Rotor rotor_two = {"Rotor Two", NULL, NULL, 0};
  initializeRotor(&rotor_two);

  struct Rotor rotor_three = {"Rotor Three", NULL, NULL, 0};
  initializeRotor(&rotor_three);

  struct Reflector reflector;
  initializeReflector(&reflector);

  char message[256];

  char decoded[256];

  char *setup = "-------------Current Rotor Setup-------------";
  char *r_one = "Rotations of Router One: ";
  char *r_two = "Rotations of Router Two: ";
  char *r_three = "Rotations of Router Three: ";

  char *strang;
  char *rotor_one_message;
  char *rotor_two_message;
  char *rotor_three_message;

  while (1) {

    int result = menu();

    switch (result) {
    case 1:
      printf("\n%*s%s\n\n%*s%s %d\n%*s%s %d\n %*s%s "
             "%d\n\n",
             format_string(setup), "", setup, format_string(r_one), "", r_one,
             rotor_one.rotation_count, format_string(r_two), "", r_two,
             rotor_two.rotation_count, format_string(r_three), "", r_three,
             rotor_three.rotation_count);

      printf("What is your message that you want encrypted or decrypted? (or "
             "type 'exit' to quit): ");
      if (!fgets(message, sizeof(message), stdin)) {
        break; // End of input
      }

      printf("Current Set up: \nRouter One: %d\nRouter Two: %d\nRouter Three: "
             "%d\n",
             rotor_one.rotation_count, rotor_two.rotation_count,
             rotor_three.rotation_count);
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

      // Convert entire message to uppercase
      for (size_t i = 0; i < len; i++) {
        message[i] = toupper(message[i]);
      }

      for (size_t i = 0; i < len; i++) {
        char originalChar = message[i];

        if (originalChar >= 'A' && originalChar <= 'Z') {
          char newChar = sendLetterThroughPlugBoard(&plugBoard, originalChar);
          newChar = sendLetterThroughRotor(&rotor_one, newChar, true);
          newChar = sendLetterThroughRotor(&rotor_two, newChar, true);
          newChar = sendLetterThroughRotor(&rotor_three, newChar, true);
          newChar = sendLetterThroughReflector(&reflector, newChar);
          newChar = sendLetterThroughRotor(&rotor_three, newChar, false);
          newChar = sendLetterThroughRotor(&rotor_two, newChar, false);
          newChar = sendLetterThroughRotor(&rotor_one, newChar, false);
          newChar = sendLetterThroughPlugBoard(&plugBoard, newChar);
          decoded[i] = newChar;

          // Rotate rotors
          rotateRotor(&rotor_one);
          if (rotor_one.rotation_count == 0) {
            rotateRotor(&rotor_two);
            if (rotor_two.rotation_count == 0) {
              rotateRotor(&rotor_three);
            }
          }
        } else {
          decoded[i] =
              originalChar; // Non-alphabetic characters are not encrypted
        }
      }
      decoded[len] = '\0';
      printf("\nMessage: %s\n", decoded);
      break;
    case 2:
      outputPlugBoard(&plugBoard);
      break;
    case 3:
      strang = "What is your message that you want decrypted?: ";

      printf("%*s%s", format_string(strang), "", strang);
      if (!fgets(message, sizeof(message), stdin)) {
        break; // End of input
      }

      rotor_one_message =
          " What is the Rotor setup you would like for Rotor One?(Please put "
          "an integer 0-25): ";
      printf("%*s%s", format_string(rotor_one_message), "", rotor_one_message);
      int router_one;
      scanf("%d", &router_one);

      rotor_two_message = " What is the Rotor setup you would like for Rotor "
                          "Two?(Please put an integer 0-25): ";
      printf("%*s%s", format_string(rotor_two_message), "", rotor_two_message);
      int router_two;
      scanf("%d", &router_two);

      rotor_three_message = " What is the Rotor setup you would like for Rotor "
                            "Three?(Please put an integer 0-25): ";
      printf("%*s%s", format_string(rotor_three_message), "",
             rotor_three_message);
      int router_three;
      scanf("%d", &router_three);
      if (strcmp(message, "exit") == 0) {
        freeRotor(&rotor_one);
        freeRotor(&rotor_two);
        freeRotor(&rotor_three);
        freeReflector(&reflector);
        return;
      }

      decode(router_one, router_two, router_three, message);
      break;

    default:
      printf("This is Default \n");
      break;
    }
    // freePlugBoard(&plugBoard);
  }
}
int main() {
  enigma();
  return 0;
}

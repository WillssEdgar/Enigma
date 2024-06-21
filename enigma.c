
#include "plugBoard.h"
#include "reflector.h"
#include "rotor.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Defines the Rotor Size
#define ROTOR_SIZE 26

int menu() {
  char *enigma_string = "-------------Enigma Machine-------------";
  int total_width = 100;
  int str_len = strlen(enigma_string);
  int padding = (total_width - str_len) / 2;

  printf("%*s%s%*s\n\n", padding, "", enigma_string, padding, "");

  char *type_message = "1. Encode/Decode Message";
  char *change_plugboard = "2. Change Plug Board";

  printf("%*s%s\n%*s%s\n\n", padding + 7, "", type_message, padding + 7, "",
         change_plugboard);

  printf("%*s Please choose a list from above: ", padding, "");

  int number;
  scanf("%d\n\n", &number); // Read an integer input from the user

  return number; // Return the chosen number}
}

void enigma() {
  struct PlugBoard plugBoard;
  initializePlugBoard(&plugBoard);
  outputPlugBoard(&plugBoard);

  struct Rotor rotor_one = {strdup("Rotor One")};
  initializeRotor(&rotor_one);

  struct Rotor rotor_two = {strdup("Rotor Two")};
  initializeRotor(&rotor_two);

  struct Rotor rotor_three = {strdup("Rotor Three")};
  initializeRotor(&rotor_three);

  struct Reflector reflector;
  initializeReflector(&reflector);

  char message[256];
  char decoded[256];

  while (1) {

    int result = menu();

    switch (result) {
    case 1:

      printf("What is your message that you want encrypted or decrypted? (or "
             "type 'exit' to quit): ");
      if (!fgets(message, sizeof(message), stdin)) {
        break; // End of input
      }

      // Remove newline character if present
      size_t len = strlen(message);
      if (message[len - 1] == '\n') {
        message[len - 1] = '\0';
      }

      if (strcmp(message, "exit") == 0) {
        break;
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
      printf("Message: %s\n", decoded);
    }
    // freePlugBoard(&plugBoard);
    freeRotor(&rotor_one);
    freeRotor(&rotor_two);
    freeRotor(&rotor_three);
    freeReflector(&reflector);
  }
  int main() {
    enigma();
    return 0;
  }

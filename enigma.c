
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

int menu() {
  char *enigma_string = "-------------Enigma Machine-------------";
  int str_len = strlen(enigma_string);
  int padding = (WIDTH - str_len) / 2;

  printf("\n%*s%s%*s\n\n", padding, "", enigma_string, padding, "");

  char *type_message = "1. Encode Message";
  char *decode_message = "2. Decode Message";
  char *change_plugboard = "3. Change Plug Board";
  char *change_rotor = "4. Change Rotor Settings";
  char *output_rotor = "5. View Current Rotor Settings";
  char *exit_message = "6. Quit Program";

  printf("%*s%s\n%*s%s\n%*s%s\n%*s%s\n%*s%s\n%*s%s\n\n",
         format_string(type_message), "", type_message,
         format_string(decode_message), "", decode_message,
         format_string(change_plugboard) + 1, "", change_plugboard,
         format_string(change_rotor) + 3, "", change_rotor,
         format_string(change_rotor) + 3, "", output_rotor,
         format_string(exit_message) - 1, "", exit_message);

  char *choose_string = "Please choose a number from above: ";
  printf("%*s %s ", format_string(choose_string), "", choose_string);

  int number;
  scanf("%d", &number); // Read an integer input from the user
  getchar();

  return number; // Return the chosen number}
}
void encode(int rotor_one_number, int rotor_two_number, int rotor_three_number,
            char *message) {
  char encoded[256];
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
      encoded[i] = newChar;

      // Rotate rotors
      rotateRotor(&rotor_one);
      if (rotor_one.rotation_count == 0) {
        rotateRotor(&rotor_two);
        if (rotor_two.rotation_count == 0) {
          rotateRotor(&rotor_three);
        }
      }

    } else {
      encoded[i] = originalChar; // Non-alphabetic characters are not encrypted
    }
  }
  encoded[len] = '\0';
  char *message_string = "Message";
  printf("\n%*s : %s\n", format_string(message_string), message_string,
         encoded);
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
int main() {
  enigma();
  return 0;
}

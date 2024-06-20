
#include "plugBoard.h"
#include "reflector.h"
#include "rotor.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Defines the Rotor Size
#define ROTOR_SIZE 26

void enigma() {
  printf("Enigma Machine \n");
  struct PlugBoard plugBoard;
  initializePlugBoard(&plugBoard);

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
          if (rotor
reeRotor(&rotor_two);

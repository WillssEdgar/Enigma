
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROTOR_SIZE 26

struct Rotor {
  char *name;
  char *side_one;
  char *side_two;
  int rotation_count;
};

struct PlugBoard {
  char *side_one;
  char *side_two;
};

struct Reflector {
  char *side_one;
  char *side_two;
};

void initializeRotor(struct Rotor *rotor) {
  rotor->side_one = (char *)malloc(ROTOR_SIZE + 1);
  rotor->side_two = (char *)malloc(ROTOR_SIZE + 1);

  if (rotor->side_one == NULL || rotor->side_two == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(rotor->name, "Rotor One") == 0) {
    strcpy(rotor->side_one, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcpy(rotor->side_two, "EKMFLGDQVZNTOWYHXUSPAIBRCJ");
  } else if (strcmp(rotor->name, "Rotor Two") == 0) {
    strcpy(rotor->side_one, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcpy(rotor->side_two, "HQZGPJTMOBLNCIFDYAWVEUSRKX");
  } else if (strcmp(rotor->name, "Rotor Three") == 0) {
    strcpy(rotor->side_one, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcpy(rotor->side_two, "UQNTLSZFMREHDPXKIBVYGJCWOA");
  }

  rotor->rotation_count = 0;
}

void initializeReflector(struct Reflector *reflector) {
  reflector->side_one = (char *)malloc(ROTOR_SIZE + 1);
  reflector->side_two = (char *)malloc(ROTOR_SIZE + 1);
  if (reflector->side_one == NULL || reflector->side_two == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  strcpy(reflector->side_one, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  strcpy(reflector->side_two, "YRUHQSLDPXNGOKMIEBFZCWVJAT");
}

void initializePlugBoard(struct PlugBoard *plugBoard) {
  plugBoard->side_one = (char *)malloc(ROTOR_SIZE + 1);
  plugBoard->side_two = (char *)malloc(ROTOR_SIZE + 1);
  if (plugBoard->side_one == NULL || plugBoard->side_two == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  strcpy(plugBoard->side_one, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  strcpy(plugBoard->side_two, "ZPHNMSWCIYTQEDOBLRFKUVGXJA");
}

char sendLetterThroughPlugBoard(struct PlugBoard *plugBoard, char letter) {
  for (int i = 0; i < ROTOR_SIZE; i++) {
    if (plugBoard->side_one[i] == letter) {
      return plugBoard->side_two[i];
    }
  }
  return letter;
}

char sendLetterThroughRotor(struct Rotor *rotor, char letter, bool forward) {
  if (forward) {
    for (int i = 0; i < ROTOR_SIZE; i++) {
      if (rotor->side_one[i] == letter) {
        return rotor->side_two[i];
      }
    }
  } else {
    for (int i = 0; i < ROTOR_SIZE; i++) {
      if (rotor->side_two[i] == letter) {
        return rotor->side_one[i];
      }
    }
  }
  return letter;
}

char sendLetterThroughReflector(struct Reflector *reflector, char letter) {
  for (int i = 0; i < ROTOR_SIZE; i++) {
    if (reflector->side_one[i] == letter) {
      return reflector->side_two[i];
    }
  }
  return letter;
}

void rotateRotor(struct Rotor *rotor) {
  char last_char_side_one = rotor->side_one[ROTOR_SIZE - 1];
  char last_char_side_two = rotor->side_two[ROTOR_SIZE - 1];
  for (int i = ROTOR_SIZE - 1; i > 0; i--) {
    rotor->side_one[i] = rotor->side_one[i - 1];
    rotor->side_two[i] = rotor->side_two[i - 1];
  }
  rotor->side_one[0] = last_char_side_one;
  rotor->side_two[0] = last_char_side_two;
  rotor->rotation_count = (rotor->rotation_count + 1) % ROTOR_SIZE;
}

void freeRotor(struct Rotor *rotor) {
  free(rotor->side_one);
  free(rotor->side_two);
  free(rotor->name);
}

void freePlugBoard(struct PlugBoard *plugBoard) {
  free(plugBoard->side_one);
  free(plugBoard->side_two);
}

void freeReflector(struct Reflector *reflector) {
  free(reflector->side_one);
  free(reflector->side_two);
}

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
    printf("What is your message that you want encrypted or decrypte? (or type "
           "'exit' to "
           "quit): ");
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

  // Free dynamically allocated memory
  freePlugBoard(&plugBoard);
  freeRotor(&rotor_one);
  freeRotor(&rotor_two);
  freeRotor(&rotor_three);
  freeReflector(&reflector);
}

int main() {
  enigma();
  return 0;
}

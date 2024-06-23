
#include "rotor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Predefined rotor wirings
static const char *ROTOR_ONE_WIRING = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
static const char *ROTOR_TWO_WIRING = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
static const char *ROTOR_THREE_WIRING = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
static const char *ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void initializeRotor(struct Rotor *rotor) {
  rotor->side_one = (char *)malloc(ROTOR_SIZE + 1);
  rotor->side_two = (char *)malloc(ROTOR_SIZE + 1);

  if (rotor->side_one == NULL || rotor->side_two == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  strcpy(rotor->side_one, ALPHABET);

  if (strcmp(rotor->name, "Rotor One") == 0) {
    strcpy(rotor->side_two, ROTOR_ONE_WIRING);
  } else if (strcmp(rotor->name, "Rotor Two") == 0) {
    strcpy(rotor->side_two, ROTOR_TWO_WIRING);
  } else if (strcmp(rotor->name, "Rotor Three") == 0) {
    strcpy(rotor->side_two, ROTOR_THREE_WIRING);
  }

  rotor->rotation_count = 0;
}

char sendLetterThroughRotor(struct Rotor *rotor, char letter, bool forward) {
  int index = (letter - 'A' + rotor->rotation_count) % ROTOR_SIZE;
  char encoded_letter;

  if (forward) {
    encoded_letter = rotor->side_two[index];
  } else {
    // Reverse the rotor side_two to find the corresponding letter on side_one
    for (int i = 0; i < ROTOR_SIZE; i++) {
      if (rotor->side_two[i] == letter) {
        encoded_letter =
            rotor->side_one[(i - rotor->rotation_count + ROTOR_SIZE) %
                            ROTOR_SIZE];
        break;
      }
    }
  }

  return encoded_letter;
}

void rotateRotor(struct Rotor *rotor) {
  rotor->rotation_count = (rotor->rotation_count + 1) % ROTOR_SIZE;
}

void freeRotor(struct Rotor *rotor) {
  free(rotor->side_one);
  free(rotor->side_two);
}

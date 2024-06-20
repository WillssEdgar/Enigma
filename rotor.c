
#include "rotor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    strcpy(rotor->side_two, "AJDKSIRUXBLHWTMCQGZNPYFVOE");
  } else if (strcmp(rotor->name, "Rotor Three") == 0) {
    strcpy(rotor->side_one, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    strcpy(rotor->side_two, "BDFHJLCPRTXVZNYEIWGAKMUSQO");
  }

  rotor->rotation_count = 0;
}

char sendLetterThroughRotor(struct Rotor *rotor, char letter, bool forward) {
  char *input = forward ? rotor->side_one : rotor->side_two;
  char *output = forward ? rotor->side_two : rotor->side_one;

  for (int i = 0; i < ROTOR_SIZE; i++) {
    if (input[i] == letter) {
      return output[i];
    }
  }
  return letter;
}

void rotateRotor(struct Rotor *rotor) {
  rotor->rotation_count = (rotor->rotation_count + 1) % ROTOR_SIZE;

  char last_char = rotor->side_one[ROTOR_SIZE - 1];
  for (int i = ROTOR_SIZE - 1; i > 0; i--) {
    rotor->side_one[i] = rotor->side_one[i - 1];
  }
  rotor->side_one[0] = last_char;

  last_char = rotor->side_two[ROTOR_SIZE - 1];
  for (int i = ROTOR_SIZE - 1; i > 0; i--) {
    rotor->side_two[i] = rotor->side_two[i - 1];
  }
  rotor->side_two[0] = last_char;
}

void freeRotor(struct Rotor *rotor) {
  free(rotor->side_one);
  free(rotor->side_two);
}

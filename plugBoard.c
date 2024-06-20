// Rotor Structure
#include "plugBoard.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void freePlugBoard(struct PlugBoard *plugBoard) {
  free(plugBoard->side_one);
  free(plugBoard->side_two);
}

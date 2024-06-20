#include "reflector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sendLetterThroughReflector(struct Reflector *reflector, char letter) {
  for (int i = 0; i < ROTOR_SIZE; i++) {
    if (reflector->side_one[i] == letter) {
      return reflector->side_two[i];
    }
  }
  return letter;
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

void freeReflector(struct Reflector *reflector) {
  free(reflector->side_one);
  free(reflector->side_two);
}

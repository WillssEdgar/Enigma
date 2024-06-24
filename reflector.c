#include "reflector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * sendLetterThroughReflector - Simulates sending a letter through the
 * reflector.
 *
 * @reflector: Pointer to the Reflector structure that holds the reflector
 * mappings.
 * @letter: The letter to be sent through the reflector.
 *
 * This function returns the letter that the input letter is mapped to on the
 * other side of the reflector. It iterates through `side_one` to find the input
 * letter and returns the corresponding letter from `side_two`. If the input
 * letter is not found, it returns the input letter itself.
 *
 * Return: The letter mapped to the input letter by the reflector.
 */
char sendLetterThroughReflector(struct Reflector *reflector, char letter) {
  for (int i = 0; i < ROTOR_SIZE; i++) {
    if (reflector->side_one[i] == letter) {
      return reflector->side_two[i];
    }
  }
  return letter;
}

/**
 * initializeReflector - Initializes the reflector with predefined mappings.
 *
 * @reflector: Pointer to the Reflector structure that will be initialized.
 *
 * This function allocates memory for `side_one` and `side_two` of the
 * reflector, and sets up the initial state of the reflector with predefined
 * mappings. If memory allocation fails, it prints an error message and exits
 * the program.
 */
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

/**
 * freeReflector - Frees the memory allocated for the reflector.
 *
 * @reflector: Pointer to the Reflector structure whose memory needs to be
 * freed.
 *
 * This function frees the memory allocated for `side_one` and `side_two` of the
 * reflector.
 */
void freeReflector(struct Reflector *reflector) {
  free(reflector->side_one);
  free(reflector->side_two);
}

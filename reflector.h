#ifndef REFLECTOR_H // Include guard to prevent multiple inclusions
#define REFLECTOR_H

#define ROTOR_SIZE 26
// Reflector Structure
struct Reflector {
  char *side_one;
  char *side_two;
};

// Function prototypes related to the struct
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
char sendLetterThroughReflector(struct Reflector *reflector, char letter);

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
void initializeReflector(struct Reflector *reflector);

/**
 * freeReflector - Frees the memory allocated for the reflector.
 *
 * @reflector: Pointer to the Reflector structure whose memory needs to be
 * freed.
 *
 * This function frees the memory allocated for `side_one` and `side_two` of the
 * reflector.
 */
void freeReflector(struct Reflector *reflector);
#endif // REFLECTOR_H

#include "reflector.h"

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
  return reflector->wiring[letter - 'A'];
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
  for (int i = 0; i < 26; i++) {
    reflector->wiring[i] = 'A' + i; // Initialize with 'A' to 'Z'
  }
  reflector->wiring['Y' - 'A'] = 'A';
  reflector->wiring['A' - 'A'] = 'Y';

  reflector->wiring['B' - 'A'] = 'R';
  reflector->wiring['R' - 'A'] = 'B';

  reflector->wiring['C' - 'A'] = 'U';
  reflector->wiring['U' - 'A'] = 'C';

  reflector->wiring['D' - 'A'] = 'H';
  reflector->wiring['H' - 'A'] = 'D';

  reflector->wiring['E' - 'A'] = 'Q';
  reflector->wiring['Q' - 'A'] = 'E';

  reflector->wiring['G' - 'A'] = 'L';
  reflector->wiring['L' - 'A'] = 'G';

  reflector->wiring['W' - 'A'] = 'V';
  reflector->wiring['V' - 'A'] = 'W';

  reflector->wiring['I' - 'A'] = 'P';
  reflector->wiring['P' - 'A'] = 'I';

  reflector->wiring['J' - 'A'] = 'X';
  reflector->wiring['X' - 'A'] = 'J';

  reflector->wiring['K' - 'A'] = 'N';
  reflector->wiring['N' - 'A'] = 'K';

  reflector->wiring['T' - 'A'] = 'Z';
  reflector->wiring['Z' - 'A'] = 'T';

  reflector->wiring['M' - 'A'] = 'O';
  reflector->wiring['O' - 'A'] = 'M';

  reflector->wiring['F' - 'A'] = 'S';
  reflector->wiring['S' - 'A'] = 'F';
}

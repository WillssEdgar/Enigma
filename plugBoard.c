// Rotor Structure
#include "plugBoard.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializePlugBoard(struct PlugBoard *plugBoard) {
  // plugBoard->side_one = (char *)malloc(ROTOR_SIZE + 1);
  // plugBoard->side_two = (char *)malloc(ROTOR_SIZE + 1);
  // if (plugBoard->side_one == NULL || plugBoard->side_two == NULL) {
  //   fprintf(stderr, "Memory allocation failed\n");
  //   exit(EXIT_FAILURE);
  // }
  // strcpy(plugBoard->side_one, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  // strcpy(plugBoard->side_two, "ZPHNMSWCIYTQEDOBLRFKUVGXJA");
  // Start with a direct mapping (no plugs)
  for (int i = 0; i < 26; i++) {
    plugBoard->wiring[i] = 'A' + i; // Initialize with 'A' to 'Z'
  }
  plugBoard->wiring['A' - 'A'] = 'D'; // Map 'A' to 'D'
  plugBoard->wiring['D' - 'A'] = 'A'; // Map 'D' to 'A'
  plugBoard->wiring['B' - 'A'] = 'F'; // Map 'B' to 'F'
  plugBoard->wiring['F' - 'A'] = 'B'; // Map 'F' to 'B'
  plugBoard->wiring['C' - 'A'] = 'G'; // Map 'C' to 'G'
  plugBoard->wiring['G' - 'A'] = 'C'; // Map 'G' to 'C'
  plugBoard->wiring['E' - 'A'] = 'J'; // Map 'E' to 'J'
  plugBoard->wiring['J' - 'A'] = 'E'; // Map 'J' to 'E'
  plugBoard->wiring['H' - 'A'] = 'K'; // Map 'H' to 'K'
  plugBoard->wiring['K' - 'A'] = 'H'; // Map 'K' to 'H'
  plugBoard->wiring['I' - 'A'] = 'M'; // Map 'I' to 'M'
  plugBoard->wiring['M' - 'A'] = 'I'; // Map 'M' to 'I'
  plugBoard->wiring['L' - 'A'] = 'N'; // Map 'L' to 'N'
  plugBoard->wiring['N' - 'A'] = 'L'; // Map 'N' to 'L'
  plugBoard->wiring['O' - 'A'] = 'P'; // Map 'O' to 'P'
  plugBoard->wiring['P' - 'A'] = 'O'; // Map 'P' to 'O'
  plugBoard->wiring['Q' - 'A'] = 'S'; // Map 'Q' to 'S'
  plugBoard->wiring['S' - 'A'] = 'Q'; // Map 'S' to 'Q'
  plugBoard->wiring['R' - 'A'] = 'T'; // Map 'R' to 'T'
  plugBoard->wiring['T' - 'A'] = 'R'; // Map 'T' to 'R'
  plugBoard->wiring['U' - 'A'] = 'V'; // Map 'U' to 'V'
  plugBoard->wiring['V' - 'A'] = 'U'; // Map 'V' to 'U'
  plugBoard->wiring['W' - 'A'] = 'X'; // Map 'W' to 'X'
  plugBoard->wiring['X' - 'A'] = 'W'; // Map 'X' to 'W'
  plugBoard->wiring['Y' - 'A'] = 'Z'; // Map 'Y' to 'Z'
  plugBoard->wiring['Z' - 'A'] = 'Y'; // Map 'Z' to 'Y'
}

char sendLetterThroughPlugBoard(struct PlugBoard *plugBoard, char letter) {
  return plugBoard->wiring[letter - 'A'];
}

void outputPlugBoard(struct PlugBoard *plugBoard) {
  char *plugboard_string = "------------Current Plug Board-------------";
  int total_width = 100;
  int str_len = strlen(plugboard_string);
  int padding = (total_width - str_len) / 2;

  printf("%*s%s%*s\n\n", padding, "", plugboard_string, padding, "");
  for (int i = 0; i < 26; i++) {
    char currentLetter = 'A' + i;
    char toLetter = currentLetter - 'A';
    if (i % 2 == 0) {
      printf("%37c -> %c", currentLetter, plugBoard->wiring[toLetter]);
    } else {
      printf("%15c -> %c\n", currentLetter, plugBoard->wiring[toLetter]);
    }
  }
}

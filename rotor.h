#ifndef ROTOR_H // Include guard to prevent multiple inclusions
#define ROTOR_H

#include <stdbool.h>
#define ROTOR_SIZE 26

// Rotor Structure
struct Rotor {
  char *name;
  char *side_one;
  char *side_two;
  int rotation_count;
};

// Function prototypes related to the struct
void initializeRotor(struct Rotor *rotor);
char sendLetterThroughRotor(struct Rotor *rotor, char letter, bool forward);
void rotateRotor(struct Rotor *rotor);
int format_string(char *message);
void outputRotors(struct Rotor *rotor_one, struct Rotor *rotor_two,
                  struct Rotor *rotor_three);
void changeRotors(struct Rotor *rotor_one, struct Rotor *rotor_two,
                  struct Rotor *rotor_three);

void freeRotor(struct Rotor *rotor);

#endif // ROTOR_H

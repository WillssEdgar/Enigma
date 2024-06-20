#ifndef STRUCTS_H // Include guard to prevent multiple inclusions
#define STRUCTS_H

#define ROTOR_SIZE 26
// Reflector Structure
struct Reflector {
  char *side_one;
  char *side_two;
};

// Function prototypes related to the struct
char sendLetterThroughReflector(struct Reflector *reflector, char letter);
void initializeReflector(struct Reflector *reflector);
void freeReflector(struct Reflector *reflector);
#endif // STRUCTS_H
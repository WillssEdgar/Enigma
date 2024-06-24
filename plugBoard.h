
#ifndef STRUCTS_H // Include guard to prevent multiple inclusions
#define STRUCTS_H
#define ROTOR_SIZE 26

struct PlugBoard {
  char wiring[26];
};

// Function prototypes related to the struct
void initializePlugBoard(struct PlugBoard *plugBoard);
char sendLetterThroughPlugBoard(struct PlugBoard *plugBoard, char letter);
void changePlugBoard(struct PlugBoard *plugBoard);
void outputPlugBoard(struct PlugBoard *plugBoard);
#endif // STRUCTS_H

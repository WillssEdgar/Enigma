
#ifndef STRUCTS_H // Include guard to prevent multiple inclusions
#define STRUCTS_H
#define ROTOR_SIZE 26
// PlugBoard Structure
// struct PlugBoard {
//   char *side_one;
//   char *side_two;
// };
struct PlugBoard {
  char wiring[26];
};

// Function prototypes related to the struct
void initializePlugBoard(struct PlugBoard *plugBoard);
char sendLetterThroughPlugBoard(struct PlugBoard *plugBoard, char letter);
// void freePlugBoard(struct PlugBoard *plugBoard);
void outputPlugBoard(struct PlugBoard *plugBoard);
#endif // STRUCTS_H


#ifndef STRUCTS_H // Include guard to prevent multiple inclusions
#define STRUCTS_H
#define ROTOR_SIZE 26

struct PlugBoard {
  char wiring[26];
};

// Function prototypes related to the struct
/**
 * initializePlugBoard - Initializes the plugboard with a predefined set of
 * wiring mappings.
 *
 * @plugBoard: Pointer to the PlugBoard structure that will be initialized.
 *
 * This function sets up the initial state of the plugboard by mapping each
 * letter to itself, and then applying specific swaps to create the predefined
 * wiring.
 */
void initializePlugBoard(struct PlugBoard *plugBoard);

/**
 * sendLetterThroughPlugBoard - Simulates sending a letter through the
 * plugboard.
 *
 * @plugBoard: Pointer to the PlugBoard structure that holds the current
 * plugboard wiring.
 * @letter: The letter to be sent through the plugboard.
 *
 * This function returns the letter that the input letter is mapped to in the
 * plugboard wiring.
 *
 * Return: The letter mapped to the input letter.
 */
char sendLetterThroughPlugBoard(struct PlugBoard *plugBoard, char letter);

/**
 * changePlugBoard - Allows the user to change the plugboard wiring by swapping
 * pairs of letters.
 *
 * @plugBoard: Pointer to the PlugBoard structure that holds the current
 * plugboard wiring.
 *
 * This function prompts the user to input two letters, then swaps their
 * mappings in the plugboard wiring. The new mappings are printed to the
 * console.
 */
void changePlugBoard(struct PlugBoard *plugBoard);

/**
 * outputPlugBoard - Prints the current state of the plugboard mappings.
 *
 * @plugBoard: Pointer to the PlugBoard structure that holds the current
 * plugboard wiring.
 *
 * This function prints the current plugboard mappings to the console in a
 * formatted manner, showing which letters are mapped to each other.
 */
void outputPlugBoard(struct PlugBoard *plugBoard);
#endif // STRUCTS_H

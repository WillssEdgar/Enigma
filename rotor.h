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
/**
 * initializeRotor - Initializes a rotor with predefined wiring.
 *
 * @rotor: A pointer to the Rotor structure to be initialized.
 *
 * This function allocates memory for the rotor's side_one and side_two arrays.
 * It then initializes side_one with the alphabet and side_two with the
 * predefined wiring based on the rotor's name. It also sets the rotor's
 * rotation count to 0.
 */
void initializeRotor(struct Rotor *rotor);

/**
 * sendLetterThroughRotor - Sends a letter through the rotor for
 * encoding/decoding.
 *
 * @rotor: A pointer to the Rotor structure.
 * @letter: The letter to be sent through the rotor.
 * @forward: A boolean indicating the direction of encoding (true for forward,
 * false for reverse).
 *
 * This function encodes or decodes a letter by passing it through the rotor. It
 * handles the letter's index transformation based on the rotor's rotation count
 * and the specified direction (forward or reverse).
 *
 * Return: The encoded or decoded letter.
 */
char sendLetterThroughRotor(struct Rotor *rotor, char letter, bool forward);

/**
 * rotateRotor - Rotates the rotor by one position.
 *
 * @rotor: A pointer to the Rotor structure.
 *
 * This function increments the rotor's rotation count, effectively rotating the
 * rotor by one position. The rotation count wraps around if it exceeds the
 * rotor size.
 */
void rotateRotor(struct Rotor *rotor);

/**
 * format_string - Calculates the padding needed to center a string within a
 * specified width.
 *
 * @message: The message to be centered.
 *
 * This function calculates the padding required to center the given message
 * within a predefined width. It returns the amount of padding needed.
 *
 * Return: The padding value as an integer.
 */
int format_string(char *message);

/**
 * outputRotors - Displays the current setup of the rotors.
 *
 * @rotor_one: A pointer to the first Rotor structure.
 * @rotor_two: A pointer to the second Rotor structure.
 * @rotor_three: A pointer to the third Rotor structure.
 *
 * This function prints the current setup of the three rotors, including their
 * names and rotation counts, in a formatted manner.
 */
void outputRotors(struct Rotor *rotor_one, struct Rotor *rotor_two,
                  struct Rotor *rotor_three);

/**
 * changeRotors - Changes the setup of the rotors based on user input.
 *
 * @rotor_one: A pointer to the first Rotor structure.
 * @rotor_two: A pointer to the second Rotor structure.
 * @rotor_three: A pointer to the third Rotor structure.
 *
 * This function prompts the user to enter new rotation counts for each of the
 * three rotors. It updates the rotation counts of the provided Rotor structures
 * based on the user input.
 */
void changeRotors(struct Rotor *rotor_one, struct Rotor *rotor_two,
                  struct Rotor *rotor_three);

/**
 * freeRotor - Frees the memory allocated for a rotor.
 *
 * @rotor: A pointer to the Rotor structure to be freed.
 *
 * This function frees the memory allocated for the rotor's side_one and
 * side_two arrays.
 */
void freeRotor(struct Rotor *rotor);

#endif // ROTOR_H

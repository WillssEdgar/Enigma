#ifndef GLOBALFUNCTIONS_H // Include guard to prevent multiple inclusions
#define GLOBALFUNCTIONS_H

#include <stdbool.h>

// Function prototypes related to the struct
/**
 * menu - Displays the main menu and prompts the user for a choice.
 *
 * This function prints the main menu for the Enigma machine simulator,
 * including options to encode a message, decode a message, change the plug
 * board, change the rotor settings, view current rotor settings, and quit the
 * program. It then prompts the user to choose an option by entering a number.
 *
 * Return: The chosen menu option as an integer.
 */
int menu();

#endif // ROTOR_H

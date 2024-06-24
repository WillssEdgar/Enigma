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

/**
 * encode - Encodes a given message using the Enigma machine settings.
 *
 * @rotor_one_number: The initial position of the first rotor.
 * @rotor_two_number: The initial position of the second rotor.
 * @rotor_three_number: The initial position of the third rotor.
 * @message: The message to be encoded.
 *
 * This function initializes the plug board, rotors, and reflector of the Enigma
 * machine. It then encodes the provided message by passing each character
 * through the plug board, rotors, and reflector, and then back through the
 * rotors and plug board. The encoded message is printed to the console.
 */
void encode(int rotor_one_number, int rotor_two_number, int rotor_three_number,
            char *message);

/**
 * decode - Decodes a given message using the Enigma machine settings.
 *
 * @rotor_one_number: The initial position of the first rotor.
 * @rotor_two_number: The initial position of the second rotor.
 * @rotor_three_number: The initial position of the third rotor.
 * @message: The message to be decoded.
 *
 * This function initializes the plug board, rotors, and reflector of the Enigma
 * machine. It then decodes the provided message by passing each character
 * through the plug board, rotors, and reflector, and then back through the
 * rotors and plug board. The decoded message is printed to the console.
 */
void decode(int rotor_one_number, int rotor_two_number, int rotor_three_number,
            char *message);

#endif // ROTOR_H

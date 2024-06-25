
#include "rotor.h"
#include <stdio.h>
#include <string.h>

#define WIDTH 100
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
int menu() {
  char *enigma_string = "-------------Enigma Machine-------------";
  int str_len = strlen(enigma_string);
  int padding = (WIDTH - str_len) / 2;

  printf("\n%*s%s%*s\n\n", padding, "", enigma_string, padding, "");

  char *type_message = "1. Encode Message";
  char *decode_message = "2. Decode Message";
  char *change_plugboard = "3. Change Plug Board";
  char *change_rotor = "4. Change Rotor Settings";
  char *output_rotor = "5. View Current Rotor Settings";
  char *exit_message = "6. Quit Program";

  printf("%*s%s\n%*s%s\n%*s%s\n%*s%s\n%*s%s\n%*s%s\n\n",
         format_string(type_message), "", type_message,
         format_string(decode_message), "", decode_message,
         format_string(change_plugboard) + 1, "", change_plugboard,
         format_string(change_rotor) + 3, "", change_rotor,
         format_string(change_rotor) + 3, "", output_rotor,
         format_string(exit_message) - 1, "", exit_message);

  char *choose_string = "Please choose a number from above: ";
  printf("%*s %s ", format_string(choose_string), "", choose_string);

  int number;
  scanf("%d", &number); // Read an integer input from the user
  getchar();

  return number; // Return the chosen number}
}

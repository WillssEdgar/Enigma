#include "rotor.h"
#include "plugBoard.h"
#include "reflector.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Predefined rotor wirings
static const char *ROTOR_ONE_WIRING = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
static const char *ROTOR_TWO_WIRING = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
static const char *ROTOR_THREE_WIRING = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
static const char *ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define WIDTH 100

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
int format_string(char *message) {
  int str_len = strlen(message);
  int padding = (WIDTH - str_len) / 2;
  return padding;
}

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
void initializeRotor(struct Rotor *rotor) {
  rotor->side_one = (char *)malloc(ROTOR_SIZE + 1);
  rotor->side_two = (char *)malloc(ROTOR_SIZE + 1);

  if (rotor->side_one == NULL || rotor->side_two == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  strcpy(rotor->side_one, ALPHABET);

  if (strcmp(rotor->name, "Rotor One") == 0) {
    strcpy(rotor->side_two, ROTOR_ONE_WIRING);
  } else if (strcmp(rotor->name, "Rotor Two") == 0) {
    strcpy(rotor->side_two, ROTOR_TWO_WIRING);
  } else if (strcmp(rotor->name, "Rotor Three") == 0) {
    strcpy(rotor->side_two, ROTOR_THREE_WIRING);
  } else {
    fprintf(stderr, "Unknown rotor name: %s\n", rotor->name);
    exit(EXIT_FAILURE);
  }

  rotor->rotation_count = 0;
}

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
char sendLetterThroughRotor(struct Rotor *rotor, char letter, bool forward) {
  int index = (letter - 'A' + rotor->rotation_count) % ROTOR_SIZE;
  if (index < 0)
    index += ROTOR_SIZE; // Ensure positive index
  char encoded_letter;

  if (forward) {
    encoded_letter = rotor->side_two[index];
  } else {
    for (int i = 0; i < ROTOR_SIZE; i++) {
      if (rotor->side_two[i] == letter) {
        encoded_letter =
            rotor->side_one[(i - rotor->rotation_count + ROTOR_SIZE) %
                            ROTOR_SIZE];
        break;
      }
    }
    // encoded_letter = rotor->side_one[index];
  }

  return encoded_letter;
}

/**
 * rotateRotor - Rotates the rotor by one position.
 *
 * @rotor: A pointer to the Rotor structure.
 *
 * This function increments the rotor's rotation count, effectively rotating the
 * rotor by one position. The rotation count wraps around if it exceeds the
 * rotor size.
 */
void rotateRotor(struct Rotor *rotor) {
  rotor->rotation_count = (rotor->rotation_count + 1) % ROTOR_SIZE;

  char temp_two[27]; // Ensure enough space for null terminator

  // Copy elements, starting from the second last to the first
  for (int i = 24; i >= 0; i--) {

    temp_two[i + 1] = rotor->side_two[i];
  }

  // Add the last element of rotor->side_two as the first element of temp_two
  temp_two[0] = rotor->side_two[25];

  // Null-terminate the temp_two array
  temp_two[26] = '\0';

  strcpy(rotor->side_two, temp_two);
}

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
                  struct Rotor *rotor_three) {

  char *setup = "-------------Current Rotor Setup-------------";
  printf("\n%*s%s\n\n", format_string(setup), "", setup);
  printf("%*s%s: %d\n%*s%s: %d\n%*s%s: %d\n", format_string(rotor_one->name),
         "", rotor_one->name, rotor_one->rotation_count,
         format_string(rotor_two->name), "", rotor_two->name,
         rotor_two->rotation_count, format_string(rotor_three->name), "",
         rotor_three->name, rotor_three->rotation_count

  );
}

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
                  struct Rotor *rotor_three) {

  char *rotor_one_message =
      " What is the Rotor setup you would like for Rotor One?(Please put "
      "an integer 0-25): ";
  printf("\n%*s%s", format_string(rotor_one_message), "", rotor_one_message);
  int rotor_one_count;
  scanf("%d", &rotor_one_count);

  char *rotor_two_message = " What is the Rotor setup you would like for Rotor "
                            "Two?(Please put an integer 0-25): ";
  printf("\n%*s%s", format_string(rotor_two_message), "", rotor_two_message);
  int rotor_two_count;
  scanf("%d", &rotor_two_count);

  char *rotor_three_message =
      " What is the Rotor setup you would like for Rotor "
      "Three?(Please put an integer 0-25): ";
  printf("\n%*s%s", format_string(rotor_three_message), "",
         rotor_three_message);
  int rotor_three_count;
  scanf("%d", &rotor_three_count);

  rotor_one->rotation_count = rotor_one_count;
  rotor_two->rotation_count = rotor_two_count;
  rotor_three->rotation_count = rotor_three_count;
}

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

void encode(struct Rotor *rotor_one, struct Rotor *rotor_two,
            struct Rotor *rotor_three, char *message) {
  char encoded[256];
  struct PlugBoard plugBoard;
  initializePlugBoard(&plugBoard);

  struct Reflector reflector;
  initializeReflector(&reflector);

  size_t len = strlen(message);
  if (message[len - 1] == '\n') {
    message[len - 1] = '\0';
    len--;
  }

  // Convert entire message to uppercase
  for (size_t i = 0; i < len; i++) {
    message[i] = toupper(message[i]);
  }

  for (size_t i = 0; i < len; i++) {
    char originalChar = message[i];

    if (originalChar >= 'A' && originalChar <= 'Z') {
      char newChar = sendLetterThroughPlugBoard(&plugBoard, originalChar);
      printf("plugboard encode forward: %c\n", newChar);
      newChar = sendLetterThroughRotor(rotor_one, newChar, true);
      printf("rotor one encode forward: %c\n", newChar);
      newChar = sendLetterThroughRotor(rotor_two, newChar, true);
      printf("rotor two encode forward: %c\n", newChar);
      newChar = sendLetterThroughRotor(rotor_three, newChar, true);
      printf("rotor three encode forward: %c\n", newChar);
      newChar = sendLetterThroughReflector(&reflector, newChar);
      printf("reflector encode forward: %c\n", newChar);
      newChar = sendLetterThroughRotor(rotor_three, newChar, false);
      printf("rotor three encode back: %c\n", newChar);
      newChar = sendLetterThroughRotor(rotor_two, newChar, false);
      printf("rotor two encode back: %c\n", newChar);
      newChar = sendLetterThroughRotor(rotor_one, newChar, false);
      printf("rotor one encode back: %c\n", newChar);
      newChar = sendLetterThroughPlugBoard(&plugBoard, newChar);
      printf("plugboard encode forward: %c\n", newChar);
      encoded[i] = newChar;

      // Rotate rotors
      printf("Before Rotate: \n Side One: %s\n Side Two: %s\n",
             rotor_one->side_one, rotor_one->side_two);
      rotateRotor(rotor_one);
      printf("After Rotate: \n Side One: %s\n Side Two: %s\n",
             rotor_one->side_one, rotor_one->side_two);
      if (rotor_one->rotation_count == 0) {
        rotateRotor(rotor_two);
        if (rotor_two->rotation_count == 0) {
          rotateRotor(rotor_three);
        }
      }
    } else {
      encoded[i] = originalChar; // Non-alphabetic characters are not encrypted
    }
  }

  encoded[len] = '\0';
  printf("\nMessage: %s\n", encoded);
}

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
void decode(struct Rotor *rotor_one, struct Rotor *rotor_two,
            struct Rotor *rotor_three, char *message) {
  char decoded[256];
  struct PlugBoard plugBoard;
  initializePlugBoard(&plugBoard);

  struct Reflector reflector;
  initializeReflector(&reflector);

  size_t len = strlen(message);
  if (message[len - 1] == '\n') {
    message[len - 1] = '\0';
  }

  // Convert entire message to uppercase
  for (size_t i = 0; i < len; i++) {
    message[i] = toupper(message[i]);
  }

  // Initialize rotors (ensure they are properly set up)
  initializeRotor(rotor_one);
  initializeRotor(rotor_two);
  initializeRotor(rotor_three);

  for (size_t i = 0; i < len; i++) {
    char originalChar = message[i];

    if (originalChar >= 'A' && originalChar <= 'Z') {
      char newChar = sendLetterThroughPlugBoard(&plugBoard, originalChar);
      newChar = sendLetterThroughRotor(rotor_one, newChar, true);
      newChar = sendLetterThroughRotor(rotor_two, newChar, true);
      newChar = sendLetterThroughRotor(rotor_three, newChar, true);
      newChar = sendLetterThroughReflector(&reflector, newChar);
      newChar = sendLetterThroughRotor(rotor_three, newChar, false);
      newChar = sendLetterThroughRotor(rotor_two, newChar, false);
      newChar = sendLetterThroughRotor(rotor_one, newChar, false);
      newChar = sendLetterThroughPlugBoard(&plugBoard, newChar);
      decoded[i] = newChar;

      // Rotate rotors
      rotateRotor(rotor_one);
      if (rotor_one->rotation_count == 0) {
        rotateRotor(rotor_two);
        if (rotor_two->rotation_count == 0) {
          rotateRotor(rotor_three);
        }
      }
    } else {
      decoded[i] = originalChar; // Non-alphabetic characters are not encrypted
    }
  }

  decoded[len] = '\0';
  printf("\nDecoded Message: %s\n", decoded);
}

/**
 * freeRotor - Frees the memory allocated for a rotor.
 *
 * @rotor: A pointer to the Rotor structure to be freed.
 *
 * This function frees the memory allocated for the rotor's side_one and
 * side_two arrays.
 */
void freeRotor(struct Rotor *rotor) {
  free(rotor->side_one);
  free(rotor->side_two);
}

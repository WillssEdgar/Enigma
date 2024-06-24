
#include "rotor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Predefined rotor wirings
static const char *ROTOR_ONE_WIRING = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
static const char *ROTOR_TWO_WIRING = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
static const char *ROTOR_THREE_WIRING = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
static const char *ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define WIDTH 100

int format_string(char *message) {
  int str_len = strlen(message);
  int padding = (WIDTH - str_len) / 2;
  return padding;
}

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
  }

  rotor->rotation_count = 0;
}

char sendLetterThroughRotor(struct Rotor *rotor, char letter, bool forward) {
  int index = (letter - 'A' + rotor->rotation_count) % ROTOR_SIZE;
  char encoded_letter;

  if (forward) {
    encoded_letter = rotor->side_two[index];
  } else {
    // Reverse the rotor side_two to find the corresponding letter on side_one
    for (int i = 0; i < ROTOR_SIZE; i++) {
      if (rotor->side_two[i] == letter) {
        encoded_letter =
            rotor->side_one[(i - rotor->rotation_count + ROTOR_SIZE) %
                            ROTOR_SIZE];
        break;
      }
    }
  }

  return encoded_letter;
}

void rotateRotor(struct Rotor *rotor) {
  rotor->rotation_count = (rotor->rotation_count + 1) % ROTOR_SIZE;
}

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

void freeRotor(struct Rotor *rotor) {
  free(rotor->side_one);
  free(rotor->side_two);
}

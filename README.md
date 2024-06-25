# Enigma Machine Simulation in C

## Overview

This project is a simulation of the famous Enigma machine used during World War II for secure communication. The Enigma machine was a cipher device that employed rotors, a plugboard, and a reflector to encrypt and decrypt messages. This simulation aims to recreate its functionality through a command-line interface (CLI) in C programming language.

## Features

- **Plugboard Configuration**: Allows users to configure initial substitutions for letters before entering the rotors.
- **Rotor Simulation**: Supports multiple rotors with customizable settings (e.g., rotor type, starting positions).
- **Reflector Configuration**: Simulates the reflector mechanism for ensuring reciprocal substitutions.
- **Encryption and Decryption**: Enables users to encrypt and decrypt messages using configured settings.
- **Interactive Menu**: Provides a user-friendly menu interface for interacting with the Enigma machine.

## Components

- **Plugboard**: Handles initial letter substitutions.
- **Rotors**: Simulates the rotating cipher mechanism.
- **Reflector**: Ensures reciprocal substitutions for encryption and decryption.

## Usage

1. **Compilation**: Compile the program using the make file.
   ```bash
   make
2. **Execution**: Run the compiled executable.
   ```bash
   ./enigma
3. **Menu Options**: Follow the on-screen menu to perfomr operations such as encryption, decryption, configuring the plugboard, changing rotor settings, and dispalying current configurations. 

## Example
- Encrypting a Message:
  - Choose encryption from the menu.
  - Enter the message to be encrypted.
  - View the encrypted output.
- Decrypting a Message:
  - Choose decryption from the menu.
  - Enter the encrypted message.
  - View the decrypted output.
## Dependencies
- Standard C libraries(`stdio.h`, `string.h`, etc.)
- Custom header files for Enigma components (`plugboard.h`, `rotor.h`, `reflector.h`, `globalFunctions.h`).

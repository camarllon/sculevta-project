/*
 * utils.h
 *
 *  Created on: Jul 4, 2014
 */

#ifndef UTILS_H_
#define UTILS_H_

#define CONST_UTIL_FILE_WRITE_BINARY 	"w"
#define CONST_UTIL_FILE_READ_BINARY 	"r"

/**
 * executeCommand
 *
 * Execute a command into system.
 */
BOOL executeCommand(char *command) {
	system(command);
	return TRUE;
}

/**
 * copyFile
 *
 * Copy some fSource file to fDest file.
 */
BOOL copyFile(char *fSource, char *fDest) {
	// Using windows to copy file.
	CopyFile((LPCTSTR) fSource, (LPCTSTR) fDest, FALSE);
	return TRUE;
}

/**
 * findSelfPath
 *
 * Find self path of executable.
 */
BOOL findSelfPath(char *path) {
	// Initialize variable self and find path of executable
	char self[1024];

	memset(&self, 0x0, sizeof(self) - 1);
	GetModuleFileName(NULL, self, sizeof(self) - 1);

	// Copy value to return
	strncpy(path, self, strlen(self));
	path[strlen(self)] = '\0';

	// Return OK
	return TRUE;
}

/**
 * generateRandomCharSequence.
 *
 * Generate a random sequence of characters.
 */
BOOL generateRandomCharSequence(char *name, int length) {

	char charset[] =
			"abcdefghijkLMNOPQRSTUVXZ54321ABCDEFGHIJKlmnopqrstuvxz09876";
	char *randomString = (char *) malloc(length * sizeof(char));
	int i;

	//Initializing random lib
	srand(time(NULL));

	// Generating sequence
	for (i = 0; i < length; i++) {
		int i = ((double) rand() / RAND_MAX ) * (strlen(charset) - 1);
		*randomString++ = charset[i];
	}
	*randomString = '\0'; // Crap trick to end

	strncpy(name, randomString-length, length+1);

	return TRUE;
}

/**
 * generateRandomNameWithPath.
 *
 * Generate random name of executable with path.
 */
BOOL generateRandomNameWithPath(char * name, char *path, int length){
	char genFile[length+2];

	strcpy(name, path);
	generateRandomCharSequence(genFile, length);
	strcat(name, genFile);
	strcat(name, ".exe");

	return TRUE;
}

#endif /* UTILS_H_ */

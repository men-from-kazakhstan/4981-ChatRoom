#ifndef CLIENT_H
#define CLIENT_H

#include "clientwindow.h"

#define BUFLEN 512

/********************************************************
 *  Function:       char * getUserMessage(ClientWindow *cw, char *IP, char *username)
 *                      ClientWindow *cw: ClientWindow pointer in order to access the UI
 *                      char *completeMsg: buffer that holds the complete message to send
 *                      char *IP: string containing the IP of the client sending the message
 *                      char *username: client username
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Will get the message entered by the user into the GUI.  Will then
 *      put a string with the IP and username appended to the front into the completeMsg buffer.
 *******************************************************/
void getUserMessage(ClientWindow *cw, char *completeMsg, char *IP, char *username);

/********************************************************
 *  Function:       void formatMessage(char *message, char *IP, char *username)
 *                      char *message: buffer that holds message to be formatted.
 *                      char *IP: string containing the IP of the client sending the message
 *                      char *username: client username
 *                      char *dest: where the formatted message should be written.
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      This will take the message passed into it and apply standard formatting rules.
 *      That is to say, It will prepend the message with the timestamp, username, and
 *      IP address of the sender. It will also colour code the username eventually.
 *******************************************************/
void formatMessage(const char *message, const char *IP, const char *username, char* dest);
#endif // CLIENT_H

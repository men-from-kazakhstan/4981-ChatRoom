#include "client.h"

void getUserMessage(ClientWindow *cw, char *completeMsg, char *IP, char *username) {
    char msg[BUFLEN];

    cw->getUIMessage(msg);

    sprintf(completeMsg, "%s %s: %s", IP, username, msg);
}

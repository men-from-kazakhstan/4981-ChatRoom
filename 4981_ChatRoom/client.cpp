#include <time.h>
#include "client.h"

void getUserMessage(ClientWindow *cw, char *completeMsg, char *IP, char *username) {
    char msg[BUFLEN];

    cw->getUIMessage(msg);

    sprintf(completeMsg, "%s %s: %s", IP, username, msg);
}

void formatMessage(const char *message, const char *IP, const char *username, char *dest) {
    char timer[BUFLEN];
    time_t timestamp;
    struct tm * timeinfo;

    time(&timestamp);
    timeinfo = localtime(&timestamp);
    strftime(timer,BUFLEN,"<%b %d - %R>",timeinfo);
    sprintf(dest,"%s %s - %s: %s\n",timer, IP, username, message);

}

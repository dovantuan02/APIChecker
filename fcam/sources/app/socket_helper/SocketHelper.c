#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#include "SocketHelper.h"

/*----------------------------------------------------*/
int SocketHelperDatagramOpen(int usPort) {
    int xSocket = -1;

    xSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (xSocket < 0) {
        return -1;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(usPort);
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(xSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        close(xSocket);
        return -1;
    }

    return xSocket;
}

/*----------------------------------------------------*/
signed long SocketHelperDatagramRead(GroupsockHelp_t xSocket, void *pvData, unsigned long uxSize) {
    if (xSocket.fSocket < 0) {
        return 0;
    }

    struct sockaddr_in address;
    socklen_t addressLen = sizeof(address);
    ssize_t number = recvfrom(xSocket.fSocket, pvData, uxSize, 0, (struct sockaddr *)&address, &addressLen);
    return number;
}

/*----------------------------------------------------*/
int SocketHelperDatagramWrite(GroupsockHelp_t xSocket, void *pvData, unsigned long uxSize) {
    if (xSocket.fSocket < 0) {
        return 0;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(xSocket.fPort);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    return sendto(xSocket.fSocket, pvData, uxSize, 0, (struct sockaddr *)&address, sizeof(struct sockaddr_in));
}

/*----------------------------------------------------*/
void SocketHelperClose(GroupsockHelp_t xSocket) {
    if (xSocket.fSocket > 0) {
        close(xSocket.fSocket);
    }
}

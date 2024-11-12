#ifndef _SOCKET_HELPER_H_
#define _SOCKET_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct {
    int fSocket;
    int fPort;
} GroupsockHelp_t;

extern int SocketHelperDatagramOpen(int usPort);
extern signed long SocketHelperDatagramRead(GroupsockHelp_t xSocket, void *pvData, unsigned long uxSize);
extern int SocketHelperDatagramWrite(GroupsockHelp_t xSocket, void *pvData, unsigned long uxSize);
extern void SocketHelperClose(GroupsockHelp_t xSocket);

#ifdef __cplusplus
}
#endif

#endif /* _SOCKET_HELPER_H_ */
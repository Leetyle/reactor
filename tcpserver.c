#include "tcpserver.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "error.h"

int createServerSocket(unsigned int tcpPort) {
    struct sockaddr_in address = {0};

    const int serverHandle = socket(PF_INET, SOCK_STREAM, 0);

    if(serverHandle < 0) {
        error("Faild to create server socket.");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(tcpPort);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serverHandle, (struct sockaddr*)&address, sizeof address) < 0) {
        error("bind() failed.");
    }

    if(listen(serverHandle, SOMAXCONN) != 0) {
        error("listen() failed.");
    }

    return serverHandle;
}

void disposeServerSocket(int serverSocket) {
    (void)close(serverSocket);
}

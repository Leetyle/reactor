#include "eventhandler.h"
#include "reactor.h"
#include "diagnosticserver.h"
#include <malloc.h>

struct DiagnosticsServer {
    EventHandler eventHandler;
    Handle listeningSocket;
};

static Handle getServerSocket(void * instance) {
    const DiagnosticsServerPtr server = instance;
    return server->listeningSocket;
}

static void handleConnectReq(void * instance) {
    DiagnosticsServerPtr server = instance;
    // add code for accepting the new connection and creating a client here...
}

DiagnosticsServerPtr createServer(unsigned int tcpPort) {
    DiagnosticsServerPtr newServer = malloc(sizeof *newServer);

    if(newServer != 0) {
        newServer->listeningSocket = createServerSocket(tcpPort);
        newServer->eventHandler.instance = newServer;
        newServer->eventHandler.getHandle = getServerSocket;
        newServer->eventHandler.handleEvent = handleConnectReq;
        registerEvtHandler(&newServer->eventHandler);
    }

    return newServer;
}

void destroyServer(DiagnosticsServerPtr server) {
    unregisterEvtHandler(&server->eventHandler);
    free(server);
}


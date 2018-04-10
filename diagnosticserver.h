#ifndef DIAGNOSTIC_SERVER_H
#define DIAGNOSTIC_SERVER_H

typedef struct DiagnosticsServer * DiagnosticsServerPtr;

DiagnosticsServerPtr createServer(unsigned int tcpPort);

void destroyServer(DiagnosticsServerPtr server);

#endif



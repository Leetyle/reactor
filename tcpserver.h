#ifndef TCPSERVER_H
#define TCPSERVER_H

int createServerSocket(unsigned int tcpPort);
void disposeServerSocket(int serverSocket);

#endif // TCPSERVER_H

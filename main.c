#include <stdio.h>
#include <stdlib.h>
#include "reactor.h"
#include <stdio.h>
#include "eventhandler.h"
#include "reactoreventloop.h"
#include "diagnosticserver.h"

int main() {
    printf("Hello world!\n");

    const int serverPort = 0xC001;
    DiagnosticsServerPtr server = createServer(serverPort);

    if(server == 0) {
        printf("Failed to create server.\n");
    }

    for(;;) {
        handleEvents();
    }

    return 0;
}

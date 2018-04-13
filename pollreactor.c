#include "reactor.h"
#include "reactoreventloop.h"
#include <assert.h>
#include <stddef.h>
#include <poll.h>
#include <stdio.h>
#include <stdbool.h>


#define MAX_NO_OF_HANDLERS       128
#define INFTIM                   -1

/* Bind an event handler to the struct used to interface poll(). */
typedef struct {
    bool isUsed;
    EventHandler handler;
    struct pollfd fd;
} HandlerRegistration;

static HandlerRegistration registerHandlers[MAX_NO_OF_HANDLERS];

static bool addToRegistry(EventHandler * handler) {
    bool isRegistered = false;
    for(int i = 0; i < MAX_NO_OF_HANDLERS && isRegistered == false; i++) {
        if(!registerHandlers[i].isUsed) {
            HandlerRegistration * freeEntry = registerHandlers + i;
            freeEntry->handler = *handler;
            freeEntry->fd.fd = handler->getHandle(handler->instance);
            freeEntry->fd.events = POLLIN;

            isRegistered = freeEntry->isUsed = true;
            (void)printf("Reactor: Added handle with FD = %d\n",
                          freeEntry->fd.fd);
        }
    }
    return isRegistered;
}

static bool removeFromRegistry(EventHandler * handler) {
    bool removed = false;

    for(int i = 0; i < MAX_NO_OF_HANDLERS && removed == 0; ++i) {
        if(&registerHandlers[i].handler == handler) {
            registerHandlers[i].isUsed = false;
            removed = true;
        }
    }

    return removed;
}

void registerEvtHandler(EventHandler * handler) {
    assert(handler != 0);
    addToRegistry(handler);
}

void unregisterEvtHandler(EventHandler * handler) {
    assert(handler != 0);
    removeFromRegistry(handler);
}

static size_t buildPollArray(struct pollfd * fds) {
    int ret = 0;
    for(int i = 0; i < MAX_NO_OF_HANDLERS; i++) {
        if(registerHandlers[i].isUsed) {
            fds[ret++] = registerHandlers[i].fd;
        }
    }

    return ret;
}

static EventHandler * findHandler(int fd) {
    EventHandler * matched = NULL;

    for(int i = 0; i < MAX_NO_OF_HANDLERS && matched == NULL; ++i) {
        if(registerHandlers[i].fd.fd == fd)
        matched = &registerHandlers[i].handler;
    }

    return matched;
}

static void dispatchSignalledHandles(const struct pollfd* fds, 
                                     size_t noOfHandles) {
    for(size_t i = 0; i < noOfHandles; i++) {
        if((POLLIN | POLLERR) & fds[i].revents) {
            EventHandler * signalledHandler = findHandler(fds[i].fd);

            if(signalledHandler != 0) {
                signalledHandler->handleEvent(signalledHandler->instance);
            }
        }
    }
}

void handleEvents(void) {
    struct pollfd fds[MAX_NO_OF_HANDLERS] = {0};
    const size_t noOfHandles = buildPollArray(fds);
    if(poll(fds, noOfHandles, INFTIM) > 0) {
        dispatchSignalledHandles(fds, noOfHandles);
    } else {
        printf("Poll failure.");
    }
}



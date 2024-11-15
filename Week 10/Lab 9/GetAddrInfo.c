#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "Practical.h"

/**
 * Main function to resolve and display IP addresses for a given hostname and port/service.
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments (hostname and port/service).
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        DieWithUserMessage("Parameter(s)", "<Address/Name> <Port/Service>");
    }

    char *addrString = argv[1];  // Hostname or address
    char *portString = argv[2];  // Port or service

    // Set up criteria for address resolution
    struct addrinfo addrCriteria;
    memset(&addrCriteria, 0, sizeof(addrCriteria));
    addrCriteria.ai_family = AF_UNSPEC;       // IPv4 or IPv6
    addrCriteria.ai_socktype = SOCK_STREAM;  // Stream sockets
    addrCriteria.ai_protocol = IPPROTO_TCP;  // TCP protocol

    // Retrieve address information
    struct addrinfo *addrList;
    int rtnVal = getaddrinfo(addrString, portString, &addrCriteria, &addrList);
    if (rtnVal != 0) {
        DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));
    }

    // Print resolved addresses
    for (struct addrinfo *addr = addrList; addr != NULL; addr = addr->ai_next) {
        PrintSocketAddress(addr->ai_addr, stdout);
        fputc('\n', stdout);
    }

    freeaddrinfo(addrList); // Free memory allocated by getaddrinfo()
    return 0;
}
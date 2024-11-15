#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "Practical.h"

/**
 * Prints a human-readable representation of a socket address.
 * Supports IPv4 and IPv6 addresses.
 * @param address Pointer to the socket address structure.
 * @param stream Output stream for printing (e.g., stdout).
 */
void PrintSocketAddress(const struct sockaddr *address, FILE *stream) {
    if (address == NULL || stream == NULL) return;

    char addrBuffer[INET6_ADDRSTRLEN]; // Buffer for address string
    in_port_t port;                    // Port number
    void *numericAddress;              // Binary IP address

    switch (address->sa_family) {
        case AF_INET: // IPv4
            numericAddress = &((struct sockaddr_in *) address)->sin_addr;
            port = ntohs(((struct sockaddr_in *) address)->sin_port);
            break;
        case AF_INET6: // IPv6
            numericAddress = &((struct sockaddr_in6 *) address)->sin6_addr;
            port = ntohs(((struct sockaddr_in6 *) address)->sin6_port);
            break;
        default:
            fputs("[unknown address type]", stream);
            return;
    }

    // Convert binary IP to string
    if (inet_ntop(address->sa_family, numericAddress, addrBuffer, sizeof(addrBuffer)) == NULL) {
        fputs("[invalid address]", stream);
    } else {
        fprintf(stream, "%s", addrBuffer);
        if (port != 0) fprintf(stream, ":%u", port); // Print port if non-zero
    }
}

/**
 * Checks if two socket addresses are equal.
 * @param addr1 First socket address.
 * @param addr2 Second socket address.
 * @return true if the addresses match, false otherwise.
 */
bool SockAddrsEqual(const struct sockaddr *addr1, const struct sockaddr *addr2) {
    if (addr1 == NULL || addr2 == NULL) return addr1 == addr2;

    if (addr1->sa_family != addr2->sa_family) return false;

    if (addr1->sa_family == AF_INET) { // Compare IPv4
        struct sockaddr_in *ipv4Addr1 = (struct sockaddr_in *) addr1;
        struct sockaddr_in *ipv4Addr2 = (struct sockaddr_in *) addr2;
        return ipv4Addr1->sin_addr.s_addr == ipv4Addr2->sin_addr.s_addr &&
               ipv4Addr1->sin_port == ipv4Addr2->sin_port;
    } else if (addr1->sa_family == AF_INET6) { // Compare IPv6
        struct sockaddr_in6 *ipv6Addr1 = (struct sockaddr_in6 *) addr1;
        struct sockaddr_in6 *ipv6Addr2 = (struct sockaddr_in6 *) addr2;
        return memcmp(&ipv6Addr1->sin6_addr, &ipv6Addr2->sin6_addr, sizeof(struct in6_addr)) == 0 &&
               ipv6Addr1->sin6_port == ipv6Addr2->sin6_port;
    }

    return false;
}
#include <stdio.h>
#include <stdlib.h>
#include "Practical.h"

/**
 * Prints a user-defined error message and exits.
 * @param msg Main error message.
 * @param detail Additional details about the error.
 */
void DieWithUserMessage(const char *msg, const char *detail) {
    fputs(msg, stderr);
    fputs(": ", stderr);
    fputs(detail, stderr);
    fputc('\n', stderr);
    exit(1);
}

/**
 * Prints a system-defined error message and exits.
 * @param msg Error message.
 */
void DieWithSystemMessage(const char *msg) {
    perror(msg);
    exit(1);
}
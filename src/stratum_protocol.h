#ifndef STRATUM_PROTOCOL
#define STRATUM_PROTOCOL

/* Takes a JSON RPC message with whitespace stripped out, performs command based on message */
int process(char *buf, char *resp);

#endif
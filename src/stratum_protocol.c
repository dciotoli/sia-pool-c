#include <stdio.h>
#include <stdin.h>
#include "stratum_protocol.h"
#include "cJSON.h"
/* Public Functions */

int process(char *buf, char *resp) {
	cJSON *root, *method;
	// Parse incoming json-rpc
	root = cJSON_Parse(buf);
	method = cJSON_GetObjectItemCaseSensitive(root, "method");
	// Call appropriate method (for now just echo back the method)
	if (cJSON_IsString(method))
	{
	  strncpy(resp, method->valuestring, 255);
	}
	// all went well, return 0
	cJSON_Delete(root);
	return 0;
}

/* Private functions */

/* 
	void *args: 	Array input (going to be either a char * or some kind of 
   					struct from the JSONc library). 

   	char *resp:		Char array where the appropriate JSON-RPC response will go.
*/

/* client -> server functions */
// mining.authorize
static int miningAuthorize(void *args, char *resp) {

	return 0;
}

// mining.extranonce.subscribe
static int miningExtranonceSubscribe(void *args, char *resp) {

	return 0;
}

// mining.get_transactions
static int miningGetTransactions(void *args, char *resp) {

	return 0;
}

// mining.submit
static int miningSubmit(void *args, char *resp) {

	return 0;
}

// mining.subscribe
static int miningSubscribe(void *args, char *resp) {

	return 0;
}

// mining.suggest_difficulty
static int miningSuggestDifficulty(void *args, char *resp) {

	return 0;
}

// mining.suggest_target
static int miningSuggestTarget(void *args, char *resp) {

	return 0;
}

// Honestly have no idea what im really going to do with these yet
/* server -> client functions */

// client.get_version
static int clientGetVersion() {

	return 0;
}

// client.reconnect
static int clientReconnect() {

	return 0;
}

// client.show_message
static int clientShowMessage() {

	return 0;
}
// mining.notify
static int miningNotify() {

	return 0;
}

// mining.suggest_difficulty
static int miningSetDifficulty() {

	return 0;
}

// mining.set_extranonce

static int miningSetExtranonce() {

	return 0;
}
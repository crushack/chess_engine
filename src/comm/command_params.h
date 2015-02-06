

#ifndef _COMMAND_PARAMS_H_
#define _COMMAND_PARAMS_H_

#include <string>

/**
 * Sender - enum semnaling the type of message
 *
 **/

enum Sender {
	Engine = 0,
	WinBoard,
	NONE
};

/**
 * WinBoard_CommandParams - contains the basic information
 *                          given when an event is triggered
 **/

struct WinBoard_CommandParams {

	// variable contains the "command" to the program

	std::string event;

	// variable contains the arguments to the command

	std::string params;

	// variable contains the time in witch the event was triggered

	time_t firedTime;

	// variable contains the type of the message 

	Sender sender;

	WinBoard_CommandParams( std::string event, std::string params );
	WinBoard_CommandParams( std::string event, std::string params, Sender s);
};

#endif

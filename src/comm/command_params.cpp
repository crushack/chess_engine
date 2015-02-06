#include "command_params.h"

#include <string>
#include <ctime>

WinBoard_CommandParams::WinBoard_CommandParams( std::string event, 
												std::string params) {
	this -> event = event;
	this -> params = params;
	this -> sender = NONE;

	firedTime = time(NULL);
}

WinBoard_CommandParams::WinBoard_CommandParams( std::string event, 
												std::string params,
												Sender sender) 
							: WinBoard_CommandParams(event, params)
{
	this -> sender = sender;
}

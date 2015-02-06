
#ifndef _WINBOARD_INTERFACE_H_
#define _WINBOARD_INTERFACE_H_

#include "command.h"
#include "command_params.h"

#include <vector>

/**
 * WinBoard_Interface - class defines a message sending interface
 *                       that helps establish the communication between
 *                       WinBoard and the program
 **/

class WinBoard_Interface {

protected:

	std::vector<WinBoard_Command> v;

public:

	WinBoard_Interface() = default;


	/** 
	 *  add - method adds a new command to the interface
	 *
	 **/

	void add( WinBoard_Command const & command );

	/**
	 *  get - method helps retrieve a command by name
	 *
	 **/

	WinBoard_Command& get( std::string event_name );

	/**
	 *  run - methods sends a message (calls) all funcions with specific name
	 *
	 **/

	void run( std::string command, Sender s = NONE );	
};

#endif

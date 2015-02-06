#include "winboard_interface.h"
#include "command.h"
#include "command_params.h"

#include <string>
#include <vector>

void WinBoard_Interface::add( WinBoard_Command const & command ) {
	v.push_back(command);
}

WinBoard_Command& WinBoard_Interface::get( std::string event_name ) {
	for ( auto it = v.begin(); it != v.end(); ++ it )
		if ( it -> event_name == event_name )
			return * it;
	static WinBoard_Command blank(" ");
	return blank;
}

void WinBoard_Interface::run( std::string command, Sender s ) {

	std::string event;
	std::string params;

	int pos = command.find(' ');
	pos = pos < (int) command.length() ? pos : command.length();

	event = command.substr(0, pos);
	params = command.substr(pos + 1);

	WinBoard_CommandParams Params( event, params, s);

	for ( auto it = v.begin(); it != v.end(); ++ it )
		if ( it -> event_name == event ) {
			it -> fire(Params);	
		}
}

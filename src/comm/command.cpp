#include "command.h"
#include "command_params.h"

#include "../util/delegate.h"

#include <string>
#include <ctime>
#include <iostream>

WinBoard_Command::WinBoard_Command( std::string event_name ) {
	
	this -> event_name = event_name;
}

WinBoard_Command::~WinBoard_Command() {

}

void WinBoard_Command::add( CDelegate delegate ) {
	event.add(delegate);
}

void WinBoard_Command::remove( CDelegate delegate ) {
	event.remove(delegate);
}

void WinBoard_Command::fire(WinBoard_CommandParams const & params) {
	event(params);
}

std::string WinBoard_Command::getName() const {
	return event_name;
}


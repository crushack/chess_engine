
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>

#include "../util/delegate.h"

#include "command_params.h"

/**
 * WinBoard_Command - class is a wrapper to the Delegate class
 *
 **/

class WinBoard_Command {

	friend class WinBoard_Interface;

protected:

	SyncEventListener<void, WinBoard_CommandParams const &> event;

	/**
	 * fire - method fires the event and transmits info to 
	 *          the subscribed functions
	 *
	 **/

	void fire(WinBoard_CommandParams const &);

	std::string event_name;

public:

	typedef Delegate<void, WinBoard_CommandParams const &> CDelegate;

	WinBoard_Command( std::string event_name );
	virtual ~WinBoard_Command();

	/**
	 * add - method subscribes the delegate to the class
	 *
	 **/

	void add( CDelegate delegate );

	/**
	 * remove - method unsubscribes the delegate to the class
	 *
	 **/

	void remove( CDelegate delegate );

	
	std::string getName() const;
};

#endif


#ifndef _DELEGATE_H__
#define _DELEGATE_H__

#include <typeinfo>
#include <functional>
#include <vector>
#include <mutex>
#include <thread>

/**
 * Delegate - class is a wrapper for a function object
 *
 **/

template <typename return_type, typename... params >
class Delegate {

	typedef std::function< return_type(params... ) > Function;

	// function wrapped by the Delegate class

	Function func;

	// uniqe id of the delegate (used for comparison issues)

	int _id;

public:

	/**
	 * counter - class is a singleton used for generating unique id's for the
	 *                 Delegate class
	 **/

	class counter {

			counter() = default;
			std::mutex block;

		public:

			static counter& instance() {
				static counter inst;
				return inst;
			}

			/**
			 *  getId() - method used to generate unique id's for the Delegate class
			 *
			 **/

			int getId() {
				static int id = 0;
				int ret;

				block.lock();
				ret = ++ id;
				block.unlock();

				return ret;
			}

	};

	Delegate(Function func) : func(func) {
		_id = counter::instance().getId();
	}

 	/**
 	 * isValid() - method is used for checking if function is callable
 	 *
 	 **/

 	bool isValid() const {
 		return ( func ? true : false ) ;
 	}

 	/**
	 * Delegate() - method contanis the logic of function beeing called
	 *
	 **/

 	return_type operator()(params... p) const {
 		if ( isValid() )
 			return func(p... );
 	}

 	bool operator == ( Delegate const & other ) const {
 		return typeid(func) == typeid(other.func) && _id == other._id;
 	}

 	bool operator < ( Delegate const & other ) const {
 		return typeid(func).name() < typeid(other.func).name() || 
 					( typeid(func).name() == typeid(other.func).name() && 
 					_id < other._id);
 	}

};

/**
 * SyncEventListener - class contains the logic of an event listener which 
 *                        calls all the functions registered to it upon event
 **/

template <typename return_type, typename... params >
class SyncEventListener {

protected:

	typedef Delegate <return_type, params...> delegate;

	// contains a vector of all registerd Delegates

	std::vector<delegate> v;

public:

	SyncEventListener() = default;

	/**
	 * @param1 -> a delegate which needs to be registered to the listener
	 *
	 **/

	void add( delegate d ) {
		if ( ! contains(d) ) {
			v.push_back(d);
		}
	}

	/**
	 * @param1 -> a delegate which needs to be unregistered to the listener
	 *
	 **/

	void remove( delegate d ) {
		for ( auto it = v.begin(); it != v.end(); ++ it ) 
			if ( (*it) == d )
			{
				v.erase(it);
				return;
			}
	}

	/**
	 * Method checks if @param1 is registered to the listener
	 *
	 **/

	bool contains( delegate d ) const {
		for ( auto it = v.begin(); it != v.end(); ++ it ) 
			if ( (*it) == d )
				return true;
		return false;
	}

	/**
	 * Method contains the logic of event trigger, in this moment all 
	 *         the methods from the delegates are called sequentially
	 **/

	virtual void operator()( params... p ) const {
		for ( auto it = v.begin(); it != v.end(); ++ it )
			(*it)(p...);
	}

	SyncEventListener& operator += ( delegate d ) {
		add(d);
		return * this;
	}

	SyncEventListener& operator -= ( delegate d ) {
		remove(d);
		return * this;
	}

};

/**
 * AsyncEventListener - class contains the logic of an event listener which 
 *         asynchroniusily calls all the functions registered to it upon event
 **/

template <typename return_type, typename... params >
class AsyncEventListener : public SyncEventListener<return_type, params...> {

	typedef Delegate <return_type, params...> delegate;

	static void run( delegate d, params... p ) {
		d( p... );
	}

public:

	virtual void operator()( params... p ) const {

		std::vector<std::thread> threads;

		for ( auto it = this -> v.begin(); it != this -> v.end(); ++ it )
			threads.push_back(std::thread(run, *it, p...));

		for ( auto& th : threads ) th.join();
	}	
};

#endif

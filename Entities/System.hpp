#ifndef KAGAMI_ENTITIES_SYSTEM_H_
#define KAGAMI_ENTITIES_SYSTEM_H_

class System
{
public:
	// The idea of enum is to identify each systems so they can be processed
	// properly by the Engine class
	enum System_type {
		Renderer
	};
	// All systems must update each game loop
	// = 0 means derived classes must provide an implementation, not that the base class can not provide an implementation.
	virtual void update() = 0;// float dt ) = 0;

	// It's good practice to separate the construction and initialization code.
	virtual bool initialize() = 0;

	virtual bool shutdown() = 0;

	// This recieves any messages sent to the core engine in Engine.cpp
	//virtual void SendMessage( Message *msg ) = 0;

	///All systems need a virtual destructor to have their destructor called 
	virtual ~System( ) {}
};

#endif
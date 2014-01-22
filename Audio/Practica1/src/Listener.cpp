#include "../include/Listener.h"

Listener* Listener::listener = 0;

Listener& Listener::Instance()
{
	if (!listener)
	{	listener = new Listener();
		return *listener;
	}
	else
		return *listener;

}
#pragma once
#include "pch.h"
#include "application.h"
#include "log.h"

/**
 * Driver file. This is the entry point for any client application. Behaviour is controlled by creating an application implementation in the client and defining create_application.
 */

extern coga::application* create_application();

int main(int argc, char** argv)
{
	coga::log::init();

	coga::application* app = coga::create_application();
	app->run();
	delete app;
	return 0;
}

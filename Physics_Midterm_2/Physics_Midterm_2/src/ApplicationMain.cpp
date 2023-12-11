
#include "PhysicsApplication.h"

int main(int argv, char* argc[])
{
	Debugger::print = true;

	PhysicsApplication application;

	application.InitializeWindow(1366, 728);
	application.Render();

	return -1;
}
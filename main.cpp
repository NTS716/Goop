#include "TestGame.hpp"

#undef main

int main()
{
	TestGame testGame;
	testGame.init();
	testGame.run();
	return 0;
}
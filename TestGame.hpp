#include "Core/headers/Game.hpp"

#ifndef TESTGAME_HPP
#define TESTGAME_HPP

class TestGame : public Goop::Game
{
public:
	virtual void conf();
	virtual void load();
	virtual void update();
	virtual void draw();
};

#endif
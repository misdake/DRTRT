#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Player.h"

class ServerPlayer : public Player
{
public:
	ServerPlayer(void);
	~ServerPlayer(void);
};
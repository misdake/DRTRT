#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Player.h"
#include "NetworkNode.h"

class ServerPlayer : public Player, public NetworkNode
{
public:
	ServerPlayer(void);
	~ServerPlayer(void);

	virtual void load(string);

	virtual void paint();

	virtual void combine(int top, float* data);

protected:
	virtual void receive(char* buf, unsigned long ip);

private:
	bool * valid; //bool[height]; valid[i]==true -> frameBuffer[i] full.
};
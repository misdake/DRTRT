#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "Player.h"
#include "NetworkNode.h"

class ClientPlayer : public Player, public NetworkNode
{
public:
	ClientPlayer(void);
	~ClientPlayer(void);

	virtual void combine(int top, float* data);

protected:
	unsigned long ip;
	virtual void receive(char* buf, unsigned long ip);
	int frameId;
};
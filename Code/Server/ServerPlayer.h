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

	void loadClientList(string);

	virtual void load(string);

	virtual void paint();

	virtual void combine(int top, float* data);

protected:
	virtual void receive(char* buf, unsigned long ip);
	vector<unsigned long> clients;
	int frameId;

private:
	int fillCount;
	int takeCount;
	bool * valid; //bool[height]; valid[i]==true -> frameBuffer[i] full.
};
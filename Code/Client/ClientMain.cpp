#include <iostream>
#include "Main.h"

#include <thread>
#include "ClientPlayer.h"

Player * player;

int main(int argc, char *argv[]) {
	player = new ClientPlayer();

	player->load("../Scene/scene1.test");
	((ClientPlayer*)player)->start();

	for(;;) {
		std::this_thread::yield();
	}
}
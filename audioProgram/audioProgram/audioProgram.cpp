// audioProgram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "fmod.hpp"
//#include "fmod_studio.hpp"
#include "Game.h"



int main()
{

	Game* game = new Game();
	FMOD::System* system = NULL;
	FMOD_RESULT result = FMOD::System_Create(&system);
	FMOD_ADVANCEDSETTINGS* settings;
	FMOD::Channel* channel1 = 0;
	FMOD::Channel* channel2 = 0;
	FMOD::Sound* sound1 = NULL;
	FMOD::Sound* sound2 = NULL;

	int wet = 1000;
	char f;

	result = system->init(512, FMOD_INIT_3D_RIGHTHANDED, 0);

	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result);
		exit(-1);
	}
	result = system->set3DSettings(1.0, 1.0f, 1.0f);
	//system->createSound("C:\\Users\\space_000\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\gula.mp3", FMOD_3D, 0, &sound1);
	//system->createSound("C:\\Users\\space_000\\source\\repos\\ConsoleApplication2\\ConsoleApplication2\\fnpig.mp3", FMOD_3D, 0, &sound2);
	system->setDriver(0);
	//For Channel 1.
	FMOD_VECTOR pos1 = { 0.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel1 = { 0.0f, 0.0f, 0.0f };
	//For Channel 2.
	FMOD_VECTOR pos2 = { 10.f * 1.0f, 0.0f, 0.0f };
	FMOD_VECTOR vel2 = { 1.0f, 0.0f, 0.0f };

	while (!glfwWindowShouldClose(game->getWindow())) {
		game->game_loop();
		system->update();
	}
	game = nullptr;
	delete game;
	exit(EXIT_SUCCESS);

}

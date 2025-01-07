#include "../headers/StartGameCommand.h"
#include "../headers/Menu.h"

StartGameCommand::StartGameCommand(Menu *menu) : menu(menu) {
}

void StartGameCommand::execute() const {
	if (menu) {
		menu->startGame();
	}
}

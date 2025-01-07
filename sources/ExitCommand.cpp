#include "../headers/ExitCommand.h"

ExitCommand::ExitCommand(Menu *menu) : menu(menu) {
}

void ExitCommand::execute() const {
	if(menu) {
		menu->exit();
	}
}

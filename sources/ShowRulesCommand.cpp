#include "../headers/ShowRulesCommand.h"
#include "../headers/Menu.h"

ShowRulesCommand::ShowRulesCommand(Menu *menu) : menu(menu) {
}

void ShowRulesCommand::execute() const {
	if(menu) {
		menu->showRules();
	}
}
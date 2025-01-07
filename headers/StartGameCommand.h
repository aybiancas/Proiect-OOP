#ifndef STARTGAMECOMMAND_H
#define STARTGAMECOMMAND_H

#include "Command.h"
#include "Menu.h"

class StartGameCommand : public Command {
	Menu *menu;

public:
	explicit StartGameCommand(Menu *menu);

	void execute() const override;
};

#endif //STARTGAMECOMMAND_H

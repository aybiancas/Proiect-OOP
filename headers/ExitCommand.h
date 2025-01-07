
#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H
#include "Command.h"
#include "Menu.h"

class ExitCommand : public Command {
	Menu* menu;

	public:

	explicit ExitCommand(Menu* menu);

	void execute() const override;
};

#endif //EXITCOMMAND_H

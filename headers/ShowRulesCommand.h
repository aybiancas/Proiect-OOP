#ifndef SHOWRULESCOMMAND_H
#define SHOWRULESCOMMAND_H

#include "Command.h"
#include "Menu.h"

class ShowRulesCommand : public Command {
	Menu *menu;

public:
	explicit ShowRulesCommand(Menu *menu);

	void execute() const override;
};

#endif //SHOWRULESCOMMAND_H

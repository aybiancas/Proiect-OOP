
#ifndef BOTBETSTRATEGY_H
#define BOTBETSTRATEGY_H

#include "BetStrategy.h"
#include "Game.h"

class BotBetStrategy : public BetStrategy {
	public:

	void bet(sf::RenderWindow* window) override;
};

#endif //BOTBETSTRATEGY_H


#ifndef BOTBETSTRATEGY_H
#define BOTBETSTRATEGY_H

#include "betStrategy.h"
#include "game.h"

class BotBetStrategy : public BetStrategy {
	public:

	void bet(sf::RenderWindow* window) override;
};

#endif //BOTBETSTRATEGY_H

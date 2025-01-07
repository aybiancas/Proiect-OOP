
#ifndef HUMANBETSTRATEGY_H
#define HUMANBETSTRATEGY_H

#include "BetStrategy.h"
#include "Game.h"

class HumanBetStrategy : public BetStrategy {
	public:

	void bet(sf::RenderWindow *window) override;
};

#endif //HUMANBETSTRATEGY_H

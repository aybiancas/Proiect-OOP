
#ifndef HUMANBETSTRATEGY_H
#define HUMANBETSTRATEGY_H

#include "betStrategy.h"
#include "game.h"

class HumanBetStrategy : public BetStrategy {
	public:

	void bet(sf::RenderWindow *window) override;
};

#endif //HUMANBETSTRATEGY_H

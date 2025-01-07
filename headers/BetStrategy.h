
#ifndef BETSTRATEGY_H
#define BETSTRATEGY_H

#include <SFML/Graphics.hpp>

class BetStrategy {
	public:

	virtual void bet(sf::RenderWindow *window) = 0;

	virtual ~BetStrategy() = default;
};

#endif //BETSTRATEGY_H


#ifndef DEALERPLAYER_H
#define DEALERPLAYER_H

#include "player.h"
#include "deck.h"
#include "card.h"

class DealerPlayer : public Player {
    Deck deck;
    int pot;

    public:

    DealerPlayer();

    DealerPlayer(const DealerPlayer &other);

    ~DealerPlayer() override;

    DealerPlayer& operator=(const DealerPlayer &other);

    int getPot() const;

    void addPot(int amount);

    void addSum(int amount) override;

    Card dealCard();
};

#endif //DEALERPLAYER_H

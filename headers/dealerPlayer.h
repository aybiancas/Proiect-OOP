
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

    int getPot() const;

    void addPot(int amount);

    Card dealCard();
};

#endif //DEALERPLAYER_H

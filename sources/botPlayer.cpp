#include "../headers/botPlayer.h"

BotPlayer::BotPlayer() : sum(500), Player(/**/) {}

BotPlayer::BotPlayer(const BotPlayer& other) : sum(other.sum), Player(other) {}

BotPlayer::~BotPlayer() {}
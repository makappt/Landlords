#include "player.h"
Player::Player(QString name, QObject *parent) : Player(parent)
{
    m_name = name;
}

Player::Player(QObject *parent): QObject{parent}
{
    m_score = 0;
    m_iswin = false;
}

void Player::setRole(Role role)
{
    m_role = role;
}

Player::Role Player::getRole()
{
    return m_role;
}

void Player::setName(QString name)
{

}

QString Player::getName()
{
    return m_name;
}

void Player::setSex(Sex type)
{
    m_sex = type;
}

Player::Sex Player::getSex()
{
    return m_sex;
}

void Player::setType(Type type)
{
    m_type = type;
}

Player::Type Player::getTye()
{
    return m_type;
}

void Player::setDiretion(Direction direction)
{
    m_direction = direction;
}

Player::Direction Player::getDirection()
{
    return m_direction;
}

void Player::setWin(bool flag)
{
    m_iswin = flag;
}

bool Player::getIsWin()
{
    return m_iswin;
}

void Player::setScore(int score)
{
    m_score = score;
}

int Player::getScore()
{
    return m_score;
}

void Player::setPrevPlayer(Player *player)
{
    m_prev = player;
}

void Player::setNextPlayer(Player *player)
{
    m_next = player;
}

Player *Player::getPrevPlayer()
{
    return m_prev;
}

Player *Player::getNextPlayer()
{
    return m_next;
}

void Player::grabLordBet(int point)
{

}

void Player::storeDispatchCard(Card &card)
{
    m_cards.add(card);
}

void Player::storeDispatchCard(Cards &cards)
{
    m_cards.add(cards);
}

Cards Player::getCards()
{
    return m_cards;
}

void Player::clearCard()
{
    m_cards.clear();
}

void Player::playHand(Cards &cards)
{
    m_cards.remove(cards);
}

void Player::setPendingInfo(Player *player, Cards &cards)
{
    m_pendCards = cards;
    m_pendPlayer = player;
}

Player* Player::getPendPlayer()
{
    return m_pendPlayer;
}

Cards Player::getpendCards()
{
    return m_pendCards;
}

void Player::prepareCallLord()
{

}

void Player::preparePlayHand()
{

}


#include "gamecontral.h"
#include <QRandomGenerator>
GameContral::GameContral(QObject *parent)
    : QObject{parent}
{

}

void GameContral::playInit()
{
    m_robotLift = new Robot("玩家A",this);
    m_robotRight = new Robot("玩家B",this);
    m_user = new UserPlayer("我自己",this);

    //set the sex
    Player::Sex sex;
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotLift->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotRight->setSex(sex);
    sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
    m_user->setSex(sex);

    //set the direction
    m_robotLift->setDiretion(Player::Left);
    m_robotRight->setDiretion(Player::Right);
    m_user->setDiretion(Player::Right);

    //set the
    m_user->setNextPlayer(m_robotRight);
    m_user->setPrevPlayer(m_robotLift);

    m_robotLift->setPrevPlayer(m_robotRight);
    m_robotLift->setNextPlayer(m_user);

    m_robotRight->setPrevPlayer(m_user);
    m_robotRight->setNextPlayer(m_robotLift);

    //设置当前玩家
    m_currentPlayer = m_user;


}

void GameContral::setCurrentPlayer(Player *player)
{
    m_currentPlayer = player;
}

Player *GameContral::getCurrentPlayer()
{
    return m_currentPlayer;
}

Robot *GameContral::getLeftRobot()
{
    return m_robotLift;
}

Robot *GameContral::getRightRobot()
{
    return m_robotRight;
}

UserPlayer *GameContral::getUser()
{
    return m_user;
}

Player *GameContral::getPendPlayer()
{
    return m_pendPlayer;
}

Cards GameContral::getPendCards()
{
    return m_pendCards;
}

void GameContral::initAllCards()
{
    m_allCards.clear();
    for(int point = Card::Card_Begin + 1;point < Card::Card_SJ; ++point){
        for(int suit = Card::Suit_Begin + 1;suit < Card::Suit_End; ++suit){
            Card c((Card::CardSuit)suit,(Card::CardPoint)point);
            m_allCards.add(c);
        }
    }
    m_allCards.add(Card(Card::Suit_Begin,Card::Card_SJ));
    m_allCards.add(Card(Card::Suit_Begin,Card::Card_BJ));
}

void GameContral::takeOneCard()
{
    m_allCards.takeRandCard();
}

Cards GameContral::getSurplusCards()
{
    return m_allCards;
}

void GameContral::resetCardDate()
{
    //shuffle cards
    initAllCards();

    //clear all the cards
    m_user->clearCard();
    m_robotLift->clearCard();
    m_robotRight->clearCard();

    //init player and cards
    m_pendPlayer = nullptr;
    m_pendCards.clear();
}

void GameContral::startLordCord()
{
    m_currentPlayer->prepareCallLord();
}

void GameContral::becomeLord(Player* player)
{
    player->setRole(Player::Lord);
    player->getPrevPlayer()->setRole(Player::Farmer);
    player->getNextPlayer()->setRole(Player::Farmer);

    m_currentPlayer = player;
    player->storeDispatchCard(m_allCards);

    m_currentPlayer->preparePlayHand();

}

void GameContral::clearPlayerScore()
{
    m_robotRight->setScore(0);
    m_robotLift->setScore(0);
    m_user->setScore(0);
}

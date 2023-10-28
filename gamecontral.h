#ifndef GAMECONTRAL_H
#define GAMECONTRAL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"

class GameContral : public QObject
{
    Q_OBJECT
public:
    explicit GameContral(QObject *parent = nullptr);
    //game status
    enum GameStatus{
        DispathCard,              //发牌状态
        CallingLord,             //叫地主状态
        PlaylingHand             //出牌状态
    };
    //player status
    enum PlayerStatus{
        ThinkingForCallLord,    //考虑叫地主状态
        ThingKingForPlayHand,   //考虑玩家状态
        Winning                 //获胜状态
    };
    //init player
    void playInit();

    void setCurrentPlayer(Player* player);

    Player* getCurrentPlayer();
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUser();

    //get the players who played and the cards played
    Player* getPendPlayer();
    Cards getPendCards();

    //init Cards
    void initAllCards();

    //one card at a time
    void takeOneCard();
    //get the last three hole cards
    Cards getSurplusCards();

    //reset the card datas
    void resetCardDate();

    //be ready to call the landlord
    void startLordCord();

    //become Lord
    void becomeLord(Player* player);

    //clear all player`s scores
    void clearPlayerScore();

    //deal with the landlord


    //Handle the play card



signals:

private:
    Robot* m_robotLift = nullptr;
    Robot* m_robotRight = nullptr;
    UserPlayer* m_user = nullptr;
    Player* m_currentPlayer;
    Cards m_pendCards;
    Player* m_pendPlayer;
    Cards m_allCards;



};

#endif // GAMECONTRAL_H

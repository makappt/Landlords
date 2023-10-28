#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "cards.h"


class Player : public QObject
{
    Q_OBJECT
public:
    enum Role{Lord,Farmer};
    enum Sex{Man,Woman};
    enum Direction{Left,Right};
    enum Type{Robot,User,UnKonw};   //player type

    explicit Player(QString name,QObject* parent = nullptr);
    explicit Player(QObject *parent = nullptr);

    void setRole(Role role);
    Role getRole();

    void setName(QString name);
    QString getName();

    void setSex(Sex type);
    Sex getSex();

    void setType(Type type);
    Type getTye();

    void setDiretion(Direction direction);
    Direction getDirection();

    void setWin(bool flag);
    bool getIsWin();

    void setScore(int score);
    int getScore();

    //Provides the upper and lower home objects of the current object
    void setPrevPlayer(Player* player);
    void setNextPlayer(Player* player);
    Player* getPrevPlayer();
    Player* getNextPlayer();

    //call the landlord please rob the landlord
    void grabLordBet(int point);

    //Save playing cards (obtained when the cards are dealt)
    void storeDispatchCard(Card& card);
    void storeDispatchCard(Cards& cards);

    //displays all the cards obtained
    Cards getCards();

    //clear all cards
    void clearCard();

    //playing card
    void playHand(Cards& cards);

    void setPendingInfo(Player* player, Cards& cards);

    Player* getPendPlayer();

    Cards getpendCards();

    virtual void prepareCallLord();
    virtual void preparePlayHand();

protected:
    QString m_name;
    Sex m_sex;
    Type m_type;
    Direction m_direction;
    Role m_role;

    int m_score = 0;
    bool m_iswin = false;

    Player* m_prev = nullptr;
    Player* m_next = nullptr;
    Cards m_cards;

    Player* m_pendPlayer = nullptr;
    Cards m_pendCards;




signals:

};

#endif // PLAYER_H

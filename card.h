#ifndef CARD_H
#define CARD_H
#include <QVector>

class Card
{
public:
    //Suit enumeration
    enum CardSuit{
        Suit_Begin,
        Diamond,
        Club,
        Heart,
        Spade,
        Suit_End
    };
    //point enumeration
    enum CardPoint{
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,
        Card_BJ,
        Card_End,

    };
    void setSuit(CardSuit suit);
    void setPoint(CardPoint point);
    CardSuit getSuit()const;
    CardPoint getPoint()const;


    Card();
    Card(CardSuit suit,CardPoint point);
private:
    CardSuit m_Suit;
    CardPoint m_Point;

};

#endif // CARD_H

using CardList = QVector<Card>;
//Compare two objects for card sorting
bool lessSort(const Card& c1,const Card& c2);
bool greatSort(const Card& c1,const Card& c2 );

bool operator ==(const Card& c1,const Card& c2);
uint qHash(const Card& card);

bool operator<(const Card& c1,const Card& c2);

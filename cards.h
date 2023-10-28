#ifndef CARDS_H
#define CARDS_H
#include "card.h"

#include <QSet>

class Cards
{
public:
    enum SortType{Asc,Desc,NoSort};
    Cards();
    //add the playing cards
    void add(const Card& card);
    void add(const Cards& cards);

    //add multiple playing cards in a row
    Cards& operator <<(const Card& card);
    Cards& operator <<(const Cards& cards);

    //delete the playing cards
    void remove(const Card& card);
    void remove(const Cards& cards);

    //number of playing cards
    int getCardCount();

    //whether the number of playing cards is empty
    bool isEmpty();

    //clear the playing cards
    void clear();

    //maximum number of points
    Card::CardPoint getMaxPoint();

    //minimum number of points
    Card::CardPoint getMinPoint();

    //specifies the number of cards for points
    int getPointCount();

    //whether a card is in the set
    bool contains(const Card& card);
    bool contains(const Cards& cards);

    //a card is dealt randomly
    Card takeRandCard();

    CardList toCardList(SortType type = Desc);
private:
    QSet<Card> m_cards;
};

#endif // CARDS_H

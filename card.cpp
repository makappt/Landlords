#include "card.h"

void Card::setSuit(CardSuit suit)
{
    this->m_Suit = suit;
}

void Card::setPoint(CardPoint point)
{
    this->m_Point = point;
}

Card::CardSuit Card::getSuit() const
{
    return this->m_Suit;
}

Card::CardPoint Card::getPoint() const
{
    return this->m_Point;
}

Card::Card()
{

}

Card::Card(CardSuit suit, CardPoint point)
{
    setPoint(point);
    setSuit(suit);
}

bool lessSort(const Card &c1, const Card & c2)
{
    if(c1.getPoint() == c2.getPoint()){
        return c1.getSuit() > c2.getSuit();
    }
    else{
        return c1.getPoint() > c2.getPoint();
    }
}

bool greatSort(const Card &c1, const Card &c2)
{

    if(c1.getPoint() == c2.getPoint()){
        return c1.getSuit() < c2.getSuit();
    }
    else{
        return c1.getPoint() < c2.getPoint();
    }
}

bool operator ==(const Card& c1,const Card& c2){
    return (c1.getPoint() == c2.getPoint() && c1.getSuit() == c2.getSuit());
}

uint qHash(const Card& card){
    return card.getPoint()*100 + card.getSuit();
}
bool operator<(const Card& c1,const Card& c2)
{
    return lessSort(c1,c2);
}

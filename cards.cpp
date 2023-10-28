#include "cards.h"
#include <QRandomGenerator>

Cards::Cards()
{

}

void Cards::add(const Card &card)
{
    m_cards.insert(card);
}

void Cards::add(const Cards &cards)
{
    m_cards.unite(cards.m_cards);
}

void Cards::remove(const Card &card)
{
    m_cards.remove(card);
}

void Cards::remove(const Cards &cards)
{
    m_cards.subtract(cards.m_cards);
}


int Cards::getCardCount()
{
    return m_cards.size();
}

bool Cards::isEmpty()
{
    return m_cards.empty();
}

void Cards::clear()
{
    m_cards.clear();
}

Card::CardPoint Cards::getMaxPoint()
{
    Card::CardPoint max = Card::Card_Begin;
    for (auto value : m_cards) {
        if(value.getPoint() > max){
            max = value.getPoint();
        }
    }
    return max;
}

Card::CardPoint Cards::getMinPoint()
{
    Card::CardPoint min = Card::Card_End;
    for (auto value : m_cards) {
        if(value.getPoint() < min){
            min = value.getPoint();
        }
    }
    return min;
}

int Cards::getPointCount()
{
    return m_cards.size();
}

bool Cards::contains(const Card &card)
{
    return m_cards.contains(card);
}

bool Cards::contains(const Cards &cards)
{
    return m_cards.contains(cards.m_cards);
}

Card Cards::takeRandCard()
{
    int num = QRandomGenerator::global()->bounded(m_cards.size());
    QSet<Card>::const_iterator it = m_cards.constBegin();
    for(int i = 0; i < num; ++i,++it);
    Card card = *it;
    m_cards.erase(it);
    return card;
}

CardList Cards::toCardList(SortType type)
{
    CardList list;
    for (auto const& var : m_cards) {
        list.push_back(var);
    }

    if(type == Asc){
        std::sort(list.begin(),list.end(),lessSort);
    }
    else if(type == Desc){
        std::sort(list.begin(),list.end(),greatSort);
    }
    return list;
}


Cards &Cards::operator <<(const Card &card)
{
    add(card);
    return *this;
}

Cards &Cards::operator <<(const Cards &cards)
{
    add(cards);
    return *this;
}




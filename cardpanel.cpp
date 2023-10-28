#include "cardpanel.h"
#include <QPainter>
#include <QMouseEvent>
Cardpanel::Cardpanel(QWidget *parent): QWidget{parent}
{

}

void Cardpanel::setImage(QPixmap &front, QPixmap &back)
{
    m_front = front;
    m_back = back;

    setFixedSize(m_front.size());

    update();
}

QPixmap Cardpanel::getImage()
{
    return m_front;
}

void Cardpanel::paintEvent(QPaintEvent *event)
{
    //todo
    Q_UNUSED(event)
    QPainter p(this);
    if(m_isfront){
        p.drawPixmap(rect(),m_front);
    }
    else{
        p.drawPixmap(rect(),m_back);
    }
}

void Cardpanel::mousePressEvent(QMouseEvent *event)
{
    emit cardSelected(event->button());
}

void Cardpanel::setFrontside(bool flag)
{
    m_isfront = flag;
}

bool Cardpanel::isFrontside()
{
    return m_isfront;
}

void Cardpanel::setSelected(bool flag)
{
    m_isSelected = flag;
}

bool Cardpanel::isSeleted()
{
    return m_isSelected;
}

void Cardpanel::setCard(Card &card)
{
    m_card = card;
}

Card Cardpanel::getCard()
{
    return m_card;
}

void Cardpanel::setOwner(Player *player)
{
   m_owner = player;
}


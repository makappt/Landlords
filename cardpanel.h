#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include "card.h"
#include "player.h"

class Cardpanel : public QWidget
{
    Q_OBJECT
public:
    explicit Cardpanel(QWidget *parent = nullptr);
    //set the image function, QPiximap Used to load image information
    void setImage(QPixmap &front,QPixmap &back);
    QPixmap getImage();

    //the side of the playing card that is shown
    void setFrontside(bool flag);
    bool isFrontside();

    //Record whether the window is selected
    void setSelected(bool flag);
    bool isSeleted();

    //suits and points of playing cards
    void setCard(Card& card);
    Card getCard();

    //suits and points of playing cards
    void setOwner(Player* player);

protected:
    //paintEvent is used to Handle drawing events
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);

signals:
    void cardSelected(Qt::MouseButton button);

private:
    QPixmap m_front;
    QPixmap m_back;
    bool m_isfront = true;
    bool m_isSelected = false;
    Card m_card;
    Player* m_owner = nullptr;
};

#endif // CARDPANEL_H

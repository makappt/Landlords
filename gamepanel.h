#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "cardpanel.h"
#include <QMainWindow>
#include "gamecontral.h"
#include <QLabel>
#include <QMap>


QT_BEGIN_NAMESPACE
namespace Ui { class GamePanel; }
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

    void paintEvent(QPaintEvent *ev);
    void gameContralInit();
    void updatePlayerScore();
    void initCardMap();
    void cropImage(QPixmap& pix,int x,int y,Card& c);
    void initPlayerContext();
    void initButtons();
    void initGameScene();
    void startDispatchCard();

private:
    enum CardAlign{Horizontal,Vertical};
    struct PlayerContest{
        //玩家扑克牌显示区域
        QRect cardRect;
        //出牌区域
        QRect playHandRect;
        //扑克牌对齐方式（水平 or 垂直）
        CardAlign align;
        //扑克牌显示正面还是背面
        bool isFrontSide;
        //游戏过程中显示的提示信息
        QLabel* info;
        //玩家头像
        QLabel* roleImg;
        //玩家刚打出的牌
        Cards lastCards;
    };
    Ui::GamePanel *ui;
    QPixmap m_bkimage;
    GameContral* m_gameCtl = nullptr;
    QVector<Player*> m_playerList;
    QMap<Card, Cardpanel*> m_cardMap;
    QSize m_cardSize;
    QPixmap m_cardBackImg;
    QMap<Player*,PlayerContest> m_contextMap;
    Cardpanel* m_baseCard = nullptr;
    Cardpanel* m_moveCard = nullptr;
    QVector<Cardpanel*> m_last3Card;
    QPoint m_baseCardPos;

};
#endif // GAMEPANEL_H

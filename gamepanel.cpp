#include "gamepanel.h"
#include "ui_gamepanel.h"
#include <QRandomGenerator>
#include <QPainter>
GamePanel::GamePanel(QWidget *parent): QMainWindow(parent), ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    //背景图
    int num = QRandomGenerator::global()->bounded(10);
    QString path = QString(":/images/background-%1.png").arg(num+1);
    m_bkimage.load(path);
    //窗口标题的大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(1000, 650);

    //实例化游戏控制类对象
    gameContralInit();
    //更新玩家得分
    updatePlayerScore();
    //切割游戏图片
    initCardMap();

    //初始化游戏中的按钮
    initButtons();

    //初始化玩家在窗口中的上下文环境
    initPlayerContext();
    //扑克牌场景初始化
    initGameScene();




}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_bkimage);
}

void GamePanel::gameContralInit()
{
    m_gameCtl = new GameContral(this);
    m_gameCtl->playInit();
    //得到三个玩家的示例对象
    Robot* leftRobot = m_gameCtl->getLeftRobot();
    Robot* rightRobot = m_gameCtl->getRightRobot();
    UserPlayer* user = m_gameCtl->getUser();

    m_playerList << leftRobot << rightRobot << user;
}

void GamePanel::updatePlayerScore()
{   ui->s->setScore(m_playerList[0]->getScore(),
                    m_playerList[1]->getScore(),
                    m_playerList[2]->getScore());

}

/*
 *QPixmap QPixmap::copy(int x, int y, int width, int height) const
 *QPixmap::copy()函数从现有的QPixmap对象中提取一个矩形区域并返回它作为一个新的QPixmap对象。
 *这可以被认为是从大的图像中"裁切"出一个小的图像。
 *函数的参数定义了要复制的矩形区域：
 *x 和 y 定义了矩形的左上角的位置。
 *width 和 height 分别定义了矩形的宽度和高度。

*/

void GamePanel::initCardMap()
{
    //加载大图
    QPixmap pixmap(":/images/card.png");
    //计算每张图的大小
    m_cardSize.setWidth(pixmap.width() / 13);
    m_cardSize.setHeight(pixmap.height() / 5);
    //背景图
    m_cardBackImg = pixmap.copy(2*m_cardSize.width(), 4*m_cardSize.height(),
                                m_cardSize.width(), m_cardSize.height());
    //正常花色
    for (int i = 0,suit = Card::Suit_Begin+1; suit < Card::Suit_End; suit++,i++) {
        for(int j = 0, point = Card::Card_Begin+1; point < Card::Card_SJ; point++,j++){
            //得到卡牌点数
            Card card((Card::CardSuit)suit,(Card::CardPoint)point);
            cropImage(pixmap,j*m_cardSize.width(),i*m_cardSize.height(),card);
        }
    }
    //大小王
    Card c;
    c.setPoint(Card::Card_SJ);
    c.setSuit(Card::Suit_Begin);
    cropImage(pixmap,0,4*m_cardSize.height(),c);

    c.setPoint(Card::Card_BJ);
    cropImage(pixmap,m_cardSize.width(),4*m_cardSize.height(),c);

}

void GamePanel::cropImage(QPixmap &pix, int x, int y, Card& c)
{
    QPixmap sub = pix.copy(x, y, m_cardSize.width(), m_cardSize.height());
    Cardpanel* panel = new Cardpanel(this);
    panel->setImage(sub, m_cardBackImg);
    panel->setCard(c);
    panel->hide();
    m_cardMap.insert(c, panel);
}

void GamePanel::initPlayerContext()
{
    //放置玩家扑克牌的区域
    const QRect cardsRect[] =
        {
            QRect(90, 130, 100, height() - 200),                    //rightRobot
            QRect(rect().right() - 190, 130, 100, height() - 200),  //leftRobot
            QRect(250, rect().bottom() - 120, width() - 500, 100)   //user
        };
    //玩家出牌的区域
    const QRect playHandRect[] =
        {
            QRect(260, 150, 100, 100),
            QRect(rect().right() - 360, 150, 100, 100),
            QRect(150, rect().bottom() - 290, width() - 300, 105)
        };
    //玩家头像显示的区域
    const QPoint roleImgPos[] =
        {
            QPoint(cardsRect[0].left()-80, cardsRect[0].height() / 2 + 20),
            QPoint(cardsRect[1].right()+10, cardsRect[1].height() / 2 + 20),
            QPoint(cardsRect[2].right()-10, cardsRect[2].top() - 10)
        };

    //循环
    int index = m_playerList.indexOf(m_gameCtl->getUser());
    for(int i = 0; i < m_playerList.size(); ++i){
        PlayerContest context;
        context.align = i==index ? Horizontal : Vertical;
        context.isFrontSide = i == index ? true : false;
        context.cardRect = cardsRect[i];
        context.playHandRect = playHandRect[i];
        //提示信息
        context.info = new QLabel(this);
        context.info->resize(160,98);
        context.info->hide();

        //显示到出牌区域的中心位置
        QRect rect = playHandRect[i];
        QPoint pt(rect.left() + (rect.width() - context.info->width()),
                  rect.top() + (rect.height()-context.info->height())/2);
        context.info->move(pt);

        //玩家头像
        context.roleImg = new QLabel(this);
        context.roleImg->resize(84,120);
        context.roleImg->hide();
        context.roleImg->move(roleImgPos[i]);
        m_contextMap.insert(m_playerList.at(i),context);
    }


}

void GamePanel::initButtons()
{
    ui->btnGroup->initButtons();
    ui->btnGroup->selectPanel(ButtonGroup::Start);

    connect(ui->btnGroup,&ButtonGroup::startGame,this,[=](){

    });
    connect(ui->btnGroup,&ButtonGroup::playHand,this,[=](){

    });
    connect(ui->btnGroup,&ButtonGroup::pass,this,[=](){

    });
    connect(ui->btnGroup,&ButtonGroup::betPoint,this,[=](){

    });
}

void GamePanel::initGameScene()
{
    //发牌区的扑克牌
    m_baseCard = new Cardpanel(this);
    m_baseCard->setImage(m_cardBackImg,m_cardBackImg);

    //发牌过程中移动的扑克牌
    m_moveCard = new Cardpanel(this);
    m_moveCard->setImage(m_cardBackImg,m_cardBackImg);

    //最后三张底牌
    for(int i = 0; i < 3; i++){
        Cardpanel* panel = new Cardpanel(this);
        panel->setImage(m_cardBackImg,m_cardBackImg);
        m_last3Card.push_back(panel);
        panel->hide();
    }

    //扑克牌的位置
    m_baseCardPos = QPoint((width() - m_cardSize.width())/2,
                        (height() - m_cardSize.height())/2 - 100);
    m_baseCard->move(m_baseCardPos);
    m_moveCard->move(m_baseCardPos);

    int base = (width() - 3*m_cardSize.width() - 2*10)/2;

    for(int i = 0; i < 3; i++){
        m_last3Card[i]->move(base + (m_cardSize.width() + 10)*i,20);
    }

}

void GamePanel::startDispatchCard()
{
    //重置每张卡牌的属性
    for(auto it = m_cardMap.begin(); it!=m_cardMap.end();it++){
        it.value()->setSelected(false);
        it.value()->setFrontside(true);
    }
    //隐藏三张底牌

    //重置玩家的窗口上下文信息

    //重置所有玩家的卡牌数据

    //显示底牌

    //隐藏按钮面板

    //启动定时器

    //播放背景音乐
}


#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    enum Panel{Start,PlayCard,PassOrdPlay,CallLord,Empty};
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    //init button
    void initButtons();

    //handles page switching
    void selectPanel(Panel type);

signals:
    //start begin
    void startGame();

    //play handing
    void playHand();

    //pass
    void pass();

    //rob the landlord
    void betPoint(int bet);


private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTONGROUP_H

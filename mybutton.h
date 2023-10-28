#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>>
#include <QString>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

    void setImage(QString normal,QString hover,QString pressed);
protected:
    //override
    //mouse press
    void mousePressEvent(QMouseEvent* ev);
    //mouse release

    void mouseReleaseEvent(QMouseEvent* ev);

    //mouse remove
    void leaveEvent(QEvent* ev);

    //mouse enter
    void enterEvent(QEvent* ev);

    //pain
    void paintEvent(QPaintEvent* ev);

signals:

private:
    QString m_normal;
    QString m_hover;
    QString m_pressed;
    QPixmap m_pixmap;
};

#endif // MYBUTTON_H

#include "scorepanel.h"
#include "ui_scorepanel.h"

ScorePanel::ScorePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScorePanel)
{
    ui->setupUi(this);
}

void ScorePanel::setScore(int left,int right,int user)
{
    ui->leftScore->setText(QString::number(left));
    ui->rightScore->setText(QString::number(right));
    ui->myscore->setText(QString::number(user));
}

ScorePanel::~ScorePanel()
{
    delete ui;
}

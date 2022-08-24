#include "widget.h"
#include "ui_widget.h"
#include <QTabBar>
#include <stylehelper.h>
#include <QStyleOption>
#include <QFontDatabase>
#include <QGridLayout>
#include <time.h>


widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);
    addFonts();
    setInterfaceStyle();
    configGameAreaButtons();
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &widget::onComputerSlot);
}

widget::~widget()
{
    delete ui;
}

void widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void widget::setInterfaceStyle()
{
    this->setStyleSheet(StyleHelper::getMainWidgetStyle());

    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);

    ui->aboutButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
    ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonActiveStyle());
    ui->rightButton->setStyleSheet(StyleHelper::getRightButtonStyle());
    ui->tabWidget->setStyleSheet(StyleHelper::getTabWidgetStyle());
    ui->exitButton->setStyleSheet(StyleHelper::getStartButtonsStyle());

    ui->messageLabel->setText("");
    ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessageStyle());
    ui->aboutTextLabel->setStyleSheet(StyleHelper::getAboutTextStyle());

    setGameAreaButtonStyle();
}

void widget::changeButtonStatus(int index)
{
    if(index == 0)
    {
        ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonActiveStyle());
        ui->rightButton->setStyleSheet(StyleHelper::getRightButtonStyle());
    }
    else
    {
        ui->leftButton->setStyleSheet(StyleHelper::getLeftButtonStyle());
        ui->rightButton->setStyleSheet(StyleHelper::getRightButtonActiveStyle());
    }
}

void widget::addFonts()
{
    QFontDatabase::addApplicationFont(":/images/resourses/fonts/Roboto-Medium.ttf");
    QFontDatabase::addApplicationFont(":/images/resourses/fonts/Roboto-MediumItalic.ttf");
}

void widget::changeButtonStyle(const int row,const int column, QString style)
{
    QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
    QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(row,column)->widget());
    btn->setStyleSheet(style);
}

void widget::configGameAreaButtons()
{
    QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
    for(int row = 0; row<3; row++)
    {
        for(int column = 0; column<3;column++)
        {
            QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(row,column)->widget());
            btn->setProperty("row",row);
            btn->setProperty("column",column);
            connect(btn, &QPushButton::clicked,this, &widget::onGameAreaButtonClicked);
        }
    }
}

void widget::setGameAreaButtonStyle()
{
    QString style = StyleHelper::getBlankButtonStyle();
    for(int row = 0; row<3; row++)
    {
        for(int column = 0; column<3;column++)
        {
            changeButtonStyle(row,column,style);
        }
    }
}

void widget::start()
{
    setGameAreaButtonStyle();
    for(int row = 0; row<3; row++)
    {
        for(int column = 0; column<3;column++)
        {
            gameArea[row][column] = '-';
        }
    }
    progress = 0;
    gameStart = true;
    stop = false;
    if(player!='X')
        computerInGame();
}

void widget::lockPlayer()
{
    if(player == 'X')
    {
        playerLocked = false;
    }
    else
    {
        playerLocked = true;
    }
}


void widget::on_leftButton_clicked()
{
    changeButtonStatus(0);
    player = 'X';
}


void widget::on_rightButton_clicked()
{
    changeButtonStatus(1);
    player = '0';
}


void widget::on_startButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    if(gameStart)
    {
        playerLocked = true;
        ui->startButton->setText("Play");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
        ui->leftButton->setDisabled(false);
        ui->rightButton->setDisabled(false);
        gameStart = false;
        ui->messageLabel->setText("You Lost");
        ui->messageLabel->setStyleSheet(StyleHelper::getLostMessageStyle());
    }
    else
    {
        ui->messageLabel->setText("The game has begun!");
        ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessageStyle());
        start();
        lockPlayer();
        ui->startButton->setText("Surrender");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsGameStyle());
        ui->leftButton->setDisabled(true);
        ui->rightButton->setDisabled(true);

    }
}

void widget::onGameAreaButtonClicked()
{
    if(!playerLocked)
    {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int row = btn->property("row").toInt();
    int column = btn->property("column").toInt();
    QString style;
    if(player == 'X')
    {
        style = StyleHelper::getCrossNormalStyle();
        gameArea[row][column] = 'X';
    }
    else
    {
        style = StyleHelper::getZeroNormalStyle();
        gameArea[row][column] = '0';
    }
    changeButtonStyle(row,column,style);
    playerLocked = true;
    progress++;
    checkGameStop();
    endGame();
    computerInGame();
    }
}

void widget::computerInGame()
{
    if(stop)
        return;
    srand(time(NULL));
    int index = rand()%4;
    QStringList list = {"Wait, I'll think about it.","You can't win.","I calculate your every move","Hmmm..."};
    ui->messageLabel->setText(list.at(index));
    timer->start(2000);
}

void widget::computersMove(const int row,const int column, QString style, char comp)
{
    gameArea[row][column] = comp;
    changeButtonStyle(row,column,style);
    ui->messageLabel->setText("Your turn!");
    progress++;
    checkGameStop();
    endGame();
    playerLocked = false;
}

void widget::checkGameStop()
{
    winner = '-';
    char symbols[2] = {'X','0'};
    for (int i = 0; i < 2; i++)
    {
        for (int row = 0; row < 3; row++)
        {
            if((gameArea[row][0]==symbols[i])and(gameArea[row][1]==symbols[i])and(gameArea[row][2]==symbols[i]))
            {
                stop=true;
                winner = symbols[i];
                changeButtonStyle(row,0,changeButtonsWinnerStyle(winner));
                changeButtonStyle(row,1,changeButtonsWinnerStyle(winner));
                changeButtonStyle(row,2,changeButtonsWinnerStyle(winner));
                return;
            }
        }
        for(int col=0;col<3;col++)
        {
            if((gameArea[0][col]==symbols[i])and(gameArea[1][col]==symbols[i])and(gameArea[2][col]==symbols[i]))
            {
                stop=true;
                winner = symbols[i];
                changeButtonStyle(0,col,changeButtonsWinnerStyle(winner));
                changeButtonStyle(1,col,changeButtonsWinnerStyle(winner));
                changeButtonStyle(2,col,changeButtonsWinnerStyle(winner));
                return;
            }
        }
        if((gameArea[0][0]==symbols[i])and(gameArea[1][1]==symbols[i])and(gameArea[2][2]==symbols[i]))
        {
            stop=true;
            winner = symbols[i];
            changeButtonStyle(0,0,changeButtonsWinnerStyle(winner));
            changeButtonStyle(1,1,changeButtonsWinnerStyle(winner));
            changeButtonStyle(2,2,changeButtonsWinnerStyle(winner));
            return;
        }
        if((gameArea[0][2]==symbols[i])and(gameArea[1][1]==symbols[i])and(gameArea[2][0]==symbols[i]))
        {
            stop=true;
            winner = symbols[i];
            changeButtonStyle(0,2,changeButtonsWinnerStyle(winner));
            changeButtonStyle(1,1,changeButtonsWinnerStyle(winner));
            changeButtonStyle(2,0,changeButtonsWinnerStyle(winner));
            return;
        }
    }
    if (progress==9)
    {
        stop=true;
    }
}

void widget::endGame()
{

    if(stop)
    {
        if(winner == player)
        {
            ui->messageLabel->setText("You win!!!");
            ui->messageLabel->setStyleSheet(StyleHelper::getVictoryMessageStyle());
        }else if(winner=='-')
        {
            ui->messageLabel->setText("Draw");
            ui->messageLabel->setStyleSheet(StyleHelper::getNormalMessageStyle());
        }
        else
        {
            ui->messageLabel->setText("You lost(((");
            ui->messageLabel->setStyleSheet(StyleHelper::getLostMessageStyle());
        }
        ui->startButton->setText("Play");
        ui->startButton->setStyleSheet(StyleHelper::getStartButtonsStyle());
        ui->leftButton->setDisabled(false);
        ui->rightButton->setDisabled(false);
        gameStart = false;
    }
}

QString widget::changeButtonsWinnerStyle(const char winner)
{
    QString style;
    if(winner==player)
    {
        if(player=='X')
        {
            style=StyleHelper::getCrossVictoryStyle();
        }
        else
        {
            style=StyleHelper::getZeroVictoryStyle();
        }
    }
    else
    {
        if (player == '0')
        {
            style=StyleHelper::getCrossLostStyle();
        }
        else
        {
            style=StyleHelper::getZeroLostStyle();
        }
    }
    return style;
}


void widget::onComputerSlot()
{
    char comp;
    QString style;
    if(player == 'X')
    {
        comp = '0';
        style = StyleHelper::getZeroNormalStyle();
    }
    else
    {
        comp = 'X';
        style = StyleHelper::getCrossNormalStyle();
    }
    timer->stop();
    while(true)
    {


        // Победный ход
        if((gameArea[0][0]==comp)and(gameArea[0][1]==comp)and(gameArea[0][2]=='-'))
        {
            computersMove(0,2,style,comp);
            break;

        }else if((gameArea[1][0]==comp)and(gameArea[1][1]==comp)and(gameArea[1][2]=='-')){
            computersMove(1,2,style,comp);
            break;

        }else if((gameArea[2][0]==comp)and(gameArea[2][1]==comp)and(gameArea[2][2]=='-')){
            computersMove(2,2,style,comp);
            break;

        }else if((gameArea[0][1]==comp)and(gameArea[0][2]==comp)and(gameArea[0][0]=='-')){
            computersMove(0,0,style,comp);
            break;

        }else if((gameArea[1][1]==comp)and(gameArea[1][2]==comp)and(gameArea[1][0]=='-')){
            computersMove(1,0,style,comp);
            break;

        }else if((gameArea[2][1]==comp)and(gameArea[2][2]==comp)and(gameArea[2][0]=='-')){
            computersMove(2,0,style,comp);
            break;

        }else if((gameArea[0][0]==comp)and(gameArea[1][0]==comp)and(gameArea[2][0]=='-')){
            computersMove(2,0,style,comp);
            break;

        }else if((gameArea[0][1]==comp)and(gameArea[1][1]==comp)and(gameArea[2][1]=='-')){
            computersMove(2,1,style,comp);
            break;

        }else if((gameArea[0][2]==comp)and(gameArea[1][2]==comp)and(gameArea[2][2]=='-')){
            computersMove(2,2,style,comp);
            break;

        }else if((gameArea[2][0]==comp)and(gameArea[1][0]==comp)and(gameArea[0][0]=='-')){
            computersMove(0,0,style,comp);
            break;

        }else if((gameArea[2][1]==comp)and(gameArea[1][1]==comp)and(gameArea[0][1]=='-')){
            computersMove(0,1,style,comp);
            break;

        }else if((gameArea[2][2]==comp)and(gameArea[1][2]==comp)and(gameArea[0][2]=='-')){
            computersMove(0,2,style,comp);
            break;

        }else if((gameArea[0][0]==comp)and(gameArea[1][1]==comp)and(gameArea[2][2]=='-')){
            computersMove(2,2,style,comp);
            break;

        }else if((gameArea[1][1]==comp)and(gameArea[2][2]==comp)and(gameArea[0][0]=='-')){
            computersMove(0,0,style,comp);
            break;

        }else if((gameArea[0][2]==comp)and(gameArea[1][1]==comp)and(gameArea[2][0]=='-')){
            computersMove(2,0,style,comp);
            break;

        }else if((gameArea[2][0]==comp)and(gameArea[1][1]==comp)and(gameArea[0][2]=='-')){
            computersMove(0,2,style,comp);
            break;

        }else if((gameArea[0][0]==comp)and(gameArea[0][2]==comp)and(gameArea[0][1]=='-')){
            computersMove(0,1,style,comp);
            break;

        }else if((gameArea[1][0]==comp)and(gameArea[1][2]==comp)and(gameArea[1][1]=='-')){
            computersMove(1,1,style,comp);
            break;

        }else if((gameArea[2][0]==comp)and(gameArea[2][2]==comp)and(gameArea[2][1]=='-')){
            computersMove(2,1,style,comp);
            break;

        }else if((gameArea[0][0]==comp)and(gameArea[2][0]==comp)and(gameArea[1][0]=='-')){
            computersMove(1,0,style,comp);
            break;

        }else if((gameArea[0][1]==comp)and(gameArea[2][1]==comp)and(gameArea[1][1]=='-')){
            computersMove(1,1,style,comp);
            break;

        }else if((gameArea[0][2]==comp)and(gameArea[2][2]==comp)and(gameArea[1][2]=='-')){
            computersMove(1,2,style,comp);
            break;

        }

        // Защитный ход
        if((gameArea[0][0]==player)and(gameArea[0][1]==player)and(gameArea[0][2]=='-'))
        {
            computersMove(0,2,style,comp);
            break;

        }else if((gameArea[1][0]==player)and(gameArea[1][1]==player)and(gameArea[1][2]=='-')){
            computersMove(1,2,style,comp);
            break;

        }else if((gameArea[2][0]==player)and(gameArea[2][1]==player)and(gameArea[2][2]=='-')){
            computersMove(2,2,style,comp);
            break;

        }else if((gameArea[0][1]==player)and(gameArea[0][2]==player)and(gameArea[0][0]=='-')){
            computersMove(0,0,style,comp);
            break;

        }else if((gameArea[1][1]==player)and(gameArea[1][2]==player)and(gameArea[1][0]=='-')){
            computersMove(1,0,style,comp);
            break;

        }else if((gameArea[2][1]==player)and(gameArea[2][2]==player)and(gameArea[2][0]=='-')){
            computersMove(2,0,style,comp);
            break;

        }else if((gameArea[0][0]==player)and(gameArea[1][0]==player)and(gameArea[2][0]=='-')){
            computersMove(2,0,style,comp);
            break;

        }else if((gameArea[0][1]==player)and(gameArea[1][1]==player)and(gameArea[2][1]=='-')){
            computersMove(2,1,style,comp);
            break;

        }else if((gameArea[0][2]==player)and(gameArea[1][2]==player)and(gameArea[2][2]=='-')){
            computersMove(2,2,style,comp);
            break;

        }else if((gameArea[2][0]==player)and(gameArea[1][0]==player)and(gameArea[0][0]=='-')){
            computersMove(0,0,style,comp);
            break;

        }else if((gameArea[2][1]==player)and(gameArea[1][1]==player)and(gameArea[0][1]=='-')){
            computersMove(0,1,style,comp);
            break;

        }else if((gameArea[2][2]==player)and(gameArea[1][2]==player)and(gameArea[0][2]=='-')){
            computersMove(0,2,style,comp);
            break;

        }else if((gameArea[0][0]==player)and(gameArea[1][1]==player)and(gameArea[2][2]=='-')){
            computersMove(2,2,style,comp);
            break;

        }else if((gameArea[1][1]==player)and(gameArea[2][2]==player)and(gameArea[0][0]=='-')){
            computersMove(0,0,style,comp);
            break;

        }else if((gameArea[0][2]==player)and(gameArea[1][1]==player)and(gameArea[2][0]=='-')){
            computersMove(2,0,style,comp);
            break;

        }else if((gameArea[2][0]==player)and(gameArea[1][1]==player)and(gameArea[0][2]=='-')){
            computersMove(0,2,style,comp);
            break;

        }else if((gameArea[0][0]==player)and(gameArea[0][2]==player)and(gameArea[0][1]=='-')){
            computersMove(0,1,style,comp);
            break;

        }else if((gameArea[1][0]==player)and(gameArea[1][2]==player)and(gameArea[1][1]=='-')){
            computersMove(1,1,style,comp);
            break;

        }else if((gameArea[2][0]==player)and(gameArea[2][2]==player)and(gameArea[2][1]=='-')){
            computersMove(2,1,style,comp);
            break;

        }else if((gameArea[0][0]==player)and(gameArea[2][0]==player)and(gameArea[1][0]=='-')){
            computersMove(1,0,style,comp);
            break;

        }else if((gameArea[0][1]==player)and(gameArea[2][1]==player)and(gameArea[1][1]=='-')){
            computersMove(1,1,style,comp);
            break;

        }else if((gameArea[0][2]==player)and(gameArea[2][2]==player)and(gameArea[1][2]=='-')){
            computersMove(1,2,style,comp);
            break;

        }

            // Сильная позиция:
            if(progress<6)
            {
                if(gameArea[1][1]=='-'){
                    computersMove(1,1,style,comp);
                    break;

                }else if(gameArea[0][0]=='-'){
                    computersMove(0,0,style,comp);
                    break;

                }else if(gameArea[0][2]=='-'){
                    computersMove(0,2,style,comp);
                    break;

                }else if(gameArea[2][2]=='-'){
                    computersMove(2,2,style,comp);
                    break;

                }else if(gameArea[2][0]=='-'){
                    computersMove(2,0,style,comp);
                    break;

                }
            }
            else
            {
                int row = rand()%3;
                int column = rand()%3;
                while(gameArea[row][column]!='-')
                {
                    row = rand()%3;
                    column = rand()%3;
                }
                if(gameArea[row][column]=='-')
                {
                computersMove(row,column,style,comp);
                break;
                }
            }
        }
}


void widget::on_aboutButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void widget::on_exitButton_clicked()
{
    qApp->exit();
}


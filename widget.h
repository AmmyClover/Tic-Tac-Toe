#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_leftButton_clicked();
    void on_rightButton_clicked();
    void on_startButton_clicked();
    void onGameAreaButtonClicked();
    void onComputerSlot();
    void on_aboutButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::widget *ui;

    void setInterfaceStyle();
    void changeButtonStatus(int index);
    void addFonts();
    void changeButtonStyle(const int row,const int column, QString style);
    void configGameAreaButtons();
    void setGameAreaButtonStyle();
    void start();
    void lockPlayer();
    void computerInGame();
    void computersMove(const int row,const int column, QString style, char comp);
    void checkGameStop();
    void endGame();

    QString changeButtonsWinnerStyle(const char winner);

    char gameArea[3][3] =
    {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}
    };
    char player = 'X';
    int progress = 0;
    bool gameStart = false;
    bool playerLocked = true;
    bool stop;
    char winner;
    QTimer *timer;
};
#endif // WIDGET_H

#include "stylehelper.h"

QString StyleHelper::getMainWidgetStyle()
{
    return "QWidget{background-image: url(:/images/resourses/images/bg.png);}";
}

QString StyleHelper::getLeftButtonStyle()
{
    return "QPushButton{"
            "background-color: qlineargradient(spread:reflect, x1:0.522472, y1:0.658, x2:0.533708, y2:0, stop:0.241573 rgba(134, 108, 255, 255), stop:1 rgba(118, 108, 255, 255));"
            "background-image: url(:/images/resourses/images/cross_small.png);"
            "background-repeat:no-repeat;"
            "background-position: center center;"
            "border: 1px solid #333;"
            "border-top-left-radius:5px;"
            "border-bottom-left-radius:5px;"
            "}"
            "QPushButton::hover{background-color: qlineargradient(spread:reflect, x1:0.522472, y1:0.658, x2:0.533708, y2:0, stop:0.241573 rgba(175, 158, 255, 255), stop:1 rgba(114, 104, 255, 255));}";
}

QString StyleHelper::getRightButtonStyle()
{
    return "QPushButton{"
            "background-color: qlineargradient(spread:reflect, x1:0.522472, y1:0.658, x2:0.533708, y2:0, stop:0.241573 rgba(134, 108, 255, 255), stop:1 rgba(118, 108, 255, 255));"
            "background-image: url(:/images/resourses/images/zero_small.png);"
            "background-repeat:no-repeat;"
            "background-position: center center;"
            "border: 1px solid #333;"
            "border-left: none;"
            "border-top-right-radius:5px;"
            "border-bottom-right-radius:5px;"
            "}"
            "QPushButton::hover{background-color: qlineargradient(spread:reflect, x1:0.522472, y1:0.658, x2:0.533708, y2:0, stop:0.241573 rgba(175, 158, 255, 255), stop:1 rgba(114, 104, 255, 255));}";
}

QString StyleHelper::getLeftButtonActiveStyle()
{
    return "QPushButton{"
            "background-color: rgb(32, 28, 65);"
            "background-image: url(:/images/resourses/images/cross_small.png);"
            "background-repeat:no-repeat;"
            "background-position: center center;"
            "border: 1px solid #333;"
            "border-top-left-radius:5px;"
            "border-bottom-left-radius:5px;"
            "}";
}

QString StyleHelper::getRightButtonActiveStyle()
{
    return "QPushButton{"
            "background-color: rgb(32, 28, 65);"
            "background-image: url(:/images/resourses/images/zero_small.png);"
            "background-repeat:no-repeat;"
            "background-position: center center;"
            "border: 1px solid #333;"
            "border-left: none;"
            "border-top-right-radius:5px;"
            "border-bottom-right-radius:5px;"
           "}";
}

QString StyleHelper::getTabWidgetStyle()
{
    return "QTabWidget{"
            "border:none;"
            "}"
            "QTabWidget::pane{"
           "border:5px solid #222;"
           "border-radius:5px;"
           "}"
           "QWidget#tab{background:none;background-color: rgb(32, 28, 65);}";
}

QString StyleHelper::getBlankButtonStyle()
{
    return "QPushButton{"
           "border:none;"
           "background:#302b63;"
           "}"
           "QPushButton::hover{"
           "background:qlineargradient(spread:pad, x1:0, y1:0, x2:0.758427, y2:0.676, stop:0 rgba(48, 43, 99, 255), stop:1 rgba(65, 58, 134, 255));"
           "}";
}

QString StyleHelper::getCrossNormalStyle()
{
    return "QPushButton{"
           "border:none;"
           "background:#302b63 url(:/images/resourses/images/cross_large.png) no-repeat center center;"
           "}"
           "QPushButton::hover{"
           "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0.758427, y2:0.676, stop:0 rgba(48, 43, 99, 255), stop:1 rgba(65, 58, 134, 255));"
           "}";
}

QString StyleHelper::getCrossVictoryStyle()
{
    return "QPushButton{"
           "border:none;"
           "background:#1bcc65 url(:/images/resourses/images/cross_large.png) no-repeat center center;"
           "}";
}

QString StyleHelper::getCrossLostStyle()
{
    return "QPushButton{"
           "border:none;"
           "background:#a53146 url(:/images/resourses/images/cross_large.png) no-repeat center center;"
           "}";
}

QString StyleHelper::getZeroNormalStyle()
{
    return "QPushButton{"
           "border:none;"
           "background:#302b63 url(:/images/resourses/images/zero_large.png) no-repeat center center;"
           "}"
           "QPushButton::hover{"
           "background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0.758427, y2:0.676, stop:0 rgba(48, 43, 99, 255), stop:1 rgba(65, 58, 134, 255));"
           "}";
}

QString StyleHelper::getZeroVictoryStyle()
{
    return "QPushButton{"
           "border:none;"
           "background:#1bcc65 url(:/images/resourses/images/zero_large.png) no-repeat center center;"
           "}";
}

QString StyleHelper::getZeroLostStyle()
{
    return "QPushButton{"
           "border:none;"
           "background:#a53146 url(:/images/resourses/images/zero_large.png) no-repeat center center;"
           "}";
}

QString StyleHelper::getNormalMessageStyle()
{
    return "QLabel {"
           "font-family:'Roboto Medium';"
           "font-size:16px;"
           "background:none;"
           "color:#ffffff;"
           "}";
}

QString StyleHelper::getVictoryMessageStyle()
{
    return "QLabel {"
           "font-family:'Roboto Medium';"
           "font-size:16px;"
           "background:#1bcc65;"
           "border:4px solid #1bcc65;"
           "border-radius:4px;"
           "color:#ffffff;"
           "}";
}

QString StyleHelper::getLostMessageStyle()
{
    return "QLabel {"
           "font-family:'Roboto Medium';"
           "font-size:16px;"
           "background:#a53146;"
           "border:4px solid #a53146;"
           "border-radius:4px;"
           "color:#ffffff;"
           "}";
}

QString StyleHelper::getAboutTextStyle()
{
    return     "QLabel {"
               "font-family:'Roboto Medium';"
               "font-size:16px;"
               "color:#ffffff;"
               "font-size:italic;"
               "}";
}


QString StyleHelper::getStartButtonsStyle()
{
    return "QPushButton{"
           "color:#fff;"
           "background: none;"
           "border:none;"
           "border-radius:20px;"
           "background-color: qlineargradient(spread:reflect, x1:0.522472, y1:0.658, x2:0.533708, y2:0, stop:0.241573 rgba(134, 108, 255, 255), stop:1 rgba(118, 108, 255, 255));"
           "font-family: 'Roboto Medium';"
           "font-size:18px;"
           "}"
            "QPushButton::hover{background-color: qlineargradient(spread:reflect, x1:0.522472, y1:0.658, x2:0.533708, y2:0, stop:0.241573 rgba(175, 158, 255, 255), stop:1 rgba(114, 104, 255, 255));}"
           "QPushButton::pressed{background-color: qlineargradient(spread:reflect, x1:0.522472, y1:0.658, x2:0.533708, y2:0, stop:0.241573 rgba(105, 85, 201, 255), stop:1 rgba(77, 71, 167, 255));}";
}

QString StyleHelper::getStartButtonsGameStyle()
{
    return "QPushButton{"
           "color:#fff;"
           "background: none;"
           "border:none;"
           "border-radius:20px;"
           "background-color: qlineargradient(spread:reflect, x1:0.484, y1:0.5225, x2:0.471146, y2:0, stop:0 rgba(241, 72, 103, 255), stop:1 rgba(165, 49, 70, 255));"
           "font-family: 'Roboto Medium';"
           "font-size:18px;"
           "}"
            "QPushButton::hover{background-color: qlineargradient(spread:reflect, x1:0.484, y1:0.5225, x2:0.471146, y2:0, stop:0 rgba(255, 96, 133, 255), stop:0.966292 rgba(226, 67, 96, 255), stop:1 rgba(165, 49, 70, 255));}"
           "QPushButton::pressed{background-color: qlineargradient(spread:reflect, x1:0.484, y1:0.5225, x2:0.471146, y2:0, stop:0 rgba(165, 62, 86, 255), stop:0.97191 rgba(131, 39, 56, 255), stop:1 rgba(165, 49, 70, 255));}";
}


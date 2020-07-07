#ifndef FORMPHOTO_H
#define FORMPHOTO_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QtGui>
#include <QtCore>
#include <QRect>
#include <QStringList>
#include <QString>


namespace Ui {
class FormPhoto;
}

class FormPhoto : public QWidget
{
    Q_OBJECT
    
public:
    explicit FormPhoto(QWidget *parent = 0);
    ~FormPhoto();
    
private:
    Ui::FormPhoto *ui;
    QApplication* app;
    QStringList imageList;
    QString imageArrary[100];
    QTimer *timer;
    QTimer *timerfordelay;
    //QTimer *timerforfade;
    QRect clientRect;
    QPixmap imagePixmap;
    QPixmap *play;
    QPixmap *stop;
    bool isplaying;
    bool isgif[100];
    int imageNum;
    int currentNo;
    int width;
    int height;
    //float opacity;

private slots:
    void getImages(QString);
    void playImageSlot();
    void hasImages();
    void Init();
    //void fade_on_fade_in();
    void on_showbutton_clicked();
    void on_playorstop_clicked();
    void on_close_clicked();
};

#endif // FORMPHOTO_H

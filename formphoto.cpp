#include "formphoto.h"
#include "ui_formphoto.h"
#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <QDesktopWidget>
//#include <QGraphicsOpacityEffect>


FormPhoto::FormPhoto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPhoto)
{
    ui->setupUi(this);
    this->Init();
}
FormPhoto::~FormPhoto()
{
    delete ui;
}
void FormPhoto::Init()
{
    width = QApplication::desktop()->width();
    height = QApplication::desktop()->height();
    ui->scrollArea -> setFrameShape(QFrame::NoFrame);
    ui->scrollArea -> resize(width,height);
    ui->scrollArea -> setAlignment(Qt::AlignCenter);
    ui->imageLabel -> resize(width,height);
    ui->imageLabel -> setAlignment(Qt::AlignCenter);
    ui->showbutton -> setStyleSheet("QToolButton{background: transparent;}");
    ui->showbutton -> resize(width,height);
    ui->playorstop -> setGeometry(QRect(QPoint(width/2-25, height/2-25), QSize(50, 50)));
    ui->playorstop -> setStyleSheet("QToolButton{background: transparent;}");
    ui->playorstop -> setVisible(false);
    ui->close-> setGeometry(QRect(QPoint(width-70,5), QSize(30, 30)));
    ui->close -> setStyleSheet("QToolButton{background: transparent;}");
    ui->close -> setVisible(false);
    currentNo = 0;
    imageNum = 0;
    isplaying = true;
    imagePixmap.load(":/image/MainPage.jpg");
    imagePixmap = imagePixmap.scaled(width,height,Qt::IgnoreAspectRatio);
    ui->imageLabel->setPixmap(imagePixmap);
    timerfordelay=new QTimer;
    connect(timerfordelay,SIGNAL(timeout()),this,SLOT(hasImages()));
    timerfordelay->start(2000);
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(playImageSlot()));
    timer->start(5000);
    //timerforfade = new QTimer;
}
void FormPhoto::hasImages()
{
    timerfordelay->stop();
    this -> getImages("/udisk/image");
    if(!imageNum)
    {
        QMessageBox message(QMessageBox::Warning,NULL,"<font size='26' color='black'>U盘中无图片</font>", QMessageBox::Retry | QMessageBox::Cancel, NULL);
        message.setButtonText (QMessageBox::Retry,QString("重试"));
        message.setButtonText (QMessageBox::Cancel,QString("退出"));
        switch(message.exec()){
            case QMessageBox::Retry: this->hasImages();break;
            case QMessageBox::Cancel:  app->quit();break;
        }
    }
    else
        this -> playImageSlot();

}

void FormPhoto::playImageSlot()
{

    if(currentNo>=imageNum)
        currentNo=0;
    QString fileName=imageArrary[currentNo++];
    if(isgif[currentNo-1] == true){
        QMovie *movie = new QMovie(fileName);
        ui->imageLabel->setMovie(movie);
        movie->start();
     }
    else{
    imagePixmap.load(fileName);
    imagePixmap = imagePixmap.scaled(width,height,Qt::KeepAspectRatio);
    ui->imageLabel->setPixmap(imagePixmap);
    }
//    opacity=0;
//    this->fade_on_fade_in();
//    connect(timerforfade,SIGNAL(timeout()),this,SLOT(fade_on_fade_in()));
//    timerforfade->start(50);


}

void FormPhoto::getImages(QString _dir)
{
    QFileInfo dir(_dir);
    if(!dir.isDir()){
        QMessageBox message(QMessageBox::Warning,NULL,"<font size='26' color='black'>请插入U盘</font>", QMessageBox::Retry | QMessageBox::Cancel, NULL);
        message.setButtonText (QMessageBox::Retry,QString("重试"));
        message.setButtonText (QMessageBox::Cancel,QString("退出"));
        switch(message.exec()){
            case QMessageBox::Retry: this->getImages(_dir);break;
            case QMessageBox::Cancel:  app->quit();break;
        }
    }
    else{
        QDirIterator it(_dir,QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
        while (it.hasNext())//存在
        {
            QString name = it.next();//读取
            QFileInfo info(name);
            if (info.isDir())//判断是目录
            {
                this->getImages(name);//递归
            }
            else
            {
                if (info.suffix() == "jpg" || info.suffix() == "bmp" || info.suffix() == "png" || info.suffix() == "gif" || info.suffix() == "jpeg")
                {
                    if(info.suffix()=="gif")
                        isgif[imageNum] = true;
                    else
                        isgif[imageNum] = false;
                    imageArrary[imageNum++]=name;//符合添加
                }
            }
        }
     }
}
void FormPhoto::on_showbutton_clicked()
{
    if(ui->playorstop->isHidden()){
        ui->playorstop->setVisible(true);
        ui->close->setVisible(true);
       }
    else{
        ui->playorstop->setVisible(false);
        ui->close->setVisible(false);
        }
}

void FormPhoto::on_playorstop_clicked()
{
    if(isplaying){
        this->timer->stop();
        isplaying = false;
        ui->playorstop->setIcon(QPixmap(":/image/play.png"));
    }
    else{
        this->timer->start(5000);
        isplaying = true;
        ui->playorstop->setIcon(QPixmap(":/image/stop.png"));
    }
}

void FormPhoto::on_close_clicked()
{
    app->quit();
}
//void FormPhoto::fade_on_fade_in()
//{   if(opacity==1.0)
//    {
//        this->timerforfade->stop();//定时器停止
//    }
//    else
//    {
//        QGraphicsOpacityEffect *effect  = new QGraphicsOpacityEffect;;
//        effect->setOpacity(opacity);
//        ui->imageLabel->setGraphicsEffect(effect);

//    }
//    opacity+=0.01;//透明度累加
//}

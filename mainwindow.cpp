#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPalette>
#include <QCursor>
#include <QDateTime>

bool m_right;
QPoint mousepos;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    QPalette palette;
    palette.setBrush(QPalette::Base, Qt::transparent);
    ui->textEdit->setPalette(palette);
    ui->textEdit->setFrameStyle(0);
    QDateTime d1 = QDateTime::currentDateTime();
    ui->label_2->setText(d1.date().toString());
    //================================
    ui->textEdit->clear();
    QFile file("D:\\today.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            QMessageBox::information(0,"error",file.errorString());

        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull()) {
            process_line(line);
            line = in.readLine();
        }
    //================================
    this->setPalette(QPalette(QPalette::Base, Qt::transparent));
//    QMessageBox::information(0,"","Now here");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::process_line(const QByteArray & line)
{

}

void MainWindow::process_line(const QString & line)
{
    ui->textEdit->append(line);
}

void MainWindow::enterEvent(QEvent *event)
{
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
//    animation->setDuration(200);
//    animation->setStartValue(0.1);
//    animation->setEndValue(1);
}


void MainWindow::leaveEvent(QEvent *event)
{
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
//    animation->setDuration(200);
//    animation->setStartValue(1);
//    animation->setEndValue(0.1);
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_right && event->buttons() && Qt::RightButton)
    {
        move(event->globalPos() - mousepos);
        event->accept();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        m_right = true;
        mousepos = event->globalPos() - this->pos();
        event->accept();
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_right = false;
}

void MainWindow::on_toolButton_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1500);                          //Quit animation duration
    animation->setStartValue(this->windowOpacity());
    animation->setEndValue(0);
    connect(animation,SIGNAL(finished()),qApp,SLOT(quit()));
    animation->start();
}


void MainWindow::on_btfontm_clicked()
{
    QFont font = ui->textEdit->font();
    int size = font.pointSize();
    size -= 3;
    if(size > 1)
    {
        font.setPointSize(size);
        ui->textEdit->setFont(font);
    }
}



void MainWindow::on_btfontp_clicked()
{
    QFont font = ui->textEdit->font();
    int size = font.pointSize();
    size += 3;
    if(size < 150)
    {
        font.setPointSize(size);
        ui->textEdit->setFont(font);
    }
}

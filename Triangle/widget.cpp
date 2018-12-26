#include "widget.h"
#include "ui_widget.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <QVector>
#include "QPen"
#include <math.h>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle ( "Rotation XYZ" );

    scene = new QGraphicsScene(); // Инициализируем графические сцены
    scenexy = new QGraphicsScene();
    scenexz = new QGraphicsScene();
    sceneyz = new QGraphicsScene();

    triangle = new Triangle();
    trxy = new Triangle();
    trxz = new Triangle();
    tryz = new Triangle();

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->graphicsView_4->setScene(scenexy);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->graphicsView_3->setScene(scenexz);
    ui->graphicsView_3->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->graphicsView_2->setScene(sceneyz);
    ui->graphicsView_4->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(-250,-250,500,500); // Устанавливаем область графической сцены
    scenexy->setSceneRect(-250,-250,500,500);
    scenexz->setSceneRect(-250,-250,500,500);
    sceneyz->setSceneRect(-250,-250,500,500);

    print_post_Strelka(0,0,70,0);//стрелки на побочных сценах
    print_post_Strelka(0,0,0,-70);

    scene->addItem(triangle);   // Добавляем на сцену объект
    triangle->setPos(0,0);



    trxy->al=0;//отображаем объект на плоскости
    trxy->gamma=M_PI/2;

    trxz->al=0;
    trxz->alpha=M_PI/2;
    trxz->beta=0;
    trxz->gamma=0;

    tryz->al=0;
    tryz->alpha=M_PI/2;
    tryz->beta=0;
    tryz->gamma=M_PI/2;

    float o1=0,o2=0; // стрелки на главной сцене
    triangle->povorot(&triangle->ox,&o1,&o2,1.4,0,0.333);
    print_Strelka(0,0,triangle->ox,o1);

    o1=0,o2=0;
    triangle->povorot(&o1,&triangle->oy,&o2,1.4,0,0.333);
    print_Strelka(0,0,o1,triangle->oy);

    o1=0,o2=0;
    triangle->povorot(&o1,&o2,&(triangle->oz),1.4,0,0.333);
    print_Strelka(0,0,o1,o2);


    scenexy->addItem(trxy);
    trxy->setPos(0,0);
    scenexz->addItem(trxz);
    trxz->setPos(0,0);
    sceneyz->addItem(tryz);
    tryz->setPos(0,0);


    Xitem = new QGraphicsTextItem("X");//указываем названия осей координат
    Xitem->setPos(110, -5);
    scene->addItem(Xitem);

    Yitem = new QGraphicsTextItem("Y");
    Yitem->setPos(-80, 30);
    scene->addItem(Yitem);

    Zitem = new QGraphicsTextItem("Z");
    Zitem->setPos(-5, -110);
    scene->addItem(Zitem);



    X1 = new QGraphicsTextItem("X");
    X1->setPos(-15,-70);
    scenexy->addItem(X1);

    Y1 = new QGraphicsTextItem("Y");
    Y1->setPos(60, 0);
    scenexy->addItem(Y1);

    Z1 = new QGraphicsTextItem("Z");
    Z1->setPos(-15,-70);
    scenexz->addItem(Z1);

    X2 = new QGraphicsTextItem("X");
    X2->setPos(60, 0);
    scenexz->addItem(X2);

    Y2 = new QGraphicsTextItem("Y");
    Y2->setPos(60, 0);
    sceneyz->addItem(Y2);

    Z2 = new QGraphicsTextItem("Z");
    Z2->setPos(-15,-70);
    sceneyz->addItem(Z2);



    scene->update();
    scenexy->update();
    scenexz->update();
    sceneyz->update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

        QString textA = ui->textEdit->toPlainText(); //считываем углы поворота
        QString textB = ui->textEdit_2->toPlainText();
        QString textC = ui->textEdit_3->toPlainText();
        ui->label->setText(textA);
        string tA=textA.toUtf8().constData();
        string tB=textB.toUtf8().constData();
        string tC=textC.toUtf8().constData();
        float alpha=0;
        float beta=0;
        float gamma=0;

        if (tA!=""){
            alpha=stof(tA.c_str() );
        }

        if (tB!=""){
            beta=stof(tB.c_str() );
        }

        if (tC!=""){
            gamma=stof(tC.c_str() );
        }

        ui->label->setText(QString::number(alpha)+'  '+QString::number(beta)+'  '+QString::number(gamma));



        scene->removeItem(triangle);// перерисовываем объект с учётом поворота
        delete triangle;
        triangle = new Triangle();
        triangle->alpha=alpha;
        triangle->beta=beta;
        triangle->gamma=gamma;
        scene->addItem(triangle);
        triangle->setPos(0,0);

        scenexy->removeItem(trxy);
        delete trxy;
        trxy = new Triangle();
        trxy->al=0;
        trxy->alpha= alpha;
        trxy->beta=beta;
        trxy->gamma=M_PI/2 +gamma;
        scenexy->addItem(trxy);
        trxy->setPos(0,0);

        scenexz->removeItem(trxz);
        delete trxz;
        trxz = new Triangle();
        trxz->al=0;
        trxz->alpha=M_PI/2+alpha;
        trxz->beta=0+beta;
        trxz->gamma=0+gamma;
        scenexz->addItem(trxz);
        trxz->setPos(0,0);

        sceneyz->removeItem(tryz);
        delete tryz;
        tryz = new Triangle();
        tryz->zxcvb=1;
        tryz->al=0;
        tryz->alpha=-alpha;
        tryz->beta=beta;
        tryz->gamma=gamma;
        sceneyz->addItem(tryz);
        tryz->setPos(0,0);


        scene->update();
        scenexy->update();
        scenexz->update();
        sceneyz->update();
}

void Widget::print_post_Strelka(float x1, float y1, float x2, float y2)
{

    float x, y;
    float f1x2 , f1y2;
    float lons, ugol;

    const float ostr = 0.25;        // острота стрелки

    scenexy->addLine(x1, y1, x2, y2);
    scenexz->addLine(x1, y1, x2, y2);
    sceneyz->addLine(x1, y1, x2, y2);

    x = x2 - x1;
    y = y2 - y1;

    lons = sqrt(x*x + y*y) / 7;     // длина лепестков % от длины стрелки
    ugol = atan2(y, x);             // угол наклона линии

    //lons = 12;

    f1x2 = x2 - lons * cos(ugol - ostr);
    f1y2 = y2 - lons * sin(ugol - ostr);

    scenexy->addLine(x2, y2, f1x2, f1y2);
    scenexz->addLine(x2, y2, f1x2, f1y2);
    sceneyz->addLine(x2, y2, f1x2, f1y2);

    f1x2 = x2 - lons * cos(ugol + ostr);
    f1y2 = y2 - lons * sin(ugol + ostr);

    scenexy->addLine(x2, y2, f1x2, f1y2);
    scenexz->addLine(x2, y2, f1x2, f1y2);
    sceneyz->addLine(x2, y2, f1x2, f1y2);
}

void Widget::print_Strelka(float x1, float y1, float x2, float y2)
{

    float x, y;
    float f1x2 , f1y2;
    float lons, ugol;

    const float ostr = 0.25;        // острота стрелки

    scene->addLine(x1, y1, x2, y2);

    x = x2 - x1;
    y = y2 - y1;

    lons = sqrt(x*x + y*y) / 7;     // длина лепестков % от длины стрелки
    ugol = atan2(y, x);             // угол наклона линии

    //lons = 12;

    f1x2 = x2 - lons * cos(ugol - ostr);
    f1y2 = y2 - lons * sin(ugol - ostr);

    scene->addLine(x2, y2, f1x2, f1y2);

    f1x2 = x2 - lons * cos(ugol + ostr);
    f1y2 = y2 - lons * sin(ugol + ostr);

    scene->addLine(x2, y2, f1x2, f1y2);
}

void Widget::resizeEvent(QResizeEvent* e){
    scene->update();
    scenexy->update();
    scenexz->update();
    sceneyz->update();
}

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QGraphicsItem>
#include <QPainter>


// Наследуемся от QGraphicsItem
class Triangle : public QGraphicsItem
{
public:
    Triangle();
    ~Triangle();
    float x[4];
    float y[4];
    float z[4];

    float a=70;
    float b=50;

    float ox=110;
    float oy=200;
    float oz=90;

    float al=1;
    int zxcvb=0;
    int flag=0;

    float alpha=0;
    float beta=0;
    float gamma=0;

    void project(float*,float*,float*, float al);
    void povorot(float*,float*,float*, float alp,float bet,float gam);

protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:


};

#endif // TRIANGLE_H

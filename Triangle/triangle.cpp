#include <QVector>
#include <math.h>
#include "QPen"
#include "triangle.h"

Triangle::Triangle() :
    QGraphicsItem()
{

}

Triangle::~Triangle()
{

}

QRectF Triangle::boundingRect() const
{
    return QRectF(-100,-100,100,100);   // Ограничиваем область, в которой лежит объект
}




void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)//рисуем объект
{

    painter->setPen(QPen(Qt::red,Qt::SolidLine));

    if((al==0)&&(flag==0)){
        a=a/1.5;
        b=b/1.5;
        flag=1;
    }

     x[0]=a;
     x[1]=a;
     x[2]=-a;
     x[3]=-a;

     y[0]=b;
     y[1]=-b;
     y[2]=-b;
     y[3]=b;

     z[0]=0;
     z[1]=0;
     z[2]=0;
     z[3]=0;







        QPolygon quadr; //прямоугольник
        QVector<QPoint> qwe;

        for (int i = 0; i < 4; ++i) {

            if(zxcvb!=1){
                povorot(&x[i],&y[i],&z[i],alpha,beta,gamma);
                project(&x[i],&y[i],&z[i],al);
           qwe.push_back(QPoint(x[i],y[i]));
            }else{
                povorot(&x[i],&y[i],&z[i],alpha,beta,gamma);
                qwe.push_back(QPoint(y[i],z[i]));
            }
        }

        quadr << qwe;


        QPolygon elips;//элипс
        QVector<QPoint> asd;

        float amountSegments=100;
        for(float i=0; i<amountSegments; i++){
            float angle = (i * 2 * M_PI) / amountSegments;
            float x2=a*cos(angle);
            float y2=b*sin(angle);
            float z2=0;
            if(zxcvb!=1){
                povorot(&x2,&y2,&z2,alpha,beta,gamma);
                project(&x2,&y2,&z2,al);
                asd.push_back(QPoint(x2,y2));
            }else{
                povorot(&x2,&y2,&z2,alpha,beta,gamma);
                asd.push_back(QPoint(y2,z2));
            }
            }

        elips << asd;

        painter->drawPolygon(quadr);
        painter->drawPolygon(elips);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}

void Triangle::project(float *xq,float *yq,float *zq, float al){ // проекция на главную сцену

    float x1=*xq;
    float y1=*yq;
    float z1=*zq;

    *xq=x1*cos(float(al*0.333))-y1*sin(float(al*0.333));
    *yq=y1*cos(float(al*0.333))+x1*sin(float(al*0.333));

     x1=*xq;
     y1=*yq;
     z1=*zq;

    *yq=y1*cos(al*1.4)-z1*sin(al*1.4);
    *zq=z1*cos(al*1.4)+y1*sin(al*1.4);

}

void Triangle::povorot(float *xq,float *yq,float *zq, float alp,float bet,float gam){ //поворот на углы beta, gamma, alpha

    float x1=(*xq);
    float y1=*yq;
    float z1=*zq;

    *xq=x1*cos(bet)-z1*sin(bet);
    *zq=z1*cos(bet)+x1*sin(bet);

    x1=*xq;
    y1=*yq;
    z1=*zq;

    *xq=x1*cos(gam)-y1*sin(gam);
    *yq=y1*cos(gam)+x1*sin(gam);

    x1=*xq;
    y1=*yq;
    z1=*zq;

    *yq=y1*cos(alp)-z1*sin(alp);
    *zq=z1*cos(alp)+y1*sin(alp);
}

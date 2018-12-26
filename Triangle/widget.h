#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <string>
#include <triangle.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;// Объявляем графическую сцену
    QGraphicsScene  *scenexy;
    QGraphicsScene  *scenexz;
    QGraphicsScene  *sceneyz;
    QGraphicsTextItem *Xitem;
    QGraphicsTextItem *Yitem;
    QGraphicsTextItem *Zitem;
    QGraphicsTextItem *X1;
    QGraphicsTextItem *Y1;
    QGraphicsTextItem *Z1;
    QGraphicsTextItem *X2;
    QGraphicsTextItem *Y2;
    QGraphicsTextItem *Z2;
    Triangle        *triangle;  // и треугольник
    Triangle *trxy;
    Triangle *trxz;
    Triangle *tryz;
    void print_Strelka(float x1, float y1, float x2, float y2);
    void print_post_Strelka(float x1, float y1, float x2, float y2);
    void resizeEvent(QResizeEvent* e);
};

#endif // WIDGET_H

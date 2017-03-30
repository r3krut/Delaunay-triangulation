#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVector>
#include "delaunay_algo.h" //Delanay algo
#include <QDebug>
#include <QRect>
#include <QPainter>
#include <QPoint>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();
private:
    QVector<QPoint> points; //vector of points
    QRect boundRect() const;

    QPoint p_circ; //coordinates of point
    bool make_triangl; //

    void triangulate(QPainter &pntr); //in this method we make the Delanay trinagulate

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void paintCircle(QPainter& p);

public slots:
    void make_triangulate(); 
};

#endif // CANVAS_H

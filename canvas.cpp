#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    this->resize(800, 600);
    //this->setFixedSize(800, 600);

    make_triangl = false;
    p_circ.setX(0);
    p_circ.setY(0);
}

Canvas::~Canvas()
{

}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        p_circ.setX(event->pos().x());
        p_circ.setY(event->pos().y());
        points.push_back(p_circ);
    }
}

void Canvas :: paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.setPen(Qt::black);

    foreach (QPoint p, points)
        painter.drawEllipse(p, 7, 7);

    if (make_triangl)
    {
        triangulate(painter);
    }

    update();

    Q_UNUSED(event);
}

//for painting a circle
QRect Canvas :: boundRect() const
{
    return QRect(QPoint(0, 0), QPoint(10, 10));
}

void Canvas::paintCircle(QPainter &p)
{
    QRect br = boundRect();
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::red);
    p.drawEllipse(br);
}

void Canvas :: make_triangulate()
{
    make_triangl = true;
}

void Canvas ::triangulate(QPainter &pntr)
{
    pntr.setBrush(Qt::black);
    pntr.setPen(Qt::black);

    int n = points.size();

    Point pnts[n];

    for (int i = 0; i < n; i++)
    {
        pnts[i].x = points[i].x();
        pnts[i].y = points[i].y();
    }

    QLinkedList<Polygon*> triangles = Triangulation(pnts, n); //make the Delanay Triangulation 

    Polygon *triangle;

    QPoint p1;
    QPoint p2;

    foreach (triangle, triangles)
    {
        for (int i = 0; i < triangle->size(); i++)
        {
            Edge e = triangle->edge(); //get edge

            //set points
            p1.setX(e.org.x);
            p1.setY(e.org.y);
            p2.setX(e.dest.x);
            p2.setY(e.dest.y);

            pntr.drawLine(p1.x(), p1.y(), p2.x(), p2.y()); //draw line

            triangle->advance(CLOCKWISE);
        }
    }
}


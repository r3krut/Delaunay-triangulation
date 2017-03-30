#include "point.h"
#include "edge.h"
#include "math.h"

Point :: Point(double _x, double _y) : x(_x), y(_y)
{

}

const Point Point::operator+(const Point &p) const
{
    return Point(x + p.x, y + p.y);
}

const Point Point::operator-(const Point &p) const
{
    return Point(x - p.x, y - p.y);
}

//dot product
Point operator* (double s, const Point &p)
{
    return Point(s * p.x, s * p.y);
}

double Point::operator [](int i)
{
    return (i == 0) ? x : y;
}

//--------------Equals perations-----------------
int Point :: operator ==(Point &p)
{
    return (x == p.x) && (y == p.y);
}

int Point :: operator !=(Point &p)
{
    return !(*this == p);
}

int Point::operator< (Point &p)
{
    return ((x < p.x) || ((x == p.x) && (y < p.y)));
}

int Point::operator> (Point &p)
{
    return ((x > p.x) || ((x == p.x) && (y > p.y)));
}

//rotation of point around another point by angle
void Point :: rotate_point(const Point &p, double angle)
{
    double rad = (3.1415 * angle) / 180;

    double x_ = x;
    double y_ = y;

    x = p.x + (x_ - p.x)*cos(rad) - (y_ - p.y)*sin(rad);
    y = p.y + (x_ - p.x)*sin(rad) + (y_ - p.y)*cos(rad);
}

//classification of point 
int Point :: classify(Point &p0, Point &p1)
{
    Point p2 = *this;
    Point a = p1 - p0;
    Point b = p2 - p0;
    double sa = a.x * b.y - b.x * a.y;
    if (sa > 0.0)
        return LEFT;
    if (sa < 0.0)
        return RIGHT;
    if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
        return BEHIND;
    if (a.length() < b.length())
        return BEYOND;
    if (p0 == p2)
        return ORIGIN;
    if (p1 == p2)
        return DESTINATION;
    return BETWEEN;
}

//calssification for edge
int Point :: classify(Edge &e)
{
    return (this->classify(e.org, e.dest));
}

//polarity angle
double Point :: polarAngle(void)
{
    if (x == 0.0 && y == 0.0)
        return -1.0;

    if (x == 0.0)
        return (y > 0.0 ? 90 : 270);

    double theta = atan( y / x );                    // in radians

    theta *= 360 / (2 * 3.1415926);            // to degrees

    if (x > 0.0)                                 // 1 and 4 sectors
        return (y >= 0.0 ? theta : 360 + theta);
    else                                         // 2 and З sectors
        return (180 + theta);
}

double Point :: length(void)
{
    return sqrt(x * x + y * y);
}

void Point ::print_point() const
{
    qDebug() << "(" << x << ", " << y << ")";
}

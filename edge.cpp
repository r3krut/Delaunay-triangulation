#include "edge.h"

Edge :: Edge(const Point &_org, const Point &_dest) : org(_org), dest(_dest)
{

}

Edge :: Edge(void) : org(Point(0, 0)), dest(Point (1, 0))
{

}

Edge& Edge::rot(void)
{
    Point m = 0.5 * (org + dest);
    Point v = dest - org;
    Point n(v.y, -v.x); //normal in edge
    org = m - 0.5 * n;
    dest = m + 0.5 * n;
    return *this;
}

//changing direction of the edge on the reverse
Edge& Edge :: flip(void)
{
    return rot().rot();
}

//turn the edges by a specified angle around an arbitrary point
void Edge ::rotate_angle(const Point &p, double angle)
{
    org.rotate_point(p, angle);
    dest.rotate_point(p, angle);
}

//parametric p(t) = a + t(b - a) ( 0 <= t <= 1)
Point Edge :: point(double t)
{
    return Point(org + t * (dest - org));
}

//return value is a enum type
int Edge :: intersect(Edge &e, double &t)
{
    //num, denom
    Point a = org;
    Point b = dest;
    Point c = e.org;
    Point d = e.dest;
    Point n = Point ((d-c).y, (c-d).x); //nurmal
    double denom = dotProduct(n, b - a); //scalar product
    if (denom == 0.0)
    {
        int aclass = org.classify(e);
        if ((aclass == LEFT) || (aclass == RIGHT))
            return PARALLEL;
        else
            return COLLINEAR;
    }

    double num = dotProduct(n, a - c); //scalar product
    t = -num / denom; //t - corresponds to the intersection point
    return SKEW;
}

//aux function - scalar product
double dotProduct(const Point &p, const Point &q)
{
    return (p.x * q.x + p.y * q.y);
}

/**
 * returns the value of the SKEW_CROSS (tilted and intersect) if and only if the current line segment intersects the line segment E. 
 * If the segments of the straight lines intersect, it returns the parameter value t along this segment of 
 * the straight line corresponding to the crossing point. Otherwise the function returns one of the following appropriate values COLLINEAR  *  (collinear) ,
 * PARALLEL (parallel) or SKEW_NO_CROSS (tilted, but without crossing)
 * 
**/

int Edge :: cross(Edge &e, double &t)
{
    double s;
    int crossType = e.intersect(*this, s);
    if ((crossType == COLLINEAR) || (crossType == PARALLEL))
        return crossType;
    if ((s < 0.0) || (s > 1.0))
        return SKEW_NO_CROSS;
    intersect(e, t);
    if ((0.0 <= t) && (t <= 1.0))
        return SKEW_CROSS;
    else
        return SKEW_NO_CROSS;
}

Point Edge :: cross_point(Edge &e, double &t)
{
    cross(e, t);
    return point(t);
}

void Edge :: print_edge() const
{
    qDebug() << "(" << org.x << ";" << org.y << ") ---> (" << dest.x << ";" << dest.y << ")";
}

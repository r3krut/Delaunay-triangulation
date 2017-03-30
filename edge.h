#ifndef EDGE
#define EDGE

#include "point.h"

enum { COLLINEAR, PARALLEL, SKEW, SKEW_CROSS, SKEW_NO_CROSS };

class Edge
{
public:
    Point org; //left point - begining of the segment
    Point dest; //right point - end of the segment
    Edge (const Point &_org, const Point &_dest);
    Edge(void);
    Edge& rot(void); //rotate edge on 90 degree
    Edge& flip(void);
    void rotate_angle(const Point &p, double angle); //rotate edge by angle
    Point point(double);
    int intersect(Edge&, double&); //intersect edges
    int cross(Edge&, double&);
    Point cross_point(Edge &, double &); //point of intersect
    void print_edge() const;
};

double dotProduct(const Point &, const Point &); //scalar prod

#endif // EDGE


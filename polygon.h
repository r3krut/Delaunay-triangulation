#ifndef POLYGON_H
#define POLYGON_H

#include "node.h"
#include "point.h"

enum {CLOCKWISE, COUNTER_CLOCKWISE};

/**
 *  for classify. Where lies a point
 */
enum { INSIDE, OUTSIDE, BOUNDARY };

//for classify the edge
enum { TOUCHING, CROSSING, INESSENTIAL };

class Polygon;
class Edge;

class Vertex : public Node, public Point
{
public:
    Vertex(double x, double y);
    Vertex(const Point &p); //init by point
    Vertex *cw(); //neighbor clockwise
    Vertex *ccw(); //neighbor counter clockwise
    Vertex *neighbor(int rotation);
    Point& point (void);
    Vertex *insert (Vertex* ); //insert vertex
    Vertex *remove (void); //delete vertex(from Node class)
    void splice (Vertex*); //connect two verteces
    Vertex *split (Vertex*); //partition two verteces
    friend class Polygon;
};

class Polygon
{
private:
    Vertex *_v; //pointer to some vertex of the polygon(current)
    int _size; //size of polygone
    void resize(void);
public:
    Polygon(void);
    Polygon(Polygon &);
    Polygon(Vertex*);
    ~Polygon();
    Vertex* v(void); //returns current vertex
    int size(void);
    Point& point(void); //returns the point which is the current node
    Edge edge();
    Vertex *cw(void);
    Vertex *ccw(void);
    Vertex *neighbor(int rotation);
    Vertex *advance(int rotation); //move forward or backward depending on the rotation parameter
    Vertex *setV(Vertex*); //navigates to the specified vertex
    Vertex *insert(Point&);
    void remove(void);
    Polygon* split(Vertex*);
};

void print_polygon(Polygon &p);

//the method of ray-tracing(verification of identity point to the polygon)
int pointInPolygon(Point &a, Polygon &p);
int edgeType(Point &a, Edge &e); //type of edge

#endif // POLYGON_H


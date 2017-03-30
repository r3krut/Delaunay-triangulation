#include "polygon.h"
#include "edge.h"
#include <iostream>

using namespace std;

Vertex::Vertex(double x, double y) : Point(x, y)
{

}

Vertex::Vertex(const Point &p) : Point(p)
{

}

Vertex* Vertex::cw(void)
{
    return (Vertex*)_next;
}

Vertex* Vertex::ccw(void)
{
    return (Vertex*)_prev;
}

//if rotation == 0, then by clockwise, else counter clockwise
Vertex* Vertex::neighbor(int rotation)
{
    return ((rotation == CLOCKWISE) ? cw() : ccw());
}

//returns the point where the top of the vertex
Point& Vertex :: point(void)
{
    return *((Point*)this);
}

Vertex* Vertex :: insert(Vertex *v)
{
    return (Vertex*) (Node :: insert(v));
}

Vertex* Vertex :: remove(void)
{
    return (Vertex*)(Node::remove());
}

void Vertex :: splice(Vertex *b)
{
    Node :: splice(b);
}

/**
 * To cut the polygon along the chord AB, first be after vertex A its duplicate and duplicate the vertex B will make before top B 
 * (these  duplicates will call AP and BP). Then produce a separation of the peaks A and BP
 **/

Vertex *Vertex :: split(Vertex *b)
{
    //bp before b vertex
    Vertex *bp = b ->ccw()->insert(new Vertex(b->point()));
    insert(new Vertex(point())); //ap after current vertex

    splice(bp);
    return bp;
}


/** Polygon **/

Polygon :: Polygon(void) : _v( NULL ), _size(0)
{

}

//copy constructor(copies of the polygon p and just sets up the top of _v as the current from p)
Polygon :: Polygon(Polygon &p)
{
    _size = p._size;
    if (_size == 0)
        _v = NULL;
    else
    {
        _v = new Vertex( p.point() );
        for (int i = 1; i < _size; i++)
        {
            p.advance(CLOCKWISE);
            _v = _v -> insert(new Vertex(p.point()));
        }
        p.advance(CLOCKWISE);
        _v = _v -> cw();
    }
}

//init polygon with a ring biconnection list of verteces
Polygon :: Polygon(Vertex *v) : _v(v)
{
    resize(); //change size
}

void Polygon :: resize(void)
{
    if (_v == NULL)
        _size = 0;
    else
    {
        Vertex *v = _v->cw();
        for (_size = 1; v != _v; _size++, v = v->cw()); //advance to a _v
    }
}

//free of verteces of current poly
Polygon :: ~Polygon(void)
{
    if (_v)
    {
        Vertex *w = _v -> cw();
        while (_v != w)
        {
            delete w->remove();
            w = _v->cw();
        }
        delete _v;
    }
}

Vertex *Polygon :: v(void)
{
    return _v;
}

int Polygon :: size(void)
{
    return _size;
}

Point& Polygon :: point(void)
{
    return _v -> point();
}

//returns the edge which starts at the current vertex and ends at the next vertex
Edge Polygon :: edge(void)
{
    return Edge(point(), _v->cw()->point());
}

//do not change the current window position of the polygon
Vertex *Polygon :: cw(void)
{
    return _v ->cw();
}

Vertex *Polygon :: ccw(void)
{
    return _v -> ccw();
}

Vertex *Polygon :: neighbor(int rotation)
{
    return _v -> neighbor(rotation);
}

//edit functions
Vertex *Polygon ::advance(int rotation)
{
    return _v = _v ->neighbor(rotation);
}

Vertex *Polygon :: setV(Vertex *v)
{
    return _v = v;
}

//makes a new node after the current and then moves the window to a new peak
Vertex *Polygon::insert(Point &p)
{
    if (_size++ == 0)
        _v = new Vertex(p);
    else
        _v = _v->insert(new Vertex(p));
    return _v;
}


/**
 * The window is moved to the previous or remains uncertain, if the polygon is empty
 */

void Polygon::remove(void)
{
    Vertex *v = _v;
    _v = (--_size == 0) ? NULL : _v->ccw();
    delete v->remove();
}

/**
 * Component function Polygon::split cuts the current polygon along a chord,
 * connecting the current vertex with vertex B.
 * It returns a pointer to the new polygon window which is placed over the top of BP, which is the counterpart of the node B
 */

Polygon *Polygon :: split(Vertex *b)
{
    Vertex *bp = _v->split(b);
    resize();
    return new Polygon(bp);
}

void print_polygon(Polygon &p)
{
    for (int i = 0; i < p.size(); i++)
    {
        p.advance(CLOCKWISE);
        Edge e = p.edge();

        e.print_edge();
    }
}

int pointInPolygon(Point &a, Polygon &p)
{
    int par = 0;

    for (int i = 0; i < p.size(); i++)
    {
        p.advance(CLOCKWISE); //traverse all edges of polygon
        Edge e = p.edge();

        switch (edgeType(a, e))
        {
            case TOUCHING :
                return BOUNDARY; //on the edge
            case CROSSING :
                par = 1 - par;
        }
    }
    return (par ? INSIDE : OUTSIDE);
}

/**
 * classify the position of edges E relative to the horizontal beam,
 * directed to the right, returning the value of TOUCHING, CROSSING or 
 * INESSENTIAL (tangent crossing or indifferent) enumeration type
 **/

int edgeType(Point &a, Edge &e)
{
    /**
     * If point A lies to the left of the edge E, the edge is crossing if and only if vertex V the start of V(=E.ORG) 
     * lies below the beam UA,   and the top end w(=e.dest) located on the ray or lies above it. 
     * Then the edge cannot be horizontal and the  beam UA must intersect the edge at some point that 
     * differs from its lower end. If point A is to the right of the edge E,
     * the role of the end points V and W are mutually changed
     */

    Point v = e.org;
    Point w = e.dest;
    switch (a.classify(e))
    {
        case LEFT:
            return ((v.y < a.y) && (a.y <= w.y)) ? CROSSING : INESSENTIAL;
        case RIGHT:
            return ((w.y < a.y) && (a.y <= v.y)) ? CROSSING : INESSENTIAL;
        case BETWEEN:
        case ORIGIN:
        case DESTINATION:
            return TOUCHING;
        default:
            return INESSENTIAL;
    }
}

#include "delaunay_algo.h"
#include <algorithm>
#include <float.h>

QLinkedList<Polygon*> Triangulation(Point s[], int n)
{
    Point p;
    QLinkedList<Polygon* > triangles;
    Dictionary<Edge*> frontier(edgeCmp);
    Edge *e = hullEdge(s, n);
    frontier.insert(e);

    while (!frontier.isEmpty()) //while not empty
    {
        e = frontier.removeMin();
        if (mate(*e, s, n, p))
        {
            updateFrontier(frontier, p, e->org);
            updateFrontier(frontier, e->dest, p);
            triangles.push_back(triangle(e->org, e->dest, p)); //add a trinagle
        }
        delete e;
    }

    return triangles;
}

int edgeCmp(Edge *a, Edge *b)
{
    if (a->org < b->org) return -1;
    if (a->org > b->org) return 1;
    if (a->dest < b->dest) return -1;
    if (a->dest > b->dest) return 1;
    return 0;
}


void updateFrontier(Dictionary<Edge*> &fr, Point &a, Point &b)
{
    Edge *e = new Edge (a, b);
    if ( fr.find(e) )
        fr.remove(e);
    else
    {
        e->flip();
        fr.insert(e);
    }
}

Edge *hullEdge(Point s[], int n)
{
    int m = 0;
    for (int i = 1; i < n; i++)
        if (s[i] < s[m])
            m = i;
    swap(s[0], s[m]);
    m = 1;
    for (int i = 2; i < n; i++)
    {
        int c = s[i].classify(s[0], s[m]);
        if ( (c == LEFT) || (c == BETWEEN) )
            m = i;
    }
    return new Edge(s[0], s[m] );
}

Polygon* triangle (Point &a, Point &b, Point &c)
{
    Polygon *t = new Polygon;
    t->insert (a);
    t->insert (b);
    t->insert (c);
    return t;
}

bool mate(Edge &e, Point s[], int n, Point &p)
{
    Point *bestp = NULL;
    double  t, bestt = FLT_MAX;
    Edge f = e;
    f.rot();      // f - normal in the middle of line segment е
    for (int i = 0; i < n; i++)
        if (s[i].classify(e) == RIGHT)
        {
            Edge g(e.dest, s[i]);
            g.rot();
            f.intersect (g, t);
            if (t < bestt)
            {
                bestp = &s[i];
                bestt = t;
            }
        }
    if (bestp)
    {
        p = *bestp;
        return true;
    }
    return false;
}

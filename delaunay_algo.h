#ifndef DELAUNAY_ALGO
#define DELAUNAY_ALGO

#include "randomized_node.h"
#include <edge.h>
#include <point.h>
#include <polygon.h>
#include <QLinkedList>

#define Dictionary RandomizedSearchTree //dictionary

/**
 * Delanay trinagulation.
 * input params - list of points , output params - list of trinagles in the trinagulation
 **/
QLinkedList<Polygon*> Triangulation(Point s[], int n);

//Comparer. Compares a start point(a) and end point(b) of line segment.
int edgeCmp (Edge *a, Edge *b);

//update frontier
void updateFrontier(Dictionary<Edge*> &fr, Point &a, Point &b);

//detects edge of convex hull among n points in s array
Edge* hullEdge(Point s[], int n);

//form triangle from three points
Polygon* triangle(Point &a, Point &b, Point &c);

/**
 *  returns TRUE if the edge e has a conjugate point, and FALSE
 *  if no such point. If a conjugate point exists, it is returned
 *  using a reference parameter p
 * **/

bool mate(Edge &e, Point s[], int n, Point &p);

#endif // DELAUNAY_ALGO


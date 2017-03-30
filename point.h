#ifndef POINT
#define POINT

#include <QDebug>

enum POSITION{LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION };

class Edge;

class Point
{
public:
    double x;
    double y;

    Point(double _x = 0.0, double _y = 0.0);

    const Point operator+(const Point &) const;
    const Point operator-(const Point &) const;
    friend Point operator* (double, const Point &);

    //returns the x coordinate if index coordinates specified value, or the y-coordinate at index 1
    double operator[] (int);

    //Equals operations
    int operator==(Point &);
    int operator!=(Point &);
    int operator< (Point&);
    int operator> (Point&);

    //Returns the value of the enumeration type indicating the position of the point relative to the segment line
    // enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
    int classify(Point&, Point&);
    int classify(Edge &); 

    void rotate_point(const Point &p, double angle); //rotate point arount point p 

    //The angle of the point in polar coordinates returns -1 if the point = (0, 0)
    double polarAngle(void);
    double length(void);

    void print_point() const;
};

#endif // POINT


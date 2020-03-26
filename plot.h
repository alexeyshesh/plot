#ifndef PLOT_H
#define PLOT_H 

#include <string>
#include <iostream>
#include <cmath>

using namespace std;


class Plot {
protected:
    struct FuncList {
        double (*f)(double);
        string color;
        FuncList *next;
    };
    FuncList *fl;
    virtual string check(double x, double y) const = 0;
    double x_from, y_from, x_to, y_to, step;
public:

    static const string white;
    static const string red;
    static const string magenta;
    static const string blue;
    static const string green;
    static const string reset;

    Plot(double x_from = -10.0, double x_to = 10.0, double y_from = 10.0, double y_to = -10.0, double step = 0.25);
    Plot(const Plot &plt);
    virtual void print(ostream& os = cout) const;
    Plot& operator=(const Plot &plt);
    virtual void add(double (*f)(double), string color = white);
    virtual void clear();
    friend ostream& operator<<(ostream& os, const Plot& plt);
    ~Plot();
};

class RectPlot: public Plot {
public:
    string check(double x, double y) const;
};

class PolarPlot: public Plot {
    double arctan(double x);
public:
    string check(double x, double y) const;
};

#endif 
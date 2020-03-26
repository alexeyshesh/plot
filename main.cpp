#include <iostream>
#include "plot.h"

using namespace std;

double f(double x) {
    return 5;
}

double g(double x) {
    return x;
}

double h(double x) {
    return 3*sin(x);
}

int main() {
    RectPlot plt;
    plt.add(g, Plot::red);
    plt.add(f, Plot::magenta);
    plt.add(h, Plot::blue);
    RectPlot plt1;
    plt1 = plt;
    cout << plt1;

    return 0;
}
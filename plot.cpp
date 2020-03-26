#include "plot.h"
#define pi 3.1415926

const string Plot::white = "\033[1;47m",
             Plot::red = "\033[1;41m",
             Plot::magenta = "\033[1;45m",
             Plot::blue = "\033[1;46m",
             Plot::green = "\033[1;42m",
             Plot::reset = "\033[0m";

Plot::Plot (double x_from, double x_to, double y_from, double y_to, double step) {
    this->x_from = x_from;
    this->y_from = y_from;
    this->x_to = x_to;
    this->y_to = y_to;
    this->step = step;
    this->fl = nullptr;
}

void Plot::add(double (*f)(double), string color) {
    if (fl) {
        FuncList *q = this->fl;
        while (q->next)
            q = q->next;
        q->next = new FuncList;
        q->next->f = f;
        q->next->color = color;
        q->next->next = nullptr;
    } else {
        this->fl = new FuncList;
        this->fl->f = f;
        this->fl->color = color;
        this->fl->next = nullptr;
    }
}

Plot& Plot::operator= (const Plot& plt) {
    x_from = plt.x_from;
    x_to = plt.x_to;
    y_from = plt.y_from;
    y_to = plt.y_to;
    step = plt.step;

    this->clear();

   FuncList *pfl = plt.fl, *tfl;
    if (!pfl) {
        this->fl = nullptr;
    } else {
        while (pfl) {
            if (!this->fl) {
                this->fl = new FuncList;
                this->fl->f = pfl->f;
                this->fl->color = pfl->color;
                this->fl->next = nullptr;
                tfl = this->fl;
            } else {
                tfl->next = new FuncList;
                tfl->next->f = pfl->f;
                tfl->next->color = pfl->color;
                tfl->next->next = nullptr;
                tfl = tfl->next;
            }
            pfl = pfl->next;
        }
    }
    
    return *this;
}

Plot::Plot (const Plot &plt) {
    x_from = plt.x_from;
    x_to = plt.x_to;
    y_from = plt.y_from;
    y_to = plt.y_to;
    step = plt.step;
    this->fl = nullptr;

    FuncList *pfl = plt.fl, *tfl;
    if (!pfl) {
        this->fl = nullptr;
    } else {
        while (pfl) {
            if (!this->fl) {
                this->fl = new FuncList;
                this->fl->f = pfl->f;
                this->fl->color = pfl->color;
                this->fl->next = nullptr;
                tfl = this->fl;
            } else {
                tfl->next = new FuncList;
                tfl->next->f = pfl->f;
                tfl->next->color = pfl->color;
                tfl->next->next = nullptr;
                tfl = tfl->next;
            }
            pfl = pfl->next;
        }
    }
}

void Plot::clear() {
    FuncList *q = this->fl;
    while (q) {
        FuncList *tmp = q->next;
        delete q;
        q = tmp;
    }
    this->fl = nullptr;
}

string RectPlot::check(double x, double y) const {
    FuncList *q = this->fl;
    while (q) {
        if ((y < q->f(x) && q->f(x) <= y + step) || (y < q->f(x + step) && (q->f(x + step) <= y + step)))
            return q->color;
        q = q->next;
    }
    return "";
}

string PolarPlot::check(double x, double y) const {
    double phi = 0;
    if (x > 0 && y > 0) {
        phi = atan(y / x);
    } else if (y < 0 && x > 0) {
        phi = 1.5*pi+abs(atan(x / y));
    } else {
        phi = -pi - atan(y / x);
    }
    FuncList *q = this->fl;
    while (q) {
        if ((sqrt(x*x + y*y) <= abs(q->f(phi))) && (abs(q->f(phi)) <= sqrt((abs(x) + step)*(abs(x) + step) + (abs(y) + step)*(abs(y) + step)))) 
            return q->color;
        q = q->next;
    }
    return "";
}

double PolarPlot::arctan(double x) {
    return atan(x);

}

void Plot::print(ostream& os) const {
    for (double y = y_from; y >= y_to; y -= step) {
        for(double x = x_from; x <= x_to; x += step) {
            if (y == 0 || x == 0) {
                if (y == 0) {
                    if (x == floor(x)) {
                        os << abs(x) << '-';
                    } else {
                        os << "--";
                    }
                } else {
                    if (y == floor(y)) {
                        os << y << ' ';
                    } else {
                        os << "| ";
                    }
                }
            } else {
                os << check(x, y) << "  " << Plot::reset;
            }
            
        }
        os << endl;
    }
}

ostream& operator<<(ostream& os, const Plot& plt) {
    plt.print(os);
    return os;
}

Plot::~Plot() {
    this->clear();
}
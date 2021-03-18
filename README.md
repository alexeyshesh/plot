# plot

## Terminal plot builder library

### Features

- You can build plots in cartesian or polar coordinates coordinates
- You can use different colors for different plots
- You can draw several functions in one plot

### Usage

To create plot in cartesian coordinates:
```c++
RectPlot plt; 
```
To create plot in polar coordinates:
```c++
PolarPlot plt;
```
There is parameters like `from_x` and `to_x` for plots - check `plot.h` file.

To add function plot:
```c++
double h(double x) {
    return 3*sin(x);
}

// main:
plt.add(h, Plot::blue);
```

And to show plot in terminal:
```c++
cout << plt;
```

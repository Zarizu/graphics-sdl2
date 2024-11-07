#pragma once

struct Point {
    float x;
    float y;
};

struct Pixel {
    int x;
    int y;
};

struct Line {
    Point p1;
    Point p2;
};

struct Circle {
    Point p;
    int r;
};
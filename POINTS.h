#ifndef POINT_H
#define POINT_H
#include"COLORS.h"
struct Point {
    float x, y, z;
    color_t c;
    float size;
};

typedef struct Point point_t;
#endif
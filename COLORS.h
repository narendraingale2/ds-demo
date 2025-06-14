#ifndef COLOR_H
#define COLOR_H
struct color_combination
{
    float red;
    float green;
    float blue;
};

typedef struct color_combination color_t;

extern color_t green;
extern color_t white;
extern color_t orange;
extern color_t red;
extern color_t gray;
extern color_t blue;
extern color_t black;
extern color_t iaf_orange;
extern color_t iaf_green;
extern color_t canopy_gray;
extern color_t light_gray;

#endif
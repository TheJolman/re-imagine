#ifndef MAP_H
#define MAP_H

#include <raylib.h>
#include <tmx.h>

typedef struct
{
    int width;
    int height;
} Screen;

extern Screen screen;

void *raylib_tex_loader(const char *path);

void raylib_free_tex(void *ptr);

Color int_to_color(int color);

void render_map(tmx_map *map);

void draw_all_layers(tmx_map *map, tmx_layer *layers);

void draw_image_layer(tmx_image *image);

void draw_layer(tmx_map *map, tmx_layer *layer);

void draw_tile(void *image, unsigned sx, unsigned sy, unsigned sw, unsigned sh, unsigned dx,
               unsigned dy, float opacity, unsigned flags);

void draw_polyline(double offset_x, double offset_y, double **points, int points_count,
                   Color color);

void draw_polygon(double offset_x, double offset_y, double **points, int points_count, Color color);

void draw_objects(tmx_object_group *objgr);

#endif

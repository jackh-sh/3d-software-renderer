#pragma once

#include <SDL.h>
#include "lib/math.h"

class Application
{
public:
    Application();
    ~Application();

    void loop();
    void update(double delta_time);

    void drawPoint(Vector2 point);
    void drawLine(Vector2 a, Vector2 b);

private:
    SDL_Window *m_window;
    SDL_Renderer *m_window_renderer;
    SDL_Event m_window_event;
    int m_shape_x;
    int m_shape_y;
    int m_shape_width;
    int m_shape_height;
    int m_shape_x_direction;
    int m_shape_y_direction;
    int m_shape_velocity;

    float m_angle;
};

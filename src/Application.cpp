#include "Application.h"
#include <SDL_rect.h>
#include <cmath>
#include <iostream>
#include "constants.h"

Application::Application()
{
    m_window = SDL_CreateWindow("3D Scene",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                0);

    if (!m_window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    m_window_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_window_renderer)
    {
        std::cout << "Failed to get window's surface\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    SDL_RaiseWindow(m_window);

    m_shape_x = 20;
    m_shape_y = 20;
    m_shape_width = 50;
    m_shape_height = 50;

    m_angle = 0;
}

Application::~Application()
{
    SDL_DestroyRenderer(m_window_renderer);
    SDL_DestroyWindow(m_window);
}

void Application::loop()
{
    bool keep_window_open = true;
    while (keep_window_open)
    {
        while (SDL_PollEvent(&m_window_event) > 0)
        {
            switch (m_window_event.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;

            case SDL_KEYDOWN:
                switch (m_window_event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    keep_window_open = false;
                    break;
                }
            }
        }
        update(1.0 / 60.0);
    }
}

void Application::drawPoint(Vector2 point) {
    int size = 10;

    SDL_Rect rect = SDL_Rect{
        .h = size,
        .w = size,
        .x = static_cast<int>(point.x - size / 2),
        .y = static_cast<int>(point.y - size / 2)
    };

    SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_window_renderer, &rect);
}

void Application::update(double delta_time)
{
    SDL_RenderClear(m_window_renderer);

    m_angle += M_PI * delta_time;

    Vector3 vs[8] = {
        vec3( -0.25f, -0.25f, -0.25f ),
        vec3(  0.25f, -0.25f, -0.25f ),
        vec3(  0.25f,  0.25f, -0.25f ),
        vec3( -0.25f,  0.25f, -0.25f ),

        vec3( -0.25f, -0.25f,  0.25f ),
        vec3(  0.25f, -0.25f,  0.25f ),
        vec3(  0.25f,  0.25f,  0.25f ),
        vec3( -0.25f,  0.25f,  0.25f ),
    };

    for (const Vector3& v : vs) {
        auto proj = project(rotate_xz(v, m_angle));
        auto p = toScreen(proj);

        this->drawPoint(p);

    }

    this->drawPoint(toScreen(Vector2{
        .x= 0.0f,
        .y= 0.0f
    }));


    SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

    SDL_RenderPresent(m_window_renderer);
}

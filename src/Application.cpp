#include "Application.h"
#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 480

Application::Application()
{
    m_window = SDL_CreateWindow("Example Application",
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

    m_shape_x = 20;
    m_shape_y = 20;
    m_shape_width = 50;
    m_shape_height = 50;
    m_shape_velocity = 1;

    m_shape_x_direction = m_shape_velocity;
    m_shape_y_direction = m_shape_velocity;
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
        draw();
    }
}

void Application::update(double delta_time)
{
    if (m_shape_x > SCREEN_WIDTH - m_shape_width)
        m_shape_x_direction = -m_shape_velocity;

    if (m_shape_x < 0)
        m_shape_x_direction = m_shape_velocity;

    if (m_shape_y > SCREEN_HEIGHT - m_shape_height)
        m_shape_y_direction = -m_shape_velocity;

    if (m_shape_y < 0)
        m_shape_y_direction = m_shape_velocity;

    std::cout << "x: " << m_shape_x << " y: " << m_shape_y << "\n";

    m_shape_x += m_shape_x_direction;
    m_shape_y += m_shape_y_direction;
}

void Application::draw()
{
    SDL_RenderClear(m_window_renderer);

    SDL_Rect rect;
    rect.x = m_shape_x;
    rect.y = m_shape_y;
    rect.w = m_shape_width;
    rect.h = m_shape_height;

    SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_window_renderer, &rect);

    SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

    SDL_RenderPresent(m_window_renderer);
}
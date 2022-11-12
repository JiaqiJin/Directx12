#include "Application.h"

#include <vector>

#include "stb_image_write.h"
#include "stb_image_resize.h"

#include "Window.h"
#include "Timer.h"

namespace Kawaii
{
    Application::Application()
        : m_frame_time(0.0),
        m_fps(0),
        m_is_running(false)
    {
    }

    Application::~Application()
    {
    }

    void Application::init(unsigned int width, unsigned int height, const std::string& title, double framerate)
    {
        m_frame_time = 1.0 / framerate;

        /* Init window */
        Window::createWindow(width, height, title);

        init_app();
    }

    unsigned int Application::get_fps() const
    {
        return m_fps;
    }

    void Application::start()
    {
        if (m_is_running)
        {
            return;
        }

        run();
    }

    void Application::stop()
    {
        if (!m_is_running)
        {
            return;
        }

        m_is_running = false;
    }

    void Application::run()
    {
        m_is_running = true;

        int frames = 0;
        double frame_counter = 0.0;

        double last_time = Timer::getTime();
        double unprocessed_time = 0.0;

        double start_time = 0.0;
        double passed_time = 0.0;

        bool should_render = false;

        while (m_is_running)
        {
            should_render = false;

            start_time = Timer::getTime();
            passed_time = start_time - last_time;

            last_time = start_time;

            unprocessed_time += passed_time;
            frame_counter += passed_time;

            while (unprocessed_time > m_frame_time)
            {
                should_render = true;

                unprocessed_time -= m_frame_time;

                if (Window::isCloseRequested())
                {
                    m_is_running = false;
                }

                input();
                update(m_frame_time);

                if (frame_counter >= 1.0)
                {
                    m_fps = 1000.0 / (double)frames;

                    frames = 0;
                    frame_counter = 0;
                }
            }

            if (should_render)
            {
                /* Render */
                render();

                Window::endFrame();
                frames++;
            }
        }
    }
}
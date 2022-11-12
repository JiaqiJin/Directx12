#pragma once

#include "common.h"
#include <string>

namespace Kawaii
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        virtual void init(unsigned int width, unsigned int height, const std::string& title, double framerate = 60.0) final;

        virtual void init_app() = 0;
        virtual void input() = 0;
        virtual void update(double delta_time) = 0;
        virtual void render() = 0;

        uint32_t get_fps() const;

        virtual void start() final;
        virtual void stop()  final;

    private:
        void run();

        double   m_frame_time;
        uint32_t m_fps;
        bool     m_is_running;
    };
}
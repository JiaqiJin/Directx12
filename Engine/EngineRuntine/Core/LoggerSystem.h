#pragma once

#include "Singleton.h"

#include <spdlog/spdlog.h>

#include <cstdint>
#include <stdexcept>

namespace Kawaii
{
	class LogSystem final : public Singleton<LogSystem>
	{
	public:
        enum class LogLevel : uint8_t
        {
            KDEBUG,
            KINFO,
            KWARN,
            KERROR,
            KFATAL
        };

    public:
        LogSystem();
        ~LogSystem();

    private:
        std::shared_ptr<spdlog::logger> m_logger;
	};
}
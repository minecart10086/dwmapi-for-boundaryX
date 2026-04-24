#include <chrono>

#include <Helpers/Time.hpp>
#include <fmt/xchar.h>
#include <fmt/chrono.h>

#if _WIN32
#define NOMINMAX
#include <Windows.h>
#ifdef TEXT
#undef TEXT
#endif
#endif

namespace RC
{
    auto get_now_as_string(StringViewType format) -> StringType
    {
        bool use_local_time = true;
#ifdef _WIN32
        if (auto module = GetModuleHandleW(L"ntdll.dll"); module && GetProcAddress(module, "wine_get_version"))
        {
            use_local_time = false;
        }
#endif

        if (use_local_time)
        {
            try
            {
                static const auto timezone = std::chrono::current_zone();
                const auto now = std::chrono::time_point_cast<std::chrono::system_clock::duration>(timezone->to_local(std::chrono::system_clock::now()));
                return fmt::format(fmt::runtime(format), now);
            }
            catch (std::runtime_error&)
            {
                const auto now = std::chrono::system_clock::now();
                return fmt::format(fmt::runtime(format), now);
            }
        }
        else
        {
            const auto now = std::chrono::system_clock::now();
            return fmt::format(fmt::runtime(format), now);
        }
    }
} // namespace RC
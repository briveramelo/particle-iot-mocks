#pragma once

#include <type_traits>
#include <chrono>
#include <functional>

#if PLATFORM_ID!=3

#include "stddef.h"
typedef void* os_timer_t;

class Timer
{
public:

    typedef std::function<void(void)> timer_callback_fn;

    Timer(unsigned period, timer_callback_fn callback_, bool one_shot=false) : running(false), handle(nullptr), callback(std::move(callback_)) {
    }

    template <typename T>
    Timer(unsigned period, void (T::*handler)(), T& instance, bool one_shot=false) : Timer(period, std::bind(handler, &instance), one_shot)
    {
    }

    virtual ~Timer() {
        // when the timer is calling the std::function, we cannot dispose of it until the function completes.
        // the call has exited.
        dispose();
    }

    bool startFromISR() { return _start(0, true); }
    bool stopFromISR() { return _stop(0, true); }
    bool resetFromISR() { return _reset(0, true); }
    bool changePeriodFromISR(unsigned period) { return _changePeriod(period, 0, true); }
    inline bool changePeriodFromISR(std::chrono::milliseconds ms) { return changePeriodFromISR(ms.count()); }

    static const unsigned default_wait = 0x7FFFFFFF;

    bool start(unsigned block=default_wait) { return _start(block, false); }
    bool stop(unsigned block=default_wait) { return _stop(block, false); }
    bool reset(unsigned block=default_wait) { return _reset(block, false); }
    bool changePeriod(unsigned period, unsigned block=default_wait) { return _changePeriod(period, block, false); }
    inline bool changePeriod(std::chrono::milliseconds ms, unsigned block=default_wait) { return changePeriod(ms.count(), block); }

    bool isValid() const { return handle!=nullptr; }
    bool isActive() const { return false; }

    bool _start(unsigned block, bool fromISR=false)
    {
        return false;
    }

    bool _stop(unsigned block, bool fromISR=false)
    {
        return false;
    }

    bool _reset(unsigned block, bool fromISR=false)
    {
        return false;
    }

    bool _changePeriod(unsigned period, unsigned block, bool fromISR=false)
    {
        return false;
    }
    bool _changePeriod(std::chrono::milliseconds ms, unsigned block, bool fromISR=false) { return _changePeriod(ms.count(), block, fromISR); }

    void dispose()
    {
    }

    /*
     * Subclasses can either provide a callback function, or override
     * this timeout method.
     */
    virtual void timeout()
    {
        if (callback) {
            callback();
        }
    }

private:
    volatile bool running;
    os_timer_t handle;
    timer_callback_fn callback;
};

#endif // PLATFORM_ID!=3

#if (0 == PLATFORM_THREADING)
namespace particle
{
    class NullTimer
    {
    public:
        typedef std::function<void(void)> timer_callback_fn;

        NullTimer(unsigned, timer_callback_fn, bool)
        {
        }

        template <typename T>
        NullTimer(unsigned, void (T::*)(), T&, bool)
        {
        }

        inline static bool changePeriod(const size_t)
        {
            return true;
        }
        inline static bool changePeriod(const std::chrono::milliseconds ms) { return changePeriod(ms.count()); }

        inline static void dispose(void)
        {
        }
        inline static bool isActive(void)
        {
            return false;
        }
        inline static void reset(void)
        {
        }
        inline static void start(void)
        {
        }
        inline static void stop(void)
        {
        }
    };
} // namespace particle
#endif // not PLATFORM_THREADING

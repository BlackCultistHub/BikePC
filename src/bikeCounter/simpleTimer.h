#pragma once

#include <Arduino.h>

class simpleTimer
{
    public:
    simpleTimer(bool enable = false);
    void Start();
    void Stop();
    uint64_t getTime();
    void Reset();

    private:
    uint64_t start = 0;
    uint64_t stop = 0;
};

class simpleTimerDownTime
{
    public:
    simpleTimerDownTime(bool enable = false);
    void Start();
    void Stop();
    uint64_t getTime();
    void Reset();

    private:
    bool state = false;
    uint64_t start = 0;
    uint64_t stop = 0;
    uint64_t downTime = 0;
};

class simpleTimerCounter : private simpleTimer
{
    public:
    simpleTimerCounter();
    simpleTimerCounter(uint64_t& workTime_, bool enabled = false);

    void Run();
    void Run(uint64_t workTime_);
    bool Inc();
    bool Add(uint8_t pulses);
    int Get();
    bool Elapsed();
    bool Running();
    void Clear();

    private:
    uint64_t workTime = 0;
    uint16_t counter = 0;
};
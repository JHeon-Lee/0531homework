#pragma once
class Timer
{
};

class Stopwatch
{
public:
    Stopwatch();
    ~Stopwatch() = default;

    void Start();

    const float GetElapsedTimeSec();
    const float GetElapsedTimeMs();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};


#include "simpleTimer.h"

simpleTimer::simpleTimer(bool enable)
{
    if (enable)
        start = millis();
}
void simpleTimer::Start() 
{
    start = millis();
    stop = 0;
}
void simpleTimer::Stop() 
{ 
    stop = millis();
}
/*
 *@return Elapsed time in millis
 */
uint64_t simpleTimer::getTime() 
{
    if (stop == 0)
    {
       if (start == 0)
       {
           return 0;
       }
       else
       {
           return (millis() - start);
       }
    }
    else
    {
        return (uint64_t)(stop - start);
    }
    //return stop==0?(start==0?0:(millis()- start)):(stop - start);
}
void simpleTimer::Reset()
{
    start = 0;
    stop = 0;
}

//with downtime
simpleTimerDownTime::simpleTimerDownTime(bool enable):
state(enable)
{
    if (state)
        start = millis();
}
void simpleTimerDownTime::Start() 
{
    if (!state)
    {
        state = true;
        if (start == 0)
            start = millis();
        if (stop != 0)
            downTime += millis() - stop;
    }
}
void simpleTimerDownTime::Stop() 
{ 
    if (state)
    {
        state = false;
        stop = millis(); 
    }
}

/*
 *@return Elapsed time in millis
 */
uint64_t simpleTimerDownTime::getTime() 
{
    return stop==0?(start==0?0:(millis()- start)):(stop - start);
}

void simpleTimerDownTime::Reset() 
{
    state = false;
    start = 0;
    stop = 0;
    downTime = 0;
}

//counter
simpleTimerCounter::simpleTimerCounter()
{}
simpleTimerCounter::simpleTimerCounter(uint64_t& workTime_, bool enabled):
simpleTimer(enabled),
workTime(workTime_)
{}

void simpleTimerCounter::Run()
{
    if (!this->Running())
        this->Start();
}

void simpleTimerCounter::Run(uint64_t workTime_)
{
    if (!this->Running())
    {
        this->workTime = workTime_;
        this->Start();
    }
}

/*
 *@return 'false' if timeout
 */
bool simpleTimerCounter::Inc()
{
    if (this->getTime() < workTime)
    {
        counter++;
        return true;
    }
    else
        return false;
}

/*
 *@return 'false' if timeout
 */
bool simpleTimerCounter::Add(uint8_t pulses)
{
    if (this->getTime() < workTime)
    {
        counter += pulses;
        return true;
    }
    else
        return false;
}

/*
 *@return Number of counts
 */
int simpleTimerCounter::Get() 
{return counter;}

/*
 *@return 'true' if timeout
 */
bool simpleTimerCounter::Elapsed()
{
    if (this->getTime() > workTime)
        return true;
    else
        return false;
}

/*
 *@return 'true' if timer is running
 */
bool simpleTimerCounter::Running()
{
    if (this->getTime() == 0)
        return false;
    else
        return true;
}

void simpleTimerCounter::Clear()
{
    this->Reset();
    this->counter = 0;
    this->workTime = 0;
}
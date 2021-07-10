#include <iostream>
#include <ctime>
#include <chrono>
#include <Windows.h>
#include <thread> 



bool timerenabled = true;
int timerdelay = 25000; //ms
std::chrono::high_resolution_clock::time_point timer_start;//ms

bool trigger = false;
std::chrono::high_resolution_clock::time_point lastprint; //last print in ms

void inputlistener();
void mactimer();
void beeploop();

int main()
{
    std::thread inputlisten(inputlistener);
    std::thread timer(mactimer);
    std::thread beeper(beeploop);

    while (true)//loops for args
    {
        std::string input;
        std::cin >> input;

        if (input.find("delay"))
        {

        }
    }
}

void beeploop()
{
    while (true)
    {
        Sleep(50);
        if (trigger)
        {
            Beep(800, 200);
            Sleep(700);
        }
    }
}

void mactimer()
{
    while (true)
    {
        if (timerenabled)
        {
            auto timerstart_since_epoch_ns = timer_start.time_since_epoch();
            auto milliseconds_timerstart = std::chrono::duration_cast<std::chrono::milliseconds>(timerstart_since_epoch_ns);

            auto current_time_epoch_ns = std::chrono::high_resolution_clock::now().time_since_epoch();
            auto milliseconds_currenttime = std::chrono::duration_cast<std::chrono::milliseconds>(current_time_epoch_ns);


            if (milliseconds_timerstart.count() + timerdelay < milliseconds_currenttime.count()) //enemy mac is ready to fire!
            {
                trigger = true;
            }
            else
            {
                trigger = false;
            }
            auto lastprint_time = std::chrono::duration_cast<std::chrono::milliseconds>(lastprint.time_since_epoch());
            if (lastprint_time.count() + 1000 < milliseconds_currenttime.count())
            {
                lastprint = std::chrono::high_resolution_clock::now();

                int printer = milliseconds_currenttime.count() - milliseconds_timerstart.count();

                std::cout << printer / 1000 << "\n";
            }
            Sleep(10);
        }
    }
}

void inputlistener()//listens for input
{
    while (true)
    {
        Sleep(14);
        if (GetAsyncKeyState(VK_DOWN)) //toggle timer enabled/disabled
        {
            //std::cout << "ttt";

            if (timerenabled) //disable it
            {
                Beep(600, 100);
                Beep(400, 100);
                Beep(200, 100);
            }
            else
            {
                Beep(200, 100);
                Beep(400, 100);
                Beep(600, 100);
            }

            timerenabled = !timerenabled;
            while (GetAsyncKeyState(VK_DOWN))
                Sleep(50); //sleep function until keypress stops
        }
        if (GetAsyncKeyState(VK_UP)) //reset timer
        {
            timer_start = std::chrono::high_resolution_clock::now();
            //play reset sound sound
            Beep(500, 50);
            while (GetAsyncKeyState(VK_UP))
                Sleep(50); //sleep function until keypress stops
        }
    }



}



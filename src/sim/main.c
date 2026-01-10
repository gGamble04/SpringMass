/**
 * @file main.c
 * @brief Entry point for the Spring-Mass System Simulation.
 * @author Gabe G.
 * @date 1-9-2026
 */

#include "core/consts.h"
#include "sim.h"
#include "UI/ui.h"

int main() 
{
    // Initialization
    SimState sim;
    InitSim(&sim);
    SetTargetFPS(120);

    float time = 0.0f;

    // Simulation loop
    while (SimRunning(&sim))
    {   
        float dt = GetFrameTime(); // Delta time
        time += dt;
        UpdateSim(&sim, dt);
        DrawSim(&sim, time);
    }
    // Cleanup
    StopSim();
    return 0;
}
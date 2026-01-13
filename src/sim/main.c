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

    float elapsedTime = 0.0f; // Track total simulation time
    // float becomes imprecise after ~4.5 hours, so this is safe.
    // Double becomes imprecise after ~34,000 years, but lets be honest, no ones using this for more that 4 hours.

    // Simulation loop
    while (SimRunning(&sim))
    {   
        float dt = GetFrameTime(); // Delta time
        if (!sim.isPaused)
        {
            elapsedTime += dt; // Only update total elapsed time if not paused
        }
        UpdateSim(&sim, dt, elapsedTime);
        DrawSim(&sim, dt, elapsedTime);
    }
    // Cleanup
    StopSim();
    return 0;
}
/*************************************************************
 * @file sim.h                                               *
 * @brief Header file for the Spring-Mass System Simulation. *
 * @author Gabe G.                                           *
 * @date 1-9-2026                                            *
 *************************************************************/

#ifndef SIM_H
#define SIM_H

#include "core/physics.h"
#include "renderer/renderer.h"
#include <stdbool.h>

// Overall simulation state
typedef struct SimState
{
    SpringMassSystemState systemState; // Physical state of the spring-mass system
    SpringMassRenderState renderState; // Rendering state of the spring-mass system

    bool isRunning; // Simulation is currently running

    bool isPaused;    // Simulation is currently paused
    float pausedTime; // Time when paused (used to freeze graph)

    bool showSettings;    // Settings dialog is shown
    bool showThemeChange; // Theme change dialog is shown

    bool isDragging;       // Mass is currently being dragged
    float dragGrabOffsetX; // Horizontal offset from grab point during drag
} SimState;

// Simulation Function declarations
void InitSim(SimState *simulation, int windowWidth, int windowHeight, const char *title,
             int FPS);                               // Initialize simulation state
void UpdateSim(SimState *sim, float dt, float time); // Update simulation state based on elapsed time
void DrawSim(SimState *sim, float dt, float time);   // Draw current state of simulation
float CurrentFrameTime(void);                        // Get time taken to render current frame
bool SimRunning(const SimState *sim);                // Check if simulation is running
void StopSim(void);                                  // Stop the simulation

#endif
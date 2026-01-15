/**
 * @file sim.c
 * @brief Implementation of the Spring-Mass System Simulation.
 * @author Gabe G.
 * @date 1-13-2026
 */

#include "sim.h"
#include "../core/consts.h"
#include "UI/ui.h"
#include "renderer/graph.h"

// Forward declarations
static bool ClickInBoundingBox(Rectangle box);
static bool SimHandleDragging(SimState *sim);
static void SimResolveBounds(SimState *sim);
static void ShowUI(SimState *sim);

void InitSim(SimState *sim, int windowWidth, int windowHeight, const char *title)
{
    InitSystem(&sim->systemState);
    InitRender(&sim->renderState, windowWidth, windowHeight, title);
    InitGraph();
    sim->isRunning = true;
    sim->isPaused = false;
    sim->pausedTime = 0.0f;
    sim->showSettings = false;
    sim->showThemeChange = false;
    sim->isDragging = false;
    sim->dragGrabOffsetX = 0.0f;
}

void UpdateSim(SimState *sim, float dt, float time)
{
    if (EscKeyPressed()) 
    {
        // Toggle pause on ESC key
        sim->isPaused = !sim->isPaused;
    }
    if (!sim->isPaused && 
        !sim->showSettings && 
        !sim->showThemeChange)
    {
        // Only update physics when not paused or in a dialog
        if (!SimHandleDragging(sim)) 
        {
            SpringmassStep(&sim->systemState, dt);
        }
        SimResolveBounds(sim);
        sim->renderState.massRectangle.x = sim->systemState.x;
        UpdateGraph(sim->systemState.x - sim->systemState.equilibrium, time);
    }
}

void DrawSim(SimState *sim, float dt, float time)
{
    Render_BeginDrawing();
        Render_ClearBackground(SIM_BLACK); // Clear last frame
        DrawGraph(sim->systemState.x - sim->systemState.equilibrium, time, sim->renderState.themeColor);
        ShowUI(sim); // Draw UI
        UpdateRender(&sim->renderState); // Update render state based on system state
        
        float textPersistTime = 8.0f; // Time to show startup text before fading (seconds)
        float fadeTime = 2.0f; // Duration of fade-out animation (seconds)
        if (time <= textPersistTime)
        {
            ShowStartupText(&sim->renderState);
        }
        else if (textPersistTime < time && time <= textPersistTime + fadeTime)
        {
            // Only update fade-out animation when not paused
            ShowStartupTextFadeOut(&sim->renderState, sim->isPaused ? 0.0f : dt, fadeTime);
        }

        // Logic for handling dialogs
        if (sim->isPaused)
        {
            switch (ShowPauseDialog())
            {
                case 1: // Resume
                    sim->isPaused = false;
                    sim->showSettings = false;
                    sim->showThemeChange = false; 
                    break;
                case 2: // Open Settings
                    sim->showSettings = true;
                    sim->isPaused = false; // Ensure that pause and settings dialog aren't trying to draw in the same frame
                    break;
                case 3: // Exit
                    sim->isRunning = false;
                    break;
            }
        }
        else if (sim->showSettings)
        {
            switch (ShowSettings())
            {
                case 2:
                    sim->showThemeChange = true;
                    sim->showSettings = false;
            }
        }
        else if (sim->showThemeChange)
        {
            ShowThemeChange(&sim->renderState);
        }
        // End of dialog handling logic
    Render_EndDrawing();
}

// TODO: fix exit logic 
// TODO: would probably be cleaner if the exit button and the pause->exit button worked together
bool SimRunning(const SimState *sim)
{
    return ExitButtonClicked() && sim->isRunning;
}


void StopSim()
{
    DestroyRenderer();
}

/***************************************
 *      Internal helper functions      *
 ***************************************/


// Check if mouse click is in bounding box
static bool ClickInBoundingBox(Rectangle box)
{
    Vec2D mousePosition = GetMousePOS();
    if(mousePosition.x >= box.x && mousePosition.x <= box.x + box.width)
    {
        if(mousePosition.y >= box.y && mousePosition.y <= box.y + box.height)
        {
            return true;
        }
    }
    return false;
}

// Handle dragging logic; returns true if dragging is occurring
static bool SimHandleDragging(SimState *sim)
{
    if (!sim->isDragging) 
    {
        if (LeftMouseButtonPressed() && ClickInBoundingBox(sim->renderState.massRectangle)) 
        {
            Vec2D mousePosition = GetMousePOS();
            sim->isDragging = true;
            sim->dragGrabOffsetX = mousePosition.x - sim->systemState.x;
        } 
        else 
        {
            return false;
        }
    }
    if (LeftMouseButtonReleased()) 
    {
        sim->isDragging = false;
        sim->systemState.velocity = 0.0f;
        return true;
    }
    if (LeftMouseButtonDown()) 
    {
        Vec2D mousePosition = GetMousePOS();
        sim->systemState.x = mousePosition.x - sim->dragGrabOffsetX;
        sim->systemState.velocity = 0.0f;
        return true;
    }
    // Defensive: if somehow lost button state, stop dragging.
    sim->isDragging = false;
    return false;
}

// Ensure the mass stays within bounds defined by the spring's anchor and max extension
static void SimResolveBounds(SimState *sim)
{
    float x_min = sim->renderState.springAnchorPoint.x + SPRING_STOP_MARGIN; // Leftmost point of spring plus some margin
    float x_max = sim->renderState.springAnchorPoint.x + (SPRING_SEGMENTS * SPRING_SEGMENT_LENGTH) - SPRING_STOP_MARGIN; // Point where spring is fully expanded minus some margin
    SpringmassResolveBounds(&sim->systemState, x_min, x_max);
}

// Draw the UI elements
static void ShowUI(SimState *sim)
{ 
    SetThemeColor(sim->renderState.themeColor);
    DrawVariableSliders(&sim->systemState);
    ShowDamping(
        sim->systemState.damping,
        sim->systemState.springConst,
        sim->systemState.mass,
        sim->renderState.themeColor
    );
}
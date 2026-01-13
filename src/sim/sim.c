#include <raylib.h>
#include "sim.h"
#include "../core/consts.h"
#include "UI/ui.h"
#include "renderer/graph.h"

// Forward declarations
static bool ClickInBoundingBox(Rectangle box);
static bool SimHandleDragging(SimState *sim);
static void SimResolveBounds(SimState *sim);
static void ShowUI(SimState *sim);

void InitSim(SimState *sim)
{
    InitWindow(WIDTH, HEIGHT, "Spring-Mass System Simulation");
    SetExitKey(KEY_NULL);
    InitSystem(&sim->systemState);
    InitRender(&sim->renderState);
    InitGraph();
    sim->isPaused = false;
    sim->pausedTime = 0.0f;
    sim->isDragging = false;
    sim->dragGrabOffsetX = 0.0f;
}

void UpdateSim(SimState *sim, float dt, float time)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        sim->isPaused = !sim->isPaused;
    }
    if (!sim->isPaused)
    {
        if (!SimHandleDragging(sim)) 
        {
            SpringmassStep(&sim->systemState, dt);
        }
        SimResolveBounds(sim);
        sim->renderState.position.x = sim->systemState.x;

        UpdateGraph(sim->systemState.x - sim->systemState.equilibrium, time);
    }
}

void DrawSim(SimState *sim, float dt, float time)
{
    BeginDrawing();
        ClearBackground(BLACK); // Clear last frame
        DrawText("Spring-Mass System", 10, 10, 30, BLUE); // Title
        DrawGraph(sim->systemState.x - sim->systemState.equilibrium, time);
        ShowUI(sim); // Draw UI
        UpdateRender(&sim->renderState); // Update render state based on system state
        
        float textPersistTime = 8.0f;
        float fadeTime = 7.0f;
        if (time <= textPersistTime)
        {
            ShowStartupText();
        }
        else if (textPersistTime < time && time <= textPersistTime + fadeTime)
        {
            // Only update fade-out animation when not paused
            ShowStartupTextFadeOut(sim->isPaused ? 0.0f : dt, fadeTime);
        }

        if (sim->isPaused)
        {
            if (!ShowPauseDialog())
            {
                sim->isPaused = !sim->isPaused;
            }
        }
    EndDrawing();
}

bool SimRunning(const SimState *sim)
{
    (void)sim;
    return !WindowShouldClose();
    // Future: 
    //  If required, lose the void and return
    //  sim->IsRunning && !WindowShouldClose 
    //  or whatever.
}

void StopSim()
{
    CloseWindow();
}

/***************************************
 *      Internal helper functions      *
 ***************************************/

// Helper to check if mouse click is in bounding box
static bool ClickInBoundingBox(Rectangle box)
{
    Vector2 point = GetMousePosition();
    if(point.x >= box.x && point.x <= box.x + box.width)
    {
        if(point.y >= box.y && point.y <= box.y + box.height)
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
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ClickInBoundingBox(sim->renderState.position)) 
        {
            Vector2 mousePosition = GetMousePosition();
            sim->isDragging = true;
            sim->dragGrabOffsetX = mousePosition.x - sim->systemState.x;
        } 
        else 
        {
            return false;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
    {
        sim->isDragging = false;
        sim->systemState.velocity = 0.0f;
        return true;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
    {
        Vector2 mousePosition = GetMousePosition();
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
    DrawVariableSliders(&sim->systemState);
    ShowDamping(
        sim->systemState.damping,
        sim->systemState.springConst,
        sim->systemState.mass
    );
}
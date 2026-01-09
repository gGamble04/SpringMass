#include <raylib.h>
#include "sim.h"
#include "core/consts.h"

void InitSim(SimState *sim)
{
    InitWindow(WIDTH, HEIGHT, "Spring-Mass System Simulation");
    InitSystem(&sim->systemState);
    InitRender(&sim->renderState);
    DrawRender(sim->renderState);
    sim->isDragging = false;
    sim->dragGrabOffsetX = 0.0f;
}

bool ClickInBoundingBox(Rectangle box)
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

bool SimHandleDragging(SimState *sim)
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

void SimResolveBounds(SimState *sim)
{
    float x_min = sim->renderState.springAnchorPoint.x + SPRING_STOP_MARGIN; // Leftmost point of spring plus some margin
    float x_max = sim->renderState.springAnchorPoint.x + (SPRING_SEGMENTS * SPRING_SEGMENT_LENGTH) - SPRING_STOP_MARGIN; // Point where spring is fully expanded minus some margin
    SpringmassResolveBounds(&sim->systemState, x_min, x_max);
}

void ShowUI(SimState *sim)
{
    DrawVariableSliders(&sim->systemState);
    ShowDamping(
        sim->systemState.damping,
        sim->systemState.springConst,
        sim->systemState.mass,
        sim->systemState.equilibrium / 2,
        sim->renderState.springAttachPoint.y - 75
    );
}

void UpdateSim(SimState *sim, float dt)
{
    if (!SimHandleDragging(sim)) 
    {
        SpringmassStep(&sim->systemState, dt);
    }
    SimResolveBounds(sim);
    sim->renderState.position.x = sim->systemState.x;
}

void DrawSim(SimState *sim)
{
    BeginDrawing();
    ClearBackground(BLACK); // Clear last frame
    DrawText("Spring-Mass System", 10, 10, 30, BLUE); // Title
    ShowUI(sim); // Draw UI
    UpdateRender(&sim->renderState); // Update render state based on system state
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
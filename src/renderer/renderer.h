/***********************************************************************
 * @file renderer.h                                                    *
 * @brief Header file for rendering the spring-mass system simulation. *
 * @author Gabe G.                                                     *
 * @date 1-8-2026                                                      *
 ***********************************************************************/

#ifndef RENDERER_H
#define RENDERER_H

#include "core/consts.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

// Utility functions
static inline Rectangle SimRectToRayRect(SimRect rect) // Convert SimColor to Raylib Color
{
    return (Rectangle){ rect.x, rect.y, rect.width, rect.height };
}

static inline Color SimColorToRayColor(SimColor color) // Convert SimColor to Raylib Color
{
    return (Color){ color.r, color.g, color.b, color.a };
}

static inline SimColor RayColorToSimColor(Color color) // Convert Raylib Color to SimColor
{
    return (SimColor){ color.r, color.g, color.b, color.a };
}

static inline Vector2 vec2Add(Vector2 v, Vector2 u) // Add two Vector2 vectors
{
    return (Vector2){ v.x + u.x, v.y + u.y };
}

static inline Vector2 vec2Sub(Vector2 v, Vector2 u) // Subtract two Vector2 vectors
{
    return (Vector2){ v.x - u.x, v.y - u.y };
}

static inline Vector2 vec2Scale(Vector2 v, double a) // Scale a Vector2 by a scalar
{
    return (Vector2){ v.x * a, v.y * a };
}

static inline double vec2Length(Vector2 v) // Compute length of a Vector2
{
    return sqrt(v.x * v.x + v.y * v.y);
}

// Rendering state for the spring-mass system
typedef struct SpringMassRenderState
{
    SimRect massRectangle; // Position and size of the mass rectangle
    SimColor massColor;    // Color of the mass rectangle

    SimColor themeColor; // Theme color used for rendering

    Vector2 springAnchorPoint; // Fixed anchor point of the spring
    Vector2 springAttachPoint; // Attachment point of the spring on the mass
    int numSpringSegments;     // Number of segments in the spring
    float segmentLength;       // Length of each spring segment

    Vector2 floorStart; // Start point of the floor line
    Vector2 floorEnd;   // End point of the floor line
    int floorThickness; // Thickness of the floor line

    float elapsedTime; // Elapsed time for animations/timing
} SpringMassRenderState;

// Function declarations
void InitRender(SpringMassRenderState *state, int windowWidth, int windowHeight, const char *title,
                int FPS);                           // Initialize rendering state
void ShowStartupText(SpringMassRenderState *state); // Show startup text
void ShowStartupTextFadeOut(SpringMassRenderState *state, float dt,
                            float fadeTime);     // Show startup text with fade-out effect
void DrawFloor(SpringMassRenderState state);     // Draw the floor
void DrawMass(SpringMassRenderState state);      // Draw the mass
void DrawSpring(SpringMassRenderState state);    // Draw the spring
void DrawRender(SpringMassRenderState state);    // Draw entire spring-mass system
void UpdateRender(SpringMassRenderState *state); // Update rendering state
void Render_BeginDrawing();                      // Begin drawing phase
void Render_EndDrawing();                        // End drawing phase
void Render_ClearBackground(SimColor color);     // Clear background with specified color
float Render_GetFrameTime();                     // Get time elapsed since last frame

#endif

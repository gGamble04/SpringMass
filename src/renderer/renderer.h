/***********************************************************************
 * @file renderer.h                                                    *
 * @brief Header file for rendering the spring-mass system simulation. *
 * @author Gabe G.                                                     *
 * @date 1-8-2026                                                      *
 ***********************************************************************/

#ifndef RENDERER_H
#define RENDERER_H

#include "consts.h"
#include <math.h>
#include <stdio.h>

// Rendering state for the spring-mass system
typedef struct SpringMassRenderState
{
    SimRect massRectangle; // Position and size of the mass rectangle
    SimColor massColor;    // Color of the mass rectangle

    SimColor themeColor; // Theme color used for rendering

    Vec2D springAnchorPoint; // Fixed anchor point of the spring
    Vec2D springAttachPoint; // Attachment point of the spring on the mass
    int numSpringSegments;   // Number of segments in the spring
    float segmentLength;     // Length of each spring segment

    Vec2D floorStart;   // Start point of the floor line
    Vec2D floorEnd;     // End point of the floor line
    int floorThickness; // Thickness of the floor line

    float elapsedTime; // Elapsed time for animations/timing
} SpringMassRenderState;

// Renderer Function Declarations
void InitRender(SpringMassRenderState *state, int windowWidth, int windowHeight, const char *title,
                int FPS);                           // Initialize rendering state
void ShowStartupText(SpringMassRenderState *state); // Show startup text
void ShowStartupTextFadeOut(SpringMassRenderState *state, float dt,
                            float fadeTime);     // Show startup text with fade-out effect
void DrawFloor(SpringMassRenderState *state);    // Draw the floor
void DrawMass(SpringMassRenderState *state);     // Draw the mass
void DrawSpring(SpringMassRenderState *state);   // Draw the spring
void DrawRender(SpringMassRenderState *state);   // Draw entire spring-mass system
void UpdateRender(SpringMassRenderState *state); // Update rendering state
void Render_BeginDrawing(void);                  // Begin drawing phase
void Render_EndDrawing(void);                    // End drawing phase
void Render_ClearBackground(SimColor color);     // Clear background with specified color
float Render_GetFrameTime(void);                 // Get time elapsed since last frame

#endif

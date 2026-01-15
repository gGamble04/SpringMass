/***********************************************************************
 * @file renderer.h                                                    *
 * @brief Header file for rendering the spring-mass system simulation. *
 * @author Gabe G.                                                     *
 * @date 1-8-2026                                                      *
 ***********************************************************************/

#ifndef RENDERER_H
#define RENDERER_H

#include<stdio.h>
#include<math.h>
#include<raylib.h>
#include "core/consts.h"

/**
 * @brief Convert SimColor to Raylib Color.
 * @param color SimColor to convert.
 * @return Converted Raylib Color.
 */
static inline Color SimColorToRayColor(SimColor color)
{
    return (Color){ color.r, color.g, color.b, color.a };
}

/**
 * @brief Convert Raylib Color to SimColor.
 * @param color Raylib Color to convert.
 * @return Converted SimColor.
 */
static inline SimColor RayColorToSimColor(Color color)
{
    return (SimColor){ color.r, color.g, color.b, color.a };
}

/**
 * @brief Add two Vector2 vectors.
 * @param v First vector.
 * @param u Second vector.
 * @return Resulting vector from addition.
 */
static inline Vector2 vec2Add(Vector2 v, Vector2 u)
{
    return (Vector2){ v.x + u.x, v.y + u.y }; 
}

/**
 * @brief Subtract two Vector2 vectors.
 * @param v First vector.
 * @param u Second vector.
 * @return Resulting vector from subtraction.
 */
static inline Vector2 vec2Sub(Vector2 v, Vector2 u)
{
    return (Vector2){ v.x - u.x, v.y - u.y }; 
}

/**
 * @brief Scale a Vector2 by a scalar.
 * @param v Vector to scale.
 * @param a Scalar value.
 * @return Scaled vector.
 */
static inline Vector2 vec2Scale(Vector2 v, double a)
{
    return (Vector2){ v.x * a, v.y * a }; 
}

/**
 * @brief Compute the length of a Vector2.
 * @param v Vector to compute length of.
 * @return Length of the vector.
 */
static inline double vec2Length(Vector2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

/**
 * @brief State for rendering the spring-mass system.
 */
typedef struct SpringMassRenderState {
    Rectangle massRectangle; /**< Position and size of the mass rectangle */
    Color massColor; /**< Color of the mass rectangle */

    SimColor themeColor; /**< Theme color used for rendering */
    
    Vector2 springAnchorPoint; /**< Fixed anchor point of the spring */
    Vector2 springAttachPoint; /**< Attachment point of the spring on the mass */
    int numSpringSegments; /**< Number of segments in the spring */
    float segmentLength; /**< Length of each spring segment */
    
    Vector2 floorStart; /**< Start point of the floor line */
    Vector2 floorEnd; /**< End point of the floor line */
    int floorThickness; /**< Thickness of the floor line */

    float elapsedTime; /**< Used to track elapsed time for animations or timing */
} SpringMassRenderState;

/**
 * @brief Initialize the rendering state for the spring-mass system.
 * @param state Pointer to the SpringMassRenderState to initialize.
 */
void InitRender(SpringMassRenderState *state, int windowWidth, int windowHeight, const char *title, int FPS);

/**
 * @brief Show startup text for the spring-mass system.
 * @param state Current rendering state.
 */
void ShowStartupText(SpringMassRenderState *state);

/**
 * @brief Show startup text with fade-out effect for the spring-mass system.
 * @param state Current rendering state.
 * @param dt Delta time since last frame.
 * @param fadeTime Total time for the fade-out effect.
 */
void ShowStartupTextFadeOut(SpringMassRenderState *state, float dt, float fadeTime);

/**
 * @brief Draw the floor in the spring-mass system.
 * @param state Current rendering state.
 */
void DrawFloor(SpringMassRenderState state);

/**
 * @brief Draw the mass in the spring-mass system.
 * @param state Current rendering state.
 */
void DrawMass(SpringMassRenderState state);

/**
 * @brief Draw the spring in the spring-mass system.
 * @param state Current rendering state.
 */
void DrawSpring(SpringMassRenderState state);

/**
 * @brief Draw the entire spring-mass system.
 * @param state Current rendering state.
 */
void DrawRender(SpringMassRenderState state);

/**
 * @brief Update the rendering state for the spring-mass system.
 * @param state Pointer to the SpringMassRenderState to update.
 */
void UpdateRender(SpringMassRenderState *state);

/**
 * @brief Begin the drawing phase.
 */
void Render_BeginDrawing();

/**
 * @brief End the drawing phase.
 */
void Render_EndDrawing();

/**
 * @brief Clear the background with a specified color.
 * @param color Color to clear the background with.
 */
void Render_ClearBackground(SimColor color);

/**
 * @brief Get the time elapsed since the last frame.
 * @return Time in seconds since the last frame.
 */
float Render_GetFrameTime();

#endif 

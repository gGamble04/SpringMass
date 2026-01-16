/**************************************************************************************
 * @file platform_internal.h                                                          *
 * @brief Internal platform-specific utilities for the Spring-Mass System Simulation. *
 * @author Gabe G.                                                                    *
 * @date 1-16-2026                                                                    *
 **************************************************************************************/

#ifndef PLATFORM_INTERNAL_H
#define PLATFORM_INTERNAL_H

#include "consts.h"
#include <math.h>
#include <raylib.h>

// Utility functions
static inline Vector2 SimVectoRayVec(Vec2D v) // Convert Vec2D to Raylib Vector2
{
    return (Vector2){ v.x, v.y };
}

static inline Rectangle SimRectToRayRect(SimRect rect) // Convert SimRect to Raylib Rectangle
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

#endif
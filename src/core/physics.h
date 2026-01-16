/*************************************************
 * @file physics.h                               *
 * @brief Header for spring-mass system physics. *
 * @author Gabe G.                               *
 * @date 1-5-2026                                *
 *************************************************/

#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>

// State of a 1D spring-mass system
typedef struct SpringMassSystemState
{
    float x;           // Position (only horizontal)
    float xMin;        // Minimum position boundary
    float xMax;        // Maximum position boundary
    float velocity;    // Velocity
    float springConst; // Spring constant
    float mass;        // Mass
    float damping;     // Damping coefficient
    float equilibrium; // Equilibrium (rest) position
    float restitution; // Coefficient of restitution (bounciness)
} SpringMassSystemState;

// Physics Function Declarations
void InitSystem(SpringMassSystemState *state); // Initialize system to default values
float SpringmassAccel(float x, float v, float k, float m,
                      float c);                              // Compute acceleration using Hooke's law and damping
void SpringmassStep(SpringMassSystemState *state, float dt); // Advance system by one time step (semi-implicit Euler)
void SpringmassResolveBounds(SpringMassSystemState *state, float x_min,
                             float x_max); // Resolve boundary collisions with restitution

#endif

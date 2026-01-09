/**
 * @file physics.h
 * @brief Header for spring-mass system physics.
 * @author Gabriel Gamble
 * @date 1-5-2026
 */
#ifndef PHYSICS_H
#define PHYSICS_H

#include<stdio.h>

/**
 * @brief State of a 1D spring-mass system.
 * 
 * Members:
 * 
 * float x: Position (horizontal only)
 * 
 * float velocity: Velocity
 * 
 * float springConst: Spring constant (k)
 * 
 * float mass: Mass (m)
 * 
 * float damping: Damping coefficient (c)
 * 
 * float equilibrium: Equilibrium (rest) position
 * 
 * float restitution: Coefficient of restitution (bounciness)
 */
typedef struct SpringMassSystemState {
    float x; /**< Position (only horizontal) */
    float xMin; /**< Minimum position boundary */
    float xMax; /**< Maximum position boundary */
    float velocity; /**< Velocity */
    float springConst; /**< Spring constant */
    float mass; /**< Mass */
    float damping; /**< Damping coefficient */
    float equilibrium; /**< Equilibrium (rest) position */
    float restitution; /**< Coefficient of restitution (bounciness) */
} SpringMassSystemState;

/**
 * @brief Initializes spring-mass system state to default values.
 * 
 * @param state Pointer to spring-mass state to initialize.
 */
void InitSystem(SpringMassSystemState *state);

/**
 * @brief Computes acceleration of spring-mass system.
 * 
 * Uses Hooke's law and damping to compute acceleration.
 * @param x Displacement from equilibrium position.
 * @param v Current velocity.
 * @param k Spring constant.
 * @param m Mass.
 * @param c Damping coefficient.
 * @return Acceleration.
 */
float SpringmassAccel(float x, float v, float k, float m, float c);

/**
 * @brief Advances spring-mass system state by one time step using semi-implicit Euler integration.
 * 
 * @param state Pointer to spring-mass state to update.
 * @param dt Time step.
 */
void SpringmassStep(SpringMassSystemState *state, float dt);

/**
 * @brief Resolves boundary collisions for spring-mass system.
 * 
 * If the mass exceeds the specified boundaries, its position is clamped and its velocity is adjusted based on restitution.
 * @param state Pointer to spring-mass state to update.
 * @param x_min Minimum position boundary.
 * @param x_max Maximum position boundary.
 */
void SpringmassResolveBounds(SpringMassSystemState *state, float x_min, float x_max);

#endif

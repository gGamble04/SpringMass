#include "core/physics.h"

void InitSystem(SpringMassSystemState *state)
{
	state->x = 150;					// Horizontal position       (x)
	state->velocity = 0.0f;			// Velocity                  (v)
	state->springConst = 100.0f;	// Spring constant           (k)
	state->mass = 5.0f;				// Mass                      (m)
	state->damping = 4.0f;			// Damping coefficient       (c)
	state->equilibrium = state->x;	// Equilibrium/rest point    (x_eq)
	state->restitution = 0.1f;		// Coefficient of restitution (e)
}

float SpringmassAccel(float x, float v, float k, float m, float c)
{
	return -(k/m) * x - (c/m) * v; // acceleration = -(k/m)x - (c/m)v
}

void SpringmassStep(SpringMassSystemState *state, float dt)
{
	float displacement = state->x - state->equilibrium; // x - x_eq, displacement from equilibrium
	float acceleration = SpringmassAccel(displacement, state->velocity, state->springConst, state->mass, state->damping);

	state->velocity += acceleration * dt;  // semi-implicit Euler velocity update
	state->x += state->velocity * dt; 	   // position update
}

void SpringmassResolveBounds(SpringMassSystemState *state, float x_min, float x_max)
{
	// Check minimum boundary
	if (state->x < x_min) {
		state->x = x_min; // Clamp to minimum
		if (state->velocity < 0) state->velocity = -(state->restitution) * state->velocity; // Bounce if moving into wall
	}
	// Check maximum boundary
	if (state->x > x_max) {
		state->x = x_max; // Clamp to maximum
		if (state->velocity > 0) state->velocity = -(state->restitution) * state->velocity; // Bounce if moving into wall
	}
}
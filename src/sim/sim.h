/**
 * @file sim.h
 * @brief Header file for the Spring-Mass System Simulation.
 * @author Gabe G.
 * @date 1-9-2026
 */

#ifndef SIM_H
#define SIM_H

#include "core/physics.h"
#include "renderer/renderer.h"

/** 
 * @struct SimState
 * @brief Represents the overall state of the simulation, including system state, render state, and dragging interaction state.
 */
typedef struct SimState {
	SpringMassSystemState systemState; /**< Physical state of the spring-mass system */
	SpringMassRenderState renderState; /**< Rendering state of the spring-mass system */
	bool isRunning;
	bool isPaused;
	float pausedTime; /**< The simulation time when paused (used to freeze graph) */
	bool showSettings;
	bool showThemeChange;
	bool isDragging; /**< Indicates if the mass is currently being dragged */
	float dragGrabOffsetX; /**< Horizontal offset from the grab point during dragging */

} SimState;

/**
 * @brief Initializes the simulation state, including system and render states.
 * @param simulation Pointer to the SimState to initialize.
 */
void InitSim(SimState *simulation);

/**
 * @brief Updates the simulation state based on elapsed time.
 * @param sim Pointer to the SimState.
 * @param dt Time delta since the last update.
 */
void UpdateSim(SimState *sim, float dt, float time);
/**
 * @brief Draws the current state of the simulation.
 * @param sim Pointer to the SimState.
 */
void DrawSim(SimState *sim, float dt, float time);
/**
 * @brief Checks if the simulation is currently running.
 * @param sim Pointer to the SimState.
 * @return true if the simulation is running, false otherwise.
 */
bool SimRunning(const SimState *sim);
/**
 * @brief Stops the simulation.
 */
void StopSim();

#endif
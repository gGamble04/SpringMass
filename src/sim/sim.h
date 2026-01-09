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
#include "UI/ui.h"

/** 
 * @struct SimState
 * @brief Represents the overall state of the simulation, including system state, render state, and dragging interaction state.
 */
typedef struct SimState {
	SpringMassSystemState systemState; /**< Physical state of the spring-mass system */
	SpringMassRenderState renderState; /**< Rendering state of the spring-mass system */
	bool isDragging; /**< Indicates if the mass is currently being dragged */
	float dragGrabOffsetX; /**< Horizontal offset from the grab point during dragging */
} SimState;

/**
 * @brief Initializes the simulation state, including system and render states.
 * @param simulation Pointer to the SimState to initialize.
 */
void InitSim(SimState *simulation);

/**
 * @brief Checks if a mouse click is within a given bounding box.
 * @param box The bounding box to check against.
 * @return true if the click is within the box, false otherwise.
 */
bool ClickInBoundingBox(Rectangle box);

/**
 * @brief Handles dragging interaction for the mass in the simulation.
 * @param sim Pointer to the SimState.
 * @return true if dragging is occurring, false otherwise.
 */
bool SimHandleDragging(SimState *sim);

/**
 * @brief Resolves boundary conditions for the spring-mass system.
 * @param sim Pointer to the SimState.
 */
void SimResolveBounds(SimState *sim);

/**
 * @brief Displays the user interface for adjusting simulation parameters.
 * @param sim Pointer to the SimState.
 */
void ShowUI(SimState *sim);
/**
 * @brief Updates the simulation state based on elapsed time.
 * @param sim Pointer to the SimState.
 * @param dt Time delta since the last update.
 */
void UpdateSim(SimState *sim, float dt);
/**
 * @brief Draws the current state of the simulation.
 * @param sim Pointer to the SimState.
 */
void DrawSim(SimState *sim);
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
/**
 * @file ui.h
 * @brief Header file for the User Interface of the Spring-Mass System Simulation.
 * @author Gabe G.
 * @date 1-9-2026
 */

#ifndef UI_H
#define UI_H

#include "core/physics.h"
#include "renderer/renderer.h"

void SetThemeColor(Color themeColor);

/**
 * @brief Draws sliders for adjusting the spring-mass system parameters.
 * @param state Pointer to the SpringMassSystemState to modify.
 */
void DrawVariableSliders(SpringMassSystemState *systemState);

/**
 * @brief Displays the damping type based on current parameters.
 * @param c Damping coefficient.
 * @param k Spring constant.
 * @param m Mass.
 * @param x X position to draw the text.
 * @param y Y position to draw the text.
 */
void ShowDamping(float c, float k, float m, Color themeColor);

int ShowPauseDialog();

int ShowSettings();

void ShowThemeChange(SpringMassRenderState *state);

#endif
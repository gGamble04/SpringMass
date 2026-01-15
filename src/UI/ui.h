/***********************************************************************************
 * @file ui.h                                                                      *
 * @brief Header file for the User Interface of the Spring-Mass System Simulation. *
 * @author Gabe G.                                                                 *                                            
 * @date 1-9-2026                                                                  *    
 ***********************************************************************************/

#ifndef UI_H
#define UI_H

#include "core/physics.h"
#include "core/consts.h"
#include "renderer/renderer.h"

/**
 * @brief Sets the theme color for the UI elements.
 * @param themeColor The SimColor to set as the theme.
 */
void SetThemeColor(SimColor themeColor);

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
void ShowDamping(float c, float k, float m, SimColor themeColor);

/**
 * @brief Displays the pause dialog with options.
 * @return An integer indicating the selected option:
 *         
 *  1 - Resume
 *
 *  2 - Settings
 * 
 *  3 - Exit
 * 
 * -1 - No selection
 */
int ShowPauseDialog();

/**
 * @brief Displays the settings dialog with options.
 * @return An integer indicating the selected option:
 *         
 *  2 - Change Theme
 * 
 * -1 - No selection
 */
int ShowSettings();

/**
 * @brief Displays the theme change dialog with color options.
 * @param state Pointer to the SpringMassRenderState to modify.
 */
void ShowThemeChange(SpringMassRenderState *state);

/**
 * @brief Checks if the Escape key has been pressed.
 * @return true if the Escape key is pressed, false otherwise.
 */
bool EscKeyPressed();

/**
 * @brief Checks if the exit button has been clicked.
 * @return true if the exit button is clicked, false otherwise.
 */
bool ExitButtonClicked();

/**
 * @brief Destroys the renderer and closes the window.
 */
void DestroyRenderer();

/**
 * @brief Gets the current mouse position.
 * @return A Vec2D structure containing the mouse position.
 */
Vec2D GetMousePOS(); 

/**
 * @brief Checks if the left mouse button has been pressed.
 * @return true if the left mouse button is pressed, false otherwise.
 */
bool LeftMouseButtonPressed();

/**
 * @brief Checks if the left mouse button has been released.
 * @return true if the left mouse button is released, false otherwise.
 */
bool LeftMouseButtonReleased();

/**
 * @brief Checks if the left mouse button is currently down.
 * @return true if the left mouse button is down, false otherwise.
 */
bool LeftMouseButtonDown();

#endif
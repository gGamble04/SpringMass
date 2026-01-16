/***********************************************************************************
 * @file ui.h                                                                      *
 * @brief Header file for the User Interface of the Spring-Mass System Simulation. *
 * @author Gabe G.                                                                 *
 * @date 1-9-2026                                                                  *
 ***********************************************************************************/

#ifndef UI_H
#define UI_H

#include "core/consts.h"
#include "core/physics.h"
#include "renderer/renderer.h"

// Function declarations
void SetThemeColor(SimColor themeColor);                          // Set theme color for UI elements
void MakeVariableSliders(SpringMassSystemState *systemState);     // Draw parameter adjustment sliders
void ShowDamping(float c, float k, float m, SimColor themeColor); // Display damping type based on parameters
int ShowPauseDialog(); // Show pause dialog (returns: 1=Resume, 2=Settings, 3=Exit, -1=None)
int ShowSettings();    // Show settings dialog (returns: 2=Change Theme, -1=None)
void ShowThemeChange(SpringMassRenderState *state); // Show theme change dialog with color options
bool EscKeyPressed();                               // Check if Escape key pressed
bool ExitButtonClicked();                           // Check if exit button clicked
void DestroyRenderer();                             // Destroy renderer and close window
Vec2D GetMousePOS();                                // Get current mouse position
bool LeftMouseButtonPressed();                      // Check if left mouse button pressed
bool LeftMouseButtonReleased();                     // Check if left mouse button released
bool LeftMouseButtonDown();                         // Check if left mouse button currently down
bool ClickInBoundingBox(SimRect boundingBox);       // Check if mouse click is within bounding box

#endif
/*************************************************************************************
 * @file graph.h                                                                     *
 * @brief Header file for the Displacement vs. Time Graph in the Spring-Mass System. *
 * @author Gabe G.                                                                   *
 * @date 1-13-2026                                                                   *
 *************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "../core/consts.h"
#include "raylib.h"

// Function declarations
void InitGraph(void);                                                // Initialize graphing system
void UpdateGraph(float displacement, float time);                    // Update graph with new data point
void DrawGraph(float displacement, float time, SimColor themeColor); // Draw graph to screen
void CloseGraph(void);                                               // Close graph window
bool GraphWindowShouldClose(void);                                   // Check if graph window should close

#endif

/**
 * @file graph.h
 * @brief Header file for the Displacement vs. Time Graph in the Spring-Mass System
 * @author Gabe G.
 * @date 1-13-2026
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "raylib.h"
#include "../core/consts.h"

/**
 * @brief Initialize the graphing system.
 */
void InitGraph(void);

/**
 * @brief Update the graph with a new data point.
 * @param displacement The displacement value to add.
 * @param time The time value to add.
 */
void UpdateGraph(float displacement, float time);

/**
 * @brief Draw the graph to the screen.
 * @param displacement The current displacement value.
 * @param time The current time value.
 */
void DrawGraph(float displacement, float time, SimColor themeColor);

/**
 * @brief Close the graph window.
 */
void CloseGraph(void);

/**
 * @brief Check if the graph window should close.
 * @return true if the graph window should close, false otherwise.
 */
bool GraphWindowShouldClose(void);

#endif

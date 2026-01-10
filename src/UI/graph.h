#ifndef GRAPH_H
#define GRAPH_H

#include "raylib.h"

// Initialize the graph window
void InitGraph(void);

// Update graph data with new displacement and time
void UpdateGraph(float displacement, float time);

// Draw the graph to the screen
void DrawGraph(float displacement, float time);

// Close the graph window
void CloseGraph(void);

// Check if graph window should close
bool GraphWindowShouldClose(void);

#endif

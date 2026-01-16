/***************************************************************************************************
 * @file graph.c                                                                                   *
 * @brief Implementation of the Displacement vs. Time Graph for the Spring-Mass System Simulation. *
 * @author Gabe G.                                                                                 *
 * @date 1-13-2026                                                                                 *
 ***************************************************************************************************/

#include "graph.h"
#include "platform_internal.h"
#include "renderer.h"
#include <stdio.h>
#include <string.h>

// Maximum number of data points to store
#define MAX_POINTS 2000

// Time window to display (in seconds)
#define TIME_WINDOW 15.0f

// Graph data storage
static Vector2 dataPoints[MAX_POINTS];
static int pointCount = 0;
static float minDisplacement = 0.0f;
static float maxDisplacement = 0.0f;
static float maxTime = 0.0f;

// Graph window dimensions and position
static const int GRAPH_WIDTH = SCREEN_WIDTH;
static const int GRAPH_HEIGHT = SCREEN_HEIGHT;
static const int GRAPH_X = SCREEN_WIDTH + 100;
static const int GRAPH_Y = 0;

// Margin for graph drawing
static const int MARGIN = 50;

void InitGraph(void)
{
    // Set the window position for the graph window
    SetWindowPosition(GRAPH_X, GRAPH_Y);

    // Initialize data
    pointCount = 0;
    minDisplacement = 0.0f;
    maxDisplacement = 0.0f;
    maxTime = 0.0f;

    memset(dataPoints, 0, sizeof(dataPoints));
}

void UpdateGraph(float displacement, float time)
{
    // Add new data point
    if (pointCount < MAX_POINTS)
    {
        dataPoints[pointCount].x = time;
        dataPoints[pointCount].y = displacement;
        pointCount++;
    }
    else
    {
        // Shift all points left and add new point at the end
        for (int i = 0; i < MAX_POINTS - 1; i++)
        {
            dataPoints[i] = dataPoints[i + 1];
        }
        dataPoints[MAX_POINTS - 1].x = time;
        dataPoints[MAX_POINTS - 1].y = displacement;
    }

    // Update min/max values for scaling
    if (displacement < minDisplacement)
        minDisplacement = displacement;
    if (displacement > maxDisplacement)
        maxDisplacement = displacement;
    if (time > maxTime)
        maxTime = time;
}

void DrawGraph(float displacement, float time, SimColor *themeColor)
{
    // All drawing is offset to start at (WIDTH+1, 0)
    int offsetX = GRAPH_X;
    int offsetY = GRAPH_Y;

    // Draw background
    DrawRectangle(offsetX, offsetY, GRAPH_WIDTH, GRAPH_HEIGHT, BLACK);

    // Draw axes
    int graphWidth = GRAPH_WIDTH - 2 * MARGIN;
    int graphHeight = GRAPH_HEIGHT - 2 * MARGIN;

    // X-axis (time)
    DrawLine(offsetX + MARGIN, offsetY + GRAPH_HEIGHT - MARGIN, offsetX + GRAPH_WIDTH - MARGIN,
             offsetY + GRAPH_HEIGHT - MARGIN, BLACK);
    DrawText("Time (s)", offsetX + GRAPH_WIDTH / 2 - 30, offsetY + GRAPH_HEIGHT - MARGIN + 25, 15, LIGHTGRAY);

    // Y-axis (displacement)
    DrawLine(offsetX + MARGIN, offsetY + MARGIN, offsetX + MARGIN, offsetY + GRAPH_HEIGHT - MARGIN, BLACK);
    DrawText("Displacement", offsetX + 5, offsetY + 30, 15, LIGHTGRAY);

    // Draw grid lines
    for (int i = 0; i <= 10; i++)
    {
        int x = offsetX + MARGIN + (graphWidth * i) / 10;
        int y = offsetY + MARGIN + (graphHeight * i) / 10;
        DrawLine(x, offsetY + MARGIN, x, offsetY + GRAPH_HEIGHT - MARGIN, LIGHTGRAY);
        DrawLine(offsetX + MARGIN, y, offsetX + GRAPH_WIDTH - MARGIN, y, LIGHTGRAY);
    }

    // Draw equilibrium line (displacement = 0) if we have data
    if (pointCount > 0)
    {
        float displacementRange = maxDisplacement - minDisplacement;
        if (displacementRange >= 0.1f)
        {
            // Calculate y position for displacement = 0
            float equilibriumY =
                offsetY + GRAPH_HEIGHT - MARGIN - ((0.0f - minDisplacement) / displacementRange) * graphHeight;

            // Create a lighter version of theme color by blending with white
            Color lighterTheme = { themeColor->r + (255 - themeColor->r) * 0.5f,
                                   themeColor->g + (255 - themeColor->g) * 0.5f,
                                   themeColor->b + (255 - themeColor->b) * 0.5f, themeColor->a };

            DrawLineEx((Vector2){ offsetX + MARGIN, equilibriumY },
                       (Vector2){ offsetX + GRAPH_WIDTH - MARGIN, equilibriumY }, 2.0f, lighterTheme);
        }
    }

    // Draw data points if we have any
    if (pointCount > 1)
    {
        // Use a sliding time window
        float timeWindowStart = (time > TIME_WINDOW) ? (time - TIME_WINDOW) : 0.0f;
        float timeWindowEnd = time;
        float timeRange = timeWindowEnd - timeWindowStart;

        float displacementRange = maxDisplacement - minDisplacement;
        if (displacementRange < 0.1f)
            displacementRange = 0.1f; // Avoid division by zero

        for (int i = 0; i < pointCount - 1; i++)
        {
            // Only draw points within the time window
            if (dataPoints[i].x < timeWindowStart && dataPoints[i + 1].x < timeWindowStart)
                continue;
            if (dataPoints[i].x > timeWindowEnd)
                break;

            // Map time to x coordinate (relative to time window)
            float x1 = offsetX + MARGIN + ((dataPoints[i].x - timeWindowStart) / timeRange) * graphWidth;
            float x2 = offsetX + MARGIN + ((dataPoints[i + 1].x - timeWindowStart) / timeRange) * graphWidth;

            // Map displacement to y coordinate (inverted because screen y is top-down)
            float y1 = offsetY + GRAPH_HEIGHT - MARGIN -
                       ((dataPoints[i].y - minDisplacement) / displacementRange) * graphHeight;
            float y2 = offsetY + GRAPH_HEIGHT - MARGIN -
                       ((dataPoints[i + 1].y - minDisplacement) / displacementRange) * graphHeight;

            DrawLineEx((Vector2){ x1, y1 }, (Vector2){ x2, y2 }, 2.0f, SimColorToRayColor(*themeColor));
        }

        // Draw current point
        float x = offsetX + MARGIN + ((dataPoints[pointCount - 1].x - timeWindowStart) / timeRange) * graphWidth;
        float y = offsetY + GRAPH_HEIGHT - MARGIN -
                  ((dataPoints[pointCount - 1].y - minDisplacement) / displacementRange) * graphHeight;
        DrawCircle(x, y, 4, RED);
    }

    // Draw current values
    DrawText(TextFormat("Current Displacement: %.2f", displacement), offsetX + GRAPH_WIDTH - 545, offsetY + MARGIN - 25,
             15, SimColorToRayColor(*themeColor));

    // Draw min/max labels
    DrawText(TextFormat("%.2f", maxDisplacement), offsetX + 5, offsetY + MARGIN, 12, GRAY);
    DrawText(TextFormat("%.2f", minDisplacement), offsetX + 5, offsetY + GRAPH_HEIGHT - MARGIN - 5, 12, GRAY);

    // Draw time labels for the sliding window
    float timeWindowStart = (time > TIME_WINDOW) ? (time - TIME_WINDOW) : 0.0f;
    DrawText(TextFormat("%.1f", timeWindowStart), offsetX + MARGIN - 10, offsetY + GRAPH_HEIGHT - MARGIN + 5, 12, GRAY);
    DrawText(TextFormat("%.1f", time), offsetX + GRAPH_WIDTH - MARGIN - 20, offsetY + GRAPH_HEIGHT - MARGIN + 5, 12,
             GRAY);
}

void CloseGraph(void)
{
    // Clean up if needed
    pointCount = 0;
}

bool GraphWindowShouldClose(void)
{
    return WindowShouldClose();
}

#ifndef CONSTS_H
#define CONSTS_H

// Project-wide constants

// #define PI 3.14159265358979323846

#define WIDTH 900 // Window width
#define HEIGHT 600 // Window height

#define FLOOR_HEIGHT (HEIGHT * 0.8) // Floor height position
#define FLOOR_THICKNESS 5 // Floor thickness

#define RECT_SIZE 100 // Size of the rectangle representing the mass

#define SPRING_SEGMENTS 20 // Number of spring segments
#define SPRING_SEGMENT_LENGTH (RECT_SIZE / 4) // Length of each spring segment
#define SPRING_STOP_MARGIN 50 // Margin to prevent spring from fully compressing or extending

#define UI_SLIDER_WIDTH 260 // Width of UI sliders
#define UI_SLIDER_HEIGHT 20 // Height of UI sliders
#define UI_SLIDER_X (WIDTH - UI_SLIDER_WIDTH - 10) // X position of UI sliders
#define UI_SLIDER_Y 20 // Y position of first UI slider

#endif
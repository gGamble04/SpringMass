/************************************************************************
 * @file consts.h                                                       *
 * @brief Project-wide constants for the Spring-Mass System Simulation. *
 * @author Gabe G.                                                      *
 * @date 1-9-2026                                                       *
 ************************************************************************/

#ifndef CONSTS_H
#define CONSTS_H

/************************************
 *      Project-wide Constants      *
 ************************************/

typedef struct Vec2D
{
    float x;
    float y;
} Vec2D;

typedef struct SimRect
{
    int x;
    int y;
    int width;
    int height;
} SimRect;

typedef struct SimColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} SimColor;

#define SCREEN_WIDTH 900  // Window width
#define SCREEN_HEIGHT 600 // Window height

#define FLOOR_HEIGHT (SCREEN_HEIGHT * 0.8) // Floor height position
#define FLOOR_THICKNESS 5                  // Floor thickness

#define RECT_SIZE 100 // Size of the rectangle representing the mass

#define SPRING_SEGMENTS 20                    // Number of spring segments
#define SPRING_SEGMENT_LENGTH (RECT_SIZE / 4) // Length of each spring segment
#define SPRING_STOP_MARGIN 50                 // Margin to prevent spring from fully compressing or extending

#define UI_SLIDER_WIDTH 260                               // Width of UI sliders
#define UI_SLIDER_HEIGHT 20                               // Height of UI sliders
#define UI_SLIDER_X (SCREEN_WIDTH - UI_SLIDER_WIDTH - 10) // X position of UI sliders
#define UI_SLIDER_Y 20                                    // Y position of first UI slider

#define SIM_LIGHTGRAY (SimColor){ 200, 200, 200, 255 } // Light Gray
#define SIM_GRAY (SimColor){ 130, 130, 130, 255 }      // Gray
#define SIM_DARKGRAY (SimColor){ 80, 80, 80, 255 }     // Dark Gray
#define SIM_YELLOW (SimColor){ 253, 249, 0, 255 }      // Yellow
#define SIM_GOLD (SimColor){ 255, 203, 0, 255 }        // Gold
#define SIM_ORANGE (SimColor){ 255, 161, 0, 255 }      // Orange
#define SIM_PINK (SimColor){ 255, 109, 194, 255 }      // Pink
#define SIM_RED (SimColor){ 230, 41, 55, 255 }         // Red
#define SIM_MAROON (SimColor){ 190, 33, 55, 255 }      // Maroon
#define SIM_GREEN (SimColor){ 0, 228, 48, 255 }        // Green
#define SIM_LIME (SimColor){ 0, 158, 47, 255 }         // Lime
#define SIM_DARKGREEN (SimColor){ 0, 117, 44, 255 }    // Dark Green
#define SIM_SKYBLUE (SimColor){ 102, 191, 255, 255 }   // Sky Blue
#define SIM_BLUE (SimColor){ 0, 121, 241, 255 }        // Blue
#define SIM_DARKBLUE (SimColor){ 0, 82, 172, 255 }     // Dark Blue
#define SIM_PURPLE (SimColor){ 200, 122, 255, 255 }    // Purple
#define SIM_VIOLET (SimColor){ 135, 60, 190, 255 }     // Violet
#define SIM_DARKPURPLE (SimColor){ 112, 31, 126, 255 } // Dark Purple
#define SIM_BEIGE (SimColor){ 211, 176, 131, 255 }     // Beige
#define SIM_BROWN (SimColor){ 127, 106, 79, 255 }      // Brown
#define SIM_DARKBROWN (SimColor){ 76, 63, 47, 255 }    // Dark Brown
#define SIM_WHITE (SimColor){ 255, 255, 255, 255 }     // White
#define SIM_BLACK (SimColor){ 0, 0, 0, 255 }           // Black
#define SIM_BLANK (SimColor){ 0, 0, 0, 0 }             // Blank (Transparent)
#define SIM_MAGENTA (SimColor){ 255, 0, 255, 255 }     // Magenta

#endif
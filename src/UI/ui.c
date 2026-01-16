/**************************************************************************************
 * @file ui.c                                                                         *
 * @brief Implementation of the User Interface for the Spring-Mass System Simulation. *
 * @author Gabe G.                                                                    *
 * @date 1-13-2026                                                                    *
 **************************************************************************************/

#define RAYGUI_IMPLEMENTATION
#include "UI/ui.h"
#include "raygui.h"
#include <stdio.h>

void SetThemeColor(SimColor themeColor)
{
    Color color = SimColorToRayColor(themeColor);

    // Focused state: brighter, more saturated
    Color bordColorFocused = ColorBrightness(color, 0.4f); // 40% brighter
    Color baseColorFocused = ColorBrightness(color, 0.8f); // 80% brighter (very light)
    Color textColorFocused = ColorBrightness(color, 0.2f); // 20% brighter

    // Pressed state: slightly brighter than normal
    Color bordColorPressed = ColorBrightness(color, 0.05f); // 5% brighter
    Color baseColorPressed = ColorBrightness(color, 0.6f);  // 60% brighter
    Color textColorPressed = ColorBrightness(color, 0.1f);  // 10% brighter

    // Disabled state: desaturated gray
    Color colorDisabled = ColorBrightness(color, 0.3f);
    colorDisabled.r = (colorDisabled.r + 180) / 2; // Mix with gray
    colorDisabled.g = (colorDisabled.g + 180) / 2;
    colorDisabled.b = (colorDisabled.b + 180) / 2;

    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x838383ff);
    GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, 0xc9c9c9ff);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(color));

    GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt(bordColorFocused));
    GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt(baseColorFocused));
    GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt(textColorFocused));

    GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, ColorToInt(bordColorPressed));
    GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, ColorToInt(baseColorPressed));
    GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt(textColorPressed));

    GuiSetStyle(DEFAULT, BORDER_COLOR_DISABLED, ColorToInt(colorDisabled));
    GuiSetStyle(DEFAULT, BASE_COLOR_DISABLED, 0xe6e9e9ff);
    GuiSetStyle(DEFAULT, TEXT_COLOR_DISABLED, ColorToInt(colorDisabled));
}

// TODO:
// only move sliders if click happeded inside bouding box
// if user is dragging mass and hovers over sliders, sliders will also move
void MakeVariableSliders(SpringMassSystemState *systemState)
{
    // Slider ranges
    const float k_min = 0.0f;
    const float k_max = 500.0f;

    const float m_min = 0.1f;
    const float m_max = 500.0f;

    const float c_min = 0.0f;
    const float c_max = 50.0f;

    const float e_min = 0.0f;
    const float e_max = 1.0f;

    // Slider and label bounds
    Rectangle sliderBounds = (Rectangle){ UI_SLIDER_X, UI_SLIDER_Y, UI_SLIDER_WIDTH, UI_SLIDER_HEIGHT };
    Rectangle labelBounds = (Rectangle){ UI_SLIDER_X, UI_SLIDER_Y - 20, UI_SLIDER_WIDTH, UI_SLIDER_HEIGHT };

    // Draw sliders and labels
    GuiLabel(labelBounds, "Spring Constant (k)");
    GuiSlider(sliderBounds, TextFormat("k=%.1f", systemState->springConst), NULL, &systemState->springConst, k_min,
              k_max);
    labelBounds.y += 2 * UI_SLIDER_HEIGHT;
    sliderBounds.y += 2 * UI_SLIDER_HEIGHT;

    GuiLabel(labelBounds, "Mass (m)");
    GuiSlider(sliderBounds, TextFormat("m=%.1f", systemState->mass), NULL, &systemState->mass, m_min, m_max);
    labelBounds.y += 2 * UI_SLIDER_HEIGHT;
    sliderBounds.y += 2 * UI_SLIDER_HEIGHT;

    GuiLabel(labelBounds, "Damping Coeficient (c)");
    GuiSlider(sliderBounds, TextFormat("c=%.1f", systemState->damping), NULL, &systemState->damping, c_min, c_max);
    labelBounds.y += 2 * UI_SLIDER_HEIGHT;
    sliderBounds.y += 2 * UI_SLIDER_HEIGHT;

    GuiLabel(labelBounds, "Restitution (e)");
    GuiSlider(sliderBounds, TextFormat("e=%.1f", systemState->restitution), NULL, &systemState->restitution, e_min,
              e_max);
}

void ShowDamping(float c, float k, float m, SimColor themeColor)
{
    // For a mass-spring-damper system, the critical damping coefficient is:
    //   c_crit = 2 * sqrt(k * m)
    // This is the boundary between oscillatory (underdamped) and non-oscillatory behavior.
    float criticalDamping = 2.0f * sqrt(k * m);

    // Damping ratio:
    //   zeta = c / c_crit
    // zeta < 1 -> underdamped, zeta = 1 -> critically damped, zeta > 1 -> overdamped.
    float zeta = c / criticalDamping;

    // Since sliders and floating point values will rarely land on exactly 1.0,
    // classify "critically damped" within a small band around 1.
    const float eps = 0.05f; // 5% band

    const char *dampingType = (zeta < 1.0f - eps)   ? "Underdamped"
                              : (zeta > 1.0f + eps) ? "Overdamped"
                                                    : "Critically damped";

    const int fontSize = 20;
    // UPDATE if I change this to label i wont have to pass themeColor
    DrawText(dampingType, UI_SLIDER_X, UI_SLIDER_Y + 7 * UI_SLIDER_HEIGHT + 5, fontSize,
             SimColorToRayColor(themeColor));
}

int ShowPauseDialog()
{
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    float dialogWidth = screenWidth / 2;
    float dialogHeight = screenHeight / 2;

    float x = (screenWidth / 2) - (dialogWidth / 2);
    float y = (screenHeight / 2) - (dialogHeight / 2);

    Rectangle dialogBounds = { x, y, dialogWidth, dialogHeight };

    DrawRectangleRec(dialogBounds, BLACK);
    GuiGroupBox(dialogBounds, NULL);

    const char *text = "Paused";
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(text, x + (dialogWidth / 2) - (textWidth / 2), y + 10, fontSize, GRAY);

    // Add buttons inside the group box
    int numButtons = 3; // UPDATE if button is added, need a fix for this
    float buttonWidth = 150;
    float buttonHeight = 40;
    float buttonX = x + (dialogWidth - buttonWidth) / 2;
    int i = 1;

    Rectangle resumeButtonBounds = { buttonX, y + dialogHeight * i / (numButtons + 1), buttonWidth, buttonHeight };
    if (GuiButton(resumeButtonBounds, "Resume"))
    {
        return 1;
    }
    i++;

    Rectangle settingsButtonBounds = { buttonX, y + dialogHeight * i / (numButtons + 1), buttonWidth, buttonHeight };
    if (GuiButton(settingsButtonBounds, "Settings"))
    {
        return 2;
    }
    i++;

    Rectangle exitButtonBounds = { buttonX, y + dialogHeight * i / (numButtons + 1), buttonWidth, buttonHeight };
    if (GuiButton(exitButtonBounds, "Exit"))
    {
        return 3;
    }
    return -1;
}

int ShowSettings()
{
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    float dialogWidth = screenWidth / 2;
    float dialogHeight = screenHeight / 2;

    float x = (screenWidth / 2) - (dialogWidth / 2);
    float y = (screenHeight / 2) - (dialogHeight / 2);

    Rectangle dialogBounds = { x, y, dialogWidth, dialogHeight };

    DrawRectangleRec(dialogBounds, BLACK);
    GuiGroupBox(dialogBounds, NULL);

    const char *text = "Settings";
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(text, x + (dialogWidth / 2) - (textWidth / 2), y + 10, fontSize, GRAY);

    // Add buttons inside the group box
    int numButtons = 2; // UPDATE if button is added, need a fix for this
    float buttonWidth = 150;
    float buttonHeight = 40;
    float buttonX = x + (dialogWidth - buttonWidth) / 2;
    int i = 1;

    Rectangle parametersButtonBounds = { buttonX, y + dialogHeight * i / (numButtons + 1), buttonWidth, buttonHeight };
    if (GuiButton(parametersButtonBounds, "Change Parameter Values"))
    {
        // TODO: Implement..
    }
    i++;

    Rectangle themeButtonBounds = { buttonX, y + dialogHeight * i / (numButtons + 1), buttonWidth, buttonHeight };
    if (GuiButton(themeButtonBounds, "Change Theme"))
    {
        return 2;
    }
    return -1;
}

// FIXME: I dont like these globals..
bool showColorPanel = false;
bool showColorScroll = true;
void ShowThemeChange(SpringMassRenderState *state)
{
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    float dialogWidth = screenWidth / 2;
    float dialogHeight = screenHeight / 2;

    float x = (screenWidth / 2) - (dialogWidth / 2);
    float y = (screenHeight / 2) - (dialogHeight / 2);

    Rectangle dialogBounds = { x, y, dialogWidth, dialogHeight };

    DrawRectangleRec(dialogBounds, BLACK);
    GuiGroupBox(dialogBounds, NULL);

    const char *text = "Change Theme";
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(text, x + (dialogWidth / 2) - (textWidth / 2), y + 10, fontSize, GRAY);

    // Add buttons inside the group box
    int numButtons = 2; // UPDATE if button is added, need a fix for this
    float buttonWidth = 150;
    float buttonHeight = 40;
    float buttonX = x + (dialogWidth - buttonWidth) / 2;
    int i = 1;

    static int listViewScroll = 0;
    static int active = 0;
    static int focus = -1;

    // Array of sim colors matching the list
    static SimColor themeColors[] = { SIM_DARKGRAY,   SIM_MAROON,    SIM_ORANGE, SIM_DARKGREEN, SIM_DARKBLUE,
                                      SIM_DARKPURPLE, SIM_DARKBROWN, SIM_GRAY,   SIM_RED,       SIM_GOLD,
                                      SIM_LIME,       SIM_BLUE,      SIM_VIOLET, SIM_BROWN,     SIM_LIGHTGRAY,
                                      SIM_PINK,       SIM_YELLOW,    SIM_GREEN,  SIM_SKYBLUE,   SIM_PURPLE,
                                      SIM_BEIGE };

    static const char *colorNames[] = { "DARKGRAY",  "MAROON", "ORANGE",    "DARKGREEN", "DARKBLUE", "DARKPURPLE",
                                        "DARKBROWN", "GRAY",   "RED",       "GOLD",      "LIME",     "BLUE",
                                        "VIOLET",    "BROWN",  "LIGHTGRAY", "PINK",      "YELLOW",   "GREEN",
                                        "SKYBLUE",   "PURPLE", "BEIGE" };

    Rectangle colorsListBounds = { buttonX, y + dialogHeight * i / (numButtons + 1), buttonWidth, buttonHeight * 3 };
    if (showColorScroll)
    {
        int result = GuiListViewEx(colorsListBounds, colorNames, 21, &listViewScroll, &active, &focus);

        // Apply the theme color based on the selected item (active)
        if (active >= 0 && active < 21)
        {
            SetThemeColor(themeColors[active]);
            state->themeColor = themeColors[active];
        }
    }
    i++;

    static bool showColorPanel = false;
    static Color customColor = BLUE;

    Rectangle customColorButtonBounds = { buttonX, y + dialogHeight * i / (numButtons + 1) + 20, buttonWidth,
                                          buttonHeight };
    if (GuiButton(customColorButtonBounds, "Custom"))
    {
        showColorPanel = !showColorPanel; // Toggle the panel
    }

    if (showColorPanel)
    {
        Rectangle colorPickerBounds = { x + (dialogWidth / 2) - 100, y + (dialogHeight / 2) - 100, 200, 200 };
        GuiColorPicker(colorPickerBounds, NULL, &customColor);

        // Apply the custom color
        SetThemeColor(RayColorToSimColor(customColor));
        state->themeColor = RayColorToSimColor(customColor);
    }
}

bool EscKeyPressed()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        return true;
    }
    return false;
}

bool ExitButtonClicked()
{
    return !WindowShouldClose();
}

void DestroyRenderer()
{
    CloseWindow();
}

Vec2D GetMousePOS()
{
    Vector2 point = GetMousePosition();
    return (Vec2D){ point.x, point.y };
}

bool LeftMouseButtonPressed()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return true;
    }
    return false;
}

bool LeftMouseButtonReleased()
{
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        return true;
    }
    return false;
}

bool LeftMouseButtonDown()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return true;
    }
    return false;
}

bool ClickInBoundingBox(SimRect boundingBox)
{
    Vector2 mousePosition = GetMousePosition();
    if (mousePosition.x >= boundingBox.x && mousePosition.x <= boundingBox.x + boundingBox.width)
    {
        if (mousePosition.y >= boundingBox.y && mousePosition.y <= boundingBox.y + boundingBox.height)
        {
            return true;
        }
    }
    return false;
}
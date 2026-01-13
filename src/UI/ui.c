/**
 * @file ui.c
 * @brief Implementation of the User Interface for the Spring-Mass System Simulation.
 * @author Gabe G.
 * @date 1-13-2026
 */

#define RAYGUI_IMPLEMENTATION
#include "UI/ui.h"
#include "core/consts.h"
#include "raygui.h"

void SetThemeColor(Color themeColor)
{
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt(themeColor));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(themeColor));
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(themeColor));
}

void DrawVariableSliders(SpringMassSystemState *systemState)
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
    Rectangle sliderBounds = (Rectangle){ UI_SLIDER_X, UI_SLIDER_Y, UI_SLIDER_WIDTH, UI_SLIDER_HEIGHT};
    Rectangle labelBounds = (Rectangle){ UI_SLIDER_X, UI_SLIDER_Y - 20, UI_SLIDER_WIDTH, UI_SLIDER_HEIGHT};

    // Draw sliders and labels
    GuiLabel(labelBounds, "Spring Constant (k)");
    GuiSlider(sliderBounds, TextFormat("k=%.1f", systemState->springConst), NULL, &systemState->springConst, k_min, k_max);
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
    GuiSlider(sliderBounds, TextFormat("e=%.1f", systemState->restitution), NULL, &systemState->restitution, e_min, e_max);
}

void ShowDamping(float c, float k, float m, Color themeColor)
{
    // For a mass-spring-damper system, the critical damping coefficient is:
    //   c_crit = 2 * sqrt(k * m)
    // This is the boundary between oscillatory (underdamped) and non-oscillatory behavior.
    float criticalDamping = 2.0f * sqrt(k * m);

    // Damping ratio:
    //   zeta = c / c_crit
    // zeta < 1 => underdamped, zeta = 1 => critically damped, zeta > 1 => overdamped.
    float zeta = c / criticalDamping;

    // Since sliders and floating point values will rarely land on exactly 1.0,
    // classify "critically damped" within a small band around 1.
    const float eps = 0.05f; // 5% band

    const char *dampingType = 
        (zeta < 1.0f - eps) ? "Underdamped":
        (zeta > 1.0f + eps) ? "Overdamped":
        "Critically damped";

    const int fontSize = 20;
    // UPDATE if I change this to label i wont have to pass themeColor
    DrawText(dampingType, UI_SLIDER_X, UI_SLIDER_Y + 7 * UI_SLIDER_HEIGHT + 5, fontSize, themeColor); 
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

bool showColorPanel = false; // This is bad, change this..
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
        
        // Array of colors matching the list
        static Color themeColors[] = {
            DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN,
            GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN,
            LIGHTGRAY, PINK, YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE
        };
        
        static const char* colorNames[] = {
            "DARKGRAY", "MAROON", "ORANGE", "DARKGREEN", "DARKBLUE", "DARKPURPLE", "DARKBROWN",
            "GRAY", "RED", "GOLD", "LIME", "BLUE", "VIOLET", "BROWN",
            "LIGHTGRAY", "PINK", "YELLOW", "GREEN", "SKYBLUE", "PURPLE", "BEIGE"
        };
        
        Rectangle colorsListBounds = { buttonX, y + dialogHeight * i / (numButtons + 1), buttonWidth, buttonHeight * 3 };
        if (showColorScroll)
        {
            int result = GuiListViewEx(colorsListBounds, 
                        colorNames,
                        21,
                        &listViewScroll,
                        &active,
                        &focus);
            
            // Apply the theme color based on the selected item (active)
            if (active >= 0 && active < 21) {
                SetThemeColor(themeColors[active]);
                state->themeColor = themeColors[active];
            }
        }
        i++;
    
    static bool showColorPanel = false;
    static Color customColor = BLUE;
    
    Rectangle customColorButtonBounds = { buttonX, y + dialogHeight * i / (numButtons + 1) + 20, buttonWidth, buttonHeight };
    if (GuiButton(customColorButtonBounds, "Custom"))
    {
        showColorPanel = !showColorPanel;  // Toggle the panel
    }
    
    if (showColorPanel)
    {
        Rectangle colorPickerBounds = { x + (dialogWidth / 2) - 100, y + (dialogHeight / 2) - 100, 200, 200 };
        GuiColorPicker(colorPickerBounds, NULL, &customColor);
        
        // Apply the custom color
        SetThemeColor(customColor);
        state->themeColor = customColor;
    }
}




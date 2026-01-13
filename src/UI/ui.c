#define RAYGUI_IMPLEMENTATION
#include "UI/ui.h"
#include "core/consts.h"
#include "raygui.h"

void DrawVariableSliders(SpringMassSystemState *state)
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

    // Change label color to blue
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt(BLUE));

    // Draw sliders and labels
    GuiLabel(labelBounds, "Spring Constant (k)");
    GuiSlider(sliderBounds, TextFormat("k=%.1f", state->springConst), NULL, &state->springConst, k_min, k_max);
    labelBounds.y += 2 * UI_SLIDER_HEIGHT;
    sliderBounds.y += 2 * UI_SLIDER_HEIGHT;

    GuiLabel(labelBounds, "Mass (m)");
    GuiSlider(sliderBounds, TextFormat("m=%.1f", state->mass), NULL, &state->mass, m_min, m_max);
    labelBounds.y += 2 * UI_SLIDER_HEIGHT;
    sliderBounds.y += 2 * UI_SLIDER_HEIGHT;
    
    GuiLabel(labelBounds, "Damping Coeficient (c)");
    GuiSlider(sliderBounds, TextFormat("c=%.1f", state->damping), NULL, &state->damping, c_min, c_max);
    labelBounds.y += 2 * UI_SLIDER_HEIGHT;
    sliderBounds.y += 2 * UI_SLIDER_HEIGHT;
    
    GuiLabel(labelBounds, "Restitution (e)");
    GuiSlider(sliderBounds, TextFormat("e=%.1f", state->restitution), NULL, &state->restitution, e_min, e_max);

    // Reset label color to gray
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt(GRAY));
}

void ShowDamping(float c, float k, float m)
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
    DrawText(dampingType, UI_SLIDER_X, UI_SLIDER_Y + 7 * UI_SLIDER_HEIGHT + 5, fontSize, BLUE);
}

int ShowPauseDialog()
{
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    
    float dialogWidth = screenWidth / 2;
    float dialogHeight = screenHeight / 2;

    float x = (screenWidth / 2) - (dialogWidth / 2);
    float y = (screenHeight / 2) - (dialogHeight / 2);

    Rectangle bounds = { x, y, dialogWidth, dialogHeight };
    Rectangle clearRect = { x, y, dialogWidth, dialogHeight };

    DrawRectangleRec(clearRect, BLACK);
    GuiGroupBox(bounds, NULL);

    const char *text = "Paused";
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);

    DrawText(text, x + (dialogWidth / 2) - (textWidth / 2), y + 10, fontSize, GRAY);
    
    // Add buttons inside the group box
    float buttonWidth = 150;
    float buttonHeight = 40;
    float buttonX = x + (dialogWidth - buttonWidth) / 2;
    float buttonY = y + dialogHeight / 2;
    
    Rectangle buttonBounds = { buttonX, buttonY, buttonWidth, buttonHeight };
    
    if (GuiButton(buttonBounds, "Resume"))
    {
        return 0;
    }

    return 1;
}

static void DrawPauseButtons()
{
    
}
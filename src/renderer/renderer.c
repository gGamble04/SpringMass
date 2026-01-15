/**
 * @file renderer.c
 * @brief Implementation of the Spring-Mass System Rendering.
 * @author Gabe G.
 * @date 1-13-2026
 */

#include "renderer/renderer.h"
#include "math.h"

// TODO: Why is the position a rectangle? Should be a Vector2 only??!
void InitRender(SpringMassRenderState *state, int windowWidth, int windowHeight, const char *title)
{
    InitWindow(windowWidth, windowHeight, title);
    SetExitKey(KEY_NULL);

    state->massRectangle = (Rectangle){ 150, FLOOR_HEIGHT - RECT_SIZE - FLOOR_THICKNESS / 2, RECT_SIZE, RECT_SIZE }; // Initial position of the mass
    state->massColor = RED; // Color of the mass rectangle
    
    state->themeColor = SIM_BLUE;
    
    state->springAnchorPoint = (Vector2){ 0, state->massRectangle.y + RECT_SIZE / 2 }; // Fixed anchor point of the spring
    state->springAttachPoint = (Vector2){ state->massRectangle.x, state->massRectangle.y + RECT_SIZE / 2 }; // Attachment point of the spring on the mass
    state->numSpringSegments = SPRING_SEGMENTS; // Number of segments in the spring
    state->segmentLength = SPRING_SEGMENT_LENGTH; // Length of each spring segment
    
    state->floorStart = (Vector2){ 0, FLOOR_HEIGHT }; // Start point of the floor line
    state->floorEnd = (Vector2){ WIDTH, FLOOR_HEIGHT}; // End point of the floor line
    state->floorThickness = FLOOR_THICKNESS; // Thickness of the floor line

    state->elapsedTime = 0.0f;
}

void ShowStartupText(SpringMassRenderState *state)
{
    DrawText("Spring-Mass System", 10, 10, 30, SimColorToRayColor(state->themeColor)); // Title 

    const char *text1 = "Welcome to the Spring-Mass Simulation!";
    int fontSize1 = 20;
    int textWidth1 = MeasureText(text1, fontSize1);
    DrawText(text1, WIDTH / 2 - textWidth1 / 2, HEIGHT / 2 - 100, fontSize1, RAYWHITE);

    const char *text2 = "Click and drag to move the mass";
    int fontSize2 = 15;
    int textWidth2 = MeasureText(text2, fontSize2);
    DrawText(text2, WIDTH / 2 - textWidth2 / 2, HEIGHT / 2 - 80, fontSize2, RAYWHITE);

    const char *text3 = "Edits parameters with sliders in top right (or in settings)";
    int fontSize3 = 15;
    int textWidth3 = MeasureText(text3, fontSize3);
    DrawText(text3, WIDTH / 2 - textWidth3 / 2, HEIGHT / 2 - 60, fontSize3, RAYWHITE);

    const char *text4 = "ESC to pause";
    int fontSize4 = 15;
    int textWidth4 = MeasureText(text4, fontSize4);
    DrawText(text4, WIDTH / 2 - textWidth4 / 2, HEIGHT / 2 - 40, fontSize4, RAYWHITE);
}

void ShowStartupTextFadeOut(SpringMassRenderState *state, float dt, float fadeTime)
{
    state->elapsedTime += dt;
    float cosValue = cos((PI / (2.0f * fadeTime)) * state->elapsedTime); // 1.0 to 0.0 (smooth): cos( π/(2a) * x ), a = fadeTime, x = elapsedTime
    if (cosValue < 0.0f) cosValue = 0.0f; // Clamp to 0
    int alpha = (int)(cosValue * 255.0f); // Map 0-1 to 0-255

    Color color = SimColorToRayColor(state->themeColor);
    color.a = alpha;
    DrawText("Spring-Mass System", 10, 10, 30, color); // Title 

    const char *text1 = "Welcome to the Spring-Mass Simulation!";
    int fontSize1 = 20;
    int textWidth1 = MeasureText(text1, fontSize1);
    DrawText(text1, WIDTH / 2 - textWidth1 / 2, HEIGHT / 2 - 100, fontSize1, (Color){ 245, 245, 245, alpha });

    const char *text2 = "Click and drag to move the mass";
    int fontSize2 = 15;
    int textWidth2 = MeasureText(text2, fontSize2);
    DrawText(text2, WIDTH / 2 - textWidth2 / 2, HEIGHT / 2 - 80, fontSize2, (Color){ 245, 245, 245, alpha });

    const char *text3 = "Edits parameters with sliders in top right (or in settings)";
    int fontSize3 = 15;
    int textWidth3 = MeasureText(text3, fontSize3);
    DrawText(text3, WIDTH / 2 - textWidth3 / 2, HEIGHT / 2 - 60, fontSize3, (Color){ 245, 245, 245, alpha });

    const char *text4 = "ESC to pause";
    int fontSize4 = 15;
    int textWidth4 = MeasureText(text4, fontSize4);
    DrawText(text4, WIDTH / 2 - textWidth4 / 2, HEIGHT / 2 - 40, fontSize4, (Color){ 245, 245, 245, alpha });
}

void DrawFloor(SpringMassRenderState state)
{
    DrawLineEx(state.floorStart, state.floorEnd, state.floorThickness, GRAY); // Draw the floor line
}


void DrawMass(SpringMassRenderState state)
{
    DrawRectangleRec(state.massRectangle, state.massColor); // Draw the mass rectangle
}

void DrawSpring(SpringMassRenderState state)
{

    Vector2 anchor = state.springAnchorPoint;
    Vector2 attach = state.springAttachPoint;
    
    int numSegments = state.numSpringSegments;
    float segmentLength = state.segmentLength;

    if (numSegments < 1) return; // No segments to draw
    Vector2 deltaSpring = vec2Sub(attach, anchor); // Vector from anchor to attach point
    float totalLength = vec2Length(deltaSpring); // Total length from anchor to attach point

    // If start==end, nothing meaningful to do (all segments collapse)
    if (totalLength <= 1e-6f) return;

    // Unit tangent
    Vector2 unitTangent = vec2Scale(deltaSpring, 1.0f / totalLength);

    // Unit normal (perpendicular)
    Vector2 unitNormal = (Vector2){ -unitTangent.y, unitTangent.x };

    // Centerline step per segment
    float stepLength = totalLength / (float)numSegments;

    // Amplitude to preserve segment length: seg_len^2 = d^2 + A^2
    float amplitudeSquared = segmentLength*segmentLength - stepLength*stepLength;
    float amplitude = (amplitudeSquared > 0.0f) ? sqrtf(amplitudeSquared) : 0.0f; // clamp if too stretched

    // Draw the spring as a zig-zag polyline from `anchor` -> `attach`.
    //
    // We walk along the spring centerline in `stepLength` increments (unitTangent),
    // and offset alternating vertices by +/- `amplitude` along the normal (unitNormal)
    // to create the zig-zag.
    //
    // Endpoints are special-cased so the spring starts exactly at `anchor` and ends
    // exactly at `attach`.
    for (int i = 0; i < numSegments; i++) 
    {
        // Current vertex: centerline point + alternating normal offset.
        Vector2 centerPoint = vec2Add(anchor, vec2Scale(unitTangent, (float)i * stepLength));
        Vector2 vertex;
        if (i == 0) vertex = anchor;
        else vertex = vec2Add(centerPoint, vec2Scale(unitNormal, ((i % 2) ? +amplitude : -amplitude)));

        int nextIndex = i + 1;
        // Next vertex (the other end of this segment).
        Vector2 nextCenterPoint = vec2Add(anchor, vec2Scale(unitTangent, (float)nextIndex * stepLength));
        Vector2 nextVertex;
        if (nextIndex == numSegments) nextVertex = attach;
        else nextVertex = vec2Add(nextCenterPoint, vec2Scale(unitNormal, ((nextIndex % 2) ? +amplitude : -amplitude)));

        // Draw this segment of the polyline.
        DrawLineEx(vertex, nextVertex, 2, WHITE);
    }
}

void DrawRender(SpringMassRenderState state)
{   
    DrawFloor(state);
    DrawMass(state);
    DrawSpring(state);
}

void UpdateRender(SpringMassRenderState *state)
{   
    DrawFloor(*state);
    state->springAttachPoint.x = state->massRectangle.x;
    DrawMass(*state);
    DrawSpring(*state);
}

void Render_BeginDrawing()
{
    BeginDrawing();
}

void Render_EndDrawing()
{
    EndDrawing();
}

void Render_ClearBackground(SimColor color)
{
    ClearBackground(SimColorToRayColor(color));
}

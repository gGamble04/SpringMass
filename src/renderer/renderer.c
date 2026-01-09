#include "renderer/renderer.h"
#include "core/consts.h"

void InitRender(SpringMassRenderState *state)
{
    state->position = (Rectangle){ 150, FLOOR_HEIGHT - RECT_SIZE - FLOOR_THICKNESS / 2, RECT_SIZE, RECT_SIZE }; // Initial position of the mass
    state->springAnchorPoint = (Vector2){ 0, state->position.y + RECT_SIZE / 2 }; // Fixed anchor point of the spring
    state->springAttachPoint = (Vector2){ state->position.x, state->position.y + RECT_SIZE / 2 }; // Attachment point of the spring on the mass
    state->numSpringSegments = SPRING_SEGMENTS; // Number of segments in the spring
    state->segmentLength = SPRING_SEGMENT_LENGTH; // Length of each spring segment
    state->floorStart = (Vector2){ 0, FLOOR_HEIGHT }; // Start point of the floor line
    state->floorEnd = (Vector2){ WIDTH, FLOOR_HEIGHT}; // End point of the floor line
    state->floorThickness = FLOOR_THICKNESS; // Thickness of the floor line
}

void DrawFloor(SpringMassRenderState state)
{
    DrawLineEx(state.floorStart, state.floorEnd, state.floorThickness, GRAY); // Draw the floor line
}


void DrawMass(SpringMassRenderState state)
{
    DrawRectangleRec(state.position, RED); // Draw the mass rectangle
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
    state->springAttachPoint.x = state->position.x;
    DrawMass(*state);
    DrawSpring(*state);
}
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 velocity;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 size;
layout (location = 4) in float timeToLive;

out vec3 positionOut;
out vec3 velocityOut;
out vec4 colorOut;
out vec2 sizeOut;
out float timeToLiveOut;

uniform float time;
uniform float dt;

uint seed = uint(time * 1000.0) + uint(gl_VertexID);
uint randhash() {
    uint i = ((seed++)^12345391u)*2654435769u;
    i ^= (i<<6u)^(i>>26u); i *= 2654435769u; i += (i<<5u)^(i>>12u);
    return i;
}
float random() {
    const float UINT_MAX = 4294967295.0;
    return float(randhash()) / UINT_MAX;
}

// Increased lifetime and speed for taller flame
const float MIN_TIME_TO_LIVE = 1.0f;    // Increased from 0.9f
const float MAX_TIME_TO_LIVE = 1.5f;    // Increased from 1.3f
const float INITIAL_HEIGHT = 0.0f;
const float INITIAL_SPEED_MIN = 0.5f;   // Increased from 0.45f
const float INITIAL_SPEED_MAX = 0.75f;  // Increased from 0.65f
const vec3 ACCELERATION = vec3(0.0f, 0.3f, 0.0f);  // Increased from 0.25f

// Color parameters (keeping vibrant yellow at bottom)
const float INITIAL_ALPHA = 0.0f;
const float MAX_ALPHA = 0.4f;
const vec3 BRIGHT_YELLOW = vec3(1.0f, 1.0f, 0.2f);
const vec3 YELLOW_ORANGE = vec3(1.0f, 0.8f, 0.1f);
const vec3 ORANGE_COLOR = vec3(1.0f, 0.5f, 0.1f);
const vec3 RED_COLOR = vec3(0.8f, 0.1f, 0.0f);
const vec3 BROWN_COLOR = vec3(0.4f, 0.15f, 0.05f);

// Size parameters - increased height components
const float INITIAL_WIDTH = 0.5f;
const float WIDTH_GROWTH_FACTOR = 1.8f;
const float INITIAL_HEIGHT_SIZE = 0.8f;  // Increased from 0.7f
const float PEAK_HEIGHT_SCALE = 2.0f;    // Increased from 1.8f

void main() {
    if (timeToLive <= 0.0f) {
        // Initialize new particle with wider base and vibrant yellow
        float horizontalSpread = (random() - 0.5) * INITIAL_WIDTH * 1.2f;
        positionOut = vec3(horizontalSpread, INITIAL_HEIGHT, 0.0);
        velocityOut = vec3(0.0, mix(INITIAL_SPEED_MIN, INITIAL_SPEED_MAX, random()), 0.0);
        timeToLiveOut = mix(MIN_TIME_TO_LIVE, MAX_TIME_TO_LIVE, random());
        colorOut = vec4(BRIGHT_YELLOW, INITIAL_ALPHA);
        sizeOut = vec2(INITIAL_WIDTH, INITIAL_HEIGHT_SIZE);
    } else {
        // Update existing particle
        vec3 newVelocity = velocity + ACCELERATION * dt;
        vec3 newPosition = position + newVelocity * dt;
        float newTimeToLive = timeToLive - dt;

        float tNorm = 1.0 - (newTimeToLive / mix(MIN_TIME_TO_LIVE, MAX_TIME_TO_LIVE, random()));

        // Color transition with extended yellow phase
        vec3 c;
        if (tNorm < 0.4) {
            if (tNorm < 0.2) {
                c = mix(BRIGHT_YELLOW, YELLOW_ORANGE, tNorm / 0.2);
            } else {
                c = mix(YELLOW_ORANGE, ORANGE_COLOR, (tNorm - 0.2) / 0.2);
            }
        } else if (tNorm < 0.6) {
            c = mix(ORANGE_COLOR, RED_COLOR, (tNorm - 0.4) / 0.2);
        } else if (tNorm < 0.8) {
            c = mix(RED_COLOR, BROWN_COLOR, (tNorm - 0.6) / 0.2);
        } else {
            c = BROWN_COLOR;
        }

        // Alpha fade
        float a;
        if (tNorm < 0.2) {
            a = smoothstep(0.0, 0.2, tNorm) * MAX_ALPHA;
        } else if (tNorm < 0.7) {
            a = MAX_ALPHA;
        } else {
            a = (1.0 - smoothstep(0.7, 1.0, tNorm)) * MAX_ALPHA;
        }

        // Size scaling with increased height
        float widthScale;
        float heightScale;
        if (tNorm < 0.3) {
            widthScale = mix(1.0, WIDTH_GROWTH_FACTOR * 0.7, tNorm / 0.3);
            heightScale = mix(1.0, 1.5, tNorm / 0.3);  // Increased initial growth
        } else if (tNorm < 0.7) {
            widthScale = mix(WIDTH_GROWTH_FACTOR * 0.7, WIDTH_GROWTH_FACTOR, (tNorm - 0.3) / 0.4);
            heightScale = mix(1.5, PEAK_HEIGHT_SCALE, (tNorm - 0.3) / 0.4);  // Taller peak
        } else {
            widthScale = mix(WIDTH_GROWTH_FACTOR, 0.8, (tNorm - 0.7) / 0.3);
            heightScale = mix(PEAK_HEIGHT_SCALE, 0.6, (tNorm - 0.7) / 0.3);
        }

        positionOut = newPosition;
        velocityOut = newVelocity;
        timeToLiveOut = newTimeToLive;
        colorOut = vec4(c, a);
        sizeOut = vec2(INITIAL_WIDTH * widthScale, INITIAL_HEIGHT_SIZE * heightScale);
    }
}
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

const float MIN_TIME_TO_LIVE = 1.5f;
const float MAX_TIME_TO_LIVE = 2.5f;
const float INITIAL_HEIGHT = 0.0f;

const float INITIAL_SPEED_MIN = 0.8f;
const float INITIAL_SPEED_MAX = 1.2f;

const float INITIAL_ALPHA = 0.0f;
const float MAX_ALPHA = 0.4f;
const vec3 YELLOW_COLOR = vec3(1.0f, 0.9f, 0.1f);
const vec3 ORANGE_COLOR = vec3(1.0f, 0.5f, 0.1f);
const vec3 RED_COLOR = vec3(0.8f, 0.1f, 0.0f);

const vec3 ACCELERATION = vec3(0.0f, 0.5f, 0.0f);

void main() {
    if (timeToLive <= 0.0f) {
        // Initialize new particle - spawn at center, move straight up
        positionOut = vec3(0.0, INITIAL_HEIGHT, 0.0);
        velocityOut = vec3(0.0, mix(INITIAL_SPEED_MIN, INITIAL_SPEED_MAX, random()), 0.0);
        timeToLiveOut = mix(MIN_TIME_TO_LIVE, MAX_TIME_TO_LIVE, random());
        colorOut = vec4(YELLOW_COLOR, INITIAL_ALPHA);
        sizeOut = vec2(0.3f, 0.6f);
    } else {
        // Update existing particle - only vertical movement
        vec3 newVelocity = velocity + ACCELERATION * dt;
        vec3 newPosition = position + newVelocity * dt;
        float newTimeToLive = timeToLive - dt;

        float tNorm = 1.0 - (newTimeToLive / mix(MIN_TIME_TO_LIVE, MAX_TIME_TO_LIVE, random()));

        // Color transition
        vec3 c;
        if (tNorm < 0.3) {
            c = mix(YELLOW_COLOR, ORANGE_COLOR, tNorm / 0.3);
        } else if (tNorm < 0.7) {
            c = mix(ORANGE_COLOR, RED_COLOR, (tNorm - 0.3) / 0.4);
        } else {
            c = RED_COLOR;
        }

        // Alpha fade
        float a;
        if (tNorm < 0.2) {
            a = smoothstep(0.0, 0.2, tNorm) * MAX_ALPHA;
        } else {
            a = (1.0 - smoothstep(0.2, 1.0, tNorm)) * MAX_ALPHA;
        }

        // Size scaling
        float sizeScale;
        if (tNorm < 0.3) {
            sizeScale = mix(0.5, 1.5, tNorm / 0.3);
        } else if (tNorm < 0.7) {
            sizeScale = mix(1.5, 2.0, (tNorm - 0.3) / 0.4);
        } else {
            sizeScale = mix(2.0, 0.5, (tNorm - 0.7) / 0.3);
        }

        positionOut = newPosition;
        velocityOut = newVelocity;
        timeToLiveOut = newTimeToLive;
        colorOut = vec4(c, a);
        sizeOut = vec2(0.3f * sizeScale, 0.6f * sizeScale);
    }
}
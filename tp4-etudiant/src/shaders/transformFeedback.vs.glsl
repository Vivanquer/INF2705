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

const float PI = 3.14159265359f;
vec3 randomInCircle(in float radius, in float height) {
    float r = radius * sqrt(random());
    float theta = random() * 2 * PI;
    return vec3(r * cos(theta), height, r * sin(theta));
}

// Particle creation parameters
const float INITIAL_RADIUS = 0.2f;
const float INITIAL_HEIGHT = 0.0f;
const float TARGET_RADIUS = 0.5f;
const float TARGET_HEIGHT = 5.0f;
const float INITIAL_SPEED_MIN = 0.5f;
const float INITIAL_SPEED_MAX = 0.6f;
const float MIN_TIME_TO_LIVE = 1.7f;
const float MAX_TIME_TO_LIVE = 2.0f;
const vec3 YELLOW_COLOR = vec3(1.0f, 0.9f, 0.0f);
const vec3 ORANGE_COLOR = vec3(1.0f, 0.4f, 0.2f);
const vec3 DARK_RED_COLOR = vec3(0.1f, 0.0f, 0.0f);
const vec3 ACCELERATION = vec3(0.0f, 0.1f, 0.0f);

void main() {
    if (timeToLive <= 0.0f) {
        // Particle creation - exactly as specified
        positionOut = randomInCircle(INITIAL_RADIUS, INITIAL_HEIGHT);
        
        vec3 target = randomInCircle(TARGET_RADIUS, TARGET_HEIGHT);
        vec3 dir = normalize(target - positionOut);
        
        float speed = mix(INITIAL_SPEED_MIN, INITIAL_SPEED_MAX, random());
        velocityOut = dir * speed;

        timeToLiveOut = mix(MIN_TIME_TO_LIVE, MAX_TIME_TO_LIVE, random());
        
        colorOut = vec4(YELLOW_COLOR, 0.0f);
        sizeOut = vec2(0.5f, 1.0f); // Initial scale: x = 0.5 (crushed by 2), y = 1.0
    } else {
        // Particle update - exactly as specified
        vec3 newPosition = position + velocity * dt; // Euler integration
        vec3 newVelocity = velocity + ACCELERATION * dt; // Euler with constant acceleration
        float newTimeToLive = timeToLive - dt;

        float tNorm = 1.0 - (newTimeToLive / mix(MIN_TIME_TO_LIVE, MAX_TIME_TO_LIVE, random()));

        // Color transitions as specified
        vec3 c = YELLOW_COLOR;
        if (tNorm > 0.25) {
            if (tNorm < 0.3) {
                c = mix(YELLOW_COLOR, ORANGE_COLOR, (tNorm - 0.25) / 0.05);
            } else if (tNorm < 0.5) {
                c = ORANGE_COLOR;
            } else {
                c = mix(ORANGE_COLOR, DARK_RED_COLOR, (tNorm - 0.5) / 0.5);
            }
        }

        // Alpha curve as specified
        float fadeIn = smoothstep(0.0, 0.2, tNorm);
        float fadeOut = 1.0 - smoothstep(0.8, 1.0, tNorm);
        float a = 0.1 * fadeIn * fadeOut;

        // Size scaling as specified
        float sizeScale = mix(1.0, 1.5, tNorm);
        vec2 size = vec2(0.5f * sizeScale, 1.0f * sizeScale);

        positionOut = newPosition;
        velocityOut = newVelocity;
        timeToLiveOut = newTimeToLive;
        colorOut = vec4(c, a);
        sizeOut = size;
    }
}
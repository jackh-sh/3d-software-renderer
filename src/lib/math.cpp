#include "math.h"
#include "../constants.h"
#include <cmath>

Vector2 toScreen(Vector2 point) {
    return Vector2{
        .x = (point.x +1)/2 * SCREEN_WIDTH,
        .y = (1-(point.y +1)/2) * SCREEN_HEIGHT,
    };
};

Vector2 vec2(float x, float y) {
    return Vector2{
        .x=x,
        .y=y
    };
}

Vector2 project(Vector3 p) {
    const float cameraZ = 1.0f;     // distance from origin
    float z = p.z + cameraZ;        // ensure z > 0

    return vec2(p.x / z, p.y / z);
}

Vector3 vec3(float x, float y, float z) {
    return Vector3{
        .x=x,
        .y=y,
        .z=z
    };
}

Vector3 rotate_xz(Vector3 p, float a) {
    float c = cos(a);
    float s = sin(a);

    return vec3(p.x*c-p.z*s, p.y, p.x*s+p.z*c);
}

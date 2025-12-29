struct Vector2 {
    float x;
    float y;
};

Vector2 toScreen(Vector2 point);
Vector2 vec2(float x, float y);

struct Vector3 {
    float x;
    float y;
    float z;
};

Vector2 project(Vector3 point);
Vector3 vec3(float x, float y, float z);
Vector3 rotate_xz(Vector3 p, float a);

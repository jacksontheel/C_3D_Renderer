#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

// 2D
float vec2_length(vec2_t vec);
vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_subtract(vec2_t a, vec2_t b);
vec2_t vec2_multiply(vec2_t vec, float factor);
vec2_t vec2_divide(vec2_t vec, float factor);
vec2_t vec2_divide(vec2_t vec, float factor);
float vec2_dot(vec2_t a, vec2_t b);

void vec2_normalize(vec2_t* vec);


// 3D
float vec3_length(vec3_t vec);
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_subtract(vec3_t a, vec3_t b);
vec3_t vec3_multiply(vec3_t vec, float factor);
vec3_t vec3_divide(vec3_t vec, float factor);
vec3_t vec3_cross(vec3_t a, vec3_t b);
float vec3_dot(vec3_t a, vec3_t b);

void vec3_normalize(vec3_t* vec);

vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);
vec3_t vec3_rotate_z(vec3_t v, float angle);

#endif
#include <math.h>
#include <stdio.h>
#include "vector.h"

// 2D
float vec2_length(vec2_t vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

vec2_t vec2_add(vec2_t a, vec2_t b) {
    vec2_t res = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
    return res;
}

vec2_t vec2_subtract(vec2_t a, vec2_t b) {
    vec2_t res = {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
    return res;
}

vec2_t vec2_multiply(vec2_t vec, float factor) {
    vec2_t res = {
        .x = vec.x * factor,
        .y = vec.y * factor
    };
    return res;
}

vec2_t vec2_divide(vec2_t vec, float factor) {
    vec2_t res = {
        .x = vec.x / factor,
        .y = vec.y / factor
    };
    return res;
}

float vec2_dot(vec2_t a, vec2_t b) {
    return (a.x * b.x) + (a.y * b.y);
}

// 3D
float vec3_length(vec3_t vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
    vec3_t res = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
    return res;
}

vec3_t vec3_subtract(vec3_t a, vec3_t b) {
    vec3_t res = {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
    return res;
}

vec3_t vec3_multiply(vec3_t vec, float factor) {
    vec3_t res = {
        .x = vec.x * factor,
        .y = vec.y * factor,
        .z = vec.z * factor
    };
    return res;
}

vec3_t vec3_divide(vec3_t vec, float factor) {
    vec3_t res = {
        .x = vec.x / factor,
        .y = vec.y / factor,
        .z = vec.z / factor
    };
    return res;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
    vec3_t res = {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x
    };
    return res;
}

float vec3_dot(vec3_t a, vec3_t b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3_t vec3_rotate_x(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };
    return rotated_vector;
}
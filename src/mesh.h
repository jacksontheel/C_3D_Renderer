#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

typedef struct {
    vec3_t* vertices;
    face_t* faces;
    vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

#define N_CUBE_VERTICES 8
extern vec3_t cube_vertices[N_CUBE_VERTICES];

#define N_CUBE_FACES (6 * 2)
extern face_t cube_faces[N_CUBE_FACES];

void load_cube_mesh_data(void);
void load_obj_file_data(char* fileName);

#endif
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"

triangle_t* triangles_to_render;

vec3_t camera_position = { 0, 0, 0 };

bool is_running = false;
int previous_frame_time = 0;

float fov_factor = 240;

void setup(void) {
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    load_obj_file_data("./assets/cube.obj");
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
            break;
    }
}

vec2_t project (vec3_t point) {
    vec2_t projected_point = {
        .x = (point.x * fov_factor / point.z),
        .y = (point.y * fov_factor / point.z)
    };
    return projected_point;
}

void update(void) {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }
    
    previous_frame_time = SDL_GetTicks();

    triangles_to_render = NULL;

    mesh.rotation.x += 0.01;
    mesh.rotation.y += 0.01;
    mesh.rotation.z += 0.01;

    for (int i = 0; i < array_length(mesh.faces); i++) {
        face_t mesh_face = mesh.faces[i];

        vec3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        vec3_t transformed_vertices[3];

        for (int j = 0; j < 3; j++) {
            vec3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);

            transformed_vertex.z += 2.5;

            transformed_vertices[j] = transformed_vertex;
        }

        vec3_t vec_a = transformed_vertices[0];
        vec3_t vec_b = transformed_vertices[1];
        vec3_t vec_c = transformed_vertices[2];

        vec3_t vec_ab = vec3_subtract(vec_b, vec_a);
        vec3_normalize(&vec_ab);
        vec3_t vec_ac = vec3_subtract(vec_c, vec_a);
        vec3_normalize(&vec_ac);

        vec3_t normal = vec3_cross(vec_ab, vec_ac);

        // Normalize the face normal vector
        vec3_normalize(&normal);

        vec3_t camera_ray = vec3_subtract(camera_position, vec_a);

        float alignment = vec3_dot(normal, camera_ray);

        if (alignment < 0) {
            continue;
        }

        triangle_t projected_triangle;

        for (int j = 0; j < 3; j++) {
            vec2_t projected_point = project(transformed_vertices[j]);
            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }

        array_push(triangles_to_render, projected_triangle);
    }

}

void render(void) {
    draw_grid();

    int  num_triangles = array_length(triangles_to_render);
    for (int i = 0; i < num_triangles; i++) {
        triangle_t triangle = triangles_to_render[i];
        draw_rect(triangle.points[0].x, triangle.points[0].y, 2, 2, 0xFFFFAAAA);
        draw_rect(triangle.points[1].x, triangle.points[1].y, 2, 2, 0xFFFFAAAA);
        draw_rect(triangle.points[2].x, triangle.points[2].y, 2, 2, 0xFFFFAAAA);

        draw_triangle(
            triangle.points[0].x,
            triangle.points[0].y,
            triangle.points[1].x,
            triangle.points[1].y,
            triangle.points[2].x,
            triangle.points[2].y,
            0xFFFFAAAA
        );

        
    }

    array_free(triangles_to_render);

    render_color_buffer();
    clear_color_buffer(0xFF222222);

    SDL_RenderPresent(renderer);
}

void free_resources(void) {
    array_free(mesh.vertices);
    array_free(mesh.faces);
}

int main(void) {
    
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    free_resources();

    return 0;
}
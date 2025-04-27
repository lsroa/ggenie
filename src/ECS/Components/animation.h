#pragma once
#include "GLFW/glfw3.h"

struct Animation {
    int total_frames;
    int current_frame;
    int speed;
    int start_time;
    bool is_loop;

    Animation(int total_frames = 1, int speed = 1, bool is_loop = true) {
      this->total_frames = total_frames;
      this->current_frame = 1;
      this->speed = speed;
      this->start_time = glfwGetTime();
      this->is_loop = is_loop;
    }
};

// g++ main.cpp -o snake -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
#include "raylib.h"
#include <iostream>
#include <map>
#include <unistd.h>
using namespace std;

// Setting Global Varibles that don't need to be global:
int screen_h = 450;
int screen_w = 450;
int p_x = screen_w / 2;
int p_y = screen_h / 2;
int length = 10;
char dir = 'w';
map<int, tuple<int, int>> pos;

void drawShit();
bool update();

int main(void) {
  pos[0] = {p_x, p_y};

  // Test code for messing with Collision logic and shit
  if (length > 1) {
    for (int i = 1; i < length - 1; i++) {
      pos[i] = tuple(get<0>(pos[0]), get<1>(pos[0]) + (25 * i));
    }
  }

  SetTargetFPS(5);
  InitWindow(screen_w, screen_h, "snake");

  while (true) {

    // Check if collided with anything
    if (update()) {
      return 0;
    }

    // Draw frames
    BeginDrawing();
    drawShit();
    EndDrawing();
  }

  return 0;
}

bool update() {

  // Inputs
  if (IsKeyPressed('W')) {
    if (dir != 's') {
      dir = 'w';
    }

  } else if (IsKeyPressed('A')) {
    if (dir != 'd') {
      dir = 'a';
    }

  } else if (IsKeyPressed('S')) {
    if (dir != 'w') {
      dir = 's';
    }

  } else if (IsKeyPressed('D')) {
    if (dir != 'a') {
      dir = 'd';
    }
  }

  // Modify pos based on inputs
  if (dir == 'w') {
    pos[0] = tuple(get<0>(pos[0]), get<1>(pos[0]) - 25);

  } else if (dir == 'a') {
    pos[0] = tuple(get<0>(pos[0]) - 25, get<1>(pos[0]));

  } else if (dir == 's') {
    pos[0] = tuple(get<0>(pos[0]), get<1>(pos[0]) + 25);

  } else {
    pos[0] = tuple(get<0>(pos[0]) + 25, get<1>(pos[0]));
  }

  // Updating the tail
  if (length > 1) {
    for (int i = length - 1; i > 0; i--) {
      pos[i] = pos[i - 1];
    }
  }

  // If Snake hits border it's gonna die
  if (get<0>(pos[0]) == 450 or get<1>(pos[0]) == 450 or get<0>(pos[0]) == 0 or
      get<1>(pos[0]) == 0) {

    return true;
  }

  // If Snake hit itslef then die
  for (int i = length - 1; i > 1; i--) {
    if (get<0>(pos[0]) == get<0>(pos[i]) and get<1>(pos[0]) == get<1>(pos[i])) {

      return true;
    }
  }

  //               TODO: MAKE FUCKING APPLES

  return false;
}

void drawShit() {

  // Just drawing shit
  ClearBackground({0, 0, 0, 255});

  for (int i = 0; i <= length - 1; i++) {
    DrawRectangle(get<0>(pos[i]), get<1>(pos[i]), 25, 25, GREEN);
  }
}

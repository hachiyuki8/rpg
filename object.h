#pragma once

#include "constants.h"
#include <SDL.h>
#include <iostream>
#include <set>
#include <stdlib.h>

class Object {
public:
  Object(SDL_Texture *t, float x = 0, float y = 0, float w = OBJECT_SIZE,
         float h = OBJECT_SIZE);
  virtual ~Object();

  void print();
  bool operator==(const Object &o);
  bool
  isInvalidPosition(float x, float y, float w,
                    float h); // invalid if object does not have CAN_COLLIDE and
                              // position collides with object
  void addObjectProperty(ObjectProperty newProp);
  void removeObjectProperty(ObjectProperty prop);
  bool canPickup(float x, float y, float w,
                 float h); // true if object has CAN_PICKUP and position
                           // collides with object

  void render(SDL_Renderer *renderer);

  static int nextID;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float width;
  float height;
  std::set<ObjectProperty> properties;

  bool isOnObject(float x, float y, float w,
                  float h); // if collides with object
};
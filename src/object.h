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
  void setInteractRange(float left, float right, float up, float down);
  bool
  isInvalidPosition(float x, float y, float w,
                    float h); // invalid if object does not have CAN_COLLIDE and
                              // position collides with object
  void addObjectProperty(ObjectProperty newProp);
  void removeObjectProperty(ObjectProperty prop);
  bool canPickup(float x, float y, float w,
                 float h); // true if object has CAN_PICKUP and position
                           // collides with object

  bool onInteract(float x, float y, float w, float h);
  void render(SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer, float x, float y, float w, float h);

  static int nextID;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float width;
  float height;

  // collider for interacting with the object, default to object size
  float xPosI;
  float yPosI;
  float widthI;
  float heightI;

  std::set<ObjectProperty> properties;

  bool isOnObject(float x, float y, float w,
                  float h); // if collides with object
  bool isInObjectRange(float x, float y, float w,
                       float h); // if collides with object's interaction range
};
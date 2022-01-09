#pragma once

#include "../constants/object_constants.h"
#include <SDL.h>
#include <iostream>
#include <math.h>
#include <set>
#include <stdlib.h>

class Object {
public:
  Object(std::string n, std::string d, SDL_Texture *t, int v = 0,
         ObjectType type = ObjectType::OTHERS, float x = 0, float y = 0,
         float w = OBJECT_SIZE, float h = OBJECT_SIZE);
  virtual ~Object();

  void print();
  bool operator==(const Object &o) const;
  bool operator<(const Object &o) const;
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
  void setPosition(float x, float y);
  void setItemlistPosition(float x, float y) const;

  bool onInteract(float x, float y, float w, float h);
  bool onUse() const;
  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);
  void
  render(SDL_Renderer *renderer, float x, float y, float w,
         float h) const; // used for rendering objects in itemlist/shops/etc

  static int nextID;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float width;
  float height;

  // collider for interacting with the object, default to object size, won't
  // automatically update if item position changed
  float xPosI;
  float yPosI;
  float widthI;
  float heightI;

  // position in itemlist or shop
  mutable float xPosIL = 0;
  mutable float yPosIL = 0;
  mutable bool isSelected = false; // if selected in item list

  std::string
      name; // different usable/pickable objects must have unique name since
            // item list and shops group items based on name instead of ID
  std::string description;
  int value;
  ObjectType type;
  std::set<ObjectProperty> properties;

  bool isOnObject(float x, float y, float w,
                  float h); // if collides with object
  bool isInObjectRange(float x, float y, float w,
                       float h); // if collides with object's interaction range

  friend class Itemlist;
  friend class Shop;
  friend class Character;
};
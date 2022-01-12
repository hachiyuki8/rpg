#pragma once

#include "../constants/object_constants.h"
#include <SDL.h>
#include <iostream>
#include <math.h>
#include <set>
#include <stdlib.h>

/*
 * object.h
 *
 * This file defines all object states and refers to object_constants.h.
 *
 */

class Object {
public:
  Object(std::string n, std::string d, SDL_Texture *t, int v = 0,
         ObjectType type = ObjectType::OTHERS, float x = 0, float y = 0,
         float w = OBJECT_SIZE, float h = OBJECT_SIZE);
  virtual ~Object();

  void print();

  /**
   * @brief Check if two objects are the exact same instance
   *
   * @param o
   * @return true if IDs are the same
   */
  bool operator==(const Object &o) const;

  /**
   * @brief Check if two objects are the same item, used for item grouping
   *
   * @param o
   * @return true if names are the same
   */
  bool operator<(const Object &o) const;

  /**
   * @brief Set the interaction collider
   *
   * @param left distance to the left of left border
   * @param right
   * @param up
   * @param down
   */
  void setInteractRange(float left, float right, float up, float down);

  /**
   * @brief Check if the given position collides with object when it should not
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if object doesn't have CAN_COLLIDE property but position
   * collides with object collider (not interaction collider)
   */
  bool isInvalidPosition(float x, float y, float w, float h);

  /**
   * @brief Add object property
   *
   * @param newProp
   */
  void addObjectProperty(ObjectProperty newProp);

  /**
   * @brief Remove object property
   *
   * @param newProp
   */
  void removeObjectProperty(ObjectProperty prop);

  /**
   * @brief Check if the given position can pick up object
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if object has CAN_PICKUP property and position colides with
   * interaction collider
   */
  bool canPickup(float x, float y, float w, float h);

  /**
   * @brief Set object position
   *
   * @param x
   * @param y
   */
  void setPosition(float x, float y);

  /**
   * @brief Set object position in inventory or shop
   *
   * @param x
   * @param y
   */
  void setInventoryPosition(float x, float y) const;

  /**
   * @brief When INTERACT is pressed, interact with the object if possible
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if player in range, object has CAN_INTERACT property, and
   * interaction carried out
   */
  bool onInteract(float x, float y, float w, float h);

  /**
   * @brief When CONFIRM is pressed, use the object in inventory if possible
   *
   * @return true if object has CAN_USE property and used
   */
  bool onUse() const;

  /**
   * @brief Render the object based on camera position
   *
   * @param renderer
   * @param camX
   * @param camY
   * @param camW
   * @param camH
   */
  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);

  /**
   * @brief Render the object in inventory or shop.
   *
   * @param renderer
   * @param x render position
   * @param y
   * @param w
   * @param h
   * @param ignore if true, don't render highlight effect even if selected
   */
  void render(SDL_Renderer *renderer, float x, float y, float w, float h,
              bool ignore = false) const;

  static int nextID;

private:
  int ID;
  SDL_Texture *texture;

  // object position
  float xPos;
  float yPos;
  float width;
  float height;

  // interaction collider, default to object size, won't automatically update if
  // position changed
  float xPosI;
  float yPosI;
  float widthI;
  float heightI;

  // position in inventory or shop
  mutable float xPosIL = 0;
  mutable float yPosIL = 0;
  mutable bool isSelected = false;

  // object properties
  // different usable/pickable objects must have unique name since inventory and
  // shops group items based on name instead of ID
  std::string name;
  std::string description;
  int value;
  ObjectType type; // determines what happens upon use
  std::set<ObjectProperty> properties;

  // Return true if given position collides with object collider
  bool isOnObject(float x, float y, float w, float h);

  // Return true if given position collides with interaction collider
  bool isInObjectRange(float x, float y, float w, float h);

  friend class Inventory;
  friend class Shop;
  friend class Character;
};
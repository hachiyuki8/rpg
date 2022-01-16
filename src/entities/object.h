#pragma once

#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include <functional>
#include <iostream>
#include <set>

#include "../constants/object_constants.h"

/*
 * object.h
 *
 * This file defines all object states and refers to object_constants.h.
 *
 * TL;DR: Maps should use object wrappers while inventory/shops should use
 * objects directly.
 *
 * An object encapsulates all information related to the object itself
 * (name/texture/properties/etc.) but contain nothing about the game state
 * (size/position on map/etc.) The latter is contained in an object wrapper.
 *
 * The point of having objects and object wrappers separately is that, with
 * objects, it is easier to define all items needed in the game independent of
 * the game state, hence reusing them to create multiple instances. So all
 * objects should be allocated and managed by AssetManager.
 *
 * But using object wrappers, different instances representing the same object
 * can each has its own independent game state. An object wrappers should be
 * managed by the game state it's dependent on, for example the map.
 *
 * When the ownership of an object changes (i.e. from one map to another), the
 * object wrapper should be destroyed and recreated while pointing to the same
 * underlying object.
 *
 */

class Object {
 public:
  /**
   * @brief Construct a new object
   *
   * @param n name
   * @param d description
   * @param t texture
   * @param v item value
   * @param type object type determines what happens upon use
   * @param x position
   * @param y
   * @param w dimension
   * @param h
   */
  Object(std::string n, std::string d, SDL_Texture *t, int v = 0,
         ObjectType type = ObjectType::OTHERS);
  virtual ~Object();

  void print();

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
   * @brief When CONFIRM is pressed, use the object in inventory if possible
   *
   * @return true if object has CAN_USE property and used
   */
  bool onUse();

  /**
   * @brief Add CAN_INTERACT to object and set the onInteract callback function
   *
   * @param i a callback that returns true when interaction succeeded
   */
  void setInteract(std::function<bool()> i);

  /**
   * @brief Add CAN_USE to object and set the onUse callback function
   *
   * @param i a callback that returns true when interaction succeeded
   */
  void setUse(std::function<bool()> u);

  /**
   * @brief Render the object in inventory or shop
   *
   * @param renderer
   * @param x render position
   * @param y
   * @param w
   * @param h
   * @param ignore if true, don't render highlight effect even if selected
   */
  void render(SDL_Renderer *renderer, float x, float y, float w, float h);

  static int nextID;

 private:
  int ID;
  SDL_Texture *texture;

  // object properties
  std::string name;
  std::string description;
  int value;
  ObjectType type;
  std::set<ObjectProperty> properties;

  // callback functions, return true if interaction succeeded
  std::function<bool()> interactCallback = []() { return false; };
  std::function<bool()> useCallback = []() { return false; };

  friend class Inventory;
  friend class Shop;
  friend class Character;
  friend class ObjectWrapper;
};

class ObjectWrapper {
 public:
  /**
   * @brief Construct a new object wrapper
   *
   * @param x position
   * @param y
   * @param w dimension
   * @param h
   */
  ObjectWrapper(Object *o, float x = 0, float y = 0, float w = OBJECT_SIZE,
                float h = OBJECT_SIZE);
  virtual ~ObjectWrapper();

  void print();

  /**
   * @brief Check if two object wrappers are the exact same instance
   *
   * @param ow
   * @return true if object wrapper IDs are the same
   */
  bool operator==(const ObjectWrapper &ow) const;

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

  static int nextID;

 private:
  int ID;
  Object *object;

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

  // Return true if given position collides with object collider
  bool isOnObject(float x, float y, float w, float h);

  // Return true if given position collides with interaction collider
  bool isInObjectRange(float x, float y, float w, float h);

  friend class Character;
};
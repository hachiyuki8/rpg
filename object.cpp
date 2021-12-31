#include "object.h"

int Object::nextID = 0;

Object::Object(SDL_Texture *t, float x, float y, float w, float h) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating object " << ID << std::endl;
  }

  texture = t;
  xPos = x;
  yPos = y;
  width = w;
  height = h;
  std::set<ObjectProperty> properties;
}

Object::~Object() {
  if (DEBUG) {
    std::cout << "Destroying object " << ID << std::endl;
  }
}

void Object::print() {
  std::cout << "Object " << ID << std::endl;
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
}

bool Object::operator==(const Object &o) { return (ID == o.ID); }

bool Object::isInvalidPosition(float x, float y, float w, float h) {
  return (!properties.count(ObjectProperty::CAN_COLLIDE) &&
          isOnObject(x, y, w, h));
}

void Object::addObjectProperty(ObjectProperty newProp) {
  properties.insert(newProp);
}

void Object::removeObjectProperty(ObjectProperty prop) {
  properties.erase(prop);
}

bool Object::canPickup(float x, float y, float w, float h) {
  return (properties.count(ObjectProperty::CAN_PICKUP) &&
          isOnObject(x, y, w, h));
}

void Object::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = xPos;
  r.y = yPos;
  r.w = width;
  r.h = height;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}

bool Object::isOnObject(float x, float y, float w, float h) {
  return (xPos <= x + w && x <= xPos + width && yPos <= y + h &&
          y <= yPos + height);
}
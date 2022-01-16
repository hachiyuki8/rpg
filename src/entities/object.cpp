#include "object.h"

int Object::nextID = 0;

Object::Object(std::string n, std::string d, SDL_Texture *t, int v,
               ObjectType oType) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating object " << ID << std::endl;
  }

  texture = t;
  name = n;
  description = d;
  value = v;
  type = oType;

  std::set<ObjectProperty> properties;
}

Object::~Object() {
  if (DEBUG) {
    std::cout << "Destroying object " << ID << std::endl;
  }
}

void Object::print() {
  std::cout << "Object " << ID << std::endl;
  std::cout << "-name: " << name << ", value: " << value << std::endl;
}

void Object::addObjectProperty(ObjectProperty newProp) {
  properties.insert(newProp);
}

void Object::removeObjectProperty(ObjectProperty prop) {
  properties.erase(prop);
}

bool Object::onUse() {
  if (!properties.count(ObjectProperty::CAN_USE)) {
    return false;
  }

  return useCallback();
}

void Object::setInteract(std::function<bool()> i) {
  addObjectProperty(ObjectProperty::CAN_INTERACT);
  interactCallback = i;
}

void Object::setUse(std::function<bool()> u) {
  addObjectProperty(ObjectProperty::CAN_USE);
  useCallback = u;
}

void Object::render(SDL_Renderer *renderer, float x, float y, float w,
                    float h) {
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  SDL_RenderCopy(renderer, texture, NULL, &r);
}

// object wrapper

int ObjectWrapper::nextID = 0;

ObjectWrapper::ObjectWrapper(Object *o, float x, float y, float w, float h) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating object wrapper " << ID << " for object " << o->name
              << std::endl;
  }

  object = o;

  xPos = x;
  yPos = y;
  width = w;
  height = h;

  xPosI = x;
  yPosI = y;
  widthI = w;
  heightI = h;
}

ObjectWrapper::~ObjectWrapper() {
  if (DEBUG) {
    std::cout << "Destroying object wrapper " << ID << " for object "
              << object->name << std::endl;
  }
}

void ObjectWrapper::print() {
  std::cout << "Object wrapper " << ID << std::endl;
  std::cout << "-position: (" << xPos << ", " << yPos << ")" << std::endl;
}

bool ObjectWrapper::operator==(const ObjectWrapper &ow) const {
  return (ID == ow.ID);
}

void ObjectWrapper::setInteractRange(float left, float right, float up,
                                     float down) {
  xPosI = xPos - left;
  widthI = width + left + right;
  yPosI = yPos - up;
  heightI = height + up + down;
}

bool ObjectWrapper::isInvalidPosition(float x, float y, float w, float h) {
  return (!object->properties.count(ObjectProperty::CAN_COLLIDE) &&
          isOnObject(x, y, w, h));
}

bool ObjectWrapper::canPickup(float x, float y, float w, float h) {
  return (object->properties.count(ObjectProperty::CAN_PICKUP) &&
          isInObjectRange(x, y, w, h));
}

bool ObjectWrapper::onInteract(float x, float y, float w, float h) {
  if (!isInObjectRange(x, y, w, h) ||
      !object->properties.count(ObjectProperty::CAN_INTERACT)) {
    return false;
  }

  return object->interactCallback();
}

void ObjectWrapper::render(SDL_Renderer *renderer, float camX, float camY,
                           float camW, float camH) {
  if (object->type == ObjectType::DIVIDER && !DEBUG) {
    return;
  }

  if (xPos + width < camX || xPos > camX + camW || yPos + height < camY ||
      yPos > camY + camH) {
    return;
  }

  SDL_Rect s;
  s.x = std::max(0.0f, round(camX - xPos));
  s.y = std::max(0.0f, round(camY - yPos));
  // rescale
  int actualW, actualH;
  SDL_QueryTexture(object->texture, NULL, NULL, &actualW, &actualH);
  s.x = s.x / width * actualW;
  s.y = s.y / height * actualH;
  s.w = actualW - s.x;
  s.h = actualH - s.y;

  SDL_Rect r;
  r.x = std::max(0.0f, round(xPos - camX));
  r.y = std::max(0.0f, round(yPos - camY));
  r.w = width - std::max(0.0f, round(camX - xPos));
  r.h = height - std::max(0.0f, round(camY - yPos));

  SDL_RenderCopy(renderer, object->texture, &s, &r);
}

bool ObjectWrapper::isOnObject(float x, float y, float w, float h) {
  return (xPos < x + w && x < xPos + width && yPos < y + h &&
          y < yPos + height);
}

bool ObjectWrapper::isInObjectRange(float x, float y, float w, float h) {
  return (xPosI <= x + w && x <= xPosI + widthI && yPosI <= y + h &&
          y <= yPosI + heightI);
}
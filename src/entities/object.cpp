#include "object.h"

int Object::nextID = 0;

Object::Object(std::string n, std::string d, SDL_Texture *t, int v,
               ObjectType oType, float x, float y, float w, float h) {
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

  xPosI = x;
  yPosI = y;
  widthI = w;
  heightI = h;

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
  std::cout << "-pos: (" << xPos << ", " << yPos << ")" << std::endl;
}

void Object::setInteractRange(float left, float right, float up, float down) {
  xPosI = xPos - left;
  widthI = width + left + right;
  yPosI = yPos - up;
  heightI = height + up + down;
}

bool Object::operator==(const Object &o) const { return (ID == o.ID); }

bool Object::operator<(const Object &o) const { return (name < o.name); }

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
          isInObjectRange(x, y, w, h));
}

void Object::setPosition(float x, float y) {
  xPos = x;
  yPos = y;
}

void Object::setInventoryPosition(float x, float y) const {
  xPosIL = x;
  yPosIL = y;
}

bool Object::onInteract(float x, float y, float w, float h) {
  if (!isInObjectRange(x, y, w, h) ||
      !properties.count(ObjectProperty::CAN_INTERACT)) {
    return false;
  }

  return interactCallback();
}

bool Object::onUse() const {
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

void Object::render(SDL_Renderer *renderer, float camX, float camY, float camW,
                    float camH) {
  if (type == ObjectType::DIVIDER && !DEBUG) {
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
  SDL_QueryTexture(texture, NULL, NULL, &actualW, &actualH);
  s.x = s.x / width * actualW;
  s.y = s.y / height * actualH;
  s.w = actualW - s.x;
  s.h = actualH - s.y;

  SDL_Rect r;
  r.x = std::max(0.0f, round(xPos - camX));
  r.y = std::max(0.0f, round(yPos - camY));
  r.w = width - std::max(0.0f, round(camX - xPos));
  r.h = height - std::max(0.0f, round(camY - yPos));

  SDL_RenderCopy(renderer, texture, &s, &r);
}

void Object::render(SDL_Renderer *renderer, float x, float y, float w, float h,
                    bool ignore) const {
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  if (!ignore && isSelected) {
    SDL_SetTextureColorMod(texture, 127, 127, 127);  // TODO: highlight item?
  }
  SDL_RenderCopy(renderer, texture, NULL, &r);
  SDL_SetTextureColorMod(texture, 255, 255, 255);
}

bool Object::isOnObject(float x, float y, float w, float h) {
  return (xPos < x + w && x < xPos + width && yPos < y + h &&
          y < yPos + height);
}

bool Object::isInObjectRange(float x, float y, float w, float h) {
  return (xPosI <= x + w && x <= xPosI + widthI && yPosI <= y + h &&
          y <= yPosI + heightI);
}
#include "stats.h"

int Stats::nextID = 0;

Stats::Stats(std::string n, float x, float y, float w, float h) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating stats " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;
  offsetBorder = width / 12;
  offsetLine = height / 9;
  offset = width / 6;

  name = n;
}

Stats::~Stats() {
  if (DEBUG) {
    std::cout << "Destroying stats " << ID << std::endl;
  }
  for (auto &s : attributes) {
    SDL_FreeSurface(s.second.name_text);
    SDL_FreeSurface(s.second.description_text);
  }
}

void Stats::print() {
  std::cout << "Stats " << ID << std::endl;
  std::cout << "-Name: " << name << std::endl;
  std::cout << "-Level " << level << ": exp " << exp << std::endl;
  std::cout << "-HP: " << hp << std::endl;
  for (auto &s : attributes) {
    std::cout << "-Attribute " << s.second.name << ": " << s.second.value
              << std::endl;
  }
}

void Stats::initAllStats() {
  hp = hpPerLevel[level];
  for (auto &s : STATS_ALL_ATTRIBUTES) {
    addAttribute(s.first, s.second.first, s.second.second);
  }
}

void Stats::increaseHP(int h) {
  if (h > 0) {
    hp = std::max(hpPerLevel[level], hp + h);
  } else {
    hp += h;
    if (hp <= 0) {
      // TODO
    }
  }
}

void Stats::increaseExp(Logs *logs, int ex) {
  int newLevel = level;
  int newExp = exp + ex;
  while (newExp >= expPerLevel[newLevel]) {
    newExp -= expPerLevel[newLevel];
    newLevel++;

    if (!expPerLevel.contains(newLevel)) {
      logs->addLog("-Max level reached");
      newLevel--;
      newExp = expPerLevel[newLevel];
      break;
    }
  }
  if (newLevel > level) {
    std::string s = "-Leveled up to " + std::to_string(newLevel);
    logs->addLog(s);
    hp = hpPerLevel[newLevel];  // hp filled when leveled up
  }
  level = newLevel;
  exp = newExp;
}

void Stats::increaseMoney(Logs *logs, int m) {
  money += m;
  if (money > STATS_MAX_MONEY) {
    logs->addLog("-Max money reach");
    money = STATS_MAX_MONEY;
  }
}

bool Stats::decreaseMoneyIfEnough(Logs *logs, int m) {
  if (money - m >= 0) {
    money -= m;
    return true;
  } else {
    logs->addLog("-Not enough moeny");
    return false;
  }
}

void Stats::increaseAttribute(Logs *logs, std::string s, int val) {
  if (!attributes.contains(s)) {
    std::cout << "Attribute doesn't exist" << std::endl;
    return;
  }
  attributes[s].value += val;
  std::string s0 = "-" + attributes[s].name + " increased to " +
                   std::to_string(attributes[s].value);
  logs->addLog(s0);
  if (attributes[s].value > attributes[s].maxValue) {
    attributes[s].value = attributes[s].maxValue;
    s0 = "-" + attributes[s].name + " reached max value";
    logs->addLog(s0);
  }
}

int Stats::getAttribute(std::string s) {
  if (!attributes.contains(s)) {
    std::cout << "Attribute doesn't exist" << std::endl;
    return -1;
  }
  return attributes[s].value;
}

void Stats::open() { isShowing = true; }

void Stats::close() { isShowing = false; }

void Stats::render(SDL_Renderer *renderer) {
  if (isShowing) {
    // background
    SDL_Rect r;
    r.x = xPos;
    r.y = yPos;
    r.w = width;
    r.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &r);

    // name
    SDL_Surface *text = TTF_RenderText_Solid(font, name.c_str(), text_color);
    if (!text) {
      std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, text);
    r.x = xPos + offsetBorder;
    r.y = yPos + offsetBorder;
    r.w = text->w;
    r.h = text->h;
    SDL_RenderCopy(renderer, t, NULL, &r);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(t);

    // HP
    std::string h = "HP: " + std::to_string(hp);
    text = TTF_RenderText_Solid(font, h.c_str(), text_color);
    if (!text) {
      std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }
    t = SDL_CreateTextureFromSurface(renderer, text);
    r.y += offsetLine;
    r.w = text->w;
    r.h = text->h;
    SDL_RenderCopy(renderer, t, NULL, &r);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(t);

    // level
    std::string l = "Level " + std::to_string(level) + ": " +
                    std::to_string(exp) + "/" +
                    std::to_string(expPerLevel[level]);
    text = TTF_RenderText_Solid(font, l.c_str(), text_color);
    if (!text) {
      std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }
    t = SDL_CreateTextureFromSurface(renderer, text);
    r.y += offsetLine;
    r.w = text->w;
    r.h = text->h;
    SDL_RenderCopy(renderer, t, NULL, &r);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(t);

    // money
    std::string m = "Money: " + std::to_string(money);
    text = TTF_RenderText_Solid(font, m.c_str(), text_color);
    if (!text) {
      std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }
    t = SDL_CreateTextureFromSurface(renderer, text);
    r.y += offsetLine;
    r.w = text->w;
    r.h = text->h;
    SDL_RenderCopy(renderer, t, NULL, &r);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(t);

    r.y += offsetLine;

    // attributes
    for (auto &s : attributes) {
      t = SDL_CreateTextureFromSurface(renderer, s.second.name_text);
      r.y += offsetLine;
      r.w = s.second.name_text->w;
      r.h = s.second.name_text->h;
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_DestroyTexture(t);

      text = TTF_RenderText_Solid(font, std::to_string(s.second.value).c_str(),
                                  text_color);
      if (!text) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
      }
      t = SDL_CreateTextureFromSurface(renderer, text);
      r.x += offset;
      r.w = text->w;
      r.h = text->h;
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_FreeSurface(text);
      SDL_DestroyTexture(t);
      r.x -= offset;
    }
  }
};

void Stats::addAttribute(std::string s, std::string d, int val) {
  if (attributes.contains(s)) {
    std::cout << "Attribute already exists" << std::endl;
    return;
  }

  struct Attribute newA;
  newA.name = s;
  newA.description = d;
  newA.value = val;
  SDL_Surface *name_text =
      TTF_RenderText_Solid(font, newA.name.c_str(), text_color);
  if (!name_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  newA.name_text = name_text;
  SDL_Surface *des_text =
      TTF_RenderText_Solid(font, newA.description.c_str(), text_color);
  if (!des_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  newA.description_text = des_text;

  attributes[s] = newA;
}
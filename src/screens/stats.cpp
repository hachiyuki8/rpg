#include "stats.h"

int Stats::nextID = 0;

Stats::Stats(std::string n, float x, float y, float w, float h,
             std::map<int, int> exp) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating stats " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;

  name = n;
  expPerLevel = exp;
}

Stats::~Stats() {
  if (DEBUG) {
    std::cout << "Destroying stats " << ID << std::endl;
  }
  SDL_DestroyTexture(texture);
  for (auto &s : stats) {
    SDL_FreeSurface(s.second.name_text);
    SDL_FreeSurface(s.second.description_text);
  }
}

void Stats::print() {
  std::cout << "Stats " << ID << std::endl;
  std::cout << "-Name: " << name << std::endl;
  std::cout << "-Level " << level << ": exp " << exp << std::endl;
  for (auto &s : stats) {
    std::cout << "-Stat " << s.second.name << ": " << s.second.value
              << std::endl;
  }
}

void Stats::initAllStats(
    std::map<std::string, std::pair<std::string, int>> st) {
  for (auto &s : st) {
    addStat(s.first, s.second.first, s.second.second);
  }
  if (DEBUG) {
    print();
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
  }
  level = newLevel;
  exp = newExp;
}

void Stats::increaseMoney(Logs *logs, int m) {
  money += m;
  std::string s = "-Money increased to " + std::to_string(money);
  logs->addLog(s);
  if (money > STATS_MAX_MONEY) {
    logs->addLog("-Max money reach");
    money = STATS_MAX_MONEY;
  }
}

void Stats::increaseStat(Logs *logs, std::string s, int val) {
  if (!stats.contains(s)) {
    std::cout << "Stat doesn't exists" << std::endl;
    return;
  }
  stats[s].value += val;
  std::string s0 =
      "-" + stats[s].name + " increased to " + std::to_string(stats[s].value);
  logs->addLog(s0);
  if (stats[s].value > stats[s].maxValue) {
    stats[s].value = stats[s].maxValue;
    s0 = "-" + stats[s].name + " reached max value";
    logs->addLog(s0);
  }
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
    r.x = xPos + offset;
    r.y = yPos + offset;
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
    r.y += offset;
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
    r.y += offset;
    r.w = text->w;
    r.h = text->h;
    SDL_RenderCopy(renderer, t, NULL, &r);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(t);

    r.y += offset;

    // stats
    for (auto &s : stats) {
      t = SDL_CreateTextureFromSurface(renderer, s.second.name_text);
      r.y += offset;
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
      r.x += offset * 2;
      r.w = text->w;
      r.h = text->h;
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_FreeSurface(text);
      SDL_DestroyTexture(t);
      r.x -= offset * 2;
    }
  }
};

void Stats::addStat(std::string s, std::string d, int val) {
  if (stats.contains(s)) {
    std::cout << "Stat already exists" << std::endl;
    return;
  }

  struct Stat newS;
  newS.name = s;
  newS.description = d;
  newS.value = val;
  SDL_Surface *name_text =
      TTF_RenderText_Solid(font, newS.name.c_str(), text_color);
  if (!name_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  newS.name_text = name_text;
  SDL_Surface *des_text =
      TTF_RenderText_Solid(font, newS.description.c_str(), text_color);
  if (!des_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  newS.description_text = des_text;

  stats[s] = newS;
}
#include "skills.h"

int Skills::nextID = 0;

Skills::Skills(float x, float y, float w, float h, int r, int c,
               std::map<int, int> exp) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating skills " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;

  numRow = r;
  numCol = c;
  cardWidth = width / numCol;
  cardHeight = height / numRow;

  expPerLevel = exp;
}

Skills::~Skills() {
  if (DEBUG) {
    std::cout << "Destroying skills " << ID << std::endl;
  }
  SDL_DestroyTexture(texture);
  for (auto &sc : skillcards) {
    SDL_FreeSurface(sc.name_text);
    SDL_FreeSurface(sc.description_text);
  }
}

void Skills::print() {
  std::cout << "Skills " << ID << std::endl;
  for (auto &s : skills) {
    std::cout << "-Skill " << s.second.name << ": level " << s.second.curLevel
              << ", exp " << s.second.curExp << ", isUnlocked "
              << s.second.isUnlocked << std::endl;
  }
}

void Skills::initAllSkills(
    std::map<std::string, std::pair<std::string, bool>> sk) {
  for (auto &s : sk) {
    addSkill(s.first, s.second.first, s.second.second);
  }
  if (DEBUG) {
    print();
  }
}

void Skills::unlockSkill(std::string s) {
  if (!skills.contains(s)) {
    std::cout << "Skill doesn't exists" << std::endl;
    return;
  }

  skills[s].isUnlocked = true;
}

void Skills::upgradeSkill(std::string s, int exp) {
  if (!skills.contains(s)) {
    std::cout << "Skill doesn't exists" << std::endl;
    return;
  } else if (!skills[s].isUnlocked) {
    std::cout << "Skill not unlocked yet" << std::endl;
    return;
  }

  int newLevel = skills[s].curLevel;
  int newExp = skills[s].curExp + exp;
  while (newExp >= expPerLevel[newLevel]) {
    newExp -= expPerLevel[newLevel];
    newLevel++;

    if (!expPerLevel.contains(newLevel)) {
      if (DEBUG) {
        std::cout << "Skill " << s << " maxed out" << std::endl;
      }
      newLevel--;
      newExp = expPerLevel[newLevel];
      break;
    }
  }
  skills[s].curLevel = newLevel;
  skills[s].curExp = newExp;
}

void Skills::open() { isShowing = true; }

void Skills::close() {
  // unselect
  if (curSelected) {
    curSelected->isSelected = false;
    curSelected = NULL;
  }
  isShowing = false;
}

void Skills::onClick(float x, float y, bool isLeft) {
  if (!isShowing) {
    return;
  }

  if (isLeft) {
    onLeftClick(x, y);
  } else {
    onRightClick(x, y);
  }
}

void Skills::onConfirm() {
  if (!isShowing) {
    return;
  }

  return; // TO-DO
}

void Skills::render(SDL_Renderer *renderer) {
  if (isShowing) {
    // background
    for (int row = 0; row < numRow; row++) {
      for (int col = 0; col < numCol; col++) {
        SDL_Rect r;
        r.x = xPos + col * cardWidth;
        r.y = yPos + row * cardHeight;
        r.w = cardWidth;
        r.h = cardHeight;
        SDL_RenderCopy(renderer, texture, NULL, &r);
      }
    }

    // text
    int nextR = 0;
    int nextC = 0;
    for (auto &sc : skillcards) {
      if (!sc.skill.isUnlocked) {
        sc.xPos = 0;
        sc.yPos = 0;
        sc.width = 0;
        sc.height = 0;
      } else {
        sc.xPos = xPos + nextC * cardWidth;
        sc.yPos = yPos + nextR * cardHeight;
        sc.width = cardWidth;
        sc.height = cardHeight;

        renderCard(renderer, sc);

        if (nextC + 1 < numCol) {
          nextC++;
        } else if (nextR + 1 < numRow) {
          nextC = 0;
          nextR++;
        }
      }
    }
  }
}

void Skills::addSkill(std::string s, std::string d, bool isUnlocked) {
  if (skills.contains(s)) {
    std::cout << "Skill already exists" << std::endl;
    return;
  }

  struct Skill newS;
  newS.name = s;
  newS.description = d;
  newS.isUnlocked = isUnlocked;
  skills[s] = newS;

  struct SkillCard newSC;
  newSC.skill = newS;

  SDL_Surface *name_text =
      TTF_RenderText_Solid(font, newS.name.c_str(), text_color);
  if (!name_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  newSC.name_text = name_text;
  SDL_Surface *des_text =
      TTF_RenderText_Solid(font, newS.description.c_str(), text_color);
  if (!des_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  newSC.description_text = des_text;

  skillcards.push_back(newSC);
}

void Skills::renderCard(SDL_Renderer *renderer, SkillCard sc) {
  if (sc.isSelected) {
    SDL_SetTextureColorMod(texture, 127, 127, 127); // TO-DO: highlight item?
    SDL_Rect r;
    r.x = sc.xPos;
    r.y = sc.yPos;
    r.w = sc.width;
    r.h = sc.height;
    SDL_RenderCopy(renderer, texture, NULL, &r);
    SDL_SetTextureColorMod(texture, 255, 255, 255);
  }

  // name
  SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, sc.name_text);
  SDL_Rect r;
  r.x = sc.xPos + (cardWidth - sc.name_text->w) / 2;
  r.y = sc.yPos + sc.name_text->h;
  r.w = sc.name_text->w;
  r.h = sc.name_text->h;
  SDL_RenderCopy(renderer, t, NULL, &r);

  // description
  t = SDL_CreateTextureFromSurface(renderer, sc.description_text);
  r.x = sc.xPos + (cardWidth - sc.description_text->w) / 2;
  r.y += sc.name_text->h;
  r.w = sc.description_text->w;
  r.h = sc.description_text->h;
  SDL_RenderCopy(renderer, t, NULL, &r);

  // level
  std::string level = "Level " + std::to_string(sc.skill.curLevel) + ": " +
                      std::to_string(sc.skill.curExp) + "/" +
                      std::to_string(expPerLevel[sc.skill.curLevel]);
  SDL_Surface *level_text =
      TTF_RenderText_Solid(font, level.c_str(), text_color);
  if (!level_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
  }
  t = SDL_CreateTextureFromSurface(renderer, level_text);
  SDL_FreeSurface(level_text);
  r.x = sc.xPos + (cardWidth - level_text->w) / 2;
  r.y = sc.yPos + cardHeight / 2;
  r.w = level_text->w;
  r.h = level_text->h;
  SDL_RenderCopy(renderer, t, NULL, &r);

  SDL_DestroyTexture(t);
}

void Skills::onLeftClick(float x, float y) {
  for (auto &sc : skillcards) {
    if (sc.xPos < x && x < sc.xPos + sc.width && sc.yPos < y &&
        y < sc.yPos + sc.height) {
      if (DEBUG) {
        std::cout << "Selecting on skill " << sc.skill.name << std::endl;
      }

      if (!sc.isSelected) {
        // unselect previous and select this
        if (curSelected) {
          curSelected->isSelected = false;
        }
        curSelected = &sc;

        // TO-DO: skill clicked, show actions
      } else {
        // unselect this
        curSelected = NULL;
      }
      sc.isSelected = !sc.isSelected;
    }
  }
}

void Skills::onRightClick(float x, float y) { return; } // TO-DO
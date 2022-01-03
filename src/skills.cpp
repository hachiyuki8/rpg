#include "skills.h"

int Skills::nextID = 0;

Skills::Skills(float x, float y, float w, float h, std::map<int, int> exp) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating skills " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;

  expPerLevel = exp;
}

Skills::~Skills() {
  if (DEBUG) {
    std::cout << "Destroying skills " << ID << std::endl;
  }
  SDL_DestroyTexture(texture);
}

void Skills::print() {
  std::cout << "Skills " << ID << std::endl;
  for (auto &s : skills) {
    std::cout << "-Skill " << s.second.name << ": level " << s.second.curLevel
              << ", exp " << s.second.curExp << ", isUnlocked "
              << s.second.isUnlocked << std::endl;
  }
}

void Skills::initAllSkills(std::map<std::string, bool> sk) {
  for (auto &s : sk) {
    addSkill(s.first, s.second);
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
  // TO-DO
  isShowing = false;
}

void Skills::addSkill(std::string s, bool isUnlocked) {
  if (skills.contains(s)) {
    std::cout << "Skill already exists" << std::endl;
    return;
  }

  struct Skill newS;
  newS.name = s;
  newS.isUnlocked = isUnlocked;
  skills[s] = newS;
}
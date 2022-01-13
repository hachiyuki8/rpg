#include "init.h"

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Surface *startup_text;
SDL_Texture *startup_t;

// indices in constants.h depend on order of elements in these
// TODO: one day I will restructure these
std::vector<TTF_Font *> fonts;
TTF_Font *mainL_f, *mainM_f, *mainS_f, *mainL_bold_f, *mainM_bold_f,
    *mainS_bold_f;
std::vector<SDL_Texture *> UIs;
SDL_Texture *inventory_t, *skills_t, *stats_t, *logs_t, *shop_t, *help_t,
    *convo_t;
SDL_Texture *inventory_bg, *shop_bg;

SDL_Texture *playerIcon;
std::map<Direction, SDL_Texture *> playerStillTextures;
std::map<Direction, std::vector<SDL_Texture *>> playerWalkTextures;
std::map<Direction, std::vector<SDL_Texture *>> playerAttackTextures;
SDL_Texture *enemyStillTexture;
std::map<Direction, std::vector<SDL_Texture *>> enemyWalkTextures;
std::map<Direction, std::vector<SDL_Texture *>> enemyAttackTextures;
std::vector<SDL_Texture *> npcTextures;
std::vector<SDL_Texture *> tileTextures;
std::vector<SDL_Texture *> objectTextures;
std::vector<SDL_Texture *> uiTextures;
std::map<SDL_Keycode, SDL_Texture *> keyTextures;
std::vector<Map *> maps;
std::vector<CharacterNPC *> allNPCs;
std::vector<Enemy *> allEnemies;

bool init() {
  std::string path;

  // libraries
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return false;
  }
  if (TTF_Init() < 0) {
    std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
    return false;
  }
  if (IMG_Init(IMG_INIT_PNG) < 0) {
    std::cout << "Failed to initialize SDL_image: " << IMG_GetError()
              << std::endl;
    return false;
  }

  // basics
  window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cout << "Error creating window: " << SDL_GetError() << std::endl;
    return false;
  }
  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  if (!init_fonts()) {
    std::cout << "Font initialization failed" << std::endl;
    return false;
  }

  // starting screen
  SDL_Color text_color = {0, 0, 0};
  std::string s = "Press " + std::string(SDL_GetKeyName(START_GAME)) +
                  " to start/resume the game";
  startup_text = TTF_RenderText_Solid(mainL_bold_f, s.c_str(), text_color);
  if (!startup_text) {
    std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    return false;
  }

  if (!init_player_texture()) {
    std::cout << "Player initialization failed" << std::endl;
    return false;
  }
  if (!init_NPC_texture()) {
    std::cout << "NPC initialization failed" << std::endl;
    return false;
  }
  if (!init_object_texture()) {
    std::cout << "Object initialization failed" << std::endl;
    return false;
  }
  if (!init_tile_texture()) {
    std::cout << "Tile initialization failed" << std::endl;
    return false;
  }
  if (!init_UI_texture()) {
    std::cout << "UI initialization failed" << std::endl;
    return false;
  }
  if (!init_key_texture()) {
    std::cout << "Key initialization failed" << std::endl;
    return false;
  }

  init_maps();
  init_NPCs();
  init_enemies();

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  return true;
}

bool init_fonts() {
  std::string path = FONT_PATH + FONTS[0];
  mainL_bold_f = TTF_OpenFont(path.c_str(), 36);
  if (!mainL_bold_f) {
    std::cout << "Error loading font " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  mainM_bold_f = TTF_OpenFont(path.c_str(), 27);
  if (!mainM_bold_f) {
    std::cout << "Error loading font " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  mainS_bold_f = TTF_OpenFont(path.c_str(), 18);
  if (!mainS_bold_f) {
    std::cout << "Error loading font " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }

  path = FONT_PATH + FONTS[1];
  mainL_f = TTF_OpenFont(path.c_str(), 36);
  if (!mainL_f) {
    std::cout << "Error loading font " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  mainM_f = TTF_OpenFont(path.c_str(), 27);
  if (!mainM_f) {
    std::cout << "Error loading font " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  mainS_f = TTF_OpenFont(path.c_str(), 18);
  if (!mainS_f) {
    std::cout << "Error loading font " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }

  fonts = {mainL_f, mainM_f, mainS_f, mainL_bold_f, mainM_bold_f, mainS_bold_f};
  return true;
}

bool init_player_texture() {
  std::string path = PLAYER_PATH + PLAYER_ICON;
  SDL_Surface *image = IMG_Load(path.c_str());
  if (!image) {
    std::cout << "Error loading image " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  playerIcon = SDL_CreateTextureFromSurface(renderer, image);
  if (!playerIcon) {
    std::cout << "Error creating texture for " << path << ": " << SDL_GetError()
              << std::endl;
    return false;
  }
  SDL_FreeSurface(image);

  for (auto &s : PLAYER_LEFT) {
    std::string path = PLAYER_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    playerWalkTextures[Direction::LEFT].push_back(texture);
    SDL_FreeSurface(image);
  }

  for (auto &s : PLAYER_RIGHT) {
    std::string path = PLAYER_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    playerWalkTextures[Direction::RIGHT].push_back(texture);
    SDL_FreeSurface(image);
  }

  for (auto &s : PLAYER_UP) {
    std::string path = PLAYER_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    playerWalkTextures[Direction::UP].push_back(texture);
    SDL_FreeSurface(image);
  }

  for (auto &s : PLAYER_DOWN) {
    std::string path = PLAYER_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    playerWalkTextures[Direction::DOWN].push_back(texture);
    SDL_FreeSurface(image);
  }

  playerStillTextures[Direction::LEFT] = playerWalkTextures[Direction::LEFT][0];
  playerStillTextures[Direction::RIGHT] =
      playerWalkTextures[Direction::RIGHT][0];
  playerStillTextures[Direction::UP] = playerWalkTextures[Direction::UP][0];
  playerStillTextures[Direction::DOWN] = playerWalkTextures[Direction::DOWN][0];
  return true;
}

bool init_NPC_texture() {
  for (auto &s : CHARACTERS) {
    std::string path = NPC_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    npcTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
  return true;
}

bool init_object_texture() {
  for (auto &s : OBJECTS) {
    std::string path = OBJECT_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    objectTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
  return true;
}

bool init_tile_texture() {
  for (auto &s : TILES) {
    std::string path = TILE_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    tileTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
  return true;
}

bool init_UI_texture() {
  for (auto &s : UI) {
    std::string path = UI_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    uiTextures.push_back(texture);
    SDL_FreeSurface(image);
  }
  inventory_t = uiTextures[15];
  skills_t = uiTextures[16];
  stats_t = uiTextures[12];
  logs_t = uiTextures[13];
  shop_t = uiTextures[14];
  help_t = uiTextures[17];
  convo_t = uiTextures[18];
  inventory_bg = uiTextures[19];
  shop_bg = uiTextures[19];
  UIs = {inventory_t, skills_t, stats_t,      logs_t, shop_t,
         help_t,      convo_t,  inventory_bg, shop_bg};
  return true;
}

bool init_key_texture() {
  for (auto &s : KEYBOARD) {
    std::string path = KEY_PATH + s.second;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    keyTextures[s.first] = texture;
    SDL_FreeSurface(image);
  }
  return true;
}

void init_maps() {
  Map *initial = new Map(MAPS[0], MAPS[0][0].size() * TILE_SIZE,
                         MAPS[0].size() * TILE_SIZE, TILE_SIZE);
  maps.push_back(initial);

  Object redHouse("big red house", "", objectTextures[23], 0,
                  ObjectType::OTHERS, 20, 20, 160, 160);
  maps[0]->addObject(redHouse);

  Object campFire("camp fire", "", objectTextures[29], 0, ObjectType::OTHERS,
                  270, 80, 100, 40);
  maps[0]->addObject(campFire);

  Object flower1("small white flower", "", objectTextures[11], 0,
                 ObjectType::OTHERS, 440, 10, 35, 35);
  flower1.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower1);

  Object flower2("small white flower", "", objectTextures[11], 0,
                 ObjectType::OTHERS, 430, 30, 30, 30);
  flower2.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower2);

  Object tree1("pale green tree", "", objectTextures[22], 0, ObjectType::OTHERS,
               480, -10, 70, 90);
  maps[0]->addObject(tree1);

  Object tree2("green tree", "", objectTextures[21], 0, ObjectType::OTHERS, 530,
               15, 85, 110);
  maps[0]->addObject(tree2);

  Object rock("rocks", "", objectTextures[19], 0, ObjectType::OTHERS, 565, 100,
              60, 50);
  maps[0]->addObject(rock);

  Object tree3("green tree", "tree", objectTextures[21], 0, ObjectType::OTHERS,
               440, 50, 80, 100);
  maps[0]->addObject(tree3);

  Object tree4("pale green tree", "", objectTextures[22], 0, ObjectType::OTHERS,
               460, 90, 80, 90);
  maps[0]->addObject(tree4);

  Object flower3("red flower", "", objectTextures[28], 20, ObjectType::OTHERS,
                 485, 190, 25, 25);
  flower3.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  flower3.addObjectProperty(ObjectProperty::CAN_PICKUP);
  maps[0]->addObject(flower3);

  Object flower4("blue flower", "", objectTextures[3], 20, ObjectType::OTHERS,
                 445, 160, 22, 22);
  flower4.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  flower4.addObjectProperty(ObjectProperty::CAN_PICKUP);
  maps[0]->addObject(flower4);

  Object flower5("small white flowers", "", objectTextures[10], 0,
                 ObjectType::OTHERS, 590, 155, 32, 32);
  flower5.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower5);

  Object tree5("green tree", "", objectTextures[21], 0, ObjectType::OTHERS, 505,
               95, 95, 120);
  maps[0]->addObject(tree5);

  Object fence1("fence top", "", objectTextures[6], 0, ObjectType::OTHERS, 240,
                520, 40, 40);
  maps[0]->addObject(fence1);

  Object fence2("fence horizontal", "", objectTextures[8], 0,
                ObjectType::OTHERS, 280, 520, 40, 40);
  maps[0]->addObject(fence2);

  Object fence3("fence horizontal", "", objectTextures[8], 0,
                ObjectType::OTHERS, 400, 520, 40, 40);
  maps[0]->addObject(fence3);

  Object fence4("fence top", "", objectTextures[6], 0, ObjectType::OTHERS, 440,
                520, 40, 40);
  maps[0]->addObject(fence4);

  Object fence5("fence vertical", "", objectTextures[9], 0, ObjectType::OTHERS,
                240, 560, 40, 40);
  maps[0]->addObject(fence5);

  Object fence6("fence vertical", "", objectTextures[9], 0, ObjectType::OTHERS,
                440, 560, 40, 40);
  maps[0]->addObject(fence6);

  Object fence7("fence vertical", "", objectTextures[9], 0, ObjectType::OTHERS,
                240, 600, 40, 40);
  maps[0]->addObject(fence7);

  Object fence8("fence vertical", "", objectTextures[9], 0, ObjectType::OTHERS,
                440, 600, 40, 40);
  maps[0]->addObject(fence8);

  Object fence9("fence vertical", "", objectTextures[9], 0, ObjectType::OTHERS,
                240, 640, 40, 40);
  maps[0]->addObject(fence9);

  Object fence10("fence vertical", "", objectTextures[9], 0, ObjectType::OTHERS,
                 440, 640, 40, 40);
  maps[0]->addObject(fence10);

  Object fence11("fence bottom left", "", objectTextures[4], 0,
                 ObjectType::OTHERS, 240, 680, 40, 40);
  maps[0]->addObject(fence11);

  Object fence12("fence horizontal", "", objectTextures[8], 0,
                 ObjectType::OTHERS, 280, 680, 40, 40);
  maps[0]->addObject(fence12);

  Object fence13("fence horizontal", "", objectTextures[8], 0,
                 ObjectType::OTHERS, 320, 680, 40, 40);
  maps[0]->addObject(fence13);

  Object fence14("fence horizontal", "", objectTextures[8], 0,
                 ObjectType::OTHERS, 360, 680, 40, 40);
  maps[0]->addObject(fence14);

  Object fence15("fence horizontal", "", objectTextures[8], 0,
                 ObjectType::OTHERS, 400, 680, 40, 40);
  maps[0]->addObject(fence15);

  Object fence16("fence bottom right", "", objectTextures[5], 0,
                 ObjectType::OTHERS, 440, 680, 40, 40);
  maps[0]->addObject(fence16);

  Object flower6("small white flowers", "", objectTextures[10], 0,
                 ObjectType::OTHERS, 280, 560, 30, 30);
  flower6.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower6);

  Object flower7("small white flower", "", objectTextures[11], 0,
                 ObjectType::OTHERS, 305, 585, 32, 32);
  flower7.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower7);

  Object flower8("small white flower", "", objectTextures[11], 0,
                 ObjectType::OTHERS, 300, 620, 27, 27);
  flower8.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower8);

  Object flower9("small white flowers", "", objectTextures[10], 0,
                 ObjectType::OTHERS, 380, 590, 25, 25);
  flower9.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower9);

  Object flower10("small white flower", "", objectTextures[11], 0,
                  ObjectType::OTHERS, 400, 575, 25, 25);
  flower10.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower10);

  Object flower11("small white flower", "", objectTextures[11], 0,
                  ObjectType::OTHERS, 420, 625, 22, 22);
  flower11.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower11);

  Object flower12("big blue flower", "", objectTextures[12], 0,
                  ObjectType::OTHERS, 280, 640, 40, 40);
  maps[0]->addObject(flower12);

  Object flower13("big yellow flower", "", objectTextures[13], 0,
                  ObjectType::OTHERS, 320, 640, 40, 40);
  maps[0]->addObject(flower13);

  Object flower14("big blue flower", "", objectTextures[12], 0,
                  ObjectType::OTHERS, 360, 640, 40, 40);
  maps[0]->addObject(flower14);

  Object flower15("big yellow flower", "", objectTextures[13], 0,
                  ObjectType::OTHERS, 400, 640, 40, 40);
  maps[0]->addObject(flower15);

  Object flower16("red flower", "", objectTextures[28], 20, ObjectType::OTHERS,
                  280, 585, 27, 27);
  flower16.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  flower16.addObjectProperty(ObjectProperty::CAN_PICKUP);
  maps[0]->addObject(flower16);

  Object flower17("white flower", "", objectTextures[2], 20, ObjectType::OTHERS,
                  320, 560, 25, 25);
  flower17.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  flower17.addObjectProperty(ObjectProperty::CAN_PICKUP);
  maps[0]->addObject(flower17);

  Object flower18("yellow flower", "", objectTextures[1], 20,
                  ObjectType::OTHERS, 340, 595, 26, 26);
  flower18.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  flower18.addObjectProperty(ObjectProperty::CAN_PICKUP);
  maps[0]->addObject(flower18);

  Object flower19("blue flower", "", objectTextures[3], 20, ObjectType::OTHERS,
                  360, 535, 28, 28);
  flower19.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  flower19.addObjectProperty(ObjectProperty::CAN_PICKUP);
  maps[0]->addObject(flower19);

  Object flower20("red flower", "", objectTextures[28], 20, ObjectType::OTHERS,
                  420, 595, 25, 25);
  flower20.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  flower20.addObjectProperty(ObjectProperty::CAN_PICKUP);
  maps[0]->addObject(flower20);

  Object flower21("small white flower", "", objectTextures[11], 0,
                  ObjectType::OTHERS, 355, 565, 24, 24);
  flower21.addObjectProperty(ObjectProperty::CAN_COLLIDE);
  maps[0]->addObject(flower21);

  Object blueHouse("blue house", "", objectTextures[25], 0, ObjectType::OTHERS,
                   990, 10, 100, 160);
  maps[0]->addObject(blueHouse);

  Object flower22("long white flower", "", objectTextures[26], 0,
                  ObjectType::OTHERS, 950, 160, 48, 34);
  maps[0]->addObject(flower22);

  Object flower23("long yellow flower", "", objectTextures[27], 0,
                  ObjectType::OTHERS, 1085, 160, 48, 34);
  maps[0]->addObject(flower23);

  Map *second = new Map(MAPS[1], MAPS[1][0].size() * TILE_SIZE,
                        MAPS[1].size() * TILE_SIZE, TILE_SIZE);
  maps.push_back(second);

  Object redHouse1("big red house", "", objectTextures[23], 0,
                   ObjectType::OTHERS, 300, 100, 200, 200);
  maps[1]->addObject(redHouse1);

  std::map<std::pair<int, int>, std::pair<int, int>> sd1 = {
      {std::make_pair(17, 25), std::make_pair(1, 0)},
      {std::make_pair(17, 26), std::make_pair(1, 0)},
      {std::make_pair(17, 27), std::make_pair(1, 0)},
      {std::make_pair(17, 28), std::make_pair(2, 0)},
      {std::make_pair(17, 29), std::make_pair(3, 0)},
  };
  std::map<std::pair<int, int>, std::pair<int, int>> sd2 = {
      {std::make_pair(1, 0), std::make_pair(17, 26)},
      {std::make_pair(1, 0), std::make_pair(17, 27)},
      {std::make_pair(1, 0), std::make_pair(17, 28)},
      {std::make_pair(2, 0), std::make_pair(17, 29)},
      {std::make_pair(3, 0), std::make_pair(17, 30)},
  };
  Teleporter tp(maps[0], maps[1], sd1);
  maps[0]->addTeleporter(tp);
  Teleporter tp2(maps[1], maps[0], sd2);
  maps[1]->addTeleporter(tp2);

  // TODO: add dividers, don't use transparent bg yet for testing purpose
}

void init_NPCs() {
  CharacterNPC *npc1 =
      new CharacterNPC(npcTextures[0], NPCState::SHOP_NPC, 620, 360, 80, 80);
  npc1->setInteractRange(5, 5, 5, 5);
  Object coin3("coin 3",
               "coin coin coin coin coin coin coin coin coin coin coin coin "
               "coin coin coin coin coin coin",
               objectTextures[0], 10, ObjectType::OTHERS, 600, 600);
  npc1->shop.addItem(coin3, 10);
  allNPCs.push_back(npc1);
  maps[0]->addNPC(npc1);

  CharacterNPC *npc2 =
      new CharacterNPC(npcTextures[1], NPCState::CONVO_NPC, 800, 360, 100, 100);
  npc2->setInteractRange(5, 5, 5, 5);
  std::vector<std::tuple<int, std::vector<std::string>>> lines;
  lines.push_back(std::make_tuple(
      1,
      std::vector<std::string>{
          "Hello world", "Just testing testing testing testing testing testing "
                         "testing testing testing testing testing testing "
                         "testing testing testing testing testing"}));
  lines.push_back(std::make_tuple(-1, std::vector<std::string>{"Bruh"}));
  npc2->setConvo(lines);
  allNPCs.push_back(npc2);
  maps[0]->addNPC(npc2);
}

bool init_enemies() {
  for (auto &s : ENEMY_WALK_LEFT) {
    std::string path = ENEMY_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    enemyWalkTextures[Direction::LEFT].push_back(texture);
    SDL_FreeSurface(image);
  }

  for (auto &s : ENEMY_WALK_RIGHT) {
    std::string path = ENEMY_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    enemyWalkTextures[Direction::RIGHT].push_back(texture);
    SDL_FreeSurface(image);
  }

  for (auto &s : ENEMY_ATTACK_LEFT) {
    std::string path = ENEMY_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    enemyAttackTextures[Direction::LEFT].push_back(texture);
    SDL_FreeSurface(image);
  }

  for (auto &s : ENEMY_ATTACK_RIGHT) {
    std::string path = ENEMY_PATH + s;
    SDL_Surface *image = IMG_Load(path.c_str());
    if (!image) {
      std::cout << "Error loading image " << path << ": " << SDL_GetError()
                << std::endl;
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
      std::cout << "Error creating texture for " << path << ": "
                << SDL_GetError() << std::endl;
      return false;
    }
    enemyAttackTextures[Direction::RIGHT].push_back(texture);
    SDL_FreeSurface(image);
  }

  enemyStillTexture = enemyWalkTextures[Direction::LEFT][0];

  Enemy *enemy = new Enemy(400, 600, 400, 800, MovementState::WALK, 100, 1, 40,
                           40, 30, 30, 0, 0);
  Object flowerReward1("blue flower", "", objectTextures[3], 20,
                       ObjectType::OTHERS, 0, 0, 0, 0);
  Object flowerReward2("red flower", "", objectTextures[28], 20,
                       ObjectType::OTHERS, 0, 0, 0, 0);
  enemy->addReward(flowerReward1, 2);
  enemy->addReward(flowerReward2, 99);
  maps[1]->addEnemy(enemy);
  return true;
}
#include "init.h"

void init() {
  initObjects();
  initMaps();
  initNPCs();
  initEnemies();
  initPlayer();
}

void free() {
  delete AssetManager::player;
  for (auto &o : AssetManager::allObjects) {
    delete o;
  }
  for (auto &m : AssetManager::allMaps) {
    delete m;
  }
  for (auto &n : AssetManager::allNPCs) {
    delete n;
  }
  for (auto &e : AssetManager::allEnemies) {
    delete e;
  }
}

void initObjects() {
  // object 0
  Object *redHouse =
      new Object("red house", "", AssetManager::objectTextures["23_house1.png"],
                 0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(redHouse);

  // object 1
  Object *blueHouse = new Object("blue house", "",
                                 AssetManager::objectTextures["25_house3.png"],
                                 0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(blueHouse);

  // object 2
  Object *campFire = new Object("camp fire", "",
                                AssetManager::objectTextures["29_bonfire.png"],
                                0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(campFire);

  // object 3
  Object *whiteFlower = new Object(
      "white flower", "", AssetManager::objectTextures["11_flower5.png"], 0,
      ObjectType::OTHERS);
  whiteFlower->addObjectProperty(ObjectProperty::CAN_COLLIDE);
  AssetManager::allObjects.push_back(whiteFlower);

  // object 4
  Object *whiteFlowers = new Object(
      "white flowers", "", AssetManager::objectTextures["10_flower4.png"], 0,
      ObjectType::OTHERS);
  whiteFlowers->addObjectProperty(ObjectProperty::CAN_COLLIDE);
  AssetManager::allObjects.push_back(whiteFlowers);

  // object 5
  Object *redFlower = new Object(
      "red flower", "", AssetManager::objectTextures["28_flower10.png"], 20,
      ObjectType::OTHERS);
  redFlower->addObjectProperty(ObjectProperty::CAN_COLLIDE);
  redFlower->addObjectProperty(ObjectProperty::CAN_PICKUP);
  redFlower->setUse([]() {
    std::cout << "Successfully used red flower" << std::endl;
    return true;
  });
  AssetManager::allObjects.push_back(redFlower);

  // object 6
  Object *blueFlower = new Object("blue flower", "",
                                  AssetManager::objectTextures["3_flower3.png"],
                                  20, ObjectType::OTHERS);
  blueFlower->addObjectProperty(ObjectProperty::CAN_COLLIDE);
  blueFlower->addObjectProperty(ObjectProperty::CAN_PICKUP);
  blueFlower->addObjectProperty(ObjectProperty::CAN_USE);
  AssetManager::allObjects.push_back(blueFlower);

  // object 7
  Object *yellowFlower = new Object(
      "yellow flower", "", AssetManager::objectTextures["1_flower1.png"], 20,
      ObjectType::OTHERS);
  yellowFlower->addObjectProperty(ObjectProperty::CAN_COLLIDE);
  yellowFlower->addObjectProperty(ObjectProperty::CAN_PICKUP);
  AssetManager::allObjects.push_back(yellowFlower);

  // object 8
  Object *bigBlueFlower = new Object(
      "big blue flower", "", AssetManager::objectTextures["12_flower6.png"], 0,
      ObjectType::OTHERS);
  AssetManager::allObjects.push_back(bigBlueFlower);

  // object 9
  Object *bigYellowFlower = new Object(
      "big yellow flower", "", AssetManager::objectTextures["13_flower7.png"],
      0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(bigYellowFlower);

  // object 10
  Object *longWhiteFlower = new Object(
      "long white flower", "", AssetManager::objectTextures["26_flower8.png"],
      0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(longWhiteFlower);

  // object 11
  Object *longYellowFlower = new Object(
      "long yellow flower", "", AssetManager::objectTextures["27_flower9.png"],
      0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(longYellowFlower);

  // object 12
  Object *coinShop = new Object(
      "coin", "a meaningless coin to demo how the shop works",
      AssetManager::objectTextures["0_coin.png"], 10, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(coinShop);

  // object  13
  Object *flowerShop = new Object(
      "flower", "a meaningless flower to demo how the shop works",
      AssetManager::objectTextures["1_flower1.png"], 20, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(flowerShop);

  // object 14
  Object *paleGreenTree = new Object(
      "pale green tree", "", AssetManager::objectTextures["22_tree2.png"], 0,
      ObjectType::OTHERS);
  AssetManager::allObjects.push_back(paleGreenTree);

  // object 15
  Object *greenTree =
      new Object("green tree", "", AssetManager::objectTextures["21_tree1.png"],
                 0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(greenTree);

  // object 16
  Object *rocks =
      new Object("rocks", "", AssetManager::objectTextures["19_rock1.png"], 0,
                 ObjectType::OTHERS);
  AssetManager::allObjects.push_back(rocks);

  // object 17
  Object *fenceTop =
      new Object("fence top", "", AssetManager::objectTextures["6_fence3.png"],
                 0, ObjectType::OTHERS);
  AssetManager::allObjects.push_back(fenceTop);

  // object 18
  Object *fenceHorizontal = new Object(
      "fence horizontal", "", AssetManager::objectTextures["8_fence5.png"], 0,
      ObjectType::OTHERS);
  AssetManager::allObjects.push_back(fenceHorizontal);

  // object 19
  Object *fenceVertical = new Object(
      "fence vertical", "", AssetManager::objectTextures["9_fence6.png"], 0,
      ObjectType::OTHERS);
  AssetManager::allObjects.push_back(fenceVertical);

  // object 20
  Object *fenceBottomLeft = new Object(
      "fence bottom left", "", AssetManager::objectTextures["4_fence1.png"], 0,
      ObjectType::OTHERS);
  AssetManager::allObjects.push_back(fenceBottomLeft);

  // object 21
  Object *fenceBottomRight = new Object(
      "fence bottom right", "", AssetManager::objectTextures["5_fence2.png"], 0,
      ObjectType::OTHERS);
  AssetManager::allObjects.push_back(fenceBottomRight);
}

void initMaps() {
  // map 0
  Map *map0 = new Map(MAPFILES[0], MAPFILES[0][0].size() * TILE_SIZE,
                      MAPFILES[0].size() * TILE_SIZE, TILE_SIZE);
  AssetManager::allMaps.push_back(map0);

  ObjectWrapper redHouseW(AssetManager::allObjects[0], 20, 20, 160, 160);
  map0->addObject(redHouseW);
  ObjectWrapper campFireW(AssetManager::allObjects[2], 270, 80, 100, 40);
  map0->addObject(campFireW);

  ObjectWrapper flower1W(AssetManager::allObjects[3], 440, 10, 35, 35);
  map0->addObject(flower1W);
  ObjectWrapper flower2W(AssetManager::allObjects[3], 430, 30, 30, 30);
  map0->addObject(flower2W);
  ObjectWrapper tree1W(AssetManager::allObjects[14], 480, -10, 70, 90);
  map0->addObject(tree1W);
  ObjectWrapper tree2W(AssetManager::allObjects[15], 530, 15, 85, 110);
  map0->addObject(tree2W);
  ObjectWrapper rocksW(AssetManager::allObjects[16], 565, 100, 60, 50);
  map0->addObject(rocksW);
  ObjectWrapper tree3W(AssetManager::allObjects[15], 440, 50, 80, 100);
  map0->addObject(tree3W);
  ObjectWrapper tree4W(AssetManager::allObjects[14], 460, 90, 80, 90);
  map0->addObject(tree4W);
  ObjectWrapper flower3W(AssetManager::allObjects[5], 485, 190, 25, 25);
  map0->addObject(flower3W);
  ObjectWrapper flower4W(AssetManager::allObjects[6], 445, 160, 22, 22);
  map0->addObject(flower4W);
  ObjectWrapper flower5W(AssetManager::allObjects[4], 590, 155, 32, 32);
  map0->addObject(flower5W);
  ObjectWrapper tree5W(AssetManager::allObjects[15], 505, 95, 95, 120);
  map0->addObject(tree5W);

  ObjectWrapper fence1W(AssetManager::allObjects[17], 240, 520, 40, 40);
  map0->addObject(fence1W);
  ObjectWrapper fence2W(AssetManager::allObjects[18], 280, 520, 40, 40);
  map0->addObject(fence2W);
  ObjectWrapper fence3W(AssetManager::allObjects[18], 400, 520, 40, 40);
  map0->addObject(fence3W);
  ObjectWrapper fence4W(AssetManager::allObjects[17], 440, 520, 40, 40);
  map0->addObject(fence4W);
  ObjectWrapper fence5W(AssetManager::allObjects[19], 240, 560, 40, 40);
  map0->addObject(fence5W);
  ObjectWrapper fence6W(AssetManager::allObjects[19], 440, 560, 40, 40);
  map0->addObject(fence6W);
  ObjectWrapper fence7W(AssetManager::allObjects[19], 240, 600, 40, 40);
  map0->addObject(fence7W);
  ObjectWrapper fence8W(AssetManager::allObjects[19], 440, 600, 40, 40);
  map0->addObject(fence8W);
  ObjectWrapper fence9W(AssetManager::allObjects[19], 240, 640, 40, 40);
  map0->addObject(fence9W);
  ObjectWrapper fence10W(AssetManager::allObjects[19], 440, 640, 40, 40);
  map0->addObject(fence10W);
  ObjectWrapper fence11W(AssetManager::allObjects[20], 240, 680, 40, 40);
  map0->addObject(fence11W);
  ObjectWrapper fence12W(AssetManager::allObjects[18], 280, 680, 40, 40);
  map0->addObject(fence12W);
  ObjectWrapper fence13W(AssetManager::allObjects[18], 320, 680, 40, 40);
  map0->addObject(fence13W);
  ObjectWrapper fence14W(AssetManager::allObjects[18], 360, 680, 40, 40);
  map0->addObject(fence14W);
  ObjectWrapper fence15W(AssetManager::allObjects[18], 400, 680, 40, 40);
  map0->addObject(fence15W);
  ObjectWrapper fence16W(AssetManager::allObjects[21], 440, 680, 40, 40);
  map0->addObject(fence16W);

  ObjectWrapper flower6W(AssetManager::allObjects[4], 280, 560, 30, 30);
  map0->addObject(flower6W);
  ObjectWrapper flower7W(AssetManager::allObjects[3], 305, 585, 32, 32);
  map0->addObject(flower7W);
  ObjectWrapper flower8W(AssetManager::allObjects[3], 300, 620, 27, 27);
  map0->addObject(flower8W);
  ObjectWrapper flower9W(AssetManager::allObjects[4], 380, 590, 25, 25);
  map0->addObject(flower9W);
  ObjectWrapper flower10W(AssetManager::allObjects[3], 400, 575, 25, 25);
  map0->addObject(flower10W);
  ObjectWrapper flower11W(AssetManager::allObjects[3], 420, 625, 22, 22);
  map0->addObject(flower11W);
  ObjectWrapper flower12W(AssetManager::allObjects[8], 280, 640, 40, 40);
  map0->addObject(flower12W);
  ObjectWrapper flower13W(AssetManager::allObjects[9], 320, 640, 40, 40);
  map0->addObject(flower13W);
  ObjectWrapper flower14W(AssetManager::allObjects[8], 360, 640, 40, 40);
  map0->addObject(flower14W);
  ObjectWrapper flower15W(AssetManager::allObjects[9], 400, 640, 40, 40);
  map0->addObject(flower15W);
  ObjectWrapper flower16W(AssetManager::allObjects[5], 280, 585, 27, 27);
  map0->addObject(flower16W);
  ObjectWrapper flower17W(AssetManager::allObjects[3], 320, 560, 25, 25);
  map0->addObject(flower17W);
  ObjectWrapper flower18W(AssetManager::allObjects[7], 340, 595, 26, 26);
  map0->addObject(flower18W);
  ObjectWrapper flower19W(AssetManager::allObjects[6], 360, 535, 28, 28);
  map0->addObject(flower19W);
  ObjectWrapper flower20W(AssetManager::allObjects[5], 420, 595, 25, 25);
  map0->addObject(flower20W);
  ObjectWrapper flower21W(AssetManager::allObjects[3], 355, 565, 24, 24);
  map0->addObject(flower21W);

  ObjectWrapper blueHouseW(AssetManager::allObjects[1], 990, 10, 100, 160);
  map0->addObject(blueHouseW);
  ObjectWrapper flower22W(AssetManager::allObjects[10], 950, 160, 48, 34);
  map0->addObject(flower22W);
  ObjectWrapper flower23W(AssetManager::allObjects[11], 1085, 160, 48, 34);
  map0->addObject(flower23W);

  // map 1
  Map *map1 = new Map(MAPFILES[1], MAPFILES[1][0].size() * TILE_SIZE,
                      MAPFILES[1].size() * TILE_SIZE, TILE_SIZE);
  AssetManager::allMaps.push_back(map1);

  ObjectWrapper redHouse1W(AssetManager::allObjects[0], 300, 100, 200, 200);
  map1->addObject(redHouse1W);

  // teleporters
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
  Teleporter tp(AssetManager::allMaps[0], AssetManager::allMaps[1], sd1);
  AssetManager::allMaps[0]->addTeleporter(tp);
  Teleporter tp2(AssetManager::allMaps[1], AssetManager::allMaps[0], sd2);
  AssetManager::allMaps[1]->addTeleporter(tp2);

  // TODO: add dividers, don't use transparent bg yet for testing purpose
}

void initNPCs() {
  // npc 0
  CharacterNPC *npc1 =
      new CharacterNPC(AssetManager::npcTextures["0_shop1.png"],
                       NPCState::SHOP_NPC, 620, 360, 80, 80);
  npc1->setInteractRange(5, 5, 5, 5);
  std::vector<std::tuple<Object *, int>> items;
  items.push_back(std::make_tuple(AssetManager::allObjects[12], 10));
  items.push_back(std::make_tuple(AssetManager::allObjects[13], 99));
  npc1->addToShop(items);
  AssetManager::allNPCs.push_back(npc1);
  AssetManager::allMaps[0]->addNPC(npc1);

  // npc 1
  CharacterNPC *npc2 =
      new CharacterNPC(AssetManager::npcTextures["1_shop1.png"],
                       NPCState::CONVO_NPC, 800, 360, 100, 100);
  npc2->setInteractRange(5, 5, 5, 5);
  std::vector<std::tuple<std::string, std::vector<std::string>>> lines;
  lines.push_back(std::make_tuple(
      "1_shop1.png",
      std::vector<std::string>{
          "Well",
          "I know everything looks ugly now, but that's cuz all the "
          "graphics are just a placeholder."}));
  lines.push_back(std::make_tuple(
      "1_shop1.png",
      std::vector<std::string>{"BTW I really hate designing GUI."}));
  lines.push_back(std::make_tuple("", std::vector<std::string>{"Ok bruh"}));
  npc2->setConvo(lines);
  AssetManager::allNPCs.push_back(npc2);
  AssetManager::allMaps[0]->addNPC(npc2);
}

void initEnemies() {
  // enemy 0
  Enemy *enemy1 = new Enemy(400, 600, 400, 800, ENEMY1_PATH,
                            MovementState::WALK, 100, 1, 40, 40, 30, 30, 0, 0);
  enemy1->addReward(AssetManager::allObjects[5], 2);
  enemy1->addReward(AssetManager::allObjects[6], 99);
  AssetManager::allEnemies.push_back(enemy1);
  AssetManager::allMaps[1]->addEnemy(enemy1);
}

void initPlayer() {
  AssetManager::player = new Character(80, 180);
  AssetManager::player->init();
  AssetManager::player->curMap = AssetManager::allMaps[1];
}

void renderStartingScreen() {
  AssetManager::startingScreen_t = SDL_CreateTextureFromSurface(
      AssetManager::renderer, AssetManager::startingScreen_text);
  SDL_Rect dest = {(SCREEN_WIDTH - AssetManager::startingScreen_text->w) / 2,
                   (SCREEN_HEIGHT - AssetManager::startingScreen_text->h) / 2,
                   AssetManager::startingScreen_text->w,
                   AssetManager::startingScreen_text->h};
  SDL_RenderCopy(AssetManager::renderer, AssetManager::startingScreen_t, NULL,
                 &dest);
}
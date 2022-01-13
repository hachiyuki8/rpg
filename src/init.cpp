#include "init.h"

void init() {
  initMaps();
  initNPCs();
  initEnemies();
}

void initMaps() {
  // map 0
  Map *map0 = new Map(MAPFILES[0], MAPFILES[0][0].size() * TILE_SIZE,
                      MAPFILES[0].size() * TILE_SIZE, TILE_SIZE);
  AssetManager::allMaps.push_back(map0);
  while (true) { // TODO: this is simply to collapse this ugly code
    Object redHouse("big red house", "",
                    AssetManager::objectTextures["23_house1.png"], 0,
                    ObjectType::OTHERS, 20, 20, 160, 160);
    map0->addObject(redHouse);

    Object campFire("camp fire", "",
                    AssetManager::objectTextures["29_bonfire.png"], 0,
                    ObjectType::OTHERS, 270, 80, 100, 40);
    map0->addObject(campFire);

    Object flower1("small white flower", "",
                   AssetManager::objectTextures["11_flower5.png"], 0,
                   ObjectType::OTHERS, 440, 10, 35, 35);
    flower1.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower1);

    Object flower2("small white flower", "",
                   AssetManager::objectTextures["11_flower5.png"], 0,
                   ObjectType::OTHERS, 430, 30, 30, 30);
    flower2.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower2);

    Object tree1("pale green tree", "",
                 AssetManager::objectTextures["22_tree2.png"], 0,
                 ObjectType::OTHERS, 480, -10, 70, 90);
    map0->addObject(tree1);

    Object tree2("green tree", "", AssetManager::objectTextures["21_tree1.png"],
                 0, ObjectType::OTHERS, 530, 15, 85, 110);
    map0->addObject(tree2);

    Object rock("rocks", "", AssetManager::objectTextures["19_rock1.png"], 0,
                ObjectType::OTHERS, 565, 100, 60, 50);
    map0->addObject(rock);

    Object tree3("green tree", "tree",
                 AssetManager::objectTextures["21_tree1.png"], 0,
                 ObjectType::OTHERS, 440, 50, 80, 100);
    map0->addObject(tree3);

    Object tree4("pale green tree", "",
                 AssetManager::objectTextures["22_tree2.png"], 0,
                 ObjectType::OTHERS, 460, 90, 80, 90);
    map0->addObject(tree4);

    Object flower3("red flower", "",
                   AssetManager::objectTextures["28_flower10.png"], 20,
                   ObjectType::OTHERS, 485, 190, 25, 25);
    flower3.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    flower3.addObjectProperty(ObjectProperty::CAN_PICKUP);
    map0->addObject(flower3);

    Object flower4("blue flower", "",
                   AssetManager::objectTextures["3_flower3.png"], 20,
                   ObjectType::OTHERS, 445, 160, 22, 22);
    flower4.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    flower4.addObjectProperty(ObjectProperty::CAN_PICKUP);
    map0->addObject(flower4);

    Object flower5("small white flowers", "",
                   AssetManager::objectTextures["10_flower4.png"], 0,
                   ObjectType::OTHERS, 590, 155, 32, 32);
    flower5.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower5);

    Object tree5("green tree", "", AssetManager::objectTextures["21_tree1.png"],
                 0, ObjectType::OTHERS, 505, 95, 95, 120);
    map0->addObject(tree5);

    Object fence1("fence top", "", AssetManager::objectTextures["6_fence3.png"],
                  0, ObjectType::OTHERS, 240, 520, 40, 40);
    map0->addObject(fence1);

    Object fence2("fence horizontal", "",
                  AssetManager::objectTextures["8_fence5.png"], 0,
                  ObjectType::OTHERS, 280, 520, 40, 40);
    map0->addObject(fence2);

    Object fence3("fence horizontal", "",
                  AssetManager::objectTextures["8_fence5.png"], 0,
                  ObjectType::OTHERS, 400, 520, 40, 40);
    map0->addObject(fence3);

    Object fence4("fence top", "", AssetManager::objectTextures["6_fence3.png"],
                  0, ObjectType::OTHERS, 440, 520, 40, 40);
    map0->addObject(fence4);

    Object fence5("fence vertical", "",
                  AssetManager::objectTextures["9_fence6.png"], 0,
                  ObjectType::OTHERS, 240, 560, 40, 40);
    map0->addObject(fence5);

    Object fence6("fence vertical", "",
                  AssetManager::objectTextures["9_fence6.png"], 0,
                  ObjectType::OTHERS, 440, 560, 40, 40);
    map0->addObject(fence6);

    Object fence7("fence vertical", "",
                  AssetManager::objectTextures["9_fence6.png"], 0,
                  ObjectType::OTHERS, 240, 600, 40, 40);
    map0->addObject(fence7);

    Object fence8("fence vertical", "",
                  AssetManager::objectTextures["9_fence6.png"], 0,
                  ObjectType::OTHERS, 440, 600, 40, 40);
    map0->addObject(fence8);

    Object fence9("fence vertical", "",
                  AssetManager::objectTextures["9_fence6.png"], 0,
                  ObjectType::OTHERS, 240, 640, 40, 40);
    map0->addObject(fence9);

    Object fence10("fence vertical", "",
                   AssetManager::objectTextures["9_fence6.png"], 0,
                   ObjectType::OTHERS, 440, 640, 40, 40);
    map0->addObject(fence10);

    Object fence11("fence bottom left", "",
                   AssetManager::objectTextures["4_fence1.png"], 0,
                   ObjectType::OTHERS, 240, 680, 40, 40);
    map0->addObject(fence11);

    Object fence12("fence horizontal", "",
                   AssetManager::objectTextures["8_fence5.png"], 0,
                   ObjectType::OTHERS, 280, 680, 40, 40);
    map0->addObject(fence12);

    Object fence13("fence horizontal", "",
                   AssetManager::objectTextures["8_fence5.png"], 0,
                   ObjectType::OTHERS, 320, 680, 40, 40);
    map0->addObject(fence13);

    Object fence14("fence horizontal", "",
                   AssetManager::objectTextures["8_fence5.png"], 0,
                   ObjectType::OTHERS, 360, 680, 40, 40);
    map0->addObject(fence14);

    Object fence15("fence horizontal", "",
                   AssetManager::objectTextures["8_fence5.png"], 0,
                   ObjectType::OTHERS, 400, 680, 40, 40);
    map0->addObject(fence15);

    Object fence16("fence bottom right", "",
                   AssetManager::objectTextures["5_fence2.png"], 0,
                   ObjectType::OTHERS, 440, 680, 40, 40);
    map0->addObject(fence16);

    Object flower6("small white flowers", "",
                   AssetManager::objectTextures["10_flower4.png"], 0,
                   ObjectType::OTHERS, 280, 560, 30, 30);
    flower6.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower6);

    Object flower7("small white flower", "",
                   AssetManager::objectTextures["11_flower5.png"], 0,
                   ObjectType::OTHERS, 305, 585, 32, 32);
    flower7.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower7);

    Object flower8("small white flower", "",
                   AssetManager::objectTextures["11_flower5.png"], 0,
                   ObjectType::OTHERS, 300, 620, 27, 27);
    flower8.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower8);

    Object flower9("small white flowers", "",
                   AssetManager::objectTextures["10_flower4.png"], 0,
                   ObjectType::OTHERS, 380, 590, 25, 25);
    flower9.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower9);

    Object flower10("small white flower", "",
                    AssetManager::objectTextures["11_flower5.png"], 0,
                    ObjectType::OTHERS, 400, 575, 25, 25);
    flower10.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower10);

    Object flower11("small white flower", "",
                    AssetManager::objectTextures["11_flower5.png"], 0,
                    ObjectType::OTHERS, 420, 625, 22, 22);
    flower11.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower11);

    Object flower12("big blue flower", "",
                    AssetManager::objectTextures["12_flower6.png"], 0,
                    ObjectType::OTHERS, 280, 640, 40, 40);
    map0->addObject(flower12);

    Object flower13("big yellow flower", "",
                    AssetManager::objectTextures["13_flower7.png"], 0,
                    ObjectType::OTHERS, 320, 640, 40, 40);
    map0->addObject(flower13);

    Object flower14("big blue flower", "",
                    AssetManager::objectTextures["12_flower6.png"], 0,
                    ObjectType::OTHERS, 360, 640, 40, 40);
    map0->addObject(flower14);

    Object flower15("big yellow flower", "",
                    AssetManager::objectTextures["13_flower7.png"], 0,
                    ObjectType::OTHERS, 400, 640, 40, 40);
    map0->addObject(flower15);

    Object flower16("red flower", "",
                    AssetManager::objectTextures["28_flower10.png"], 20,
                    ObjectType::OTHERS, 280, 585, 27, 27);
    flower16.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    flower16.addObjectProperty(ObjectProperty::CAN_PICKUP);
    map0->addObject(flower16);

    Object flower17("white flower", "",
                    AssetManager::objectTextures["2_flower2.png"], 20,
                    ObjectType::OTHERS, 320, 560, 25, 25);
    flower17.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    flower17.addObjectProperty(ObjectProperty::CAN_PICKUP);
    map0->addObject(flower17);

    Object flower18("yellow flower", "",
                    AssetManager::objectTextures["1_flower1.png"], 20,
                    ObjectType::OTHERS, 340, 595, 26, 26);
    flower18.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    flower18.addObjectProperty(ObjectProperty::CAN_PICKUP);
    map0->addObject(flower18);

    Object flower19("blue flower", "",
                    AssetManager::objectTextures["3_flower3.png"], 20,
                    ObjectType::OTHERS, 360, 535, 28, 28);
    flower19.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    flower19.addObjectProperty(ObjectProperty::CAN_PICKUP);
    map0->addObject(flower19);

    Object flower20("red flower", "",
                    AssetManager::objectTextures["28_flower10.png"], 20,
                    ObjectType::OTHERS, 420, 595, 25, 25);
    flower20.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    flower20.addObjectProperty(ObjectProperty::CAN_PICKUP);
    map0->addObject(flower20);

    Object flower21("small white flower", "",
                    AssetManager::objectTextures["11_flower5.png"], 0,
                    ObjectType::OTHERS, 355, 565, 24, 24);
    flower21.addObjectProperty(ObjectProperty::CAN_COLLIDE);
    map0->addObject(flower21);

    Object blueHouse("blue house", "",
                     AssetManager::objectTextures["25_house3.png"], 0,
                     ObjectType::OTHERS, 990, 10, 100, 160);
    map0->addObject(blueHouse);

    Object flower22("long white flower", "",
                    AssetManager::objectTextures["26_flower8.png"], 0,
                    ObjectType::OTHERS, 950, 160, 48, 34);
    map0->addObject(flower22);

    Object flower23("long yellow flower", "",
                    AssetManager::objectTextures["27_flower9.png"], 0,
                    ObjectType::OTHERS, 1085, 160, 48, 34);
    map0->addObject(flower23);

    break;
  }

  // map 1
  Map *map1 = new Map(MAPFILES[1], MAPFILES[1][0].size() * TILE_SIZE,
                      MAPFILES[1].size() * TILE_SIZE, TILE_SIZE);
  AssetManager::allMaps.push_back(map1);
  Object redHouse1("big red house", "",
                   AssetManager::objectTextures["23_house1.png"], 0,
                   ObjectType::OTHERS, 300, 100, 200, 200);
  map1->addObject(redHouse1);

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
  Object coin3("coin", "a meaningless coin to demo how the shop works",
               AssetManager::objectTextures["0_coin.png"], 10,
               ObjectType::OTHERS, 0, 0);
  npc1->shop.addItem(coin3, 10);
  Object flowers("flowers", "meaningless flowers",
                 AssetManager::objectTextures["1_flower1.png"], 20,
                 ObjectType::OTHERS, 0, 0);
  npc1->shop.addItem(flowers, 99);
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
          "Well", "I know everything looks ugly now, but that's cuz all the "
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
  Object flowerReward1("blue flower", "",
                       AssetManager::objectTextures["3_flower3.png"], 20,
                       ObjectType::OTHERS, 0, 0, 0, 0);
  Object flowerReward2("red flower", "",
                       AssetManager::objectTextures["28_flower10.png"], 20,
                       ObjectType::OTHERS, 0, 0, 0, 0);
  enemy1->addReward(flowerReward1, 2);
  enemy1->addReward(flowerReward2, 99);
  AssetManager::allEnemies.push_back(enemy1);
  AssetManager::allMaps[1]->addEnemy(enemy1);
}
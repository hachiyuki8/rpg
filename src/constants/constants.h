#pragma once
#include <SDL.h>
#include <stdlib.h>
#include <string>
#include <vector>

const bool DEBUG = true;

const std::string FONT_PATH = "../fonts/";
const std::string IMAGE_PATH = "../assets/";

const std::string NPC_PATH = IMAGE_PATH + "NPCs/";
const std::string OBJECT_PATH = IMAGE_PATH + "objects/";
const std::string TILE_PATH = IMAGE_PATH + "tiles/";
const std::string UI_PATH = IMAGE_PATH + "UI/";

const std::vector<std::string> FONTS = {
    "0_abaddon_bold.ttf", "1_abaddon_light.ttf", "2_quicksand_regular.ttf"};
const std::vector<std::string> NPCS = {"0_shop1.png"};
const std::vector<std::string> OBJECTS = {
    "0_coin.png",     "1_flower1.png",  "2_flower2.png",   "3_flower3.png",
    "4_fence1.png",   "5_fence2.png",   "6_fence3.png",    "7_fence4.png",
    "8_fence5.png",   "9_fence6.png",   "10_flower4.png",  "11_flower5.png",
    "12_flower6.png", "13_flower7.png", "14_mailbox1.png", "15_mailbox2.png",
    "16_sign1.png",   "17_sign2.png",   "18_sign3.png",    "19_rock1.png",
    "20_rock2.png",   "21_tree1.png",   "22_tree2.png",    "23_house1.png",
    "24_house2.png"};
const std::vector<std::string> TILES = {
    "0_water1.png",   "1_grass.png",    "2_land.png",     "3_ground.png",
    "4_water.png",    "5_pond1.png",    "6_pond2.png",    "7_pond3.png",
    "8_pond4.png",    "9_pond5.png",    "10_pond6.png",   "11_pond7.png",
    "12_pond8.png",   "13_stairs1.png", "14_stairs2.png", "15_stairs3.png",
    "16_stairs4.png", "17_stairs5.png", "18_bridge1.png", "19_bridge2.png",
    "20_bridge3.png", "21_bridge4.png", "22_bridge5.png", "23_bridge6.png"};
const std::vector<std::string> UI = {
    "0_textbox.png",   "1_grid1.png",  "2_grid2.png",   "3_panel1.png",
    "4_panel2.png",    "5_panel3.png", "6_panel4.png",  "7_longbox.png",
    "8_panel5.png",    "9_panel6.png", "10_panel7.png", "11_panel8.png",
    "12_namecard.png", "13_box.png",   "14_grid3.png",  "15_grid4.png",
    "16_grid5.png"};

enum class GameState { PAUSE, IN_PROGRESS };
enum class UIState {
  IN_GAME,
  IN_ITEMLIST,
  IN_SKILLS,
  IN_STATS,
  IN_SHOP,
  IN_CONVO
};

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
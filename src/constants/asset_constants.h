#pragma once
#include <SDL.h>

#include <map>
#include <string>
#include <vector>

#include "constants.h"

const std::string FONT_PATH = "../fonts/";
const std::string IMAGE_PATH = "../assets/";

const std::string PLAYER_PATH = IMAGE_PATH + "player/";
const std::string NPC_PATH = IMAGE_PATH + "NPCs/";
const std::string OBJECT_PATH = IMAGE_PATH + "objects/";
const std::string TILE_PATH = IMAGE_PATH + "tiles/";
const std::string UI_PATH = IMAGE_PATH + "UI/";
const std::string KEY_PATH = IMAGE_PATH + "keys/";
const std::string ENEMY_PATH = IMAGE_PATH + "enemies/";

const std::vector<int> FONT_SIZES = {18, 27, 36};
const std::vector<std::string> FONTS = {
    "0_abaddon_bold.ttf", "1_abaddon_light.ttf", "2_quicksand_regular.ttf"};

const std::string PLAYER_ICON = "right_0.png";
const std::vector<std::string> PLAYER_IDLE_LEFT = {"left_0.png"};
const std::vector<std::string> PLAYER_IDLE_RIGHT = {"right_0.png"};
const std::vector<std::string> PLAYER_IDLE_UP = {"right_0.png"};
const std::vector<std::string> PLAYER_IDLE_DOWN = {"right_0.png"};
const std::map<Direction, std::vector<std::string>> PLAYER_IDLE = {
    {Direction::LEFT, PLAYER_IDLE_LEFT},
    {Direction::RIGHT, PLAYER_IDLE_RIGHT},
    {Direction::UP, PLAYER_IDLE_UP},
    {Direction::DOWN, PLAYER_IDLE_DOWN}};
const std::vector<std::string> PLAYER_WALK_LEFT = {"left_0.png", "left_1.png",
                                                   "left_2.png", "left_3.png",
                                                   "left_4.png", "left_5.png"};
const std::vector<std::string> PLAYER_WALK_RIGHT = {
    "right_0.png", "right_1.png", "right_2.png",
    "right_3.png", "right_4.png", "right_5.png"};
const std::vector<std::string> PLAYER_WALK_UP = {"right_0.png", "right_1.png",
                                                 "right_2.png", "right_3.png",
                                                 "right_4.png", "right_5.png"};
const std::vector<std::string> PLAYER_WALK_DOWN = {
    "right_0.png", "right_1.png", "right_2.png",
    "right_3.png", "right_4.png", "right_5.png"};
const std::map<Direction, std::vector<std::string>> PLAYER_WALK = {
    {Direction::LEFT, PLAYER_WALK_LEFT},
    {Direction::RIGHT, PLAYER_WALK_RIGHT},
    {Direction::UP, PLAYER_WALK_UP},
    {Direction::DOWN, PLAYER_WALK_DOWN}};
const std::vector<std::string> PLAYER_ATTACK_LEFT = {
    "left_0.png", "left_1.png", "left_2.png",
    "left_3.png", "left_4.png", "left_5.png"};
const std::vector<std::string> PLAYER_ATTACK_RIGHT = {
    "right_0.png", "right_1.png", "right_2.png",
    "right_3.png", "right_4.png", "right_5.png"};
const std::vector<std::string> PLAYER_ATTACK_UP = {
    "right_0.png", "right_1.png", "right_2.png",
    "right_3.png", "right_4.png", "right_5.png"};
const std::vector<std::string> PLAYER_ATTACK_DOWN = {
    "right_0.png", "right_1.png", "right_2.png",
    "right_3.png", "right_4.png", "right_5.png"};
const std::map<Direction, std::vector<std::string>> PLAYER_ATTACK = {
    {Direction::LEFT, PLAYER_ATTACK_LEFT},
    {Direction::RIGHT, PLAYER_ATTACK_RIGHT},
    {Direction::UP, PLAYER_ATTACK_UP},
    {Direction::DOWN, PLAYER_ATTACK_DOWN}};
const std::map<MovementState, std::map<Direction, std::vector<std::string>>>
    PLAYER_TEXTURES = {{MovementState::IDLE, PLAYER_IDLE},
                       {MovementState::WALK, PLAYER_WALK},
                       {MovementState::ATTACK, PLAYER_ATTACK}};

const std::vector<std::string> CHARACTERS = {"0_shop1.png", "1_shop1.png"};
const std::vector<std::string> OBJECTS = {
    "0_coin.png",      "1_flower1.png",  "2_flower2.png",   "3_flower3.png",
    "4_fence1.png",    "5_fence2.png",   "6_fence3.png",    "7_fence4.png",
    "8_fence5.png",    "9_fence6.png",   "10_flower4.png",  "11_flower5.png",
    "12_flower6.png",  "13_flower7.png", "14_mailbox1.png", "15_mailbox2.png",
    "16_sign1.png",    "17_sign2.png",   "18_sign3.png",    "19_rock1.png",
    "20_rock2.png",    "21_tree1.png",   "22_tree2.png",    "23_house1.png",
    "24_house2.png",   "25_house3.png",  "26_flower8.png",  "27_flower9.png",
    "28_flower10.png", "29_bonfire.png"};
const std::vector<std::string> TILES = {
    "0_water1.png",    "1_grass.png",     "2_land.png",      "3_ground.png",
    "4_water.png",     "5_pond1.png",     "6_pond2.png",     "7_pond3.png",
    "8_pond4.png",     "9_pond5.png",     "10_pond6.png",    "11_pond7.png",
    "12_pond8.png",    "13_stairs1.png",  "14_stairs2.png",  "15_stairs3.png",
    "16_stairs4.png",  "17_stairs5.png",  "18_bridge1.png",  "19_bridge2.png",
    "20_bridge3.png",  "21_bridge4.png",  "22_bridge5.png",  "23_bridge6.png",
    "24_pond9.png",    "25_pond10.png",   "26_pond11.png",   "27_pond12.png",
    "28_stairs6.png",  "29_stairs7.png",  "30_stairs8.png",  "31_stairs9.png",
    "32_stairs10.png", "33_stairs11.png", "34_stairs12.png", "35_stairs13.png",
    "36_stairs14.png", "37_stairs15.png", "38_stairs16.png", "39_stairs17.png",
    "40_bridge7.png",  "41_bridge8.png"};
const std::vector<std::string> UIS = {
    "0_textbox.png",    "1_grid1.png",        "2_grid2.png",
    "3_panel1.png",     "4_panel2.png",       "5_panel3.png",
    "6_panel4.png",     "7_longbox.png",      "8_panel5.png",
    "9_panel6.png",     "10_panel7.png",      "11_panel8.png",
    "12_namecard.png",  "13_box.png",         "14_grid3.png",
    "15_grid4.png",     "16_grid5.png",       "17_panel9.png",
    "18_chatbox1.png",  "19_panel10.png",     "20_healthbarbg.png",
    "21_healthbar.png", "22_healthbarbg2.png"};
const std::map<SDL_Keycode, std::string> KEYS = {
    {SDLK_w, "w.png"},           {SDLK_a, "a.png"},
    {SDLK_s, "s.png"},           {SDLK_d, "d.png"},
    {SDLK_h, "h.png"},           {SDLK_p, "p.png"},
    {SDLK_l, "l.png"},           {SDLK_e, "e.png"},
    {SDLK_f, "f.png"},           {SDLK_TAB, "tab.png"},
    {SDLK_LSHIFT, "shift.png"},  {SDLK_RETURN, "return.png"},
    {SDLK_CAPSLOCK, "caps.png"}, {SDLK_ESCAPE, "esc.png"}};
const std::map<Uint8, std::string> MOUSE = {{SDL_BUTTON_LEFT, "left.png"},
                                            {SDL_BUTTON_RIGHT, "right.png"}};

const std::string ENEMY1_PATH = "enemy1/";
const std::vector<std::string> ENEMY1_IDLE_LEFT = {"walk_left_0.png"};
const std::vector<std::string> ENEMY1_IDLE_RIGHT = {"walk_right_0.png"};
const std::vector<std::string> ENEMY1_WALK_LEFT = {
    "walk_left_0.png", "walk_left_1.png", "walk_left_2.png", "walk_left_3.png",
    "walk_left_4.png", "walk_left_5.png", "walk_left_6.png", "walk_left_7.png",
};
const std::vector<std::string> ENEMY1_WALK_RIGHT = {
    "walk_right_0.png", "walk_right_1.png", "walk_right_2.png",
    "walk_right_3.png", "walk_right_4.png", "walk_right_5.png",
    "walk_right_6.png", "walk_right_7.png",
};
const std::vector<std::string> ENEMY1_ATTACK_LEFT = {
    "attack_left_0.png", "attack_left_1.png", "attack_left_2.png",
    "attack_left_3.png", "attack_left_4.png", "attack_left_5.png",
    "attack_left_6.png", "attack_left_7.png",
};
const std::vector<std::string> ENEMY1_ATTACK_RIGHT = {
    "attack_right_0.png", "attack_right_1.png", "attack_right_2.png",
    "attack_right_3.png", "attack_right_4.png", "attack_right_5.png",
    "attack_right_6.png", "attack_right_7.png",
};
const std::vector<std::string> ENEMY1_DEATH_LEFT = {
    "death_left_0.png", "death_left_1.png", "death_left_2.png",
    "death_left_3.png", "death_left_4.png", "death_left_5.png",
    "death_left_6.png", "death_left_7.png",
};
const std::vector<std::string> ENEMY1_DEATH_RIGHT = {
    "death_right_0.png", "death_right_1.png", "death_right_2.png",
    "death_right_3.png", "death_right_4.png", "death_right_5.png",
    "death_right_6.png", "death_right_7.png",
};
const std::map<MovementState, std::map<Direction, std::vector<std::string>>>
    ENEMY1_TEXTURES = {{MovementState::IDLE,
                        {{Direction::LEFT, ENEMY1_IDLE_LEFT},
                         {Direction::RIGHT, ENEMY1_IDLE_RIGHT}}},
                       {MovementState::WALK,
                        {{Direction::LEFT, ENEMY1_WALK_LEFT},
                         {Direction::RIGHT, ENEMY1_WALK_RIGHT}}},
                       {MovementState::ATTACK,
                        {{Direction::LEFT, ENEMY1_ATTACK_LEFT},
                         {Direction::RIGHT, ENEMY1_ATTACK_RIGHT}}},
                       {MovementState::DEATH,
                        {{Direction::LEFT, ENEMY1_DEATH_LEFT},
                         {Direction::RIGHT, ENEMY1_DEATH_RIGHT}}}};
const std::map<
    std::string,
    std::map<MovementState, std::map<Direction, std::vector<std::string>>>>
    ENEMY_TEXTURES = {{ENEMY1_PATH, ENEMY1_TEXTURES}};
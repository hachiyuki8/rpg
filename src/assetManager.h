#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <map>
#include <vector>

#include "constants/asset_constants.h"
#include "constants/controls.h"

/*
 * assetManager.h
 *
 * This file includes initializations of all resources except the player, which
 * is currently done in main.cpp. Most functions return false upon failure.
 *
 */

class Character;
class CharacterNPC;
class Enemy;
class Map;
class Object;

class AssetManager {
 public:
  AssetManager();
  virtual ~AssetManager();

  /**
   * Initialize libraries, fonts, and all game assets listed below
   *
   * @return false if any initialization failed
   */
  static bool init();

  /**
   * @brief Free all game resources and close libraries.
   * Note that all allocated player, NPCs, enemies and maps are freed in init.h.
   *
   */
  static void quit();

  static SDL_Window *window;
  static SDL_Renderer *renderer;
  static std::map<std::string, std::map<int, TTF_Font *>> allFonts;

  static SDL_Surface *startingScreen_text;
  static SDL_Texture *startingScreen_t;

  static Character *player;
  static SDL_Texture *playerIcon;
  static std::map<MovementState,
                  std::map<Direction, std::vector<SDL_Texture *>>>
      playerTextures;

  static std::map<
      std::string,
      std::map<MovementState, std::map<Direction, std::vector<SDL_Texture *>>>>
      enemyTextures;
  static std::map<std::string, SDL_Texture *> npcTextures;
  static std::map<std::string, SDL_Texture *> objectTextures;
  static std::map<std::string, SDL_Texture *> tileTextures;
  static std::map<std::string, SDL_Texture *> uiTextures;
  static std::map<SDL_Keycode, SDL_Texture *> keyTextures;
  static std::map<Uint8, SDL_Texture *> mouseTextures;

  static std::vector<Object *> allObjects;
  static std::vector<Map *> allMaps;
  static std::vector<CharacterNPC *> allNPCs;
  static std::vector<Enemy *> allEnemies;

 private:
  // Initialize libraries, winder and renderer
  static bool initLibraries();

  // Initialize all fonts in FONTS and store in allFonts
  static bool initFonts();

  // Initialize text on the starting screen and store in startingScreen
  static bool initStartingScreen();

  // Initialize all textures in PLAYER_TEXTURES and store in playerIcon/Textures
  static bool initTextures_Player();

  // Initialize all textures in CHARACTERS and store in npcTextures
  static bool initTextures_NPC();

  // Initialize all textures in OBJECTS and store in objectTextures
  static bool initTextures_Object();

  // Initialize all textures in TILES and store in tileTextures
  static bool initTextures_Tile();

  // Initialize all textures in UIS and store in UIs
  static bool initTextures_UI();

  // Initialize all textures in KEYS and store in keyTextures/mouseTextures
  static bool initTextures_KeyMouse();

  // Initialize all textures in ENEMY_TEXTURES and store in playerIcon/Textures
  static bool initTextures_Enemy();
};
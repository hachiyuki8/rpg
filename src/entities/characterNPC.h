#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdlib.h>

#include <iostream>
#include <tuple>

#include "../assetManager.h"
#include "../constants/npc_constants.h"
#include "../screens/convo.h"
#include "../screens/shop.h"

/*
 * characterNPC.h
 *
 * This file defines all NPC states and refers to npc_constants.h.
 *
 */

class Character;

class CharacterNPC {
 public:
  /**
   * @brief Construct a new NPC
   *
   * @param t NPC texture (TODO: currently no animation supported)
   * @param st NPC type
   * @param x position
   * @param y
   * @param w dimension
   * @param h
   */
  CharacterNPC(SDL_Texture *t, NPCState st = NPCState::SHOP_NPC,
               float x = (SCREEN_WIDTH - NPC_WIDTH) / 2,
               float y = (SCREEN_HEIGHT - NPC_HEIGHT) / 2, float w = NPC_WIDTH,
               float h = NPC_HEIGHT);
  virtual ~CharacterNPC();

  void print();

  /**
   * @brief Set the interaction collider
   *
   * @param left distance to the left of left border
   * @param right
   * @param up
   * @param down
   */
  void setInteractRange(float left, float right, float up, float down);

  /**
   * @brief Check if the given position collides with NPC
   *
   * @param x
   * @param y
   * @param w
   * @param h
   * @return true if collides with NPC collider (not interaction collider)
   */
  bool isInvalidPosition(float x, float y, float w, float h);

  /**
   * @brief When INTERACT is pressed, do one of the followings depending on
   * NPCState:
   * - open shop
   * - start conversation
   *
   * @param curPlayer
   * @param x player position
   * @param y
   * @param w
   * @param h
   * @return true if player in range and interaction carried out
   */
  bool onInteract(Character *curPlayer, float x, float y, float w, float h);

  /**
   * @brief When QUIT is pressed, do one of the followings depending on state:
   * - quit the conversation (progress lost)
   * - close the shop
   *
   */
  void onQuit();

  /**
   * @brief When left mouse button is pressed, do one of the followings
   * depending on state:
   * - select/unselect items in shop
   *
   * @param x cursor position
   * @param y
   */
  void onClick(float x, float y);

  /**
   * @brief When CONFIRM is pressed, do one of the followings
   * depending on state:
   * - buy one selected item in shop
   * - proceed the current conversation
   *
   * @param curPlayer
   * @return false if is CONVO_NPC and current conversation ended
   */
  bool onConfirm(Character *curPlayer);

  /**
   * @brief Reset conversation contents for CONVO_NPC, no-op for other NPC type
   *
   * @param lines a vector of (speaker texture name, lines to be shown on the
   * same screen), where name refers to npcTextures or playerIcon if empty
   */
  void setConvo(
      std::vector<std::tuple<std::string, std::vector<std::string>>> lines);

  /**
   * @brief Add given items to SHOP_NPC's shop, no-op for other NPC type
   *
   * @param items a vector of (object, quantity)
   */
  void addToShop(std::vector<std::tuple<Object *, int>> items);

  /**
   * @brief Render the NPC based on camera position. Note that the associated UI
   * screen will not be rendered.
   *
   * @param renderer
   * @param camX
   * @param camY
   * @param camW
   * @param camH
   */
  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);

  /**
   * @brief Render the NPC's associated UI screen depending on state, being one
   * of the followings:
   * - shop
   * - conversation
   *
   * @param renderer
   */
  void renderScreen(SDL_Renderer *renderer);

  static int nextID;

 private:
  int ID;

  NPCState state;
  // depending on NPC's state, at most one of the followings will be meaningful
  Shop shop;
  Convo convo;

  // NPC textures
  SDL_Texture *texture;

  // NPC position
  float xPos;
  float yPos;
  float width;
  float height;

  // TODO: NPC movement states

  // interaction collider, default to NPC size, won't automatically update if
  // position changed
  float xPosI;
  float yPosI;
  float widthI;
  float heightI;

  // Return true if given position collides with interaction collider
  bool isInRange(float x, float y, float w, float h);
};
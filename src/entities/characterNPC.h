#pragma once

#include "../constants/npc_constants.h"
#include "../globals.h"
#include "../screens/convo.h"
#include "../screens/shop.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

/*
 * characterNPC.h
 *
 * This file defines all NPC states and refers to npc_constants.h.
 *
 */

class Character;

class CharacterNPC {
public:
  CharacterNPC(SDL_Texture *t, NPCState st = NPCState::SHOP_NPC,
               float x = (SCREEN_WIDTH - DEFAULT_NPC_WIDTH) / 2,
               float y = (SCREEN_HEIGHT - DEFAULT_NPC_HEIGHT) / 2,
               float w = DEFAULT_NPC_WIDTH, float h = DEFAULT_NPC_HEIGHT);
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
   * @brief Reset conversation contents for NPCs
   *
   * @param lines a list of (speaker texture index, lines to be shown on the
   * same screen), where index refers to npcTextures or playerIcon if -1
   */
  void setConvo(std::vector<std::tuple<int, std::vector<std::string>>> lines);

  /**
   * @brief Show the next screen of the conversation
   *
   * @return false if conversation ends
   */
  bool nextConvo();

  /**
   * @brief Quit the conversation, progress not preserved
   *
   */
  void quitConvo();

  /**
   * @brief Render the NPC based on camera position
   *
   * @param renderer
   * @param camX
   * @param camY
   * @param camW
   * @param camH
   */
  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);

  static int nextID;

  // depending on NPC's state, at most one of the followings will be meaningful
  Shop shop;
  Convo convo;

private:
  int ID;

  NPCState state;

  // NPC textures
  // TODO: add animations
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

  // Return true if given position colliders with interaction collider
  bool isInRange(float x, float y, float w, float h);
};
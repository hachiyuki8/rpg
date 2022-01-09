#pragma once

#include "../constants/npc_constants.h"
#include "../globals.h"
#include "../screens/shop.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

class Character;

class CharacterNPC {
public:
  CharacterNPC(SDL_Texture *t, NPCState st = NPCState::SHOP_NPC,
               float x = (SCREEN_WIDTH - DEFAULT_NPC_WIDTH) / 2,
               float y = (SCREEN_HEIGHT - DEFAULT_NPC_HEIGHT) / 2,
               float w = DEFAULT_NPC_WIDTH, float h = DEFAULT_NPC_HEIGHT);
  virtual ~CharacterNPC();

  void print();
  void setInteractRange(float left, float right, float up, float down);
  bool isInvalidPosition(float x, float y, float w, float h);
  bool onInteract(Character *curPlayer, float x, float y, float w,
                  float h); // caller ensures that curPlayer->uiState is IN_GAME

  void render(SDL_Renderer *renderer, float camX, float camY, float camW,
              float camH);

  static int nextID;
  Shop shop;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float width;
  float height;
  NPCState state;

  // collider for interacting with character, default to character size, won't
  // automatically update if character position changed
  float xPosI;
  float yPosI;
  float widthI;
  float heightI;

  bool isInRange(float x, float y, float w,
                 float h); // if collides with character's interaction range
};
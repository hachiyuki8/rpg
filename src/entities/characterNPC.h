#pragma once

#include "../constants/character_constants.h"
#include "../screens/shop.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>

class Character;

class CharacterNPC {
public:
  CharacterNPC(SDL_Texture *t, SDL_Texture *shop_t, TTF_Font *f,
               PlayerState st = PlayerState::SHOP_NPC,
               float x = (SCREEN_WIDTH - DEFAULT_CHARACTER_WIDTH) / 2,
               float y = (SCREEN_HEIGHT - DEFAULT_CHARACTER_HEIGHT) / 2,
               float w = DEFAULT_CHARACTER_WIDTH,
               float h = DEFAULT_CHARACTER_HEIGHT);
  virtual ~CharacterNPC();

  void print();
  void setInteractRange(float left, float right, float up, float down);
  bool onInteract(Character *curPlayer, float x, float y, float w,
                  float h); // caller ensures that curPlayer->uiState is IN_GAME

  void render(SDL_Renderer *renderer);

  static int nextID;
  Shop shop;

private:
  int ID;
  SDL_Texture *texture;

  float xPos;
  float yPos;
  float width;
  float height;
  PlayerState state;

  // collider for interacting with character, default to character size, won't
  // automatically update if character position changed
  float xPosI;
  float yPosI;
  float widthI;
  float heightI;

  bool isInRange(float x, float y, float w,
                 float h); // if collides with character's interaction range
};
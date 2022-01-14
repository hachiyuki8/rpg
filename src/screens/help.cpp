#include "help.h"

int Help::nextID = 0;

Help::Help(float x, float y, float w, float h) {
  ID = nextID;
  nextID++;
  if (DEBUG) {
    std::cout << "Creating help " << ID << std::endl;
  }

  xPos = x;
  yPos = y;
  width = w;
  height = h;
}

Help::~Help() {
  if (DEBUG) {
    std::cout << "Destroying help " << ID << std::endl;
  }
  for (auto &c : controls) {
    SDL_FreeSurface(c.name_text);
  }
}

void Help::print() { std::cout << "Help " << ID << std::endl; }

void Help::init() {
  for (auto &c : HELP_KEY) {
    struct Control newC;
    newC.isKey = true;
    newC.key = std::get<1>(c);
    SDL_Surface *text =
        TTF_RenderText_Solid(font, std::get<0>(c).c_str(), text_color);
    if (!text) {
      std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }
    newC.name_text = text;
    switch (newC.key) {
      case SDLK_TAB:
      case SDLK_LSHIFT:
      case SDLK_RETURN:
      case SDLK_CAPSLOCK:
        newC.button_width = 2 * HELP_ICON_HEIGHT;
    }
    controls.push_back(newC);
  }

  for (auto &c : HELP_MOUSE) {
    struct Control newC;
    newC.isKey = false;
    newC.mouse = std::get<1>(c);
    SDL_Surface *text =
        TTF_RenderText_Solid(font, std::get<0>(c).c_str(), text_color);
    if (!text) {
      std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }
    newC.name_text = text;
    controls.push_back(newC);
  }
}

void Help::open() { isShowing = true; }

void Help::close() { isShowing = false; }

void Help::render(SDL_Renderer *renderer) {
  if (isShowing) {
    SDL_Rect r;
    r.x = xPos;
    r.y = yPos;
    r.w = width;
    r.h = height;
    SDL_RenderCopy(renderer, texture, NULL, &r);

    int nextR = 0;
    int nextC = 0;
    for (auto &c : controls) {
      SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, c.name_text);
      r.x = xPos + HELP_OFFSET_BORDER +
            nextC * (width - HELP_OFFSET_BORDER * 2) / NUM_COL;
      r.y = yPos + HELP_OFFSET_BORDER + nextR * HELP_LINE_HEIGHT;
      r.w = c.name_text->w;
      r.h = c.name_text->h;
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_DestroyTexture(t);

      r.w = c.button_width;
      r.h = c.button_height;
      r.x += width / 2 - HELP_OFFSET_BORDER * 3 - r.w;
      if (c.isKey) {
        SDL_RenderCopy(renderer, AssetManager::keyTextures[c.key], NULL, &r);
      } else {
        SDL_RenderCopy(renderer, AssetManager::mouseTextures[c.mouse], NULL,
                       &r);
      }

      r.x -= width / 2 - HELP_OFFSET_BORDER * 3 - r.w;

      if (nextR + 1 < NUM_ROW) {
        nextR++;
      } else if (nextC + 1 < NUM_COL) {
        nextR = 0;
        nextC++;
      }
    }
  }
}
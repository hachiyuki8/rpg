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
    SDL_FreeSurface(c.second.name_text);
  }
}

void Help::init() {
  for (auto &c : HELP_ALL) {
    if (controls.contains(c.first)) {
      std::cout << "Control already exists" << std::endl;
      return;
    }

    struct Control newC;
    newC.key = c.second;
    SDL_Surface *text = TTF_RenderText_Solid(font, c.first.c_str(), text_color);
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
    controls[c.first] = newC;
  }
}

void Help::print() { std::cout << "Help " << ID << std::endl; }

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
      SDL_Texture *t =
          SDL_CreateTextureFromSurface(renderer, c.second.name_text);
      r.x = xPos + HELP_OFFSET_BORDER +
            nextC * (width - HELP_OFFSET_BORDER * 2) / NUM_COL;
      r.y = yPos + HELP_OFFSET_BORDER + nextR * HELP_LINE_HEIGHT;
      r.w = c.second.name_text->w;
      r.h = c.second.name_text->h;
      SDL_RenderCopy(renderer, t, NULL, &r);
      SDL_DestroyTexture(t);

      r.w = c.second.button_width;
      r.h = c.second.button_height;
      r.x += width / 2 - HELP_OFFSET_BORDER * 3 - r.w;
      SDL_RenderCopy(renderer, keyTextures[c.second.key], NULL, &r);
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
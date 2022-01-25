#include "itemlist.h"

#include "mapEditor.h"

Itemlist::Itemlist() {}

Itemlist::~Itemlist() {}

void Itemlist::render(SDL_Renderer *renderer) {
  SDL_Rect r;
  r.x = ITEMLIST_XPOS;
  r.y = ITEMLIST_YPOS;
  r.w = ITEMLIST_WIDTH;
  r.h = ITEMLIST_HEIGHT;
  SDL_RenderCopy(renderer, MapEditor::editorTextures[ITEMLIST_GRID_BG_TEXTURE],
                 NULL, &r);
}
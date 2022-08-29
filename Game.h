#ifndef _GAME_H
#define _GAME_H

#include "QUAD.h"

class Game : public QUAD{

   public:
      Game(HINSTANCE* hInstance);
      ~Game();
      void run();

};
#endif




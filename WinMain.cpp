#include "Game.h"

int WINAPI WinMain(
      HINSTANCE hInstance, 
      HINSTANCE hPrevInstance, 
      LPSTR lpCmdLine, 
      int nCmdShow){
   Game quad(&hInstance);
   quad.run();
   return 0;
}

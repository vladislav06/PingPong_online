#pragma comment( lib, "wsock32.lib" )
#include <sdl.h>
#include "SDL.h"
#include <random>
#include <iostream>

int main(int argc, char* argv[])
{
    SDL window(SDL_INIT_EVENTS);//create window
    window.createWindow("pong", 100, 100, 1000, 500, SDL_WINDOW_SHOWN);
    window.createRenderer(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
   

    object::rectangle rect;        //create texture
    rect.color(0, 0, 0, 255);//set trexture properties
    rect.size(100, 100);


    object ball(&rect);    //create object and pass to it a texture
    ball.update();
    ball.coordinates(50, 50);
    ball.vector(1, 2);

    object ball2(&rect);
    ball2.update();
    ball2.coordinates(100, 100);
    ball2.vector(1, 1);

    window.addElement(&ball);   //say to window that we have new object
    window.addElement(&ball2);

    SDL_Event e;
here:
    window.calculate();
    window.Render();

    if (SDL_PollEvent(&e)) {
        //If user closes the window
        if (e.type == SDL_QUIT) {
            //quit = true;
        }
        //If user presses any key
        if (e.type == SDL_KEYDOWN) {

        }
        //If user clicks the mouse
        if (e.type == SDL_MOUSEBUTTONDOWN) {

        }
    }
    goto here;
    std::cin >> argc;
    window.clean();
    std::cout << "end render\n";
    return 0;
}
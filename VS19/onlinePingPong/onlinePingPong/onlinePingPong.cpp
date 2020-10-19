#pragma comment( lib, "wsock32.lib" )
#include <sdl.h>
#include "SDL.h"
#include <random>
#include <iostream>
#include <chrono>


int main(int argc, char* argv[])
{
                  

    SDL window(SDL_INIT_EVENTS);//create window
    window.createWindow("pong", 100, 100, 1000, 500, SDL_WINDOW_SHOWN);  
    window.createRenderer(-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    const int snake_thikness = 10;

    object::rectangle rect;        //create texture
    rect.color(0, 255, 0, 255);//set trexture properties
    rect.size(snake_thikness, snake_thikness);


    int snake_speed = 3;
    int lenght = 100;
    object::cord2D coordinates[5000];//mah snake lenght

    object::array body(&rect);
    body.setTexture(coordinates, lenght*sizeof(coordinates[0]));

    object snake(&body);  //create object and pass to it a texture
    snake.update();
    snake.coordinates(0, 0);

    window.addElement(&snake);   //say to window that we have new object

    object::rectangle apple_t;
    apple_t.color(255, 0, 0, 0);
    apple_t.size(10, 10);
    
    object apple(&apple_t);
    apple.update();
    apple.coordinates(100, 100);

    window.addElement(&apple);

    SDL_Rect field;
    field.x = 0;
    field.y = 0;
    field.h = 500;
    field.w = 1000;


    SDL_Event e;
    object::cord2D localVector;
    bool loop = true;

    while (loop)
    {
        auto start = std::chrono::high_resolution_clock::now();
        if (SDL_PollEvent(&e)) {
            //If user closes the window
            if (e.type == SDL_QUIT) {
                loop = false;
            }
        }

        const Uint8* key = SDL_GetKeyboardState(NULL);

        if (key[SDL_SCANCODE_UP])
        {

            // snake can turn only if 10 or more pixels are past
            //     divide by snake_speed to compensate speed(for ex. if speed == 2 then evry cyclel next pont wuld be 2 nor 1)
            if (coordinates[10 / snake_speed].y == snake.coordinates().y)
            {
                localVector.y = -snake_speed;
                localVector.x = 0;
            }
        }

        if (key[SDL_SCANCODE_DOWN])
        {
            if (coordinates[10 / snake_speed].y == snake.coordinates().y)
            {
                localVector.y = snake_speed;
                localVector.x = 0;
            }
        }

        if (key[SDL_SCANCODE_LEFT])
        {
            if (coordinates[10 / snake_speed].x == snake.coordinates().x)
            {
                localVector.x = -snake_speed;
                localVector.y = 0;
            }
        }

        if (key[SDL_SCANCODE_RIGHT])
        {
            if (coordinates[10 / snake_speed].x == snake.coordinates().x)
            {
                localVector.x = snake_speed;
                localVector.y = 0;
            }
        }
        if (coordinates[0].x >= 10)
        {//i = 20 just because head hits body when rotates
            for (int i = 20; i <= lenght ; i += snake_thikness) //take evry 10 body pice
            {
                //take pice of body and convert it to rect
                SDL_Rect body;
                body.x = coordinates[i].x;
                body.y = coordinates[i].y;
                body.h = snake_thikness;    
                body.w = snake_thikness;
               
                if ( SDL_HasIntersection(&body, &snake.toRect()) )
                {
                    rect.color(255, 0, 0, 0);//set red color
                }
            }
        }
       

        //if snake eat apple
        if ( SDL_HasIntersection(&snake.toRect(), &apple.toRect()) ) {
            rect.color(0, 255, 0, 0);//set green color

            apple.coordinates(std::rand() % 990, std::rand() % 490);//spawn new apple

            lenght += 10;//increase snake lenght by 10 pixels
        }
        //if snake out of bound
        SDL_Rect* tmp = new SDL_Rect;
        
        if (!SDL_HasIntersection(&field, &snake.toRect()))
        {
            std::cout << "!!!!!!!" << std::endl;
            rect.color(255, 0, 0, 0);//set red color
        }


        snake.vector(localVector.x, localVector.y);
        coordinates[0] = snake.coordinates(); //set [0] body coordinate to head

        for (int i = lenght; i >= 1; i--)//move all body coordinates to back
        {
            coordinates[i] = coordinates[i-1];
        }

        body.setTexture(coordinates, lenght * sizeof(coordinates[0]));//update body
        snake.update();

        window.calculate();
        window.Render();

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        std::cout << 1000 / (float)(microseconds / 1000) << std::endl;//get fps
    }
    window.clean();

    return 0;
}
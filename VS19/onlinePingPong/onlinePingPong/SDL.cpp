#include "SDL.h"
#include <sdl.h>
#include <iostream>
#include "vector.h"
//main type




SDL::SDL(Uint32 flags)
{
	SDL_Init(flags);
};

int SDL::createWindow(const char* WinName, int x, int y, int w, int h, Uint32 WinFlags) 
{
	window = SDL_CreateWindow(WinName, x, y, w, h, WinFlags);
	if (window == nullptr)
	{
		SDL_DestroyWindow(window);
		return 1;
	}
	return 0;
};

int SDL::createRenderer(int index, Uint32 flags)
{
	render = SDL_CreateRenderer(window, index, flags);
	if (render == nullptr)
	{
		SDL_DestroyRenderer(render);
		return 1;
	}
	return 0;
};

void SDL::Render()
{
	//clear all screen 
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderClear(render);
	//render each object
	for (int i = 0; i < elements.size(); i++)
	{
		//std::cout << "object: "<<i << "\n";

		elements[i]->render(render);
		//std::cout << elements[i]->cordinates.x << std::endl;
	
	}
	//present render
	SDL_RenderPresent(render);
};
void SDL::calculate()
{
	for (int i = 0; i < elements.size(); i++)
	{
		//std::cout << "object: "<<i << "\n";

		elements[i]->calculate();
		//std::cout << elements[i]->cordinates.x << std::endl;

	}
};

void SDL::clean()
{
	SDL_Quit();
}

void SDL::addElement(object* element)
{
	elements.push_back(element);
};




///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////

//inner type (object)
//inner type (object)
//inner type (object)




object::object(rectangle* r)// Set the reference.
{
	rect = r;//set pointer to texture
	sdl_rect = new SDL_Rect;
};



void object::update()
{
	//update properties
	rect->update(&cord_, sdl_rect);
};


//coordinates
void object::coordinates(int x, int y)
{
	cord_.x = x;
	cord_.y = y;
};

object::cord2D object::coordinates()
{
	return cord_;
};


//vector
void object::vector(float x, float y)
{
	vector_.x = x;
	vector_.y = y;
};

struct VectMath::vector object::vector()
{
	return vector_;
};


//process
void object::render(SDL_Renderer* rend)
{
	rect->render(rend, sdl_rect);
	//std::cout << "rendering.....\n";
};

void object::calculate()
{
	rect->proces(&cord_, &vector_);
	//update
	update();
};




//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////


void object::rectangle::proces(struct cord2D* cord_, VectMath::vector* vector_)
{
	VectMath::vector vect;
	
	vect.x = cord_->x;
	vect.y = cord_->y;

	vect = VectMath::sum(vect, *vector_);

	cord_->x = vect.x;
	cord_->y = vect.y;
	std::cout << vect.x << "|" << vect.y<<"| |";
	//update(cord_, SDL_rect);
}

void object::rectangle::render(SDL_Renderer* rend, SDL_Rect* SDL_rect)
{
	SDL_SetRenderDrawColor(rend, color_.r, color_.g, color_.b, color_.a);

	SDL_RenderFillRect(rend, SDL_rect);
}

void object::rectangle::update(object::cord2D *cord_, SDL_Rect* SDL_rect)
{
	SDL_rect->h = size_.h;
	SDL_rect->w = size_.w;

	SDL_rect->x = cord_->x;
	SDL_rect->y = cord_->y;
	std::cout << cord_->x << "|" << cord_->y<<std::endl;
}

void object::rectangle::color(int r, int g, int b, int a)
{
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
}


void object::rectangle::size(int h, int w)
{
	size_.h = h;
	size_.w = w;
}
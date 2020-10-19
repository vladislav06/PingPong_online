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
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
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
	rect_ = r;//set pointer to texture
	sdl_rect_ = new SDL_Rect;
	type = RECTANGLE;
};



object::object(array* ar)// Set the reference.
{
	arr_ = ar;
	type = ARRAY;
};



void object::update()
{
	//update properties
	switch (type)
	{
	case RECTANGLE:
		rect_->update(&cord_, sdl_rect_);
		break;
	case ARRAY:
		arr_->update();
	}

	
};



SDL_Rect object::toRect()
{
	SDL_Rect rect;

	switch (type)
	{
	case RECTANGLE:
		rect.x = cord_.x;
		rect.y = cord_.y;
		rect.h = rect_->size_.h;
		rect.w = rect_->size_.w;
		break;
	case ARRAY:
		rect.x = cord_.x;
		rect.y = cord_.y;
		rect.h = arr_->rect_->h;
		rect.w = arr_->rect_->w;
	}
	

	return rect;
}



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
	switch (type)
	{
	case RECTANGLE:
		rect_->render(rend, sdl_rect_);
		break;
	case ARRAY:
		arr_->render(rend, sdl_rect_);
	}

	
	//std::cout << "rendering.....\n";
};

void object::calculate()
{
	switch (type)
	{
	case RECTANGLE:
		rect_->proces(&cord_, &vector_);
		break;
	case ARRAY:
		VectMath::vector vect;

		vect.x = cord_.x;
		vect.y = cord_.y;

		vect = VectMath::sum(vect, vector_);

		cord_.x = vect.x;
		cord_.y = vect.y;
		break;
	}
	
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
	//std::cout << vect.x << "|" << vect.y<<"| |";
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
}

void object::rectangle::update(SDL_Rect* SDL_rect)
{
	SDL_rect->h = size_.h;
	SDL_rect->w = size_.w;
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







//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
object::array::array( object::rectangle* r)
{
	rect = r;//set pointer to texture
	rect_ = new SDL_Rect;
}

void object::array::addTexture(int x, int y)
{
	cord2D cord;
	cord.x = x;
	cord.y = y;
	elements.push_back(cord);
}

void object::array::addTexture(cord2D cords[], int size)
{
	size = size / sizeof(cords[0]);
	for (int i = 0; i < size; i++)
	{
		elements.push_back(cords[i]);
	}
}

void object::array::setTexture(cord2D cords[], int size)
{
	elements.clear();
	size = size / sizeof(cords[0]);
	//std::cout << "size" << size << std::endl;
	for (int i = 0; i < size; i++)
	{
		elements.push_back(cords[i]);
		//std::cout << "set!  " << i << std::endl;
	}
}


void object::array::render(SDL_Renderer* rend, SDL_Rect* SDL_rect)
{

	// Iterate and render each object
	for (cord2D cord : elements)
	{
		rect_->x = cord.x;
		rect_->y = cord.y;
		rect->render(rend, rect_);
	}
}


void object::array::update()
{

	rect->update(rect_);
}

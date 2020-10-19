#pragma once
#include <sdl.h>
#include "SDL.h"
#include <string>
#include <vector>
#include "vector.h"



class object
{
private:
	struct color
	{
		int r = 0;//red
		int g = 0;//green
		int b = 0;//blue
		int a = 0;//alpha
	};
	struct size2D
	{
		int h = 0;
		int w = 0;
	};

	friend class rectangle;
	//friend class array;
public:
	//data types
	struct cord2D
	{
		int x = 0;
		int y = 0;
	};


	////////////////////////////////////

	class rectangle
	{
	protected:
		//SDL_Rect SDL_rect;
		struct color color_;
		struct size2D size_;
		//update SDL_Rectangle
		void update(object::cord2D *cord_, SDL_Rect* SDL_rect);
		void update(SDL_Rect* SDL_rect);//just update size
		//refresh coordinates
		void proces(struct cord2D* cord_, VectMath::vector* vector_);
		//render
		void render(SDL_Renderer* rend, SDL_Rect* SDL_rect);
	public:

		void color(int r, int g, int b, int a);//set color
		void size(int h, int w);//set size
		friend class object;
	};

	class array
	{
	protected:
		std::vector<cord2D>elements;

		rectangle* rect;

		SDL_Rect* rect_;
	public:
		array();
		array(object::rectangle* rect);
		void addTexture(int x, int y);
		void addTexture(cord2D[], int size);
		void setTexture(cord2D[], int size);
		//update SDL_Rectangle
		void update();
		//render
		void render(SDL_Renderer* rend, SDL_Rect* SDL_rect);
		

		friend class object;
	};



	
	////////////////////////////////////

private:
	
	

	//variables
	//struct cord2D cord;

	//functions
	enum type
	{
		RECTANGLE,
		ARRAY
	};
	int type;
	void render(SDL_Renderer* rend);
	void calculate();

	friend class SDL;

	// data 

	struct cord2D cord_;
	VectMath::vector vector_;

	//object

	rectangle* rect_;
	array* arr_;
	SDL_Rect* sdl_rect_;


public:

	object(rectangle* r);
	object(array* r);

	//functions
	void update();
	SDL_Rect toRect();


	//coordinates (set;get)
	void coordinates(int x, int y);
	struct cord2D coordinates();
	//vector (set;get)
	void vector(float x, float y);
	struct VectMath::vector vector();
}; 



class SDL
{
private:




public:

	//functions
	SDL(Uint32 flags);
	int createWindow(const char* windowName, int x, int y, int w, int h, Uint32 WinFlags);
	int createRenderer(int index, Uint32 flags);
	void calculate();
	void Render();
	void clean();



	////////////////////////////////////




	void addElement(object* element);




private:




	//friend class object;

	//members (variables)
	SDL_Window* window;
	SDL_Renderer* render;
	int LastError = 0;
	std::vector<object*>elements;
};

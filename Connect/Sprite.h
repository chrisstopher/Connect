#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "SDL_Image.h"
#include "SDL_opengl.h"
#include "Position.h"
#include "Color.h"
#include "Rect.h"
#include <fstream>
#include <iostream>
#include <string>

class Sprite {
public:
	Sprite();
	Sprite(const std::string& file, int spriteWidth, int spriteHeight);
	Sprite(std::ifstream& file);
	~Sprite();
	bool load(const char* file, int spriteWidth, int spriteHeight);
	bool load();
	void start();
		void translateTo(int x, int y);
		void translateTo(Position& position);
		void scaleXnY(float scalar);
		void rotateX(float angle);
			void draw(int x, int y, int frame);
			void toggleTexture2d();
	void end();
	int getMaxRows() const;
	int getMaxColumns() const;
	unsigned int getSpriteWidth() const;
	unsigned int getSpriteHeight() const;
	int getImageWidth() const;
	int getImageHeight() const;
	void changeTextureColorAt(int frame, Color& newColor);
	friend std::ostream& operator<<(std::ostream& os, Sprite* sprite);
private:
	GLuint texture;
	Rect *texCoords;
	int spriteWidth;
	int spriteHeight;
	unsigned int imageWidth;
	unsigned int imageHeight;
	int maxRows;
	int maxColumns;
	Color* texColors;
	std::string filename;
};

#endif
#include "Sprite.h"

Sprite::Sprite() : texture(NULL), texCoords(NULL),
				   spriteWidth(0), spriteHeight(0), imageWidth(0), imageHeight(0), maxRows(0), maxColumns(0),
				   texColors(NULL), filename("") {

}

Sprite::Sprite(const std::string& file, int newSpriteWidth, int newSpriteHeight) : texture(NULL), texCoords(NULL),
				   spriteWidth(newSpriteWidth), spriteHeight(newSpriteHeight), imageWidth(0), imageHeight(0), maxRows(0), maxColumns(0),
				   texColors(NULL), filename(file) {
	
}

Sprite::Sprite(std::ifstream& file) : texture(NULL), texCoords(NULL),
									  spriteWidth(0), spriteHeight(0), imageWidth(0), imageHeight(0), maxRows(0), maxColumns(0),
									  texColors(NULL) {
	file >> filename >> spriteWidth >> spriteHeight;
}

Sprite::~Sprite() {
	if (texture) {
		glDeleteTextures(1, &texture);
	}
	texture = NULL;
	if (texCoords) {
		delete [] texCoords;
	}
	texCoords = NULL;
	if (texColors) {
		delete [] texColors;
	}
	texColors = NULL;
}

bool Sprite::load() {
	if (filename.empty()) {
		std::cout << "Could not load NULL file!\n";
		return false;
	}
	if (spriteWidth < 0 || spriteHeight < 0) {
		std::cout << "Sprite width and height have to be greater than 0.\n";
		return false;
	}
	SDL_Surface *image = NULL;
	if ((image = IMG_Load(filename.c_str())) == NULL) {
		std::cout << "Could not load: " << filename << "!\n";
		return false;
	}
	if (spriteWidth > image->w || spriteHeight > image->h) {
		if (spriteWidth > image->w) {
			std::cout << "The sprite of:" << filename << "width cannot be greater than or equal to the image width:\n"
					  << "Sprite width specified: " << spriteWidth << "    Image width: " << image->w << "\n"; 
		}
		if (spriteHeight > image->h) {
			std::cout << "The sprite of:" << filename << " height cannot be greater than or equal to the image height:\n"
					  << "Sprite height specified: " << spriteHeight << "    Image height: " << image->h << "\n"; 
		}
		SDL_FreeSurface(image);
		return false;
	}
	SDL_DisplayFormatAlpha(image);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int mode;
	int numOfColors = image->format->BytesPerPixel;
	if (numOfColors == 4) {// contains an alpha channel
		if (image->format->Rmask == 0x000000ff)
			mode = GL_RGBA;
		else
			mode = GL_BGRA;
	} else if (numOfColors == 3) {// no alpha channel
		if (image->format->Rmask == 0x000000ff)
			mode = GL_RGB;
		else
			mode = GL_BGR;
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, mode/*GL_RGBA*/, GL_UNSIGNED_BYTE, image->pixels);
	imageWidth = image->w;
	imageHeight = image->h;
	if (spriteWidth == 0) {
		spriteWidth = imageWidth;
	}
	if (spriteHeight == 0) {
		spriteHeight = imageHeight;
	}
	maxColumns = imageWidth / spriteWidth;
	maxRows = imageHeight / spriteHeight;
	if (image) {
		SDL_FreeSurface(image);
	}
	image = NULL;
	int spriteCount = maxRows * maxColumns;
	texCoords = new Rect[spriteCount];
	texColors = new Color[spriteCount];
	int i = 0;
	for (int y = 0; y < maxRows; y++) {
		for (int x = 0; x < maxColumns; x++) {
			texCoords[i].x = static_cast<float>(spriteWidth * x) / imageWidth;
			texCoords[i].y = static_cast<float>(spriteHeight * y) / imageHeight;
			texCoords[i].w = static_cast<float>(spriteWidth * (/*x+*/1)) / imageWidth;
			texCoords[i].h = static_cast<float>(spriteHeight * (/*y+*/1)) / imageHeight;
			texColors[i].r = 255;
			texColors[i].g = 255;
			texColors[i].b = 255;
			texColors[i].a = 255;
			i++;
		}
	}
	return true;
}

bool Sprite::load(const char* file, int newSpriteWidth, int newSpriteHeight) {
	filename = file;
	spriteWidth = newSpriteWidth;
	spriteHeight = newSpriteHeight;
	return load();
}

/*
Always called before any drawing starts
*/
void Sprite::start() {
	glEnable(GL_TEXTURE_2D);// enabling textures
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

void Sprite::translateTo(int x, int y) {
	glPushMatrix();
	glTranslatef(static_cast<GLfloat>(x), static_cast<GLfloat>(y), 0);
}

void Sprite::translateTo(Position& position) {
	glPushMatrix();
	glTranslatef(static_cast<GLfloat>(position.x), static_cast<GLfloat>(position.y), 0);
}

void Sprite::scaleXnY(float scalar) {
	glScalef(scalar, scalar, 0);
}

void Sprite::rotateX(float angle) {
	glRotatef(angle, 0, 0, 1);
}

void Sprite::toggleTexture2d() {
	if (glIsEnabled(GL_TEXTURE_2D)) {
		glDisable(GL_TEXTURE_2D);
	} else {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}

/*
x and y are offsets of the position you want
*/
void Sprite::draw(int x, int y, int frame) {
	const GLubyte COLOR[] = {
		texColors[frame].r, texColors[frame].g, texColors[frame].b, texColors[frame].a, 
		texColors[frame].r, texColors[frame].g, texColors[frame].b, texColors[frame].a, 
		texColors[frame].r, texColors[frame].g, texColors[frame].b, texColors[frame].a, 

		texColors[frame].r, texColors[frame].g, texColors[frame].b, texColors[frame].a, 
		texColors[frame].r, texColors[frame].g, texColors[frame].b, texColors[frame].a, 
		texColors[frame].r, texColors[frame].g, texColors[frame].b, texColors[frame].a
	};

	const GLint vertices[] = {
		x, y,
		x + spriteWidth, y,
		x, y + spriteHeight,

		x + spriteWidth, y,
		x, y + spriteHeight,
		x + spriteWidth, y + spriteHeight
	};

	const GLfloat TEXTURE_COORDS[] = {
		texCoords[frame].x, texCoords[frame].y,
		texCoords[frame].x + texCoords[frame].w, texCoords[frame].y,
		texCoords[frame].x, texCoords[frame].y + texCoords[frame].h,

		texCoords[frame].x + texCoords[frame].w, texCoords[frame].y,
		texCoords[frame].x, texCoords[frame].y + texCoords[frame].h,
		texCoords[frame].x + texCoords[frame].w, texCoords[frame].y + texCoords[frame].h
	};
	glVertexPointer(2, GL_INT, 0, vertices);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, COLOR);
	glTexCoordPointer(2, GL_FLOAT, 0, TEXTURE_COORDS);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
	glPopMatrix();
}

/*
Always called after any drawing ends
*/
void Sprite::end() {
	glDisableClientState(GL_VERTEX_ARRAY);// deactivate vertex arrays after drawing
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);// deactivate coord arrays after drawing
	glDisableClientState(GL_COLOR_ARRAY);// deactivate color arrays after drawing

	glDisable(GL_TEXTURE_2D);
}

int Sprite::getMaxRows() const {
	return maxRows;
}

int Sprite::getMaxColumns() const {
	return maxColumns;
}

unsigned int Sprite::getSpriteWidth() const {
	return spriteWidth;
}

unsigned int Sprite::getSpriteHeight() const {
	return spriteHeight;
}

int Sprite::getImageWidth() const {
	return imageWidth;
}

int Sprite::getImageHeight() const {
	return imageHeight;
}

void Sprite::changeTextureColorAt(int frame, Color& newColor) {
	texColors[frame] = newColor;
}

std::ostream& operator<<(std::ostream& os, Sprite* sprite) {
	os << sprite->filename.substr(sprite->filename.find_last_of('/')+1) << "    " << sprite->spriteWidth << "    " << sprite->spriteHeight << "    " << sprite->imageWidth 
		<< "    " << sprite->imageHeight << "    " << sprite->maxColumns << "    " << sprite->maxRows;
	return os;
}
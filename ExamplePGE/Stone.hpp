#ifndef STONE_INCLUDE
#define STONE_INCLUDE

#include "Entity.cpp"

class Stone : public Entity {

public:
	olc::vi2d pos;
	olc::vi2d size = { 1, 1 };
	olc::Pixel col;
	bool solid;
	bool moving;

	void Draw(olc::PixelGameEngine* pge);
	void Update(olc::PixelGameEngine* pge);
};

#endif //STONE_INCLUDE
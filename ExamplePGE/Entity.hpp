#include "olcPixelGameEngine.h"

class Entity {

public:
	olc::vi2d pos;
	olc::vi2d size = { 1, 1 };
	olc::Pixel col;
	bool solid;
	bool moving;

	Entity(int x, int y);
	~Entity();

	void Draw(olc::PixelGameEngine* pge);

	virtual void Update(olc::PixelGameEngine* pge);
};
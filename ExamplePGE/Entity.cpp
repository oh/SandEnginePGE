#include "olcPixelGameEngine.h"

class Entity {

public:
	olc::vi2d pos;
	olc::vi2d size;
	olc::Pixel col = olc::BLACK;
	bool solid = false;
	bool moving = false;

	Entity(int x, int y) {
		this->pos.x = x;
		this->pos.y = y;
	}

	~Entity() {
		delete this;
	}

	void Draw(olc::PixelGameEngine* pge) {
		pge->FillRect(pos, size, col);
	}

	virtual void Update(olc::PixelGameEngine* pge) {
		this->Draw(pge);
	}
};
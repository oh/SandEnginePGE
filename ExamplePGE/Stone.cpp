#include "Entity.cpp"

class Stone : public Entity {

public:
	olc::vi2d pos;
	olc::vi2d size = { 1, 1 };
	olc::Pixel col = olc::DARK_YELLOW;
	bool solid = true;
	bool moving;



	void Update(olc::PixelGameEngine* pge) {
		this->Draw(pge);
	}
};
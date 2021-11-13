#define OLC_PGE_APPLICATION
#include "glob.hpp"

class SandEngine : public olc::PixelGameEngine {
public:

	float fTargetFrameTime = 1.0f / 120.0f;
	float fAccumulatedTime = 0.0f;

	int selected = BACK;
	int* data = new int[G_SIZE * G_SIZE];
	int r = 3, b, mDelta, index = 0;
	olc::Pixel col;
	olc::Key k;

	enum Cells {
		BACK = 0,
		SAND = 1,
		STONE = 2,
		WATER = 4,
	};

	enum CellFlags {
		SOLID = 16,
		MOVING = 32,
	};

	int CellTypes[sizeof(Cells)] = {
		SAND + MOVING,
		STONE + SOLID,
		WATER + MOVING,
	};

	SandEngine() {
		sAppName = "Sand Engine";
	}

	bool OnUserCreate() override {
		for (int x = 0; x < G_SIZE; x++)
			for (int y = 0; y < G_SIZE; y++)
				data[(x * G_SIZE) + y] = BACK;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		selected = CellTypes[index];

		if (GetKey(olc::ESCAPE).bPressed) return false;
		if (GetKey(olc::TAB).bPressed) index = (++index % (sizeof(Cells) - 1));

		fAccumulatedTime += fElapsedTime;
		if (fAccumulatedTime >= fTargetFrameTime) {
			fAccumulatedTime -= fTargetFrameTime;
			fElapsedTime = fTargetFrameTime;
		} else return true;

		if (GetKey(olc::Q).bHeld) if (r < 20) r++;
		if (GetKey(olc::E).bHeld) if (r > 4) r--;

		Clear(olc::BLACK);
		
		for (int x = G_SIZE; x >= 0; x--) {
			for (int y = G_SIZE; y >= 0; y--) {
				if (x == 0 || y == 0 || x == G_SIZE - 1 || y == G_SIZE - 1) data[(x * G_SIZE) + y] = SOLID;

				if (data[(x * G_SIZE) + y] & SAND) {
					if (!(data[(x * G_SIZE) + (y + 1)] & SOLID)) { // Below
						data[(x * G_SIZE) + y] = BACK;
						data[(x * G_SIZE) + (y + 1)] = SAND + MOVING;
						continue;
					}

					// Sand
					if ((int)fElapsedTime % 2 == 0) {
						if (!(data[((x - 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down left
							data[(x * G_SIZE) + y] = BACK;
							data[((x - 1) * G_SIZE) + (y + 1)] = SAND + MOVING;
							continue;
						}
						if (!(data[((x + 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down right
							data[(x * G_SIZE) + y] = BACK;
							data[((x + 1) * G_SIZE) + (y + 1)] = SAND + MOVING;
							continue;
						}
					}

					if (!(data[((x + 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down right
						data[(x * G_SIZE) + y] = BACK;
						data[((x + 1) * G_SIZE) + (y + 1)] = SAND + MOVING;
						continue;
					}
					if (!(data[((x - 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down left
						data[(x * G_SIZE) + y] = BACK;
						data[((x - 1) * G_SIZE) + (y + 1)] = SAND + MOVING;
						continue;
					}

					data[(x * G_SIZE) + y] = SAND + SOLID;
				}

				// Water
				if (data[(x * G_SIZE) + y] & WATER) {
					int temp;

					if (!(data[(x * G_SIZE) + (y + 1)] & SOLID)) { // Below
						data[(x * G_SIZE) + y] = data[(x * G_SIZE) + (y + 1)];
						data[(x * G_SIZE) + (y + 1)] = WATER + MOVING;
						continue;
					}

					if ((int)fElapsedTime % 2 == 0) {
						if (!(data[((x - 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down left
							data[(x * G_SIZE) + y] = data[((x - 1) * G_SIZE) + (y + 1)];
							data[((x - 1) * G_SIZE) + (y + 1)] = WATER + MOVING;
							continue;
						}
						if (!(data[((x + 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down right
							data[(x * G_SIZE) + y] = data[((x + 1) * G_SIZE) + (y + 1)];
							data[((x + 1) * G_SIZE) + (y + 1)] = WATER + MOVING;
							continue;
						}
						if (!(data[((x - 1) * G_SIZE) + (y + 2)] & SOLID)) { // Down 2 left
							data[(x * G_SIZE) + y] = data[((x - 1) * G_SIZE) + (y + 1)];
							data[((x - 1) * G_SIZE) + (y + 2)] = WATER + MOVING;
							continue;
						}
						if (!(data[((x + 1) * G_SIZE) + (y + 2)] & SOLID)) { // Down 2 right
							data[(x * G_SIZE) + y] = data[((x + 1) * G_SIZE) + (y + 1)];
							data[((x + 1) * G_SIZE) + (y + 2)] = WATER + MOVING;
							continue;
						}
						if (!(data[((x - 1) * G_SIZE) + y] & SOLID) && !(data[((x - 1) * G_SIZE) + y] & WATER)) { // Left
							data[(x * G_SIZE) + y] = data[((x - 1) * G_SIZE) + y];
							data[((x - 1) * G_SIZE) + y] = WATER + MOVING;
							continue;
						}
					}

					if (!(data[((x - 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down left
						data[(x * G_SIZE) + y] = data[((x - 1) * G_SIZE) + (y + 1)];
						data[((x - 1) * G_SIZE) + (y + 1)] = WATER + MOVING;
						continue;
					}
					if (!(data[((x + 1) * G_SIZE) + (y + 1)] & SOLID)) { // Down right
						data[(x * G_SIZE) + y] = data[((x + 1) * G_SIZE) + (y + 1)];
						data[((x + 1) * G_SIZE) + (y + 1)] = WATER + MOVING;
						continue;
					}
					if (!(data[((x - 1) * G_SIZE) + (y + 2)] & SOLID)) { // Down 2 left
						data[(x * G_SIZE) + y] = data[((x - 1) * G_SIZE) + (y + 1)];
						data[((x - 1) * G_SIZE) + (y + 2)] = WATER + MOVING;
						continue;
					}
					if (!(data[((x + 1) * G_SIZE) + (y + 2)] & SOLID)) { // Down 2 right
						data[(x * G_SIZE) + y] = data[((x + 1) * G_SIZE) + (y + 1)];
						data[((x + 1) * G_SIZE) + (y + 2)] = WATER + MOVING;
						continue;
					}
					if (!(data[((x + 1) * G_SIZE) + y] & SOLID) && !(data[((x + 1) * G_SIZE) + y] & WATER)) { // Right
						data[(x * G_SIZE) + y] = data[((x + 1) * G_SIZE) + y];
						data[((x + 1) * G_SIZE) + y] = WATER + MOVING;
						continue;
					}

					data[(x * G_SIZE) + y] = WATER & SOLID;
				}
			}
		}


		for (int x = 0; x < G_SIZE; x++) {
			for (int y = 0; y < G_SIZE; y++) {
				if (data[(x * G_SIZE) + y] == SOLID)
					this->Draw(olc::vi2d(x, y), olc::GREY);
				if (data[(x * G_SIZE) + y] & SAND)
					this->Draw(olc::vi2d(x, y), olc::YELLOW);
				if (data[(x * G_SIZE) + y] & STONE)
					this->Draw(olc::vi2d(x, y), olc::DARK_GREY);
				if (data[(x * G_SIZE) + y] & WATER)
					this->Draw(olc::vi2d(x, y), olc::CYAN);
			}
		}


		if (GetMouse(0).bHeld) {
			olc::vi2d pos = GetMousePos();
			if (pos.x < 0 || pos.y < 0 || pos.x > G_SIZE || pos.y > G_SIZE) return true;

			this->FillCircle(GetMousePos(), r);

			for (int x = 0; x <= r; x++)
				for (int y = 0; y <= r; y++) {
					if ((x * x) + (y * y) <= (r * r)) {
						if (data[((pos.x + x) * G_SIZE) + (pos.y + y)] == BACK)
							data[((pos.x + x) * G_SIZE) + (pos.y + y)] = selected;
						if (data[((pos.x + x) * G_SIZE) + (pos.y - y)] == BACK)
							data[((pos.x + x) * G_SIZE) + (pos.y - y)] = selected;
						if (data[((pos.x + x) * G_SIZE) + (pos.y + y)] == BACK)
							data[((pos.x + x) * G_SIZE) + (pos.y + y)] = selected;
						if (data[((pos.x + x) * G_SIZE) + (pos.y - y)] == BACK)
							data[((pos.x + x) * G_SIZE) + (pos.y - y)] = selected;
						if (data[((pos.x - y) * G_SIZE) + (pos.y + x)] == BACK)
							data[((pos.x - y) * G_SIZE) + (pos.y + x)] = selected;
						if (data[((pos.x - y) * G_SIZE) + (pos.y - x)] == BACK)
							data[((pos.x - y) * G_SIZE) + (pos.y - x)] = selected;
						if (data[((pos.x - y) * G_SIZE) + (pos.y + x)] == BACK)
							data[((pos.x - y) * G_SIZE) + (pos.y + x)] = selected;
						if (data[((pos.x - y) * G_SIZE) + (pos.y - x)] == BACK)
							data[((pos.x - y) * G_SIZE) + (pos.y - x)] = selected;
					}
				}
		} else if (GetMouse(1).bHeld) {
			olc::vi2d pos = GetMousePos();
			if (pos.x < 0 || pos.y < 0 || pos.x > G_SIZE || pos.y > G_SIZE) return true;

			this->FillCircle(GetMousePos(), r);

			for (int x = 0; x <= r + 1; x++)
				for (int y = 0; y <= r + 1; y++) {
					if ((x * x) + (y * y) <= ((r + 1) * (r + 1))) {
						data[((pos.x + x) * G_SIZE) + (pos.y + y)] = BACK;
						data[((pos.x + x) * G_SIZE) + (pos.y - y)] = BACK;
						data[((pos.x + x) * G_SIZE) + (pos.y + y)] = BACK;
						data[((pos.x + x) * G_SIZE) + (pos.y - y)] = BACK;
						data[((pos.x - y) * G_SIZE) + (pos.y + x)] = BACK;
						data[((pos.x - y) * G_SIZE) + (pos.y - x)] = BACK;
						data[((pos.x - y) * G_SIZE) + (pos.y + x)] = BACK;
						data[((pos.x - y) * G_SIZE) + (pos.y - x)] = BACK;
					}
				}
		} else this->DrawCircle(GetMousePos(), r);

		/*char fps[5]; 
		_itoa_s(GetFPS(), fps, 10);*/

		//this->DrawString(olc::vi2d(10, 10), std::string("FPS: ").append(fps), olc::WHITE, 1);


		return true;
	}
};


int main() {
	SandEngine game;
	if (game.Construct(G_SIZE, G_SIZE, 4, 4))
		game.Start();

	return 0;
}

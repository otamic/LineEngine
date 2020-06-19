#include <engine.h>

class Game :public Engine {
	// declear member hear

	void Init() {
		// initialize members
	}

	void ProcessInput(float dt) {
		// optimal, can move all codes to Update
		// process any inputs hear
	}

	void Update(float dt) {
		// define the game logic hear
	}
};

DECLARE_MAIN(Game)
#include <WhizzEngine.h>

class Game : public WhizzEngine::Application {
public:
	Game()
	{

	}

	~Game()
	{

	}
};

WhizzEngine::Application* WhizzEngine::CreateApplication()
{
	return new Game();
}
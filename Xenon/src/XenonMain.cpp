#include "Engine/Core/GameEngine.h"
#include "Engine/Core/GameWorld.h"
#include "GameManager.h"

int main(int argc, char** argv) {
	Engine::GameEngine engine;

	engine.Initialize("EventOut Engine", 1280, 720);

	engine.GetWorld().CreateActor<GameManager>();
		
	engine.Run();
}
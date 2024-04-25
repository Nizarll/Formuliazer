// Formuliazer.cpp : définit le point d'entrée de l'application.
//

#include "Formuliazer.h"
#include "libs/Renderer.h"
#include "direct.h"


int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 400, "Formuliazer");
	SetTargetFPS(120);
	Renderer* renderer = new Renderer();
	std::shared_ptr<Object> _obj = std::static_pointer_cast<Object>(std::make_shared<ImageObj>(Vector2{ 500, 500 },
		Vector2{ 100, 100 },
		std::string{ "lepepe.png" }
	));
	std::static_pointer_cast<ImageObj>(_obj)->init();
	renderer->add_item(_obj);
	char cwd[1024];
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		for (std::shared_ptr<Object> _obj : renderer->get_items()) {
			_obj->render();
		}
		EndDrawing();
	}
	return 0;
}


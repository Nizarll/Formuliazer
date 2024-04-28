// Formuliazer.cpp : définit le point d'entrée de l'application.
//

#include "Formuliazer.h"

constexpr auto WIDTH = 800, HEIGHT = 400;

void setup()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 400, "Formuliazer");
	SetTargetFPS(120);
}

int main()
{
	setup();
	auto bg_img = new ImageObj(
		Vector2{ 100, 100 },
		Vector2{ 200, 200},
		std::string{ "grid.png" }
	);
	auto renderer = std::make_unique<Renderer>();
	{
		bg_img->init();
	}
	while (!WindowShouldClose()) {
		BeginDrawing();
		render_background(bg_img);
		for (auto& _o : renderer->get_items()) {
			_o->render();
		}
		static bool show_window = true;
		ImGui::Begin("My Window", &show_window);

		if (ImGui::Button("Save"))
		{
			std::cout << "Button Pressed"; //or your IDE equivalent output log
		}

		if (ImGui::Button("Cancel"))
		{
			std::cout << "Button Pressed"; //or your IDE equivalent output log
		}
		ImGui::End();
		EndDrawing();
	}
}

// Formuliazer.cpp : définit le point d'entrée de l'application.
//

#include "formualizer.h"
#include "raylib.h"

constexpr auto WIDTH = 800, HEIGHT = 400;
constexpr auto X_PADDING = 10, Y_PADDING = 40;

void setup()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 400, "Formuliazer");
	SetTargetFPS(120);
	rlImGuiSetup(true);
	setup_style();
}
static bool used = false;
int main()
{
	setup();
	auto bg_img = new ImageObj(   // new ImageObj{size, pos, texture_path)
		Vector2{ 450, 450 },
		Vector2{ 0, 0 },
		std::string{ "grid4.png" }
	);
	auto renderer = std::make_unique<Renderer>();
	{
		bg_img->init();
	}

	static bool show_window = true;
	static char buff[1024]{};
	while (!WindowShouldClose()) {
		BeginDrawing();
		render_background(bg_img);
		for (auto& _o : renderer->get_items()) {
			_o->render();
		}
		rlImGuiBegin();
		use_font(Fonts::CASCADIA_MONO_20);
		ImGui::SetNextWindowSize(ImVec2(GetScreenWidth() / 5 - X_PADDING, GetScreenHeight() - .03 * GetScreenHeight()), ImGuiCond_Always);
		ImGui::Begin("Formuliazer", &show_window, ImGuiWindowFlags_NoCollapse);
		if (ImGui::InputText("##Equation", buff, sizeof(buff))) {
			ImGui::Text("Equation put");
		}
		ImGui::End();
		ImGui::PopFont();
		rlImGuiEnd();
		EndDrawing();
	}
	ImGui::DestroyContext();
}

#include "../libs/renderer.h"

constexpr auto PATH_PREFIX = "C:\\Users\\Elite\\source\\repos\\Formuliazer\\Formuliazer\\resources\\";


static std::array<ImFont*, FONTS_LEN> loaded_fonts;

const std::vector<std::shared_ptr<Object>>& Renderer::get_items() const {
	return m_items;
}

Renderer::~Renderer() {
	for (auto& item : get_items()) {
		UnloadTexture(std::static_pointer_cast<ImageObj>(item)->get_texture());
	}
}

void Renderer::add_item(std::shared_ptr<Object> item) {
	m_items.push_back(item);
}

void Object::set_size(Vector2 size) {
	this->size = size;
}

void Object::set_position(Vector2 position) {
	this->position = position;
}

Vector2 Object::get_size() const {
	return this->size;
}

Vector2 Object::get_position() const {
	return this->position;
}

Object::Object(Vector2 size, Vector2 position) {
	this->position = position;
	this->size = size;
}

ImageObj::ImageObj(Vector2 size, Vector2 pos, const std::string& path) : Object(size, pos) {
	this->texture_path = path;
	this->texture = Texture2D{};
}

const std::string& ImageObj::get_texture_path() const {
	return this->texture_path;
}

const Texture2D& ImageObj::get_texture() const {
	return this->texture;
}

void ImageObj::init() {
	this->texture = LoadTexture((std::string{ PATH_PREFIX } + this->get_texture_path()).c_str());
	this->texture.width = this->get_size().x;
	this->texture.height = this->get_size().y;
}

void ImageObj::render() {
	DrawTexture(this->get_texture(),
		this->get_position().x,
		this->get_position().y,
		WHITE);
}

void render_background(ImageObj* background_image) {
	for (int i = 0; i < GetScreenWidth() / background_image->get_size().x + 1; i++) {
		for (int y = 0; y < GetScreenHeight() / background_image->get_size().y + 1; y++) {
			DrawTexture(background_image->get_texture(),
				i * background_image->get_size().x,
				y * background_image->get_size().y,
				WHITE);
		}
	}
}

void use_font(int font) {
	if (font >= FONTS_LEN) return;
	if (loaded_fonts[font] == nullptr) return;
	ImGui::PushFont(loaded_fonts[font]);
}

void setup_style() {

	ImGuiIO& io = ImGui::GetIO();
	ImFont* cascadia_font_20 = io.Fonts->AddFontFromFileTTF(
		(
			std::string{ PATH_PREFIX } + std::string{"fonts\\CascadiaCode.ttf"}
		).c_str()
		, 20.0f);
	ImFont* cascadia_font_14 = io.Fonts->AddFontFromFileTTF(
		(
			std::string{ PATH_PREFIX } + std::string{"fonts\\CascadiaCode.ttf"}
		).c_str()
		, 14.0f);
	ImFont* cascadia_mono_font_20 = io.Fonts->AddFontFromFileTTF(
		(
			std::string{ PATH_PREFIX } + std::string{"fonts\\CascadiaMono.ttf"}
		).c_str()
		, 20.0f);
	ImFont* cascadia_mono_font_14 = io.Fonts->AddFontFromFileTTF(
		(
			std::string{ PATH_PREFIX } + std::string{"fonts\\CascadiaMono.ttf"}
		).c_str()
		, 14.0f);

	assert(cascadia_font_20 != nullptr, "FONT COULD NOT LOAD !");
	assert(cascadia_font_14 != nullptr, " FONT COULD NOT LOAD !");
	assert(cascadia_mono_font_14 != nullptr, " FONT COULD NOT LOAD !");
	assert(cascadia_mono_font_20 != nullptr, "FONT COULD NOT LOAD !");

	loaded_fonts[Fonts::CASCADIA_COVE_20] = cascadia_mono_font_20;
	loaded_fonts[Fonts::CASCADIA_MONO_20] = cascadia_font_20;
	loaded_fonts[Fonts::CASCADIA_MONO_14] = cascadia_mono_font_14;
	loaded_fonts[Fonts::CASCADIA_COVE_14] = cascadia_font_14;
	
	io.Fonts->Build();
	rlImGuiReloadFonts();
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//	style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	//	style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	//	style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	//	style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	//	style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	//	style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	//style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

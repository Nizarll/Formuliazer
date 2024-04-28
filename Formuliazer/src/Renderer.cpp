#include "../libs/Renderer.h"
#include "iostream"

constexpr auto PATH_PREFIX = "C:\\Users\\Elite\\source\\repos\\Formuliazer\\Formuliazer\\resources\\";

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
	this->texture = LoadTexture((std::string{PATH_PREFIX} + this->get_texture_path()).c_str());
	this->texture.width = this->get_size().x;
	this->texture.height = this->get_size().y;
}

void ImageObj::render() {
	DrawTexture(this->get_texture(),
		this->get_position().x,
		this->get_position().y,
		WHITE);
}

void render_background(ImageObj *background_image) {
	for (int i = 0; i < GetMonitorWidth(0) / background_image->get_texture().width + 1; i++) {
		for (int y = 0; y < GetMonitorHeight(0) / background_image->get_texture().height + 1; y++) {
		DrawTexture(background_image->get_texture(),
			i * background_image->get_texture().width,
			y * background_image->get_texture().height,
			WHITE);
		}
	}
}

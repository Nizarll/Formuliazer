#include "../libs/Renderer.h"

#define PATH_PREFIX "C:\\Users\\Elite\\source\\repos\\Formuliazer\\Formuliazer\\resources\\"

const std::vector<std::shared_ptr<Object>>& Renderer::get_items() const {
	return m_items;
}

void Renderer::add_item(std::shared_ptr<Object> item) {
	m_items.push_back(item);
}

void Object::set_size(const Vector2& size) {
	this->size = size;
}

void Object::set_position(const Vector2& position) {
	this->position = position;
}

const Vector2& Object::get_size() const {
	return this->size;
}

const Vector2& Object::get_position() const {
	return this->position;
}

Object::Object(const Vector2& size, const Vector2& position) {
	this->position = position;
	this->size = size;
}

ImageObj::ImageObj(const Vector2& size, const Vector2& pos, const std::string& path) : Object(size, pos) {
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
}

void ImageObj::render() {
	DrawTexture(this->get_texture(),
		this->get_position().x,
		this->get_position().y,
		WHITE);
}

#undef PATH_PREFIX

#pragma once

#include "raylib.h"
#include <memory>
#include <string>
#include <vector>

class Object {
private:
	Vector2 position;
	Vector2 size;
public:
	virtual void render() = 0;
	Object(const Vector2& size, const Vector2& position);
	void set_size(const Vector2& size);
	void set_position(const Vector2& position);
	const Vector2& get_position() const;
	const Vector2& get_size() const;
};

class ImageObj : public Object {
private:
	std::string texture_path;
	Texture2D texture;
public:
	ImageObj(const Vector2& size,
		const Vector2& pos,
		const std::string& path);
	const std::string& get_texture_path() const;
	const Texture2D& get_texture() const;
	void init();
	void render();
};

class Renderer {
private:
	std::vector<std::shared_ptr<Object>> m_items;
public:
	void add_item(std::shared_ptr<Object> item);
	const std::vector<std::shared_ptr<Object>>& get_items() const;
};

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
	Object(Vector2 size, Vector2 position);
	virtual ~Object() = default;
	void set_size(Vector2 size);
	void set_position(Vector2 position);
	Vector2 get_position() const;
	Vector2 get_size() const;
};

class ImageObj : public Object {
private:
	std::string texture_path;
public:
	Texture2D texture;
	ImageObj(Vector2 size,
		 		Vector2 pos,
		 		const std::string& path);
	virtual ~ImageObj() = default;
	const std::string& get_texture_path() const;
	const Texture2D& get_texture() const;
	void init();
	void render();
};

class Renderer {
private:
	std::vector<std::shared_ptr<Object>> m_items;
public:
	~Renderer();
	void add_item(std::shared_ptr<Object> item);
	const std::vector<std::shared_ptr<Object>>& get_items() const;
};

void render_background(ImageObj* background_image);

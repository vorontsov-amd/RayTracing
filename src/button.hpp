#pragma once
#include "widget.hpp"
#include "color.hpp"
#include <SFML/Graphics.hpp>
#include <string>


class Button : public Widget
{
protected:
    sf::RectangleShape class_button;
    bool class_is_pressed = false;
public:
    Button(const Vector& position, unsigned width, unsigned height) :
        class_button{sf::Vector2f{width, height}} {
            class_button.setPosition(position);
        }

    virtual void draw(sf::RenderWindow& window) const override {
        window.draw(class_button);
    }

    virtual bool contains(unsigned x, unsigned y) const final override {
        return class_button.getGlobalBounds().contains(x, y);
    }

    virtual void pressButton(const sf::Vector2i& coord) override {
    } 

    void move(int dx, int dy) override {
        class_button.setPosition(class_button.getPosition().x + dx, class_button.getPosition().y + dy);
    }

    ~Button() = 0;
};

inline Button::~Button() {}


class TextureButton : public Button
{
private:
    sf::Texture class_texture;
public:
    TextureButton(const Vector& position, unsigned width, unsigned height, const std::string& path) :
        Button{position, width, height} {
            class_texture.loadFromFile(path);
            class_button.setTexture(&class_texture);
        }
};



class ColorButton : public Button
{
public:
    ColorButton(const Vector& position, unsigned width, unsigned height, const sf::Color& color) :
        Button{position, width, height} {
            class_button.setFillColor(color);
        }
};

using Panel = ColorButton;
#pragma once

class BaseScene;

class Scene : public BaseScene
{
private:
	sf::CircleShape shape;
	
public:
	Scene(int width, int height, std::string title)
		:BaseScene{ width, height, title }
	{
		shape.setRadius(100.0f);
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(halfWidth - 100.0f, halfHeight - 100.0f);
	}

	void updateScene(float elapsed) override
	{

	}

	void drawScene() override
	{
		window.draw(shape);
	}
};
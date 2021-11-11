#pragma once
#include <algorithm>

class BaseScene;

class Scene : public BaseScene
{
private:
	sf::VertexArray lines;
	RandomGenerator rnd;

public:
	Scene(int width, int height, std::string title)
		:BaseScene{ width, height, title }
	{
		//RandomGenerator rnd{ 1171 };		
		//doRandomLines();
		//rnd.resetNormal(0.25, 0.1);
	}
	
	void doRandomLines()
	{
		int numLines{ 512 };
		int numToGen{ 10000 };
			

		// generate a bunch of random numbers
		std::vector<int> rndNumbers(numLines, 0);
		for (int i = 0; i < numToGen; i++)
		{
			int x = (int)rnd.getNormal(0, numLines-1);
			//int x = rnd.getUniform(0, numLines);					

			x = std::clamp(x, 0, numLines);
			rndNumbers[x]++;
		}
		
		int max = -INFINITY;
		for (auto i : rndNumbers) if (i > max) max = i;
		max += 20; // for scaling away from top of window		

		// generate lines to represent random number distribution
		lines = sf::VertexArray{ sf::Lines, (size_t)numLines * 2 };
		int index = 0;
		for (size_t i = 0; i < numLines * 2; i += 2)
		{
			float x = (float)index * ((float)width / (float)numLines);
			float top = (float)height - (((float)rndNumbers[index] / (float)max) * (float)height);
			float bottom = (float)height;

			lines[i].position = sf::Vector2f{ x, top };
			lines[i + 1].position = sf::Vector2f{ x, bottom };
			lines[i].color = lines[i + 1].color = sf::Color(148, 91, 10);

			index++;
		}
	}
	
	void updateScene(float elapsed) override
	{
		doRandomLines();
	}

	void drawScene() override
	{
		window.draw(lines);
	}
};
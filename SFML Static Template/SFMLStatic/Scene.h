#pragma once

class BaseScene;

class Scene : public BaseScene
{
private:
	sf::CircleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	
public:
	Scene(int width, int height, std::string title)
		:BaseScene{ width, height, title }
	{
		shape.setRadius(100.0f);
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(halfWidth - 100.0f, halfHeight - 100.0f);

		if (texture.create(width, height)) {
			makeNoise();
		}
		else
		{
			std::cout << "ERROR: failed to create texture" << std::endl;
		}
	}

	void makeNoise()
	{
		auto simplex = FastNoise::New<FastNoise::Simplex>(FastSIMD::Level_AVX2);
		auto fractal = FastNoise::New<FastNoise::FractalFBm>(FastSIMD::Level_AVX2);

		fractal->SetSource(simplex);
		fractal->SetOctaveCount(5);
		
		std::vector<float> noise(width * height);

		fractal->GenUniformGrid2D(noise.data(), 0, 0, width, height, 0.02f, 1337);


		const size_t numPixels = width * height * 4;
		sf::Uint8* pixels = new sf::Uint8[numPixels];
		
		size_t index = 0;
		for (size_t x = 0; x < noise.size(); x++)
		{
			index = x * 4;
			int rgb = mapRange(noise.at(x), -1, 1, 0, 255);
			pixels[index] = rgb;
			pixels[index + 1] = rgb;
			pixels[index + 2] = rgb;
			pixels[index + 3] = 255;
		}

		texture.update(pixels);
		sprite.setTexture(texture);

		delete[] pixels;
	}

	int mapRange(float value, float minSource, float maxSource, float minTarget, float maxTarget)
	{
		//https://math.stackexchange.com/a/377174
		return ((value - minSource) * ((maxTarget - minTarget) / (maxSource - minSource))) + minTarget;
	}

	void updateScene(float elapsed) override
	{
		//makeNoise();
	}

	void drawScene() override
	{
		window.draw(sprite);
		window.draw(shape);
	}
};
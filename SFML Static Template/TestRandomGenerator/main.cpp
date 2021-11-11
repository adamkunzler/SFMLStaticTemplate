#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <FastNoise/FastNoise.h>

#include <SFML/Graphics.hpp>

#include "utils/Math.h"
#include "utils/RandomGenerator.h"
#include "BaseScene.h"
#include "Scene.h"

int main()
{    
    Scene scene{ 1024, 1024, "RandomGenerator Tests" };

    sf::Clock clock;
    while (scene.getWindow().isOpen())
    {
        sf::Event event;
        while (scene.getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                scene.getWindow().close();
        }

        sf::Time elapsed = clock.restart();

        scene.getWindow().clear();        
        scene.update(elapsed.asSeconds());
        scene.draw(elapsed.asSeconds());
        scene.getWindow().display();
    }

	return EXIT_SUCCESS;
}
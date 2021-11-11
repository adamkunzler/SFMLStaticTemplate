#include <iostream>
#include <vector>
#include <string>

#include <FastNoise/FastNoise.h>

#include <SFML/Graphics.hpp>

#include "BaseScene.h"
#include "Scene.h"

int main()
{    
    Scene scene{ 500, 500, "SFML Static" };

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
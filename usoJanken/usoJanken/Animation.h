#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
	public:
		Animation(sf::Texture* texture, sf::Vector2u imgCount, float switchTime);
	
		void Update(int row, float deltatime);

		sf::IntRect uvRect;
		sf::Vector2u imageCount;
		sf::Vector2u currentImage;

		float totalTime;
		float switchTime;
};


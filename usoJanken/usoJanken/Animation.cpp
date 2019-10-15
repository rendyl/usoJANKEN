#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imgCount, float switchTime)
{
	this->imageCount = imgCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(int row, float deltatime) 
{
	currentImage.y = row;
	totalTime += deltatime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) currentImage.x = 0;
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}
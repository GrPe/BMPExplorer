#include "BMPViewer.hpp"

void BMPViewer::BMPViewer::LoadBitMap(const char* rawData)
{
	if(!image.loadFromMemory(rawData, sizeof(rawData)))
		throw std::exception();
}

void BMPViewer::BMPViewer::ShowBitMap()
{
	//prepare window
	sf::RenderWindow window(sf::VideoMode(1024, 800), "BMP Viewer 1.0");
	window.setFramerateLimit(15);

	//prepare image to display
	sf::Texture imageToDisplay;
	sf::Sprite imageTD;
	imageTD.setTexture(imageToDisplay, true);
	imageToDisplay.loadFromImage(image);


	while (window.isOpen())
	{		
		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(imageTD);
		window.display();
	}
}

#include "BMPViewer.hpp"

void BMPViewer::BMPViewer::LoadBitMap(sf::Uint8* rawData, int sizeX, int sizeY)
{
	image.create(sizeX, sizeY, rawData);
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

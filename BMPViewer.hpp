#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

namespace BMPViewer
{
	class BMPViewer
	{
	private:
		sf::Image image;
	public:
		BMPViewer() = default;
		~BMPViewer() = default;
		BMPViewer(BMPViewer&) = default;
		BMPViewer(BMPViewer&&) = delete;

		void LoadBitMap(sf::Uint8* rawData, int sizeX, int sizeY);
		void ShowBitMap();
	};
}
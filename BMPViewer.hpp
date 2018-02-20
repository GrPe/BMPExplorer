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

		void LoadBitMap(const uint8_t* rawData, int sizeX, int sizeY);
		void ShowBitMap();
	};
}
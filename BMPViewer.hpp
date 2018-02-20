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

		void LoadBitMap(const char* rawData);
		void ShowBitMap();
	};
}
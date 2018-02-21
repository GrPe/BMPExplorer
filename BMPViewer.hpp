#pragma once

#include <SDL.h>

#include <exception>

namespace BMPViewer
{
	class BMPViewer
	{
	private:
		const int WINDOW_W{ 1200 };
		const int WINDOW_H{ 1000 };
	public:
		BMPViewer() = default;
		~BMPViewer() = default;
		BMPViewer(BMPViewer&) = default;
		BMPViewer(BMPViewer&&) = delete;

		void ShowBitMap(SDL_Surface* image);
	};
}
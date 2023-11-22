#include "epch.h"
#include "Renderer.h"

namespace Engine {
	SDL_Renderer* Renderer::m_RenderTarget;

	void Renderer::Init(SDL_Window* window)
	{	
		if (window != nullptr) {
			m_RenderTarget = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_RenderTarget == nullptr) {
				std::cout << "Error Creating render target (Render is null)" << std::endl;
			}
			else {

				std::cout << "Render target created!" << std::endl;
			}

		}
		else {
			std::cout << "Error Creating render target (Window is null)" << std::endl;

		}

	}

	SDL_Texture* Renderer::LoadTexture(std::string filePath)
	{
		SDL_Texture* texture = nullptr;
		SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
		if (surface == nullptr) {
			std::cout << "Error loading the image: " << filePath << std::endl;
		}
		else {
			SDL_SetSurfaceColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));
			if (m_RenderTarget != nullptr) {
				texture = SDL_CreateTextureFromSurface(m_RenderTarget, surface);
				if (texture == nullptr)
					std::cout << "Error creating texture from surface: " << filePath << std::endl;
			}
			else {
				std::cout << "Error creating texture from surface (render is null pointer): " << filePath << std::endl;

			}
		}

		SDL_DestroySurface(surface);
		return texture;
	}

	void Renderer::RenderTexture(Texture2D& texture) {
		SDL_RenderTexture(m_RenderTarget, texture, texture.t_ScreenRect, texture.t_ScreenPosition);
	}

}

#pragma once

namespace Engine 
{
	struct Texture2D;

	class Renderer
	{
	public:
		static void Init(SDL_Window* window);
		static SDL_Texture* LoadTexture(std::string filePath);
		static void RenderTexture(Texture2D& tex);

		static SDL_Renderer* GetRenderer() { return m_RenderTarget; }
	private:
		static SDL_Renderer* m_RenderTarget;

	};

	struct TextureData {

		TextureData() {}

		TextureData(float x, float y, float w, float h)
			: d_X(x), d_Y(y), d_W(w), d_H(h)
		{
		}

		SDL_FRect* FillRect(SDL_FRect& rect) {

			rect.x = this->d_X;
			rect.y = this->d_Y;
			rect.w = this->d_W;
			rect.h = this->d_H;

			return &rect;

		}

		float d_X;
		float d_Y;
		float d_W;
		float d_H;
	};

	struct Texture2D {

		Texture2D() {};

		Texture2D(const char* filepath, TextureData rect, TextureData posRect)
		{
			t_Texture = Renderer::LoadTexture(filepath);

			t_ScreenPosition = new SDL_FRect();
			t_ScreenRect = new SDL_FRect();

			t_ScreenRect->x = rect.d_X;
			t_ScreenRect->y = rect.d_Y;
			t_ScreenRect->w = rect.d_W;
			t_ScreenRect->h = rect.d_H;

			t_ScreenPosition->x = posRect.d_X;
			t_ScreenPosition->y = posRect.d_Y;
			t_ScreenPosition->w = posRect.d_W;
			t_ScreenPosition->h = posRect.d_H;
		}

		Texture2D(std::string filepath)
		{
			t_Texture = Renderer::LoadTexture(filepath);

			t_ScreenRect = 0;
			t_ScreenPosition = 0;
		}

		void LoadRects(TextureData* rect, TextureData* posRect) {
			t_ScreenRect->x = rect->d_X;
			t_ScreenRect->y = rect->d_Y;
			t_ScreenRect->w = rect->d_W;
			t_ScreenRect->h = rect->d_H;

			t_ScreenPosition->x = posRect->d_X;
			t_ScreenPosition->y = posRect->d_Y;
			t_ScreenPosition->w = posRect->d_W;
			t_ScreenPosition->h = posRect->d_H;
		}

		void LoadPositionRect(TextureData* posRect) {
			t_ScreenPosition->x = posRect->d_X;
			t_ScreenPosition->y = posRect->d_Y;
			t_ScreenPosition->w = posRect->d_W;
			t_ScreenPosition->h = posRect->d_H;
		}

		Texture2D(const Texture2D& other) = default;

		SDL_Texture* t_Texture;
		SDL_FRect* t_ScreenPosition;
		SDL_FRect* t_ScreenRect;
		int t_PixelSize;

		operator SDL_Texture* () const { return t_Texture; }
		operator const SDL_Texture* () const { return t_Texture; }
	};

}


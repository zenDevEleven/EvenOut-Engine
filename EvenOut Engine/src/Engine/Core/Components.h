#pragma once
#include "epch.h"
#include "Component.h"

#include "Engine/Core/Renderer.h"
#include "Engine/Core/PhysicsWorld.h"

using namespace std::chrono_literals;

namespace Engine {

	struct TransformComponent : public Component{
		glm::vec2 Position;

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec2& position)
			: Position(position)
		{
		}

		void Start() override
		{
			
		}

		void UpdateComponent(float deltaTime) override {

		}

		void DrawComponent() override
		{

		}

		void Translate(float x, float y) {
			Position.x = x;
			Position.y = y;
		}

		void AddPos(float x, float y) {
 			Position.x += x;
			Position.y += y;
		}


	};

	struct BoxCollider2DComponent : public Component
	{
		glm::vec2 Offset{ 0.0f,0.0f };
		glm::vec2 Size{ 0.5f,0.5f };

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		void* RuntimeFixture = nullptr;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent& other) = default;

		void Start() override
		{

		}

		void UpdateComponent(float deltaTime) override
		{
			
		}

		void DrawComponent() override
		{

		}
	};

	struct AnimatorComponent : public Component{

		struct Animation;
		struct AnimationFrame;

		AnimatorComponent() = default;
		AnimatorComponent(const AnimatorComponent& other) = default;

		AnimatorComponent(Texture2D& texture)
			: m_Texture(texture)
		{
		}

		void Start() override
		{
		}

		void UpdateComponent(float deltaTime) override
		{

		}

		void DrawComponent() override
		{
			
		}

		void SetStartFrame(AnimationFrame&& frame) {
			if (m_Texture.t_PixelSize == -1) {
				std::cout << "Specify a pixel size when creating a SpriteRenderer2D" << std::endl;
			}
			else {
				int frameX = frame.f_x * m_Texture.t_PixelSize;
				int frameY = frame.f_y * m_Texture.t_PixelSize;
				m_Texture.t_ScreenRect->x = frameX;
				m_Texture.t_ScreenRect->y = frameY;
			}
		}

		void CreateAnimation(Animation* animation) {
			m_Animations.emplace_back(animation);

		}

		void PlayAnimation(std::string animationName, float frameRate, float deltaTime, bool looping) {
			Animation a = FindAnimation(animationName);
			if (!a.a_Finished) {
				m_Time += deltaTime;
				if (m_Time >= frameRate) {
					int nextFrame = GetNextFrame(a, m_Texture.t_ScreenRect->x, m_Texture.t_ScreenRect->y);

					if (a.a_Frames.size() == nextFrame) {
						if (looping) {
							nextFrame = 0;
							a.a_Finished = false;
						}
						else {
							a.a_Finished = true;
						}
					}
					else {

						m_Time = 0;
						std::cout << nextFrame << std::endl;
						m_Texture.t_ScreenRect->x = a.a_Frames[nextFrame].f_x * m_Texture.t_PixelSize;
						m_Texture.t_ScreenRect->y = a.a_Frames[nextFrame].f_y * m_Texture.t_PixelSize;
					}
				}
			}
		}

	private:
		Animation& FindAnimation(std::string& name) {
			for (Animation* a : m_Animations)
			{
				if (a->a_Name == name) {
					return *a;
				}
			}

			//not found animation
		}

		int GetNextFrame(Animation a, int x, int y)
		{
			for (int i = 0; i < a.a_Frames.size(); ++i)
			{
				if ((a.a_Frames[i].f_x * m_Texture.t_PixelSize) == x && (a.a_Frames[i].f_y * m_Texture.t_PixelSize) == y) {
					if (i + 1 < a.a_Frames.size()) {
						return i + 1;
					}
					else {
						return a.a_Frames.size();
					}
				}
			}

			return 0;
		}

	public:
		Texture2D m_Texture;

		std::vector<Animation*> m_Animations = {};

		struct AnimationFrame {
			AnimationFrame(int x, int y)
			{
				f_x = x - 1;
				f_y = y - 1;
			}

			int f_x;
			int f_y;
		};

		struct Animation {
			Animation(std::string name, std::vector<AnimationFrame> frames)
				: a_Name(name), a_Frames(frames)
			{
			}

			std::string a_Name;
			std::vector<AnimationFrame> a_Frames;
			bool a_Finished = false;
		};

	private:
		float m_Time = 0;

	};

	struct SpriteRenderer2D : public Component{
		SpriteRenderer2D() {};
		SpriteRenderer2D(const char* filepath)
		{
			m_SpriteTexture = Texture2D(filepath);
			m_SpriteRect = TextureData(0.0f, 0.0f, 0.0f, 0.0f);
			m_SpritePos = TextureData(0.0f, 0.0f, 0.0f, 0.0f);
			m_SpriteTexture.t_PixelSize = -1;
		}

		~SpriteRenderer2D() {
			std::cout << "destroyed sprite" << std::endl;

		}
		SpriteRenderer2D(const char* filepath, int SpritePixelSize)
		{
			m_SpriteRect = TextureData(0.0f, 0.0f, SpritePixelSize, SpritePixelSize);
			m_SpritePos = TextureData(0.0f, 0.0f, SpritePixelSize, SpritePixelSize);
			m_SpriteTexture = Texture2D(filepath, m_SpriteRect, m_SpritePos);
			m_SpriteTexture.t_PixelSize = SpritePixelSize;
		}
		SpriteRenderer2D(const char* filepath, int SpritePixelSize, int scale)
		{
			m_SpriteRect = TextureData(0.0f, 0.0f, SpritePixelSize, SpritePixelSize);
			m_SpritePos = TextureData(0.0f, 0.0f, SpritePixelSize * scale, SpritePixelSize * scale);
			m_SpriteTexture = Texture2D(filepath, m_SpriteRect, m_SpritePos);
			m_SpriteTexture.t_PixelSize = SpritePixelSize;
		}
		SpriteRenderer2D(const char* filepath, glm::vec2 size)
		{
			m_SpriteRect = TextureData(0.0f, 0.0f, size.x, size.y);
			m_SpritePos = TextureData(0.0f, 0.0f, size.x, size.y);
			m_SpriteTexture = Texture2D(filepath, m_SpriteRect, m_SpritePos);
			m_SpriteTexture.t_Size = size;
		}

		void Start()
		{
			m_Transform = &m_Actor->GetComponent<TransformComponent>();
		}

		void UpdateComponent(float deltaTime)  
		{
			m_SpritePos.d_X = m_Transform->Position.x;
			m_SpritePos.d_Y = m_Transform->Position.y;
			m_SpriteTexture.LoadPositionRect(&m_SpritePos);
		}

		void DrawComponent()
		{
			Renderer::RenderTexture(m_SpriteTexture);
		}

		Texture2D m_SpriteTexture;
		TextureData m_SpriteRect;
		TextureData m_SpritePos;
		TransformComponent* m_Transform;

	};

	struct Rigidbody2D : public Component{
		enum class BodyType { Static = 0, Dynamic, Kinematic };

		BodyType Type = BodyType::Dynamic;
		bool FixedRotation = false;

		b2BodyDef m_bodyDef;
		b2Body* m_Body;

		void* RuntimeBody = nullptr;

		Rigidbody2D() {}

		Rigidbody2D(BodyType type) : Type(type){}
		Rigidbody2D(const Rigidbody2D& other) = default;

		void Start() override 
		{
			auto& transform = m_Actor->GetComponent<TransformComponent>();
			auto& rigidBody = m_Actor->GetComponent<Rigidbody2D>();

			switch (rigidBody.Type) {
			case BodyType::Dynamic:
				m_bodyDef.type = b2_dynamicBody;
				break;
			case BodyType::Static:
				m_bodyDef.type = b2_staticBody;
				break;
			case BodyType::Kinematic:
				m_bodyDef.type = b2_kinematicBody;
				break;

			}

			m_bodyDef.position.Set(transform.Position.x / 100, transform.Position.y / 100);

			m_Body = PhysicsWorld::GetPhysicsWorld().CreateBody(m_bodyDef);
			RuntimeBody = m_Body;
		}

		void UpdateComponent(float deltaTime) override
		{
			
		}


		void DrawComponent() override
		{
			
		}

	};
}


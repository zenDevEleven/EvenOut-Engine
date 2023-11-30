#pragma once
#include "epch.h"
#include "Component.h"

#include "Engine/Core/Renderer.h"
#include "Engine/Core/PhysicsWorld.h"
#include "GameEngine.h"

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

		~TransformComponent() {
			std::cout << "Destroyed Transform" << std::endl;
		}

		void Start() override
		{
			
		}

		void UpdateComponent(float deltaTime) override {

		}

		void DrawComponent() override
		{

		}

		void SetPosition(float x, float y) {
			Position.x = x;
			Position.y = y;
		}

		void AddPos(float x, float y) {
 			Position.x += x;
			Position.y += y;
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

		~AnimatorComponent() {
			std::cout << "Destroyed Animator" <<  std::endl;
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
		
		void PlayAnimationContiniousToFrame(std::string animationName, float frameRate, float deltaTime, bool looping)
		{
			Animation* a = FindAnimation(animationName);

			m_Time += deltaTime;

			if (!a->a_Finished) {
				if (m_Time >= frameRate)
				{
					m_Time = 0;

					if (a->a_CurrentFrame.f_x * m_Texture.t_PixelSize >= m_Texture.t_TextWidth) {
						a->a_CurrentFrame.f_x = 0;
						a->a_CurrentFrame.f_y += 1;
						if (a->a_CurrentFrame.f_y * m_Texture.t_PixelSize >= m_Texture.t_TextHeight) {
							if (looping) {
								a->a_CurrentFrame = a->a_Frames[0];
							}
							else {
								a->a_Finished = true;
							}
						}
					}

					m_Texture.t_ScreenRect->x = a->a_CurrentFrame.f_x * m_Texture.t_PixelSize;
					m_Texture.t_ScreenRect->y = a->a_CurrentFrame.f_y * m_Texture.t_PixelSize;
					a->a_CurrentFrame.f_x += 1;
				}
			}

		}

		void PlayAnimation(std::string animationName, float frameRate, float deltaTime, bool looping) {
			Animation* a = FindAnimation(animationName);
			if (!a->a_Finished) {
				m_Time += deltaTime;
				if (m_Time >= frameRate) {
					int nextFrame = GetNextFrame(*a, m_Texture.t_ScreenRect->x, m_Texture.t_ScreenRect->y);

					if (a->a_Frames.size() == nextFrame) {
						if (looping) {
							nextFrame = 0;
							a->a_Finished = false;
						}
						else {
							a->a_Finished = true;
						}
					}
					else {

						m_Time = 0;
						m_Texture.t_ScreenRect->x = a->a_Frames[nextFrame].f_x * m_Texture.t_PixelSize;
						m_Texture.t_ScreenRect->y = a->a_Frames[nextFrame].f_y * m_Texture.t_PixelSize;
					}
				}
			}
		}

		bool IsPlayingAnimation(std::string animationName) {
			Animation* a = FindAnimation(animationName);
			return !a->a_Finished;
		}

	private:
		Animation* FindAnimation(std::string& name) {
			for (Animation* a : m_Animations)
			{
				if (a->a_Name == name) {
					return a;
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
			AnimationFrame() {}
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
				a_CurrentFrame = frames[0];
			}

			std::string a_Name;
			std::vector<AnimationFrame> a_Frames;
			AnimationFrame a_CurrentFrame;
			bool a_Finished = false;
		};

	private:
		float m_Time = 0;

	};

	struct SpriteRenderer2D : public Component{
		SpriteRenderer2D() {};
		SpriteRenderer2D(const char* filepath, int sortingLayer)
		{
			m_SpriteRect = TextureData(0.0f, 0.0f, 0.0f, 0.0f);
			m_SpritePos = TextureData(0.0f, 0.0f, 0.0f, 0.0f);
			m_SpriteTexture = Texture2D(filepath);
			m_SpriteTexture.t_PixelSize = -1;
			m_SortingLayer = sortingLayer;
		}

		~SpriteRenderer2D() {
			std::cout << "Destroyed SpriteRenderer" << std::endl;
		}

		SpriteRenderer2D(const char* filepath, int SpritePixelSize, int sortingLayer)
		{
			m_SpriteRect = TextureData(0.0f, 0.0f, SpritePixelSize, SpritePixelSize);
			m_SpritePos = TextureData(0.0f, 0.0f, SpritePixelSize, SpritePixelSize);
			m_SpriteTexture = Texture2D(filepath, m_SpriteRect, m_SpritePos);

			m_SpriteTexture.t_PixelSize = SpritePixelSize;
			m_SortingLayer = sortingLayer;
		}

		SpriteRenderer2D(const char* filepath, int SpritePixelSize, int scale, int sortingLayer)
		{
			m_SpriteRect = TextureData(0.0f, 0.0f, SpritePixelSize, SpritePixelSize);
			m_SpritePos = TextureData(0.0f, 0.0f, SpritePixelSize * scale, SpritePixelSize * scale);
			m_SpriteTexture = Texture2D(filepath, m_SpriteRect, m_SpritePos);

			m_SpriteTexture.t_PixelSize = SpritePixelSize * scale;
			m_SortingLayer = sortingLayer;
		}

		SpriteRenderer2D(const char* filepath, glm::vec2 size, int sortingLayer)
		{
			m_SpriteRect = TextureData(0.0f, 0.0f, size.x, size.y);
			m_SpritePos = TextureData(0.0f, 0.0f, size.x, size.y);

			m_SpriteTexture = Texture2D(filepath, m_SpriteRect, m_SpritePos);
			m_SpriteTexture.t_Size = size;
			m_SortingLayer = sortingLayer;
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

		int m_SortingLayer;

	};

	struct Rigidbody2D : public Component{

		Rigidbody2D() {}

		~Rigidbody2D()
		{
			std::cout << "Destroyed rigidBOyd" << std::endl;
			PhysicsWorld::GetPhysicsWorld().DestroyBody(m_Body);
			m_Body = nullptr;
		}

		enum class BodyType { Static = 0, Dynamic, Kinematic };
		Rigidbody2D(BodyType type) : Type(type) {}
		Rigidbody2D(const Rigidbody2D& other) = default;

		BodyType Type = BodyType::Dynamic;
		bool FixedRotation = false;

		b2BodyDef m_bodyDef;
		b2Body* m_Body = nullptr;


		void Start() 
		{
			auto& transform = m_Actor->GetComponent<TransformComponent>();

			switch (Type) {
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

			m_bodyDef.position.Set(transform.Position.x, transform.Position.y);

			m_bodyDef.fixedRotation = true;
			m_bodyDef.gravityScale = 0.0f;
			m_bodyDef.bullet = true;

			LOG_CORE("Physics Body" + m_Actor->GetTag(), LOG_WARNING)

			if(!GameEngine::GetEngine()->IsRunning())
				m_Body = PhysicsWorld::GetPhysicsWorld().CreateBody(m_bodyDef);
			else
				PhysicsWorld::GetPhysicsWorld().QueueCreateBody(m_Body, m_bodyDef);
		}

		void UpdateComponent(float deltaTime)
		{
			auto& transform = m_Actor->GetComponent<TransformComponent>();

			if (m_Body != nullptr)
				m_Body->SetTransform(b2Vec2(transform.Position.x, transform.Position.y), 0.0f);
		}


		void DrawComponent()
		{
			
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


		Rigidbody2D* m_Rb;

		void* RuntimeFixture = nullptr;

		b2FixtureDef fixtureDef;

		BoxCollider2DComponent(glm::vec2 size, Rigidbody2D* rb) : Size(size), m_Rb(rb) {
		}
		BoxCollider2DComponent(const BoxCollider2DComponent& other) = default;
		
		~BoxCollider2DComponent() {
			std::cout << "Destroyed Collider" << std::endl;
		}

		void Start() override
		{
			b2PolygonShape shape;
			shape.SetAsBox(Size.x / 2, Size.y / 2);

			fixtureDef.shape = &shape;
			fixtureDef.density = Density;
			fixtureDef.friction = Friction;
			fixtureDef.restitution = Restitution;
			fixtureDef.restitutionThreshold = RestitutionThreshold;

			fixtureDef.userData.pointer = (uintptr_t)m_Actor;
			fixtureDef.isSensor = true;


			if (!GameEngine::GetEngine()->IsRunning()) 
				m_Rb->m_Body->CreateFixture(&fixtureDef);
			else 
				PhysicsWorld::GetPhysicsWorld().QueueFixtureCreation(m_Rb->m_Body, fixtureDef, shape);
			

		}

		void UpdateComponent(float deltaTime) override
		{
			
		}

		void DrawComponent() override
		{

		}
	};

	struct HealthComponent : public Component {

	public:
		using CallbackFunction = std::function<void()>;

		HealthComponent(int MaxhealthSegments) 
			: m_MaxHealthSegments(MaxhealthSegments) {}

		HealthComponent(float MaxHealth)
			: m_MaxHealth(MaxHealth) {}

		template <typename T>
		void setOnDieCallback(T* instance, void (T::* memberFunction)()) {
			m_OnDieCallback = std::bind(memberFunction, instance);
		}

		void Start() override
		{
			m_HealthSegment = m_MaxHealthSegments;
			m_Health = m_MaxHealth;
		}

		void AddHealthSegment(int segmetsToAdd) 
		{
			m_HealthSegment += segmetsToAdd;
			if (m_HealthSegment > m_MaxHealthSegments)
				m_HealthSegment = m_MaxHealthSegments;
		}

		void AddHealth(float healthToAdd)
		{
			m_Health += healthToAdd;
			if (m_Health > m_MaxHealth)
				m_Health = m_MaxHealth;
		}

		void TakeDamageSegment(int segmentsToTakeDmg) {
			m_HealthSegment -= segmentsToTakeDmg;
			if (m_HealthSegment <= 0) {
				m_HealthSegment = 0;
				m_OnDieCallback();
			}
		}

		void TakeDamage(float healthToTakeDmg) {
			m_Health -= healthToTakeDmg;
			if (m_Health <= 0) {
				m_Health = 0;
				std::cout << "TAKE DAMAGE MY LIFE NOW: " << m_Health << std::endl;
				m_OnDieCallback();
			}
		}


		void UpdateComponent(float deltaTime) override
		{
			
		}
		void DrawComponent() override
		{
			
		}

	private:
		int m_MaxHealthSegments = 0;
		int m_HealthSegment = 0;

		CallbackFunction m_OnDieCallback;


		float m_Health = 0;
		float m_MaxHealth = 0;

	};
}


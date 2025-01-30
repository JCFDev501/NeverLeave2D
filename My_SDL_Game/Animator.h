#pragma once

#include <map>
#include <string>

#include <SDL.h>
class Animator
{
	struct AnimationSequence
	{
		std::string m_name;
		int m_firstFrame = 0;
		int m_lastFrame = 0;

	};

	const double m_kFrameRate; // How fast the animation will go

	int m_numSpriteSheetColumns; // How many frames in a single row

	SDL_Texture* m_pSpriteSheet; // The actually sprite sheet

	SDL_Rect m_Transform;  //  objects location on screen

	SDL_Rect m_SrcTransform; // Area of the sprite sheet to render

	std::map<std::string, AnimationSequence> m_allAnimations;

	std::string m_currentSequenceName;

	int m_currentFrame;

	std::string m_AnimationState;


	double m_FrameTime;
public:
	Animator(const char* pSpriteSheetPath,
		double frameRate,
		int frameWidth,
		int frameHeight,
		int frameCount,
		SDL_Renderer* pRenderer);
	~Animator();

	void AddAnimation(std::string name, int firstFrame, int lastFrame);
	void PlayAnimation(std::string sequenceName);
	void ResetFrameTime();
	void UpdateScrTransform();

	void Update(double deltaTime);

	void Render(SDL_Renderer* pRenderer) const;

	SDL_Rect GetTransform() const { return m_Transform; }
	void SetTransform(SDL_Rect transform) { m_Transform = transform; }

	std::string GetAnimationState() { return m_AnimationState; }
	void SetAnimationState(const std::string& animation) { m_AnimationState = animation; }

	

	
};


#include "Animator.h"

#include <iostream>
#include "SDL_image.h"

Animator::Animator(const char* pSpriteSheetPath, double frameRate, int frameWidth, int frameHeight,
                                       int frameCount, SDL_Renderer* pRenderer)
	:m_kFrameRate(frameRate)
	,m_numSpriteSheetColumns(0)
	,m_pSpriteSheet(nullptr)
	,m_Transform(SDL_Rect{0,0,0,0})
	,m_SrcTransform(SDL_Rect{ 0,0,0,0 })
	,m_currentFrame(-1)
	,m_FrameTime(0)
	
{
	// Attempt to load image to a surface.
	SDL_Surface* pSpriteSheetSurface = IMG_Load(pSpriteSheetPath);
	if (pSpriteSheetSurface == nullptr)
	{
		std::cout << "image loading failed. Error: " << SDL_GetError() << std::endl;
		return;
	}
	// Calculate the number of columns.
	m_numSpriteSheetColumns = pSpriteSheetSurface->w / frameWidth;

	// Initialize the transform.
	m_Transform.x = 0;
	m_Transform.y = 0;
	m_Transform.w = frameWidth;
	m_Transform.h = frameHeight;

	// Initialize the Src transform.
	m_SrcTransform = m_Transform;

	// Create the texture.
	m_pSpriteSheet = SDL_CreateTextureFromSurface(pRenderer, pSpriteSheetSurface);
	if (m_pSpriteSheet == nullptr)
	{
		std::cout << "Texture loading failed. Error: " << SDL_GetError() << std::endl;
		return;
	}

	// Free the surface.
	SDL_FreeSurface(pSpriteSheetSurface);

	ResetFrameTime();
}

Animator::~Animator()
{
	// Destroy the texture
	SDL_DestroyTexture(m_pSpriteSheet);
}

void Animator::AddAnimation(std::string name, int firstFrame, int lastFrame)
{
	// Create animation sequence.
	m_allAnimations[name] = AnimationSequence{ name, firstFrame, lastFrame };
}

void Animator::PlayAnimation(std::string sequenceName)
{
	// if  the particular sequence is already playing or dose not exist do nothing
	// if already playing or has not been added
	if(sequenceName == m_currentSequenceName || m_allAnimations.find(sequenceName) == m_allAnimations.end())
	{
		return;
	}

	// Access the sequence with this name and set its first frame.
	AnimationSequence& newSequence = m_allAnimations[sequenceName];
	m_currentFrame = newSequence.m_firstFrame;
	m_currentSequenceName = sequenceName;

	// Update current sequence name, frame time, and source transform.
	ResetFrameTime();
	UpdateScrTransform();
}

void Animator::ResetFrameTime()
{
	// How many seconds on the current frame rate
	m_FrameTime = 1 / m_kFrameRate;
}

void Animator::UpdateScrTransform()
{
	const int frameX = m_currentFrame % m_numSpriteSheetColumns;
	const int frameY = m_currentFrame / m_numSpriteSheetColumns;

	m_SrcTransform.x = frameX * m_SrcTransform.w;
	m_SrcTransform.y = frameY * m_SrcTransform.h;
}

void Animator::Update(double deltaTime)
{
	// See if a animation is playing.
	if(m_currentFrame == -1)
	{
		return;
	}

	// Access the current animation sequence.
	const AnimationSequence& currentSequence = m_allAnimations[m_currentSequenceName];

	// Allocate a dirty flag to see if the number changers.
	bool frameIsDirty = false;

	// As long as deltaTime is large, update the frame.
	while (deltaTime > m_FrameTime)
	{
		frameIsDirty = true;  // Time to change to next frame

		deltaTime -= m_FrameTime;
		ResetFrameTime();

		// check for looping
		if(m_currentFrame == currentSequence.m_lastFrame) // if on the last frame
		{
			m_currentFrame = currentSequence.m_firstFrame;      // loop back to first frame
		}
		else
		{
			++m_currentFrame;
		}
	}

	// After the frame has been updated, subtract deltaTime
	m_FrameTime -= deltaTime;

	// If the frame is dirty, update srcTransform
	if(frameIsDirty)
	{
		UpdateScrTransform();
	}
}

void Animator::Render(SDL_Renderer* pRenderer) const
{
	SDL_RenderCopy(pRenderer, m_pSpriteSheet, &m_SrcTransform, &m_Transform);
}

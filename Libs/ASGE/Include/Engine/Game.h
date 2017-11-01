#pragma once
#include <memory>

#include "Gametime.h"
#include "Input.h"
#include "Renderer.h"

namespace ASGE {

	/**
	*  The core of the engine.
	*  A skeleton structure and interface for running an instance
	*  of a Game. It stores access to the renderer and the input
	*  system. Input is often intrinsically linked to the render
	*  subsystem. To help speed up development, a typical update
	*  and render function is provided, along with GameTime. The
	*  initilisation code is not created by the Game, but by its
	*  dervied classes as the setup of the renderer is platform
	*  specific. 
	*  @see GameTime
	*/
	class Game
	{

	public:

		/**
		* Default constructor.
		*/
		Game() = default;
		
		/**
		* Default destructor.
		*/
		~Game() = default;

		/**
		* Pure virtual function for setup and intialisation
		* of the game. Every game must provide this. It is a
		* good idea to perform checks to make sure everything
		* is initialised correctly and return false if it hasn't.
		* This will cause the game to gracefully exit. 
		* @return The result of the initialisation operation.
		*/
		virtual bool init() = 0;

		/**
		* Pure virtual function used to update the game.
		* The update pattern is common usage within engines
		* and will be automatically called every frame. Here
		* all game objects that need simulation should be 
		* updated, ready to be rendered shortly thereafter. 
		* @param GameTime Game and Frame deltas.
		* @see GameTime
		*/
		virtual void update(const GameTime&) = 0;
		
		/**
		* Pure virtual function that sets up the renderer
		  before rendering a frame.
		* Can include flushing of buffers, clearing screens etc.
		* **This is handled inside the platform's specific
		  implementation.**
		*/
		virtual void beginFrame() = 0;
		
		/**
		* Pure virtual function used to render the game world.
		* The render pattern is common usage within engines
		* and will be automatically called every frame. All 
		* game objects to be visualised need to be drawn at this
		* stage using the Game's renderer. 
		*/
		virtual void render(const GameTime&) = 0;
		
		/**
		* Pure virtual function that completes the render frame.
		* Typically, flushes the render queue, instructs any 
		* batched calls to complete and swaps the video buffers.
		* **This is handled inside the platform's specific
		  implementation.**
		*/
		virtual void endFrame() = 0;

		/**
		* Pure virtual function for setup and intialisation of API.
		* **This is handled inside the platform's specific
		  implementation.**
		* @return The result of the initialisation operation.
		*/
		virtual bool initAPI() = 0;
		
		/**
		* Pure virtual function for terminating the API.
		* **This is handled inside the platform's specific
		  implementation.**
		* @return The result of the initialisation operation.
		*/
		virtual bool exitAPI() = 0;
		
		/**
		* The main game loop. 
		* Will keep looping unti a request to exit is received
		* either from the renderer or via the signal exit
		* function. 
		* @see signalExit
		* @return The exit code for the game.
		*/
		int run();

		/**
		* Signals the game should exit.
		*/
		void signalExit();

	protected:
		/**
		* Toggles the FPS on-screen.
		*/
		void toggleFPS();
		
		/**
		* Updates the FPS counter.
		*/
		void updateFPS();

		std::unique_ptr<Renderer> renderer; /**< Renderer Pointer. A smart pointer managing the renderer. */
		std::unique_ptr<Input>    inputs;   /**< Input Pointer. A smart pointer managing the input handler. */

		int  game_width  = 640;   /**< Game design resolution. The intended width of the game in pixels. */
		int  game_height = 480;   /**< Game design resolution. The intended height of the game in pixels. */
		bool show_fps    = false; /**< FPS counter. Shows the FPS on screen if set to true. */	
		bool exit		 = false; /**< Exit boolean. If true the game loop will exit. */

	private:
		static std::chrono::milliseconds getGameTime();
		GameTime us; /**< Delta. The frame deltas and total running time. */
	};
}
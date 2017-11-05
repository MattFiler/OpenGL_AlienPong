#pragma once
#include "NonCopyable.h"
namespace ASGE
{
	/**
	* SpriteSortMode.
	* Used to control the sprite batching techniques
	* that renderers may support. 
	*/
	enum class SpriteSortMode
	{
		IMMEDIATE,     /**< Renders the sprite immediately.*/
		DEFERRED,      /**< Defers (batches) the rendering to end of the render cycle. */
		TEXTURE,       /**< Batches and sorts by texture ID. */
		BACK_TO_FRONT, /**< Batches and reverses the order using z-ordering. */
		FRONT_TO_BACK  /**< Batches and sorts the order using z-ordering. */
	};

	/**
	* A simple 2D non-renderable texture.
	* A texture is used to load images into the GPU.
	* They retain a handle or link to it and the 
	* renderers are free to implement any caching systems
	* they see fit. 
	*/
	class Texture2D
	{
	public:

		/**
		* Default constructor.
		* @param width The width of the texture.
		* @param height the height of the texture. 
		*/
		Texture2D(int width, int height)
		{
			dims[0] = width;
			dims[1] = height;
		}
			
		/**
		* Default destructor.
		* The destructor does not free the memory used on the GPU.
		* **This is handled inside the platform's specific implementation.**
		*/
		virtual ~Texture2D() = default;

		/**
		* The format of the texture
		*/
		enum Format
		{
			MONOCHROME = 1, /**< The texture is monochromatic.*/
			MONOCHROME_ALPHA = 2, /**< The texture is monochromatic and has an alpha channel.*/
			RGB = 3, /**< There are Red, Green & Blue channels present.*/
			RGBA = 4 /**< There are RGB plus alpha chanels present .*/
		};

		/**
		* Sets the format of the texture. 
		* @param f The format of the stored texture.
		* @see Format
		*/
		void setFormat(Format f) {	format = f; }

		/**
		* Retrieves the format of the stored texture. 
		* @return The format of the texture. 
		* @see Format
		*/
		Format getFormat() const { return format;}

		/**
		* Loads the texture into GPU memory.
		* @param data The binary file loaded in memory.
		*/
		virtual void  setData(void* data) = 0;

		/**
		* Retrieves the texture from GPU memory.
		* Retrieving memory from the GPU like this is a 
		* slow process. It is best to do this infrequently.
		* @return The binary file loaded in memory.
		*/
		virtual void* getData() = 0;

		/**
		* Retrieves the width of the loaded texture.
		* @return The width of the texture.
		*/
		unsigned int getWidth()  const { return dims[0]; }
		
		/**
		* Retrieves the width of the loaded texture.
		* @return The height of the texture.
		*/
		unsigned int getHeight() const { return dims[1]; }

	protected:
		Format format = RGB;			/**< Texture2D Format. The pixel format used when loading the texture file. */
		unsigned int dims[2]{ 0,0 };	/**< Texture2D Dimensions. The dimensions of the loaded texture file. */
	};
}
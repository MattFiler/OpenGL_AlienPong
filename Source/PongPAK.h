#pragma once
#include <iostream>
#include <string>
#include <fstream>

class PongPAK {
public:
	std::string file_contents;

	PongPAK();
	void PongPAK::FetchFile(std::string requested_file);

	/*
	
	Due to engine limitations, PongPAK has been disabled.
	For future reference, the class would be used as...

		PongFileHandler.FetchFile("whitepixel.jpg");
		paddle1->loadTexture(PongFileHandler.file_contents.c_str());

	...rather than...

		paddle1->loadTexture(".\\Resources\\Textures\\whitepixel.jpg");

	...to obscure files in a "PongPAK" archive format.

	ASGE doesn't support passing of binary contents through loadTexture
	however, which is why this has been disabled for now.

	If re-enabled, the PongPAK program (separate project in this solution)
	must be run to regenerate "resources.pongpak" and "resources.pongmfst".
	Make sure to copy all resources into "Source Assets" first.
	
	*/
};
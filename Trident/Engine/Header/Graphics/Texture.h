#pragma once
class Texture
{
public:
	Texture();
	~Texture();

	int width, height, nrChannels;
	unsigned char* image;
};


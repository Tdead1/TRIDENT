#include <Graphics/Resource.h>
#define STB_IMAGE_IMPLEMENTATION
#include <Engine/stb_image.h>
Resource::Resource(){}
Resource::~Resource(){}

vector<float> Resource::LoadObject(string fileName)
{
	// It gets read from the main.cpp file.
	vector<GLfloat> vertexCoords;
	vector<GLfloat> textureCoords;
	vector<GLfloat> normalCoords;
	vector<GLuint> facesList;
	vector<GLfloat> finalData;

	string filePath = "Resources\\Objects\\" + fileName;
	string objectType = filePath.substr(filePath.length() - 4, filePath.length());

	if (filePath.substr(filePath.length() - 4, filePath.length()) == ".obj")
	{
		cout << "Type is .obj file." << endl;

		ifstream in(filePath);
		string line;

		bool storeNextNumber = false;

		string numberToStoreString;
		float numberToStoreFloat;
		int numberToStoreInt;
		while (getline(in, line))
		{
			// Ignoring the comments
			if (line.substr(0, 1) == "#")
			{
			}
			// Storing the vertices
			else if (line.substr(0, 2) == "v ")
			{
				for (int i = 0; i < (int)line.length() + 1; i++)
				{
					if (storeNextNumber && i < (int)line.length())
					{
						// storeNextNumber = true && i < line.length && (line.at(i) == ' ' || line.at(i) == '/')
						if (line.at(i) == ' ' || line.at(i) == '/')
						{
							numberToStoreFloat = stof(numberToStoreString, 0);
							numberToStoreString.clear();
							vertexCoords.push_back(numberToStoreFloat);
							storeNextNumber = false;
							numberToStoreFloat = 0;
						}
						else
							numberToStoreString += line.at(i);
					}
					if (i < (int)line.length())
					{
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					else if (i == line.length() && storeNextNumber)
					{
						numberToStoreFloat = stof(numberToStoreString, 0);
						numberToStoreString.clear();
						vertexCoords.push_back(numberToStoreFloat);
						storeNextNumber = false;
						numberToStoreFloat = 0;
					}

				}
			}
			// Storing the textures
			else if (line.substr(0, 2) == "vt")
			{
				for (int i = 0; i < (int)line.length() + 1; i++)
				{
					if (storeNextNumber && i < (int)line.length())
					{
						// storeNextNumber = true && i < line.length && (line.at(i) == ' ' || line.at(i) == '/')
						if (line.at(i) == ' ' || line.at(i) == '/')
						{
							numberToStoreFloat = stof(numberToStoreString, 0);
							numberToStoreString.clear();
							textureCoords.push_back(numberToStoreFloat);
							storeNextNumber = false;
							numberToStoreFloat = 0;
						}
						else
							numberToStoreString += line.at(i);
					}
					if (i < (int)line.length())
					{
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					else if (i == line.length() && storeNextNumber)
					{
						numberToStoreFloat = stof(numberToStoreString, 0);
						numberToStoreString.clear();
						textureCoords.push_back(numberToStoreFloat);
						storeNextNumber = false;
						numberToStoreFloat = 0;
					}

				}
			}
			// Storing the normals
			else if (line.substr(0, 2) == "vn")
			{
				for (int i = 0; i < (int)line.length() + 1; i++)
				{
					if (storeNextNumber && i < (int)line.length())
					{
						// storeNextNumber = true && i < line.length && (line.at(i) == ' ' || line.at(i) == '/')
						if (line.at(i) == ' ' || line.at(i) == '/')
						{
							numberToStoreFloat = stof(numberToStoreString, 0);
							numberToStoreString.clear();
							normalCoords.push_back(numberToStoreFloat);
							storeNextNumber = false;
							numberToStoreFloat = 0;
						}
						else
							numberToStoreString += line.at(i);
					}
					if (i < (int)line.length())
					{
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					else if (i == line.length() && storeNextNumber)
					{
						numberToStoreFloat = stof(numberToStoreString, 0);
						numberToStoreString.clear();
						normalCoords.push_back(numberToStoreFloat);
						storeNextNumber = false;
						numberToStoreFloat = 0;
					}

				}

			}
			// Storing the facesList
			else if (line.substr(0, 2) == "f ")
			{
				for (int i = 0; i < (int)line.length() + 1; i++)
				{
					if (storeNextNumber && i < (int)line.length())
					{
						// storeNextNumber = true && i < line.length && (line.at(i) == ' ' || line.at(i) == '/')
						if (line.at(i) == ' ' || line.at(i) == '/')
						{
							numberToStoreInt = stoi(numberToStoreString, 0);
							numberToStoreString.clear();
							facesList.push_back(numberToStoreInt);
							storeNextNumber = false;
							numberToStoreInt = 0;
						}
						else
							numberToStoreString += line.at(i);
					}
					if (i < (int)line.length())
					{
						if (line.at(i) == ' ' || line.at(i) == '/')
							storeNextNumber = true;
					}
					else if (i == line.length() && storeNextNumber)
					{
						numberToStoreInt = stoi(numberToStoreString, 0);
						numberToStoreString.clear();
						facesList.push_back(numberToStoreInt);
						storeNextNumber = false;
						numberToStoreInt = 0;
					}

				}
			}
		}

		cout << endl << "Successfully read " << filePath << endl;
		cout << endl << "Vertex Coords: ";
		for (int i = 0; i < (int)vertexCoords.size(); i++)
			cout << vertexCoords[i] << "  ";

		cout << endl << "Texture Coords: ";
		for (int i = 0; i < (int)textureCoords.size(); i++)
			cout << textureCoords[i] << "  ";

		cout << endl << "Normal Coords: ";
		for (int i = 0; i < (int)normalCoords.size(); i++)
			cout << normalCoords[i] << "  ";

		cout << endl << "facesList: ";
		for (int i = 0; i < (int)facesList.size(); i++)
			cout << facesList[i] << "  ";

		// For every line...
		for (int i = 0; i < (int)(facesList.size() / 9); i++)
		{
			// f v1[/vt1][/vn1] v2[/vt2][/vn2] v3[/vt3][/vn3]
			/* Vertex 1 */
			//Points
			finalData.push_back(vertexCoords[((facesList[9 * i + 0] - 1) * 3 + 0)]);
			finalData.push_back(vertexCoords[((facesList[9 * i + 0] - 1) * 3 + 1)]);
			finalData.push_back(vertexCoords[((facesList[9 * i + 0] - 1) * 3 + 2)]);
			//Textures
			finalData.push_back(textureCoords[((facesList[9 * i + 1] - 1) * 2 + 0)]);
			finalData.push_back(textureCoords[((facesList[9 * i + 1] - 1) * 2 + 1)]);

			/* Vertex 2 */
			//Points
			finalData.push_back(vertexCoords[((facesList[9 * i + 3] - 1) * 3 + 0)]);
			finalData.push_back(vertexCoords[((facesList[9 * i + 3] - 1) * 3 + 1)]);
			finalData.push_back(vertexCoords[((facesList[9 * i + 3] - 1) * 3 + 2)]);
			//Textures
			finalData.push_back(textureCoords[((facesList[9 * i + 4] - 1) * 2 + 0)]);
			finalData.push_back(textureCoords[((facesList[9 * i + 4] - 1) * 2 + 1)]);

			/* Vertex 3 */
			//Points
			finalData.push_back(vertexCoords[((facesList[9 * i + 6] - 1) * 3 + 0)]);
			finalData.push_back(vertexCoords[((facesList[9 * i + 6] - 1) * 3 + 1)]);
			finalData.push_back(vertexCoords[((facesList[9 * i + 6] - 1) * 3 + 2)]);
			//Textures
			finalData.push_back(textureCoords[((facesList[9 * i + 7] - 1) * 2 + 0)]);
			finalData.push_back(textureCoords[((facesList[9 * i + 7] - 1) * 2 + 1)]);
		}

		cout << endl << "Final data: ";
		for (int i = 0; i < (int)finalData.size(); i++)
		{
			cout << finalData[i] << ' ';
		}
	}
	else
	{
		cout << "File type unknown or unsupported." << endl;
	}
	vertexCoords.clear();
	textureCoords.clear();
	normalCoords.clear();
	facesList.clear();
	return finalData;
}
Texture Resource::LoadTexture(string fileName)
{
	Texture tex;

	string filePath = "Resources\\Textures\\" + fileName;
	tex.image = stbi_load(filePath.c_str(), &tex.width, &tex.height, &tex.nrChannels, 0);

	if (tex.image == nullptr)
		std::cout << "ERROR LOADING TEXTURE! Faulty filename?" << std::endl;

	return tex;
}
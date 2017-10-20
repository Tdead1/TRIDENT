#include <Graphics/Window.h>
#include <iostream>

Window::Window()
{
}


Window::~Window()
{
}

void Window::Create(Camera* _camera)
{
	glfw = InitGLFW();
	CreateShaders(_camera);
}
void Window::Update()
{
	// Clearing the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.0f, 0.1f, 1.0f);

	// Swap buffers
	glfwSwapBuffers(glfw);
	glfwPollEvents();

}


bool Window::Draw(std::vector<GLfloat> &_data, Matrix &_model, Texture &_texture)
{
	/*  ENABLE PROGRAM					*/
	glUseProgram(programID);
	CheckGLErrors("ModelLoader Use Program");

	/*  GENERATE AND BIND VERTEXARRAY	*/
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	CheckGLErrors("ModelLoader VertexArrayID");

	/*  SETUP MVP						*/
	Matrix mvp = camera->pv * _model;
	CheckGLErrors("ModelLoader Setting Up MVP");

	/*  SET MVP IN SHADERS				*/
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp.m[0][0]);
	CheckGLErrors("ModelLoader Sending MVP");

	/*  IDENTIFY VERTEXBUFFER			*/
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _data.size(), &_data.front(), GL_STATIC_DRAW);
	CheckGLErrors("ModelLoader Vertex Buffer");

	/*  FIRST  ATTRIBUTE HERE: VERTEX LOCATIONS  */
	GLuint VertexID = glGetAttribLocation(programID, "_position");
	glVertexAttribPointer(VertexID, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)0);
	glEnableVertexAttribArray(VertexID);
	CheckGLErrors("ModelLoader first attribute");

	//  Optional: Other atribute buffers here
	/*  SECOND ATTRIBUTE HERE: TEXTURE COORDS	*/
	GLuint textureID = glGetAttribLocation(programID, "_texcoord");
	glVertexAttribPointer(textureID, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(textureID);
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texture.width, _texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texture.image);
	CheckGLErrors("ModelLoader second attribute");

	/*  THIRD  ATTRIBUTE HERE: NORMAL LOCATIONS		*/


	/*  DRAW THE END RESULT				*/
	glDrawArrays(GL_TRIANGLES, 0, _data.size());
	glDisableVertexAttribArray(0);
	CheckGLErrors("ModelLoader DrawArrays");


	glDeleteTextures(1, &texture1);
	return false;
}
void Window::CheckGLErrors(std::string whereIsTheCheck)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "GLError in: " << whereIsTheCheck << std::endl;
		std::cout << "Error: " << error << std::endl << std::endl;
	}
}


GLFWwindow* Window::InitGLFW()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW!\n";
		return NULL;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);								// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//We don't want the old OpenGL 
																	// Open a window and create its OpenGL context
	GLFWwindow* window;												// (In the accompanying source code, this variable is global)
	window = glfwCreateWindow(1024, 768, "PERSONAL PROJECT", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.";
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = true;		// Needed in core profile
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		return NULL;
	}
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	return window;
}
void Window::CreateShaders(Camera *_camera)
{
	// Create and compile the GLSL program from the shaders
	programID = LoadShaders("Resources/Shaders/Simple.vsh", "Resources/Shaders/Simple.fsh");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CheckGLErrors("ModelLoader Use Program");
	camera = _camera;
}
GLuint Window::LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
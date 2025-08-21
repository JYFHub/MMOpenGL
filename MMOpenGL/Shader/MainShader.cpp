#include "MainShader.h"
#include "CommonDefine.h"
#include "cmath"

#define EnableEBO 0
#define EnableTexture 1

char* VertexShaderSource = nullptr;//顶点着色器代码
char* FragmentShaderSource = nullptr;//片段着色器代码
GLuint ShaderProgram = 0;
GLuint VAO = 0;
GLuint VBO = 0;
GLuint EBO = 0;
GLuint TextuteID = 0;

void InitMainShader()
{
	InitSharderSource();

	GLuint VertexShader = CreateShader(GL_VERTEX_SHADER,VertexShaderSource);

	GLuint FragmentShader = CreateShader(GL_FRAGMENT_SHADER,FragmentShaderSource);
	
	ShaderProgram = CreateShaderProgram(VertexShader, FragmentShader);

	InitVAOVBOEBO();

	glClearColor(0.2,0.3, 0.3, 1.0);
}

void InitSharderSource()
{
	VertexShaderSource = SHADER(
		#version 330\n

		uniform float ua;
		
		layout(location = 0) in vec3 pos;
		layout(location = 1) in vec3 Color;

		out vec3 outPos;
		out vec3 outColor;

		void main()
		{
			outPos = pos;
			outColor = Color;
			//gl_Position = vec4(pos.x+ua, pos.y, pos.z, 1.0);
			gl_Position = vec4(pos.x * ua, pos.y * ua, pos.z * ua, 1.0);
		}
	);
	FragmentShaderSource = SHADER(
		#version 330\n

		out  vec4 rgbaColor;
		in vec3 outPos;
		in vec3 outColor;

		uniform sampler2D ub;
		uniform float uvx;
		uniform float uvy;

		void main()
		{
			//rgbaColor = vec4(outColor, 1.0);
			rgbaColor = texture(ub,vec2(uvx,uvy));
		}
	);
}

void InitVAOVBOEBO()
{
#if EnableEBO
	float Vertex[] = {
		0,0.5,0,
		-0.5,-0.5,0,
		0.5,-0.5,0,
		-0.5,0.5,0,
		0.5,0.5,0
	};
	unsigned int EBOIndex[] = {
		0,1,3,
		0,1,2,
		0,4,2
	};

	float Color[] = {
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(EBOIndex), EBOIndex, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	GLuint VColor = 0;
	glGenBuffers(1, &VColor);
	glBindBuffer(GL_ARRAY_BUFFER, VColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

	glBindVertexArray(0);
#elif EnableTexture
	float Vertex[] = {
		0,1,0,
		-1,-1,0,
		1,-1,0,
		-1,1,0,
		1,1,0
	};
	unsigned int EBOIndex[] = {
		0,1,3,
		0,1,2,
		0,4,2
	};
	int imgWidth = 2;
	int imgHeight = 2;
	unsigned char imgData[] = {
		255,0,0,0,255,0,0,0,255,255,255,255
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(EBOIndex), EBOIndex, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	glGenTextures(1, &TextuteID);
	glBindTexture(GL_TEXTURE_2D,TextuteID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB,GL_UNSIGNED_BYTE, imgData);

#else
	float Vertices[] = {
		-0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
		0.0f,0.5f,0.0f,0.0f,0.0f,1.0f	
	};

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glBindVertexArray(0);
#endif
}

void SetUniformFloat(const std::string name, float value)
{
	GLint Location = glGetUniformLocation(ShaderProgram, name.c_str());
	glUniform1f(Location,value);
}

GLuint CreateShader(GLenum type,char* ShaderSource)
{
	GLuint Shader = glCreateShader(type); 
	glShaderSource(Shader, 1, &ShaderSource, NULL);
	glCompileShader(Shader);

	//编译状态
	GLint CompileStatus;
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &CompileStatus);

	if (!CompileStatus)
	{
		GLint LogLen = 0;
		glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &LogLen);

		if (LogLen > 0)
		{
			char* LogContext = new char[LogLen + 1];
			glGetShaderInfoLog(Shader, LogLen, NULL, LogContext);
			std::cout << "Shader Comple Error Log:" << std::endl;
			std::cout << LogContext << std::endl;
			delete LogContext;
		}
	}
	return Shader;
}

GLuint CreateShaderProgram(GLuint VertexShader,GLuint FragmentShader)
{
	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	GLint LogLen = 0;
	glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &LogLen);

	if (LogLen > 0)
	{
		char* LogContext = new char[LogLen + 1];
		glGetProgramInfoLog(ShaderProgram, LogLen, NULL, LogContext);
		std::cout << "ShaderProgram Error Log:" << std::endl;
		std::cout << LogContext << std::endl;
		delete LogContext;
	}
	return ShaderProgram;
}

void UpdateMainShader()
{
	glClear(GL_COLOR_BUFFER_BIT); //清除颜色通道

	glUseProgram(ShaderProgram); 

#if EnableEBO
	glBindVertexArray(VAO);

	static float ua = 0.0;
	static int XI = 1.0;
	GLint loc = glGetUniformLocation(ShaderProgram,"ua");
	glUniform1f(loc, ua);
	ua += 0.001f * XI;
	if (XI > 0 && ua > 0.5)
	{
		XI = -1;
	}
	else if (XI < 0 && ua < -0.5)
	{
		XI = 1;
	}

	glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,(void*)(sizeof(int)*3));

	glBindVertexArray(0);
#elif EnableTexture
	glBindVertexArray(VAO);

	GLint loc = glGetUniformLocation(ShaderProgram, "ua");
	glUniform1f(loc, 0.5);

	GLint locu = glGetUniformLocation(ShaderProgram, "uvx");
	static float x = 0.0f;
	static float y = 0.0f;
	glUniform1f(locu, x);
	GLint locv = glGetUniformLocation(ShaderProgram, "uvy");
	glUniform1f(locv,y);
	x += 0.01;
	if (x > 1)
	{
		x = 0;
		y += 0.01;	
		if (y > 1)
		{
			y = 0;
		}
	}

	GLint tloc = glGetUniformLocation(ShaderProgram,"ub");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,TextuteID);
	glUniform1i(tloc,0);

	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

#else
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
#endif
}

void ShutdownMainShader()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(ShaderProgram);
}

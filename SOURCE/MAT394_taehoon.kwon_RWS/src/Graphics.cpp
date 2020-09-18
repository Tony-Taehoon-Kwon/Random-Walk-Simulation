#include "GridCanvas.h"
#include <iostream>

#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

using namespace SimulationSection;

/* Definition of class static variable */
Graphics* Graphics::_instance = NULL;
bool Graphics::firstMouse = true;
int Graphics::dimension = 3;
int Graphics::width = 850;
int Graphics::height = 520;
float Graphics::lastX = Graphics::width / 2.0f;
float Graphics::lastY = Graphics::height / 2.0f;
Camera Graphics::camera3D(glm::vec3(15.0f, 15.f, 15.f),
			 glm::normalize(glm::vec3(-1.0f, 1.0f, -1.0f)),
			 glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f)));
Camera Graphics::camera2D(glm::vec3(0.0f, 0.f, 30.f),
			 glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)),
			 glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)));

Graphics* Graphics::instance()
{
	if (_instance == NULL)
		_instance = new Graphics;

	return _instance;
}

void Graphics::DestroyInstance(void)
{
	/* release instance memory */
	if (_instance)
	{
		delete _instance;
		_instance = 0;
	}
}

int Graphics::Init()
{
	/* Initialise GLFW */
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return -1;
	}

	//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing, 4 samples in each pixel
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);  // opengl version 4.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);  // opengl verion   .4
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(Graphics::width, Graphics::height, "graphics_title", NULL, NULL);
	if (window == NULL) {
		printf("Failed to open GLFW window.\n");
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Embed glfw window inside windows form */
	glfwHWND = glfwGetWin32Window(window);
	HWND parentHWND = GridCanvas::getParentHWND();

	if (glfwHWND == NULL)
	{
		printf("Failed to embed GLFW window. glfwGetWin32Window() returns NULL.\n");
		glfwTerminate();
		return -1;
	}

	if (parentHWND == NULL)
	{
		printf("Failed to embed GLFW window. getParentHWND() returns NULL.\n");
		glfwTerminate();
		return -1;
	}

	SetParent(glfwHWND, parentHWND);
	LONG newStyle = GetWindowLong(glfwHWND, GWL_STYLE) 
		& ~WS_POPUP | WS_VISIBLE | //~WS_BORDER | ~WS_CAPTION |
		WS_CHILDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	SetWindowLong(glfwHWND, GWL_STYLE, newStyle);
	//SetWindowPos(glfwHWND, parentHWND, 0, 0, 50, 100, ~SWP_DRAWFRAME);
	//ShowWindow(glfwHWND, SW_SHOW);
	glfwSetWindowPos(window, 50, 100);
	glfwShowWindow(window);

	glfwSetCursorPosCallback(window, Graphics::MouseCallback);
	glfwSetScrollCallback(window, Graphics::ScrollCallback);

	/* Initialize GLAD before we call any OpenGL function */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad\n";
		return -1;
	}

	/* Ensure we can capture the escape key being pressed below */
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	
	/* calculate the aspect ratio */
	aspect = float(width) / float(height);

	/* set the initial value of max domain as 10 */
	mainAxisDomain = 10;

	/* set the initial value of minor axis interval as 1 */
	minorAxisInterval = 1;

	/* set the initial value of simulation id as 0 : simple random walk */
	simulationId = 0;

	/* set the initial simulation stats for walker */
	walkerStepSize = 1;
	walkerStepCount = 100;
	walkerStepInfinite = true;

	/* set the value of the handle to 0 to show it's not generated yet */
	axis_vao = axis_vbo = 0;
	for (int i = 0; i < NUM_OF_QUAD_IN_3D; ++i)
		axis_minor_vao[i] = axis_minor_vbo[i] = 0;
	for (int i = 0; i < MAX_NUM_OF_WALKERS; ++i)
		track_vao[i] = track_vbo[i] = 0;

	/* clear and allocate the memory for sphere models */
	spheres.clear();
	spheres.resize(MAX_NUM_OF_WALKERS);
	walkersVisibility.clear();
	for (int i = 0; i < MAX_NUM_OF_WALKERS; ++i)
		walkersVisibility.push_back(true);

	/* Initialize the shader, axis and models */
	InitShader();
	InitModels();
	InitRandomSimulationStatus(numOfWalkers, walkerStepSize, walkerStepCount, walkerStepInfinite, 1);
	isAppFirstStarted = true;
	isSimulationChanged = false;

	/* Enable depth test */
	glEnable(GL_DEPTH_TEST);
	/* Accept fragment if it closer to the camera than the former one */
	glDepthFunc(GL_LESS);

	/* Cull triangles which normal is not towards the camera */
	//glEnable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 0;
}

HWND Graphics::GetHandle(void)
{
	return glfwHWND;
}

void Graphics::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float f_xpos = float(xpos);
	float f_ypos = float(ypos);

	if (firstMouse)
	{
		lastX = f_xpos;
		lastY = f_ypos;
		firstMouse = false;
	}

	float xoffset = f_xpos - lastX;
	float yoffset = lastY - f_ypos;

	lastX = f_xpos;
	lastY = f_ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_RELEASE)
	{
		if (dimension == 3)
			camera3D.ProcessMouseMovement(xoffset, yoffset, dimension);
		else
			camera2D.ProcessMouseMovement(xoffset, yoffset, dimension);
	}
}

void Graphics::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (dimension == 3)
		camera3D.ProcessMouseScroll(float(yoffset));
	else
		camera2D.ProcessMouseScroll(float(yoffset));
}

void Graphics::InitShader(void)
{
	basicShader = new Shader("res/Basic.shader");
	basicLineShader = new Shader("res/BasicLine.shader");
}

void Graphics::ShutdownShader(void)
{
	delete basicShader;
	delete basicLineShader;
}

void Graphics::Render(void)
{
	/*if (!isAppFirstStarted && !isSimulationPlaying && !isSimulationChanged)
		return;

	isAppFirstStarted = false;
	isSimulationChanged = false;*/

	/* set the clear color to white background */
	glClearColor(1.0f, 1.0f, 1.0f, 0.f);
	/* clear the color and the depth buffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* render the axis */
	DrawAxis();
	DrawMinorAxis();

	/* render the walkers */
	DrawModels();
	DrawSimulationStatus();
}

void Graphics::InitRandomSimulationStatus(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier)
{
	/* clear the log and result */
	oldLog = log;
	oldResult = result;
	ClearOldLog();
	ClearOldResult();

	/* initialize the axis */
	InitAxis();
	InitMinorAxis();

	/* initialize model information */
	numOfWalkers = walker_num;
	walkerStepSize = stepSize;
	walkerStepCount = stepCount;
	walkerStepInfinite = infiniteStep;

	/* clear old position data */
	initWalkersPos.clear();

	/* initialize variable for chart */
	chartUpdate = false;
	countOfPosNegMove.clear();
	for (int i = 0; i < 6; ++i)
		countOfPosNegMove.push_back(0);

	/* set the walker speed */
	walkerSpeed = 0.04f * speedMultiplier;

	/* set the initial position of the walker */
	for (int i = 0; i < numOfWalkers; ++i)
	{
		if (dimension == 3)
		{
			spheres[i].position = { rand() % (mainAxisDomain * 2 + 1) - mainAxisDomain,
								   rand() % (mainAxisDomain * 2 + 1) - mainAxisDomain,
								   rand() % (mainAxisDomain * 2 + 1) - mainAxisDomain };
		}
		else if (dimension == 2)
		{
			spheres[i].position = { rand() % (mainAxisDomain * 2 + 1) - mainAxisDomain,
								   rand() % (mainAxisDomain * 2 + 1) - mainAxisDomain,
								   0.f };
		}
		else
		{
			spheres[i].position = { rand() % (mainAxisDomain * 2 + 1) - mainAxisDomain,
								   0.f,
								   0.f };
		}

		initWalkersPos.push_back(spheres[i].position);
	}
	randomWalk.Init(initWalkersPos);

	/* initialize the simulation flag */
	oneStepMoved = true;
	isSimulationPlaying = false;

	for (int i = 0; i < numOfWalkers; ++i)
	{
		track_vertex_buffer[i].clear();
		// sphere position before moving
		track_vertex_buffer[i].push_back(spheres[i].position);
		
		/* Set the vertex array object and vertex buffer object for the track */
		if (!track_vao[i])	glGenVertexArrays(1, &track_vao[i]);
		if (!track_vbo[i])	glGenBuffers(1, &track_vbo[i]);

		/* Bind the vertex array and vertex buffer */
		glBindVertexArray(track_vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, track_vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, track_vertex_buffer[i].size() * sizeof(glm::vec3), &track_vertex_buffer[i][0], GL_STATIC_DRAW);

		/* Set the vertex attribute array */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

		/* Unbind the vertex array object */
		glBindVertexArray(0);
	}
}

void Graphics::InitGivenSimulationStatus(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier, const std::vector<glm::vec3>& init_walkers_pos)
{
	/* clear the log and result */
	oldLog = log;
	oldResult = result;
	ClearOldLog();
	ClearOldResult();

	/* initialize the axis */
	InitAxis();
	InitMinorAxis();

	/* initialize model information */
	numOfWalkers = walker_num;
	walkerStepSize = stepSize;
	walkerStepCount = stepCount;
	walkerStepInfinite = infiniteStep;

	/* clear old position data */
	initWalkersPos.clear();

	/* initialize variable for chart */
	chartUpdate = false;
	countOfPosNegMove.clear();
	for (int i = 0; i < 6; ++i)
		countOfPosNegMove.push_back(0);

	/* set the walker speed */
	walkerSpeed = 0.04f * speedMultiplier;

	/* set the initial position of the walker */
	for (int i = 0; i < numOfWalkers; ++i)
	{
		if (dimension == 3)
		{
			spheres[i].position = init_walkers_pos[i];
		}
		else if (dimension == 2)
		{
			spheres[i].position = { init_walkers_pos[i].x,
								    init_walkers_pos[i].y,
								    0.f };
		}
		else
		{
			spheres[i].position = { init_walkers_pos[i].x,
								    0.f,
								    0.f };
		}

		initWalkersPos.push_back(spheres[i].position);
	}
	randomWalk.Init(initWalkersPos);

	/* initialize the simulation flag */
	oneStepMoved = true;
	isSimulationPlaying = false;

	for (int i = 0; i < numOfWalkers; ++i)
	{
		track_vertex_buffer[i].clear();
		// sphere position before moving
		track_vertex_buffer[i].push_back(spheres[i].position);

		/* Set the vertex array object and vertex buffer object for the track */
		if (!track_vao[i])	glGenVertexArrays(1, &track_vao[i]);
		if (!track_vbo[i])	glGenBuffers(1, &track_vbo[i]);

		/* Bind the vertex array and vertex buffer */
		glBindVertexArray(track_vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, track_vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, track_vertex_buffer[i].size() * sizeof(glm::vec3), &track_vertex_buffer[i][0], GL_STATIC_DRAW);

		/* Set the vertex attribute array */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

		/* Unbind the vertex array object */
		glBindVertexArray(0);
	}
}

void Graphics::UpdateSimulationStatus(void)
{
	if (!isSimulationPlaying)
		return;

	bool simulationDone = true;

	if (oneStepMoved)
	{
		walkersDir = randomWalk.Update(simulationId, dimension, countOfPosNegMove,
										walkerStepSize, walkerStepCount, walkerStepInfinite);
		for (unsigned i = 0; i < walkersDir.size(); ++i) {
			if (walkersDir[i] != -1) {
				simulationDone = false;
				break;
			}
		}
		
		if (!simulationDone) 
		{
			oneStepMoved = false;

			for (int i = 0; i < numOfWalkers; ++i)
			{
				if (randomWalk.trapped[i])
					continue;

				dirCalculated[i] = false;

				/* create another space for next track, value does not have meaning */
				track_vertex_buffer[i].push_back(spheres[i].position);
			}
		}
		//else {
		//	isSimulationPlaying = false;
		//}
	}

	if (!oneStepMoved || !simulationDone) {
		oldLog = log;
		ClearOldLog();
	}
	else {
		oldResult = result;
		ClearOldResult();
		UpdateResult();
		CheckStringChanged(false);
		//	isSimulationPlaying = false;
		return;
	}

	for (int i = 0; i < numOfWalkers; ++i)
	{
		if (randomWalk.trapped[i]) {
			/* Add position log */
			std::string index = std::to_string(i + 1);
			std::string x_pos = std::to_string(spheres[i].position.x);
			std::string y_pos = dimension == 3 ? std::to_string(spheres[i].position.z) : std::to_string(-spheres[i].position.y);
			std::string z_pos = dimension == 3 ? std::to_string(spheres[i].position.y) : std::to_string(0);
			AddLog("Walker " + index + " Current Position: " +
				" x : " + x_pos + ", y : " + y_pos + ", z : " + z_pos + "\n");
			CheckStringChanged(true);
			continue;
		}

		/* calculate direction vector */
		if (dirCalculated[i] == false)
		{
			dir[i] = glm::vec3(
				(randomWalk.walkers[i].x - spheres[i].position.x) * walkerSpeed / (float)walkerStepSize,
				(randomWalk.walkers[i].y - spheres[i].position.y) * walkerSpeed / (float)walkerStepSize,
				(randomWalk.walkers[i].z - spheres[i].position.z) * walkerSpeed / (float)walkerStepSize);

			dirCalculated[i] = true;
		}
		
		/* update walkers' next frame position */
		spheres[i].position += dir[i];
		std::string index = std::to_string(i+1);
		std::string x_pos = std::to_string(spheres[i].position.x);
		std::string y_pos = dimension == 3 ? std::to_string(spheres[i].position.z) : std::to_string(-spheres[i].position.y);
		std::string z_pos = dimension == 3 ? std::to_string(spheres[i].position.y) : std::to_string(0);
		AddLog("Walker " + index + " Current Position: " +
			 " x : " + x_pos + ", y : " + y_pos + ", z : " + z_pos + "\n");
		CheckStringChanged(true);

		/* calculate if walkers pass the target boundary */
		bool targetArrived = false;
		switch (walkersDir[i]) {
			case 0: if (randomWalk.walkers[i].x <= spheres[i].position.x) targetArrived = true; break;
			case 1: if (randomWalk.walkers[i].x >= spheres[i].position.x) targetArrived = true; break;
			case 2: if (randomWalk.walkers[i].y <= spheres[i].position.y) targetArrived = true; break;
			case 3: if (randomWalk.walkers[i].y >= spheres[i].position.y) targetArrived = true; break;
			case 4: if (randomWalk.walkers[i].z <= spheres[i].position.z) targetArrived = true; break;
			case 5: if (randomWalk.walkers[i].z >= spheres[i].position.z) targetArrived = true; break;
			default: break;
		}

		/* if walkers pass the target position,
		   set walkers' position with the target position */
		if (targetArrived) {
			spheres[i].position = randomWalk.walkers[i];
			oneStepMoved = true;
			chartUpdate = true;
		}

		/* update the track line vertex buffer */
		track_vertex_buffer[i].pop_back();
		track_vertex_buffer[i].push_back(spheres[i].position); // actual assign of end point of track line

		/* Bind the vertex array and vertex buffer */
		glBindVertexArray(track_vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, track_vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, track_vertex_buffer[i].size() * sizeof(glm::vec3), &track_vertex_buffer[i][0], GL_STATIC_DRAW);
		
		/* Unbind the vertex array object */
		glBindVertexArray(0);
	}
}

void Graphics::RewindOneFrame(void)
{
	/* clear the log and result */
	oldLog = log;
	oldResult = result;
	ClearOldLog();
	ClearOldResult();

	for (int i = 0; i < numOfWalkers; ++i)
	{
		/* if there is no previous frame, then skip the walker */
		if (randomWalk.histories[i].size() < 2)
			continue;

		/* variable for updating chart */
		glm::vec3 currentPos = spheres[i].position;

		/* update walkers' next frame position to previous frame position */
		spheres[i].position = randomWalk.histories[i][randomWalk.histories[i].size()-2];
		randomWalk.histories[i].pop_back();
		randomWalk.walkers[i] = spheres[i].position;
		randomWalk.trapped[i] = false;
		dirCalculated[i] = true;
		for (int j = 0; j < walkerStepSize; ++j)
			randomWalk.histories_interval_one[i].pop_back();
		randomWalk.intersectInNextStep = false;
		randomWalk.intersected = false;
		randomWalk.returnedToOrigin[i] = false;

		/* calculate positive and negative move for updating chart */
		if (currentPos.x - spheres[i].position.x > walkerSpeed)				{ countOfPosNegMove[0] -= 1; }
		else if (currentPos.x - spheres[i].position.x < -walkerSpeed)		{ countOfPosNegMove[1] -= 1; }
		if (dimension == 2) {
			if (currentPos.y - spheres[i].position.y > walkerSpeed)			{ countOfPosNegMove[3] -= 1; }
			else if (currentPos.y - spheres[i].position.y < -walkerSpeed)	{ countOfPosNegMove[2] -= 1; }
		}
		if (dimension == 3) {
			if (currentPos.y - spheres[i].position.y > walkerSpeed)			{ countOfPosNegMove[4] -= 1; }
			else if (currentPos.y - spheres[i].position.y < -walkerSpeed)	{ countOfPosNegMove[5] -= 1; }
			else if (currentPos.z - spheres[i].position.z > walkerSpeed)	{ countOfPosNegMove[2] -= 1; }
			else if (currentPos.z - spheres[i].position.z < -walkerSpeed)	{ countOfPosNegMove[3] -= 1; }
		}

		std::string index = std::to_string(i + 1);
		std::string x_pos = std::to_string(spheres[i].position.x);
		std::string y_pos = dimension == 3 ? std::to_string(spheres[i].position.z) : std::to_string(-spheres[i].position.y);
		std::string z_pos = dimension == 3 ? std::to_string(spheres[i].position.y) : std::to_string(0);
		AddLog("Walker " + index + " Current Position: " +
			" x : " + x_pos + ", y : " + y_pos + ", z : " + z_pos + "\n");
		CheckStringChanged(true);

		/* update the track line vertex buffer */
		track_vertex_buffer[i].pop_back();

		/* Bind the vertex array and vertex buffer */
		glBindVertexArray(track_vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, track_vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, track_vertex_buffer[i].size() * sizeof(glm::vec3), &track_vertex_buffer[i][0], GL_STATIC_DRAW);

		/* Set the vertex attribute array */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

		/* Unbind the vertex array object */
		glBindVertexArray(0);
		
		oneStepMoved = true;
		chartUpdate = true;
	}
}

void Graphics::PlayOneFrame(void)
{
	bool simulationDone = true;

	if (oneStepMoved)
	{
		walkersDir = randomWalk.Update(simulationId, dimension, countOfPosNegMove,
										walkerStepSize, walkerStepCount, walkerStepInfinite);

		for (unsigned i = 0; i < walkersDir.size(); ++i) {
			if (walkersDir[i] != -1) {
				simulationDone = false;
				break;
			}
		}

		if (!simulationDone) {
			for (int i = 0; i < numOfWalkers; ++i)
			{
				if (randomWalk.trapped[i])
					continue;

				/* create another space for next track, value does not have meaning */
				track_vertex_buffer[i].push_back(spheres[i].position);
			}
		}
	}

	if (!oneStepMoved || !simulationDone) {
		oldLog = log;
		ClearOldLog();
	}
	else {
		oldResult = result;
		ClearOldResult();
		UpdateResult();
		CheckStringChanged(false);
		return;
	}

	for (int i = 0; i < numOfWalkers; ++i)
	{
		if (randomWalk.trapped[i])
			continue;

		/* update walkers' next frame position */
		spheres[i].position = randomWalk.walkers[i];
		dirCalculated[i] = true;

		std::string index = std::to_string(i + 1);
		std::string x_pos = std::to_string(spheres[i].position.x);
		std::string y_pos = dimension == 3 ? std::to_string(spheres[i].position.z) : std::to_string(-spheres[i].position.y);
		std::string z_pos = dimension == 3 ? std::to_string(spheres[i].position.y) : std::to_string(0);
		AddLog("Walker " + index + " Current Position: " +
			" x : " + x_pos + ", y : " + y_pos + ", z : " + z_pos + "\n");
		CheckStringChanged(true);

		/* update the track line vertex buffer */
		track_vertex_buffer[i].pop_back();
		track_vertex_buffer[i].push_back(spheres[i].position); // actual assign of end point of track line

		/* Bind the vertex array and vertex buffer */
		glBindVertexArray(track_vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, track_vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, track_vertex_buffer[i].size() * sizeof(glm::vec3), &track_vertex_buffer[i][0], GL_STATIC_DRAW);

		/* Set the vertex attribute array */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

		/* Unbind the vertex array object */
		glBindVertexArray(0);

		oneStepMoved = true;
		chartUpdate = true;
	}
}

void Graphics::ClearSimulation(void)
{
	/* clear track line */
	for (int i = 0; i < numOfWalkers; ++i)
		track_vertex_buffer[i].clear();

	numOfWalkers = 0;
}

/* This function draws the trace of random walk */
void Graphics::DrawSimulationStatus(void)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0)) * glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	glm::mat4 view, projection;
	if (dimension == 3)
	{
		view = camera3D.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera3D.zoom), aspect, 0.1f, 100.0f);
	}
	else
	{
		view = glm::mat4(1.0);
		projection = glm::ortho((-mainAxisDomain + camera2D.position.x) *camera2D.zoom /30.f * aspect,	// left
								 (mainAxisDomain + camera2D.position.x) *camera2D.zoom /30.f * aspect,	// right
								 (mainAxisDomain + camera2D.position.y) *camera2D.zoom /30.f,			// bottom
								(-mainAxisDomain + camera2D.position.y) *camera2D.zoom /30.f,			// top
								-1.0f, 1.0f);
	}
	
	basicLineShader->Bind();
	/* Set uniform location of each matrices */
	basicLineShader->SetUniformMatrix4fv("model", model);
	basicLineShader->SetUniformMatrix4fv("view", view);
	basicLineShader->SetUniformMatrix4fv("projection", projection);

	glLineWidth(3.0f);
	for (int i = 0; i < numOfWalkers; ++i)
	{
		/* if walker is hidden, skip */
		if (walkersVisibility[i] == false)
			continue;

		basicLineShader->SetUniform1i("sphere_index", i);

		/* render the axis line */
		glBindVertexArray(track_vao[i]);
		glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)track_vertex_buffer[i].size());
	}
	glBindVertexArray(0);
	glLineWidth(1.0f);
}

void Graphics::InitModels(void)
{
	srand((unsigned int)time(NULL));

	/* Read .obj file */
	OBJLoader objLoader;
	objLoader.loadOBJ("res/sphere.obj");

	/* Create model based on obj file information */
	for(int i = 0; i < MAX_NUM_OF_WALKERS; ++i)
	{
		spheres[i].CreateModel(objLoader.m_vertices, objLoader.m_vertexIndices);
		spheres[i].color = GetSphereColor(i);
		spheres[i].scale = { 0.25f, 0.25f, 0.25f };
		spheres[i].min = objLoader.min;
		spheres[i].max = objLoader.max;
	}

	numOfWalkers = 10;
}

glm::vec3 Graphics::GetSphereColor(int sphere_index)
{
	switch (sphere_index)
	{
	case 0:	return COLOR_PASTEL_RED;
	case 1: return COLOR_PASTEL_BLUE;
	case 2: return COLOR_PASTEL_GREEN;
	case 3: return COLOR_PASTEL_YELLOW;
	case 4: return COLOR_PASTEL_PURPLE;
	case 5: return COLOR_PASTEL_ORANGE;
	case 6: return COLOR_PINK;
	case 7: return COLOR_SKYBLUE;
	case 8: return COLOR_GOLD;
	case 9: return COLOR_MINT;
	default: return COLOR_BLACK;
	}
}

void Graphics::DrawModels(void)
{
	basicShader->Bind();
	if (dimension == 3)
	{
		camera3D.Update(basicShader);
		basicShader->SetUniform3fv("lightPos", camera3D.position);
	}
	else
	{
		camera2D.Update(basicShader);
		basicShader->SetUniform3fv("lightPos", camera2D.position);
	}
	basicShader->SetUniform3fv("I_a", glm::vec3(1.0f));
	basicShader->SetUniform3fv("I_d", glm::vec3(0.5f));

	/* render the walkers */
	for (int i = 0; i < numOfWalkers; ++i)
	{
		/* if walker is hidden, skip */
		if (walkersVisibility[i] == false)
			continue;

		if (dimension == 3)
			spheres[i].Render(&camera3D, basicShader, aspect, GL_TRIANGLES, dimension, (float)mainAxisDomain);
		else
			spheres[i].Render(&camera2D, basicShader, aspect, GL_TRIANGLES, dimension, (float)mainAxisDomain);
	}
}

void Graphics::InitMinorAxis(void)
{
	for (int i = 0; i < NUM_OF_QUAD_IN_3D; ++i)
		axis_minor_vertex_buffer[i].clear();

	if (minorAxisInterval == 0)
		return;

	/* create data for vertex buffer */
	for (int i = 0; i < mainAxisDomain; ++i)
	{
		if (dimension == 3)
		{
			if ((i + 1) % minorAxisInterval == 0)
			{
				axis_minor_vertex_buffer[0].push_back(glm::vec3(i + 1, -mainAxisDomain, 0));
				axis_minor_vertex_buffer[0].push_back(glm::vec3(i + 1, mainAxisDomain, 0));
				axis_minor_vertex_buffer[1].push_back(glm::vec3(-i - 1, -mainAxisDomain, 0));
				axis_minor_vertex_buffer[1].push_back(glm::vec3(-i - 1, mainAxisDomain, 0));
				axis_minor_vertex_buffer[2].push_back(glm::vec3(i + 1, 0, -mainAxisDomain));
				axis_minor_vertex_buffer[2].push_back(glm::vec3(i + 1, 0, mainAxisDomain));
				axis_minor_vertex_buffer[3].push_back(glm::vec3(-i - 1, 0, -mainAxisDomain));
				axis_minor_vertex_buffer[3].push_back(glm::vec3(-i - 1, 0, mainAxisDomain));
				axis_minor_vertex_buffer[4].push_back(glm::vec3(-mainAxisDomain, i + 1, 0));
				axis_minor_vertex_buffer[4].push_back(glm::vec3(mainAxisDomain, i + 1, 0));
				axis_minor_vertex_buffer[5].push_back(glm::vec3(-mainAxisDomain, -i - 1, 0));
				axis_minor_vertex_buffer[5].push_back(glm::vec3(mainAxisDomain, -i - 1, 0));
				axis_minor_vertex_buffer[6].push_back(glm::vec3(0, i + 1, -mainAxisDomain));
				axis_minor_vertex_buffer[6].push_back(glm::vec3(0, i + 1, mainAxisDomain));
				axis_minor_vertex_buffer[7].push_back(glm::vec3(0, -i - 1, -mainAxisDomain));
				axis_minor_vertex_buffer[7].push_back(glm::vec3(0, -i - 1, mainAxisDomain));
				axis_minor_vertex_buffer[8].push_back(glm::vec3(-mainAxisDomain, 0, i + 1));
				axis_minor_vertex_buffer[8].push_back(glm::vec3(mainAxisDomain, 0, i + 1));
				axis_minor_vertex_buffer[9].push_back(glm::vec3(-mainAxisDomain, 0, -i - 1));
				axis_minor_vertex_buffer[9].push_back(glm::vec3(mainAxisDomain, 0, -i - 1));
				axis_minor_vertex_buffer[10].push_back(glm::vec3(0, -mainAxisDomain, i + 1));
				axis_minor_vertex_buffer[10].push_back(glm::vec3(0, mainAxisDomain, i + 1));
				axis_minor_vertex_buffer[11].push_back(glm::vec3(0, -mainAxisDomain, -i - 1));
				axis_minor_vertex_buffer[11].push_back(glm::vec3(0, mainAxisDomain, -i - 1));
			}
		}
		else if (dimension == 2)
		{
			axis_minor_vertex_buffer[0].push_back(glm::vec3(i + 1, -mainAxisDomain, 0));
			axis_minor_vertex_buffer[0].push_back(glm::vec3(i + 1, mainAxisDomain, 0));
			axis_minor_vertex_buffer[1].push_back(glm::vec3(-i - 1, -mainAxisDomain, 0));
			axis_minor_vertex_buffer[1].push_back(glm::vec3(-i - 1, mainAxisDomain, 0));
			axis_minor_vertex_buffer[4].push_back(glm::vec3(-mainAxisDomain, i + 1, 0));
			axis_minor_vertex_buffer[4].push_back(glm::vec3(mainAxisDomain, i + 1, 0));
			axis_minor_vertex_buffer[5].push_back(glm::vec3(-mainAxisDomain, -i - 1, 0));
			axis_minor_vertex_buffer[5].push_back(glm::vec3(mainAxisDomain, -i - 1, 0));
		}
		else
		{
			axis_minor_vertex_buffer[0].push_back(glm::vec3(i + 1, -TICK_SIZE_1D, 0));
			axis_minor_vertex_buffer[0].push_back(glm::vec3(i + 1, TICK_SIZE_1D, 0));
			axis_minor_vertex_buffer[1].push_back(glm::vec3(-i - 1, -TICK_SIZE_1D, 0));
			axis_minor_vertex_buffer[1].push_back(glm::vec3(-i - 1, TICK_SIZE_1D, 0));
		}
	}
	
	for (int i = 0; i < NUM_OF_QUAD_IN_3D; ++i)
	{
		if (dimension == 2)
		{
			if (i != 0 && i != 1 && i != 4 && i != 5)
				continue;
		}
		else if (dimension == 1)
		{
			if (i != 0 && i != 1)
				continue;
		}

		/* Set the vertex array object and vertex buffer object for the axis */
		if (!axis_minor_vao[i])	 glGenVertexArrays(1, &axis_minor_vao[i]);
		if (!axis_minor_vbo[i])	 glGenBuffers(1, &axis_minor_vbo[i]);

		/* Bind the vertex array and vertex buffer */
		glBindVertexArray(axis_minor_vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, axis_minor_vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, axis_minor_vertex_buffer[i].size() * sizeof(glm::vec3), &axis_minor_vertex_buffer[i][0], GL_STATIC_DRAW);

		/* Set the vertex attribute array */
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

		/* Unbind the vertex array object */
		glBindVertexArray(0);
	}
}

void Graphics::DrawMinorAxis(void)
{
	if (minorAxisInterval == 0)
		return;

	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0)) * glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	glm::mat4 view, projection;
	if (dimension == 3)
	{
		view = camera3D.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera3D.zoom), aspect, 0.1f, 100.0f);
	}
	else
	{
		view = glm::mat4(1.0);
		projection = glm::ortho((-mainAxisDomain + camera2D.position.x) *camera2D.zoom /30.f * aspect,	// left
								 (mainAxisDomain + camera2D.position.x) *camera2D.zoom /30.f * aspect,	// right
								 (mainAxisDomain + camera2D.position.y) *camera2D.zoom /30.f,			// bottom
								(-mainAxisDomain + camera2D.position.y) *camera2D.zoom /30.f,			// top
								-1.0f, 1.0f);
	}

	basicLineShader->Bind();
	/* Set uniform location of each matrices */
	basicLineShader->SetUniformMatrix4fv("model", model);
	basicLineShader->SetUniformMatrix4fv("view", view);
	basicLineShader->SetUniformMatrix4fv("projection", projection);
	basicLineShader->SetUniform1i("sphere_index", 10); // 10 : gray color

	/* render the axis line */
	for (int i = 0; i < NUM_OF_QUAD_IN_3D; ++i)
	{
		if (dimension == 2)
		{
			if (i != 0 && i != 1 && i != 4 && i != 5)
				continue;
		}
		else if (dimension == 1)
		{
			if (i != 0 && i != 1)
				continue;
		}

		glBindVertexArray(axis_minor_vao[i]);
		glDrawArrays(GL_LINES, 0, (GLsizei)axis_minor_vertex_buffer[i].size());
	}
	glBindVertexArray(0);
}

void Graphics::InitAxis(void)
{
	axis_vertex_buffer.clear();

	if (dimension == 3)
	{
		axis_vertex_buffer.push_back(glm::vec3(-mainAxisDomain, 0, 0));	// negative x-axis end point
		axis_vertex_buffer.push_back(glm::vec3(mainAxisDomain, 0, 0));  // positive x-axis end point
		axis_vertex_buffer.push_back(glm::vec3(0, -mainAxisDomain, 0));	// negative y-axis end point
		axis_vertex_buffer.push_back(glm::vec3(0, mainAxisDomain, 0));  // positive y-axis end point
		axis_vertex_buffer.push_back(glm::vec3(0, 0, -mainAxisDomain));	// negative z-axis end point
		axis_vertex_buffer.push_back(glm::vec3(0, 0, mainAxisDomain));  // positive z-axis end point
	}
	else if (dimension == 2)
	{
		axis_vertex_buffer.push_back(glm::vec3(-mainAxisDomain, 0, 0));	// negative x-axis end point
		axis_vertex_buffer.push_back(glm::vec3(mainAxisDomain, 0, 0));  // positive x-axis end point
		axis_vertex_buffer.push_back(glm::vec3(0, -mainAxisDomain, 0));	// negative y-axis end point
		axis_vertex_buffer.push_back(glm::vec3(0, mainAxisDomain, 0));  // positive y-axis end point
	}
	else
	{
		axis_vertex_buffer.push_back(glm::vec3(-mainAxisDomain, 0, 0));	// negative x-axis end point
		axis_vertex_buffer.push_back(glm::vec3(mainAxisDomain, 0, 0));  // positive x-axis end point
		axis_vertex_buffer.push_back(glm::vec3(0, -TICK_SIZE_1D, 0));	// origin tick line negative end point
		axis_vertex_buffer.push_back(glm::vec3(0, TICK_SIZE_1D, 0));	// origin tick line positive end point
	}

	/* Set the vertex array object and vertex buffer object for the axis */
	if (!axis_vao)  glGenVertexArrays(1, &axis_vao);
	if (!axis_vbo)  glGenBuffers(1, &axis_vbo);

	/* Bind the vertex array and vertex buffer */
	glBindVertexArray(axis_vao);
	glBindBuffer(GL_ARRAY_BUFFER, axis_vbo);
	glBufferData(GL_ARRAY_BUFFER, axis_vertex_buffer.size() * sizeof(glm::vec3), &axis_vertex_buffer[0], GL_STATIC_DRAW);

	/* Set the vertex attribute array */
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

	/* Unbind the vertex array object */
	glBindVertexArray(0);
}

void Graphics::DrawAxis(void)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0)) * glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	glm::mat4 view, projection;
	if (dimension == 3)
	{
		view = camera3D.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera3D.zoom), aspect, 0.1f, 100.0f);
	}
	else
	{
		view = glm::mat4(1.0);
		projection = glm::ortho((-mainAxisDomain + camera2D.position.x) *camera2D.zoom /30.f * aspect,	// left
								 (mainAxisDomain + camera2D.position.x) *camera2D.zoom /30.f * aspect,	// right
								 (mainAxisDomain + camera2D.position.y) *camera2D.zoom /30.f,			// bottom
								(-mainAxisDomain + camera2D.position.y) *camera2D.zoom /30.f,			// top
								-1.0f, 1.0f);
	}

	basicLineShader->Bind();
	/* Set uniform location of each matrices */
	basicLineShader->SetUniformMatrix4fv("model", model);
	basicLineShader->SetUniformMatrix4fv("view", view);
	basicLineShader->SetUniformMatrix4fv("projection", projection);
	basicLineShader->SetUniform1i("sphere_index", 11); // 11 : default color = black

	glLineWidth(1.5f);

	/* render the axis line */
	glBindVertexArray(axis_vao);
	glDrawArrays(GL_LINES, 0, (GLsizei)axis_vertex_buffer.size());
	glBindVertexArray(0);

	glLineWidth(1.0f);
}

void Graphics::ShutdownAxisAndWalker(void)
{
	glDeleteVertexArrays(1, &axis_vao);
	glDeleteBuffers(1, &axis_vbo);

	for (int i = 0; i < NUM_OF_QUAD_IN_3D; ++i)
	{
		if (!axis_minor_vao[i])  glDeleteVertexArrays(1, &axis_minor_vao[i]);
		if (!axis_minor_vbo[i])  glDeleteBuffers(1, &axis_minor_vbo[i]);
	}
	
	for (int i = 0; i < numOfWalkers; ++i)
	{
		glDeleteVertexArrays(1, &track_vao[i]);
		glDeleteBuffers(1, &track_vbo[i]);
	}
	ShutdownShader();
}

void Graphics::SwapBuffers(void)
{
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
}

void Graphics::HandleKeyEvents(void)
{
	/* Poll for and process events */
	glfwPollEvents();
}

void Graphics::Shutdown()
{
	ShutdownAxisAndWalker();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Graphics::ProcessInput(char keycode, float deltaTime)
{
	if (dimension == 3)
	{
		if (keycode == 'W')
			camera3D.ProcessKeyboard(FORWARD, deltaTime, dimension);
		if (keycode == 'S')
			camera3D.ProcessKeyboard(BACKWARD, deltaTime, dimension);
		if (keycode == 'A')
			camera3D.ProcessKeyboard(LEFT, deltaTime, dimension);
		if (keycode == 'D')
			camera3D.ProcessKeyboard(RIGHT, deltaTime, dimension);
	}
	else
	{
		if (keycode == 'W')
			camera2D.ProcessKeyboard(FORWARD, deltaTime, dimension);
		if (keycode == 'S')
			camera2D.ProcessKeyboard(BACKWARD, deltaTime, dimension);
		if (keycode == 'A')
			camera2D.ProcessKeyboard(LEFT, deltaTime, dimension);
		if (keycode == 'D')
			camera2D.ProcessKeyboard(RIGHT, deltaTime, dimension);
	}
}

void Graphics::AddLog(char* newLog)
{
	log.append(newLog);
}

void Graphics::AddLog(std::string newLog)
{
	log.append(newLog);
}

void Graphics::AddResult(std::string newLog)
{
	result.append(newLog);
}

void Graphics::ClearOldLog(void)
{
	log.clear();
}

void Graphics::ClearOldResult(void)
{
	result.clear();
}

void Graphics::UpdateResult(void)
{
	switch (simulationId) {
	case 2:
		AddResult("[Numerical estimation of the distance from origin to endpoint of random walk]\n");
		for (int i = 0; i < numOfWalkers; ++i) {
			std::string index = std::to_string(i + 1);
			std::string distance = std::to_string(randomWalk.distance[i]);
			AddResult("Walker " + index + " : " + distance + "\n");
		}
		break;
	case 3:
		AddResult("[Numerical estimation of the number of steps until a random walk returns to the origin]\n");
		for (int i = 0; i < numOfWalkers; ++i) {
			std::string index = std::to_string(i + 1);
			if (randomWalk.returnedToOrigin[i]) {
				std::string steps = std::to_string(randomWalk.histories[i].size() - 1);
				AddResult("Walker " + index + " : " + steps + "\n");
			}
			else
				AddResult("Walker " + index + " : Failed to reach the origin\n");
		}
		break;
	case 4:
		AddResult("[Numerical estimation of the number of steps until two random walks intersect]\n");
		if (randomWalk.intersected) {
			std::string steps = std::to_string(randomWalk.histories[0].size() - 1);
			AddResult("Steps : " + steps + "\n");
		}
		else {
			AddResult("Walkers did not intersect with each other.\n");
			AddResult("All walkers are trapped in its trace.\n");
			AddResult("Or N fixed steps are done.\n");
		}
		break;
	case 5:
		AddResult("[Numerical estimation of the number of steps until two SAW intersect]\n");
		if (randomWalk.intersected) {
			for (int i = 0; i < numOfWalkers; ++i) {
				std::string index = std::to_string(i + 1);
				std::string steps = std::to_string(randomWalk.histories[i].size() - 1);
				AddResult("Walker " + index + " : " + steps + "\n");
			}
		}
		else {
			AddResult("Walkers did not intersect with each other.\n");
			AddResult("All walkers are trapped in its trace.\n");
			AddResult("Or N fixed steps are done.\n");
		}
		break;
	case 6:
		AddResult("[Counting the number of self avoiding walks]\n");
		for (int i = 0; i < numOfWalkers; ++i) {
			std::string index = std::to_string(i + 1);
			std::string steps = std::to_string(randomWalk.countOfSAW[i]);
			AddResult("Walker " + index + " : " + steps + "\n");
		}
		break;
	default:
		AddResult("No result for general simulation test.\n");
		AddResult("Try selecting another simulation type.\n");
		break;
	}
}

const char* Graphics::GetLog(void)
{
	return log.c_str();
}

const char* Graphics::GetResult(void)
{
	return result.c_str();
}

bool Graphics::GetLogChanged(void)
{
	return logChanged;
}

void Graphics::SetLogChanged(bool statement)
{
	logChanged = statement;
}

bool Graphics::GetResultChanged(void)
{
	return resultChanged;
}

void Graphics::SetResultChanged(bool statement)
{
	resultChanged = statement;
}

const std::vector<glm::vec3>& Graphics::GetWalkersPos(void)
{
	return initWalkersPos;
}

void Graphics::ToggleWalkerVisibility(int index)
{
	walkersVisibility[index] = !walkersVisibility[index];
}

const std::vector<int>& Graphics::GetCountOfPosNegMove(void)
{
	return countOfPosNegMove;
}

void Graphics::SetWalkerSpeed(int speedMultiplier)
{
	walkerSpeed = 0.04f * speedMultiplier;
}

void Graphics::SetCameraInitialPos(void)
{
	camera2D.position = glm::vec3(0.0f, 0.f, 30.f);
	camera2D.zoom = ZOOM;
	camera3D.position = glm::vec3(15.0f, 15.f, 15.f);
	camera3D.up = glm::vec3(-1.0f, 1.0f, -1.0f);
	camera3D.front = glm::vec3(-1.0f, -1.0f, -1.0f);
	camera3D.yaw = YAW;
	camera3D.pitch = PITCH;
	camera3D.zoom = ZOOM;
}

bool Graphics::CheckStringChanged(bool isItLog)
{
	if (isItLog) {
		if (oldLog.compare(log) == 0)
			logChanged = false;
		else
			logChanged = true;
		return logChanged;
	}
	else {
		if (oldResult.compare(result) == 0)
			resultChanged = false;
		else
			resultChanged = true;
		return resultChanged;
	}
}
#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "ObjLoader.h"
#include "RandomWalk.h"

#include <GLFW/glfw3.h>

namespace SimulationSection
{
#define MAX_NUM_OF_WALKERS 10
#define NUM_OF_QUAD_IN_3D 12
#define TICK_SIZE_1D 0.5f
#pragma region COLOR_MAP
#define COLOR_GOLD { 0.925781f, 0.796875f, 0.492187f }
#define COLOR_SKYBLUE { 0.066666f, 0.549019f, 0.807843f }
#define COLOR_PASTEL_RED { 0.97647f, 0.341176f, 0.356862f }
#define COLOR_PASTEL_ORANGE { 0.980392f, 0.623529f, 0.337254f }
#define COLOR_PASTEL_YELLOW { 0.984313f, 0.949019f, 0.333333f }
#define COLOR_PASTEL_GREEN { 0.349019f, 0.968627f, 0.443137f }
#define COLOR_PASTEL_BLUE { 0.349019f, 0.533333f, 0.968627f }
#define COLOR_PASTEL_NAVY { 0.168627f, 0.223529f, 0.741176f }
#define COLOR_PASTEL_PURPLE { 0.505882f, 0.317647f, 1.f }
#define COLOR_RED { 1.f, 0, 0 }
#define COLOR_ORANGE { 1.f, 0.411f, 0 }
#define COLOR_YELLOW { 1.f, 0.909f, 0 }
#define COLOR_LIGHT_GREEN { 0.643f, 1.f, 0 }
#define COLOR_GREEN { 0.352f, 1.f, 0 }
#define COLOR_MINT { 0, 1.f, 0.784f }
#define COLOR_LIGHT_BLUE { 0, 0.988f, 1 }
#define COLOR_AQUA_BLUE { 0, 0.643f, 1 }
#define COLOR_BLUE { 0, 0, 1 }
#define COLOR_DEEP_BLUE { 0.168f, 0.047f, 0.552f }
#define COLOR_LIGHT_PURPLE { 0.36f, 0, 1 }
#define COLOR_PURPLE { 0.631, 0, 1 }
#define COLOR_PINK { 1, 0, 0.764 }
#define COLOR_DEEP_PINK { 1, 0, 0.505 }
#define COLOR_LIGHT_GRAY { 0.752f, 0.752f, 0.749f }
#define COLOR_GRAY { 0.411f, 0.415f, 0.407f }
#define COLOR_BLACK { 0, 0, 0 }
#define COLOR_WHITE { 1, 1, 1 }
#define COLOR_DARKRED { 0.427450f, 0.070588f, 0 }
#pragma endregion

	public class Graphics
	{
	private:
		static Graphics* _instance;
		GLFWwindow* window;
		HWND glfwHWND;
		Shader *basicShader, *basicLineShader;
		std::vector<Model> spheres;
		std::vector<glm::vec3> initWalkersPos;
		std::vector<bool> walkersVisibility;
		/*	0: +1(x)
			1: -1(x)
			2: +1(y)
			3: -1(y)
			4: +1(z)
			5: -1(z) */
		std::vector<int> countOfPosNegMove;
		int numOfWalkers;
		float walkerSpeed;
		std::vector<int> walkersDir;
		CalculationSection::RandomWalk randomWalk;
		bool oneStepMoved;
		glm::vec3 dir[MAX_NUM_OF_WALKERS];
		bool dirCalculated[MAX_NUM_OF_WALKERS];
		std::string log, result;
		std::string oldLog, oldResult;
		bool logChanged, resultChanged;
		bool isAppFirstStarted;
		int walkerStepSize, walkerStepCount;
		bool walkerStepInfinite;
		
		/* set the vertex buffer for the axis line */
		std::vector<glm::vec3> axis_vertex_buffer;
		unsigned int axis_vao, axis_vbo;

		/* set the vertex buffer for the minor axis line
			0 - perpendicular to xz-plane and have positive x-value
			1 - perpendicular to xz-plane and have negative x-value
			2 - perpendicular to xy-plane and have positive x-value
			3 - perpendicular to xy-plane and have negative x-value
			4 - perpendicular to yz-plane and have positive y-value
			5 - perpendicular to yz-plane and have negative y-value
			6 - perpendicular to yx-plane and have positive y-value
			7 - perpendicular to yx-plane and have negative y-value
			8 - perpendicular to zy-plane and have positive z-value
			9 - perpendicular to zy-plane and have negative z-value
		   10 - perpendicular to zx-plane and have positive z-value
		   11 - perpendicular to zx-plane and have negative z-value
		*/
		std::vector<glm::vec3> axis_minor_vertex_buffer[NUM_OF_QUAD_IN_3D];
		unsigned int axis_minor_vao[NUM_OF_QUAD_IN_3D], axis_minor_vbo[NUM_OF_QUAD_IN_3D];

		/* set the vertex buffer for the track line */
		std::vector<glm::vec3> track_vertex_buffer[MAX_NUM_OF_WALKERS];
		unsigned int track_vao[MAX_NUM_OF_WALKERS], track_vbo[MAX_NUM_OF_WALKERS];

	public:
		static int width, height;
		static bool firstMouse;
		static float lastX, lastY;
		float aspect;
		static Camera camera3D;
		static Camera camera2D;
		bool isSimulationPlaying, isSimulationChanged;
		int mainAxisDomain, minorAxisInterval;
		int simulationId;
		static int dimension;
		bool chartUpdate;

	private:
		Graphics(void) {}
		void InitShader(void);
		void ShutdownShader(void);
		void InitAxis(void);
		void DrawAxis(void);
		void ShutdownAxisAndWalker(void);
		void InitMinorAxis(void);
		void DrawMinorAxis(void);
		void InitModels(void);
		void DrawModels(void);
		glm::vec3 GetSphereColor(int sphere_index);
		void DrawSimulationStatus(void);
		void AddLog(char* newLog);
		void AddLog(std::string newLog);
		void AddResult(std::string newLog);
		void ClearOldLog(void);
		void ClearOldResult(void);
		void UpdateResult(void);
		bool CheckStringChanged(bool isItLog);

	public:
		~Graphics(void) {}
		int Init(void);
		void Shutdown(void);
		void InitRandomSimulationStatus(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier);
		void InitGivenSimulationStatus(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier, const std::vector<glm::vec3>& init_walkers_pos);
		void UpdateSimulationStatus(void);
		void ClearSimulation(void);
		void RewindOneFrame(void);
		void PlayOneFrame(void);
		void Render(void);
		void SwapBuffers(void);
		void HandleKeyEvents(void);
		void ProcessInput(char keycode, float deltaTime);
		HWND GetHandle(void);
		const char* GetLog(void);
		const char* GetResult(void);
		bool GetLogChanged(void);
		void SetLogChanged(bool statement);
		bool GetResultChanged(void);
		void SetResultChanged(bool statement);
		const std::vector<glm::vec3>& GetWalkersPos(void);
		void ToggleWalkerVisibility(int index);
		const std::vector<int>& GetCountOfPosNegMove(void);
		void SetWalkerSpeed(int speedMultiplier);
		void SetCameraInitialPos(void);

	public:
		static Graphics* instance(void);
		static void DestroyInstance(void);
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}

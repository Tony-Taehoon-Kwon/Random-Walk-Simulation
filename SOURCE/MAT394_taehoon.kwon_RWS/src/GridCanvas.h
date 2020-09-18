#pragma once

#include <windows.h>
#include "Graphics.h"

using namespace System::Windows::Forms;

namespace SimulationSection
{
	public ref class GridCanvas: public System::Windows::Forms::NativeWindow
	{
	private:
		static HWND m_hWND;
		static HWND m_parentHWND;
		HDC m_hDC;
		HGLRC m_hglrc;

	public:
		GridCanvas(System::Windows::Forms::Form^ parentForm);
		~GridCanvas(System::Void);

	public:
		static HWND getParentHWND(void);
		virtual System::Void Render(System::Void);
		System::Void SwapOpenGLBuffers(System::Void);
		void ProcessInput(char keycode, float deltaTime);
		void HandleKeyEvents(void);
		void Update(void);
		void NotifySimulationPlay(bool statement);
		void NotifySimulationChanged(void);
		void ChangeAxisDomain(int max_value);
		void ChangeMinorAxisInterval(int interval_value);
		void ChangeSimulationType(int simulation_id);
		void ChangeDimension(int dimension);
		void InitRandomSimulation(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier);
		void InitGivenSimulation(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier, const std::vector<glm::vec3>& init_walkers_pos);
		void ClearSimulation(void);
		void RewindOneFrame(void);
		void PlayOneFrame(void);
		const char* GetLog(void);
		const char* GetResult(void);
		bool GetLogChanged(void);
		void SetLogChanged(bool statement);
		bool GetResultChanged(void);
		void SetResultChanged(bool statement);
		const std::vector<glm::vec3>& GetWalkersPos(void);
		void ToggleWalkerVisibility(int index);
		bool GetChartUpdate(void);
		void SetChartUpdate(bool statement);
		const std::vector<int>& GetCountOfPosNegMove(void);
		void SetWalkerSpeed(int speedMultiplier);
	};
}
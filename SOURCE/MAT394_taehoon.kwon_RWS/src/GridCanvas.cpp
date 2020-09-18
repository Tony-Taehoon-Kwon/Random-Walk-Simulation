#include "GridCanvas.h"

using namespace SimulationSection;

GridCanvas::GridCanvas(System::Windows::Forms::Form^ parentForm)
{	
	m_parentHWND = (HWND)parentForm->Handle.ToPointer();
	
	/* Initialize the glfw and create child window */
	Graphics::instance()->Init();
}

GridCanvas::~GridCanvas(System::Void)
{
	Graphics::instance()->Shutdown();
	Graphics::instance()->DestroyInstance();
	this->DestroyHandle();
}

HWND GridCanvas::getParentHWND(void)
{
	return m_parentHWND;
}

void GridCanvas::NotifySimulationPlay(bool statement)
{
	Graphics::instance()->isSimulationPlaying = statement;
}

void GridCanvas::NotifySimulationChanged(void)
{
	Graphics::instance()->isSimulationChanged = true;
}

void GridCanvas::ChangeAxisDomain(int max_value)
{
	Graphics::instance()->mainAxisDomain = max_value;
}

void GridCanvas::ChangeMinorAxisInterval(int interval_value)
{
	Graphics::instance()->minorAxisInterval = interval_value;
}

void GridCanvas::ChangeSimulationType(int simulation_id)
{
	Graphics::instance()->simulationId = simulation_id;
}

void GridCanvas::ChangeDimension(int dimension)
{
	Graphics::instance()->dimension = dimension;
	Graphics::instance()->SetCameraInitialPos();
}

void GridCanvas::InitRandomSimulation(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier)
{
	Graphics::instance()->InitRandomSimulationStatus(walker_num, stepSize, stepCount, infiniteStep, speedMultiplier);
}

void GridCanvas::InitGivenSimulation(int walker_num, int stepSize, int stepCount, bool infiniteStep, int speedMultiplier, const std::vector<glm::vec3>& init_walkers_pos)
{
	Graphics::instance()->InitGivenSimulationStatus(walker_num, stepSize, stepCount, infiniteStep, speedMultiplier, init_walkers_pos);
}

void GridCanvas::ClearSimulation(void)
{
	Graphics::instance()->ClearSimulation();
}

void GridCanvas::RewindOneFrame(void)
{
	Graphics::instance()->RewindOneFrame();
}

void GridCanvas::PlayOneFrame(void)
{
	Graphics::instance()->PlayOneFrame();
}

void GridCanvas::Update(void)
{
	Graphics::instance()->UpdateSimulationStatus();
}

System::Void GridCanvas::Render(System::Void)
{
	Graphics::instance()->Render();
}

System::Void GridCanvas::SwapOpenGLBuffers(System::Void)
{
	Graphics::instance()->SwapBuffers();
}

void GridCanvas::ProcessInput(char keycode, float deltaTime)
{
	Graphics::instance()->ProcessInput(keycode, deltaTime);
}

void GridCanvas::HandleKeyEvents(void)
{
	Graphics::instance()->HandleKeyEvents();
}

const char* GridCanvas::GetLog(void)
{
	return Graphics::instance()->GetLog();
}

const char* GridCanvas::GetResult(void)
{
	return Graphics::instance()->GetResult();
}

bool GridCanvas::GetLogChanged(void)
{
	return Graphics::instance()->GetLogChanged();
}

void GridCanvas::SetLogChanged(bool statement)
{
	Graphics::instance()->SetLogChanged(statement);
}

bool GridCanvas::GetResultChanged(void)
{
	return Graphics::instance()->GetResultChanged();
}

void GridCanvas::SetResultChanged(bool statement)
{
	Graphics::instance()->SetResultChanged(statement);
}

const std::vector<glm::vec3>& GridCanvas::GetWalkersPos(void)
{
	return Graphics::instance()->GetWalkersPos();
}

void GridCanvas::ToggleWalkerVisibility(int index)
{
	Graphics::instance()->ToggleWalkerVisibility(index);
}

bool GridCanvas::GetChartUpdate(void)
{
	return Graphics::instance()->chartUpdate;
}

void GridCanvas::SetChartUpdate(bool statement)
{
	Graphics::instance()->chartUpdate = statement;
}

const std::vector<int>& GridCanvas::GetCountOfPosNegMove(void)
{
	return Graphics::instance()->GetCountOfPosNegMove();
}

void GridCanvas::SetWalkerSpeed(int speedMultiplier)
{
	Graphics::instance()->SetWalkerSpeed(speedMultiplier);
}
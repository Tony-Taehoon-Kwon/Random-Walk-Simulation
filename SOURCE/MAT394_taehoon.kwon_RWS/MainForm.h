#pragma once

#include "src/GridCanvas.h"
#include "src/Debug.h"

namespace MAT394taehoonkwonRWS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	using namespace SimulationSection;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			DEBUG_CREATE_CONSOLE();
			canvas = gcnew GridCanvas(this);
			isPlaying = false;
			walkers_num = 10;
			dimension = 3;
			step_size = 1;
			step_count = 100;
			minorAxisInterval = 1;
			quickInstructionTimeInterval = 0;
			quickInstructionIndex = 1;
			initQuickInstruction();
			loadChart();
			updateWalkersPositionValue();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			DEBUG_DESTROY_CONSOLE();
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:
	private: System::Windows::Forms::Timer^ timer1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		GridCanvas^ canvas;
		float deltaTime, lastFrame;
		bool isPlaying;
		int walkers_num;
		int dimension;
		int step_size;
		int step_count;
		int minorAxisInterval;
		float quickInstructionTimeInterval;
		int quickInstructionIndex;
		Generic::List<System::String^> tip;
		Generic::List<System::String^> axisLabelList;

	private: System::Windows::Forms::TabControl^ controlPanel;

	private: System::Windows::Forms::TabPage^ Configuration;
	private: System::Windows::Forms::TabPage^ Log;
	private: System::Windows::Forms::TrackBar^ walkersNumTrackBar;

	private: System::Windows::Forms::TextBox^ simulationTypeText;
	private: System::Windows::Forms::RadioButton^ threeDimRadioButton;
	private: System::Windows::Forms::RadioButton^ twoDimRadioButton;
	private: System::Windows::Forms::RadioButton^ oneDimRadioButton;
	private: System::Windows::Forms::TextBox^ dimensionText;
	private: System::Windows::Forms::TextBox^ numOfWalkersTitleText;
	private: System::Windows::Forms::ComboBox^ simulationTypeComboBox;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ playFrameButton;

	private: System::Windows::Forms::Button^ stopButton;

	private: System::Windows::Forms::Button^ playButton;

	private: System::Windows::Forms::Button^ rewindButton;
	private: System::Windows::Forms::ImageList^ imageList1;

	private: System::Windows::Forms::RichTextBox^ logTextBox;
	private: System::Windows::Forms::TextBox^ axisDomainTitleText;

	private: System::Windows::Forms::TrackBar^ axisDomainTrackBar;
	private: System::Windows::Forms::TextBox^ axisDomainValueText;
	private: System::Windows::Forms::TextBox^ numOfWalkersValueText;
	private: System::Windows::Forms::TextBox^ minorAxisIntervalValueText;

	private: System::Windows::Forms::TextBox^ minorAxisIntervalTitleText;
	private: System::Windows::Forms::TrackBar^ minorAxisIntervalTrackBar;

	private: System::Windows::Forms::Label^ walkersTitleLabel1;
	private: System::Windows::Forms::Label^ walkersXLabel1;
	private: System::Windows::Forms::Label^ walkersYLabel1;
	private: System::Windows::Forms::Label^ walkersZLabel1;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown1;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown1;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown1;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox1;

	private: System::Windows::Forms::Label^ walkersTitleLabel2;
	private: System::Windows::Forms::Label^ walkersXLabel2;
	private: System::Windows::Forms::Label^ walkersYLabel2;
	private: System::Windows::Forms::Label^ walkersZLabel2;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown2;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown2;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown2;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox2;

	private: System::Windows::Forms::Label^ walkersTitleLabel3;
	private: System::Windows::Forms::Label^ walkersXLabel3;
	private: System::Windows::Forms::Label^ walkersYLabel3;
	private: System::Windows::Forms::Label^ walkersZLabel3;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown3;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown3;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown3;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox3;

	private: System::Windows::Forms::Label^ walkersTitleLabel4;
	private: System::Windows::Forms::Label^ walkersXLabel4;
	private: System::Windows::Forms::Label^ walkersYLabel4;
	private: System::Windows::Forms::Label^ walkersZLabel4;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown4;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown4;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown4;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox4;

	private: System::Windows::Forms::Label^ walkersTitleLabel5;
	private: System::Windows::Forms::Label^ walkersXLabel5;
	private: System::Windows::Forms::Label^ walkersYLabel5;
	private: System::Windows::Forms::Label^ walkersZLabel5;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown5;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown5;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown5;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox5;

	private: System::Windows::Forms::Label^ walkersTitleLabel6;
	private: System::Windows::Forms::Label^ walkersXLabel6;
	private: System::Windows::Forms::Label^ walkersYLabel6;
	private: System::Windows::Forms::Label^ walkersZLabel6;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown6;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown6;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown6;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox6;

	private: System::Windows::Forms::Label^ walkersTitleLabel7;
	private: System::Windows::Forms::Label^ walkersXLabel7;
	private: System::Windows::Forms::Label^ walkersYLabel7;
	private: System::Windows::Forms::Label^ walkersZLabel7;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown7;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown7;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown7;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox7;

	private: System::Windows::Forms::Label^ walkersTitleLabel8;
	private: System::Windows::Forms::Label^ walkersXLabel8;
	private: System::Windows::Forms::Label^ walkersYLabel8;
	private: System::Windows::Forms::Label^ walkersZLabel8;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown8;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown8;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown8;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox8;

	private: System::Windows::Forms::Label^ walkersTitleLabel9;
	private: System::Windows::Forms::Label^ walkersXLabel9;
	private: System::Windows::Forms::Label^ walkersYLabel9;
	private: System::Windows::Forms::Label^ walkersZLabel9;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown9;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown9;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown9;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox9;

	private: System::Windows::Forms::Label^ walkersTitleLabel10;
	private: System::Windows::Forms::Label^ walkersXLabel10;
	private: System::Windows::Forms::Label^ walkersYLabel10;
	private: System::Windows::Forms::Label^ walkersZLabel10;
	private: System::Windows::Forms::NumericUpDown^ walkersXnumUpDown10;
	private: System::Windows::Forms::NumericUpDown^ walkersYnumUpDown10;
	private: System::Windows::Forms::NumericUpDown^ walkersZnumUpDown10;
	private: System::Windows::Forms::CheckBox^ walkersHideCheckBox10;
	
	private: System::Windows::Forms::Button^ buildRandPosSimulationButton;
	private: System::Windows::Forms::Button^ buildGivenPosSimulationButton;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::TextBox^ speedOfWalkersValueText;
	private: System::Windows::Forms::TextBox^ speedOfWalkersTitleText;
	private: System::Windows::Forms::TrackBar^ walkersSpeedTrackBar;
	private: System::Windows::Forms::CheckBox^ infiniteStepCheckBox;
	private: System::Windows::Forms::NumericUpDown^ stepCountUpDown;
	private: System::Windows::Forms::TextBox^ stepCountText;
	private: System::Windows::Forms::NumericUpDown^ stepSizeUpDown;
	private: System::Windows::Forms::TextBox^ stepSizeText;
	private: System::Windows::Forms::TabPage^ Result;
	private: System::Windows::Forms::RichTextBox^ resultTextBox;
	private: System::Windows::Forms::CheckBox^ minorAxisHideCheckBox;
private: System::Windows::Forms::TabPage^ HowToRun;
private: System::Windows::Forms::RichTextBox^ howToRunTextBox;
private: System::Windows::Forms::RichTextBox^ quickInstructionTextBox;
private: System::Windows::Forms::CheckBox^ hideTipCheckBox;

	private: System::Windows::Forms::TabPage^ Statistics;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->components = (gcnew System::ComponentModel::Container());
		System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
		System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
		System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::Windows::Forms::DataVisualization::Charting::Series^ series6 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
		this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
		this->controlPanel = (gcnew System::Windows::Forms::TabControl());
		this->Configuration = (gcnew System::Windows::Forms::TabPage());
		this->hideTipCheckBox = (gcnew System::Windows::Forms::CheckBox());
		this->minorAxisHideCheckBox = (gcnew System::Windows::Forms::CheckBox());
		this->infiniteStepCheckBox = (gcnew System::Windows::Forms::CheckBox());
		this->stepCountUpDown = (gcnew System::Windows::Forms::NumericUpDown());
		this->stepCountText = (gcnew System::Windows::Forms::TextBox());
		this->stepSizeUpDown = (gcnew System::Windows::Forms::NumericUpDown());
		this->stepSizeText = (gcnew System::Windows::Forms::TextBox());
		this->speedOfWalkersValueText = (gcnew System::Windows::Forms::TextBox());
		this->speedOfWalkersTitleText = (gcnew System::Windows::Forms::TextBox());
		this->walkersSpeedTrackBar = (gcnew System::Windows::Forms::TrackBar());
		this->walkersZnumUpDown10 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown10 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown10 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown9 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown9 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown9 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown8 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown8 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown8 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown6 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown5 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersZnumUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersYnumUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersXnumUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
		this->walkersHideCheckBox10 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox9 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox8 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox7 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox6 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox5 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox4 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox3 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox2 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersHideCheckBox1 = (gcnew System::Windows::Forms::CheckBox());
		this->walkersTitleLabel10 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel10 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel10 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel10 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel9 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel9 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel9 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel9 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel8 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel8 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel8 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel8 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel7 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel7 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel7 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel7 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel6 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel6 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel6 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel6 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel5 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel5 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel5 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel5 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel4 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel4 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel4 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel4 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel3 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel3 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel3 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel3 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel1 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel1 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel1 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel1 = (gcnew System::Windows::Forms::Label());
		this->walkersTitleLabel2 = (gcnew System::Windows::Forms::Label());
		this->walkersXLabel2 = (gcnew System::Windows::Forms::Label());
		this->walkersYLabel2 = (gcnew System::Windows::Forms::Label());
		this->walkersZLabel2 = (gcnew System::Windows::Forms::Label());
		this->minorAxisIntervalValueText = (gcnew System::Windows::Forms::TextBox());
		this->minorAxisIntervalTitleText = (gcnew System::Windows::Forms::TextBox());
		this->minorAxisIntervalTrackBar = (gcnew System::Windows::Forms::TrackBar());
		this->numOfWalkersValueText = (gcnew System::Windows::Forms::TextBox());
		this->axisDomainValueText = (gcnew System::Windows::Forms::TextBox());
		this->axisDomainTitleText = (gcnew System::Windows::Forms::TextBox());
		this->axisDomainTrackBar = (gcnew System::Windows::Forms::TrackBar());
		this->simulationTypeComboBox = (gcnew System::Windows::Forms::ComboBox());
		this->numOfWalkersTitleText = (gcnew System::Windows::Forms::TextBox());
		this->dimensionText = (gcnew System::Windows::Forms::TextBox());
		this->threeDimRadioButton = (gcnew System::Windows::Forms::RadioButton());
		this->twoDimRadioButton = (gcnew System::Windows::Forms::RadioButton());
		this->oneDimRadioButton = (gcnew System::Windows::Forms::RadioButton());
		this->walkersNumTrackBar = (gcnew System::Windows::Forms::TrackBar());
		this->simulationTypeText = (gcnew System::Windows::Forms::TextBox());
		this->Log = (gcnew System::Windows::Forms::TabPage());
		this->logTextBox = (gcnew System::Windows::Forms::RichTextBox());
		this->Statistics = (gcnew System::Windows::Forms::TabPage());
		this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
		this->Result = (gcnew System::Windows::Forms::TabPage());
		this->resultTextBox = (gcnew System::Windows::Forms::RichTextBox());
		this->HowToRun = (gcnew System::Windows::Forms::TabPage());
		this->howToRunTextBox = (gcnew System::Windows::Forms::RichTextBox());
		this->panel1 = (gcnew System::Windows::Forms::Panel());
		this->playFrameButton = (gcnew System::Windows::Forms::Button());
		this->stopButton = (gcnew System::Windows::Forms::Button());
		this->playButton = (gcnew System::Windows::Forms::Button());
		this->rewindButton = (gcnew System::Windows::Forms::Button());
		this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
		this->buildRandPosSimulationButton = (gcnew System::Windows::Forms::Button());
		this->buildGivenPosSimulationButton = (gcnew System::Windows::Forms::Button());
		this->quickInstructionTextBox = (gcnew System::Windows::Forms::RichTextBox());
		this->controlPanel->SuspendLayout();
		this->Configuration->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepCountUpDown))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepSizeUpDown))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersSpeedTrackBar))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown10))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown10))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown10))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown9))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown9))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown9))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown8))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown8))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown8))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown7))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown7))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown7))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown6))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown6))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown6))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown5))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown5))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown5))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown4))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown4))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown4))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown3))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown3))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown3))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown2))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown2))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown2))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minorAxisIntervalTrackBar))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axisDomainTrackBar))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersNumTrackBar))->BeginInit();
		this->Log->SuspendLayout();
		this->Statistics->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
		this->Result->SuspendLayout();
		this->HowToRun->SuspendLayout();
		this->panel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// timer1
		// 
		this->timer1->Enabled = true;
		this->timer1->Interval = 20;
		this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
		// 
		// controlPanel
		// 
		this->controlPanel->Controls->Add(this->Configuration);
		this->controlPanel->Controls->Add(this->Log);
		this->controlPanel->Controls->Add(this->Statistics);
		this->controlPanel->Controls->Add(this->Result);
		this->controlPanel->Controls->Add(this->HowToRun);
		this->controlPanel->ItemSize = System::Drawing::Size(85, 18);
		this->controlPanel->Location = System::Drawing::Point(950, 78);
		this->controlPanel->Name = L"controlPanel";
		this->controlPanel->SelectedIndex = 0;
		this->controlPanel->Size = System::Drawing::Size(450, 544);
		this->controlPanel->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
		this->controlPanel->TabIndex = 1;
		this->controlPanel->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// Configuration
		// 
		this->Configuration->AutoScroll = true;
		this->Configuration->AutoScrollMinSize = System::Drawing::Size(0, 980);
		this->Configuration->Controls->Add(this->hideTipCheckBox);
		this->Configuration->Controls->Add(this->minorAxisHideCheckBox);
		this->Configuration->Controls->Add(this->infiniteStepCheckBox);
		this->Configuration->Controls->Add(this->stepCountUpDown);
		this->Configuration->Controls->Add(this->stepCountText);
		this->Configuration->Controls->Add(this->stepSizeUpDown);
		this->Configuration->Controls->Add(this->stepSizeText);
		this->Configuration->Controls->Add(this->speedOfWalkersValueText);
		this->Configuration->Controls->Add(this->speedOfWalkersTitleText);
		this->Configuration->Controls->Add(this->walkersSpeedTrackBar);
		this->Configuration->Controls->Add(this->walkersZnumUpDown10);
		this->Configuration->Controls->Add(this->walkersYnumUpDown10);
		this->Configuration->Controls->Add(this->walkersXnumUpDown10);
		this->Configuration->Controls->Add(this->walkersZnumUpDown9);
		this->Configuration->Controls->Add(this->walkersYnumUpDown9);
		this->Configuration->Controls->Add(this->walkersXnumUpDown9);
		this->Configuration->Controls->Add(this->walkersZnumUpDown8);
		this->Configuration->Controls->Add(this->walkersYnumUpDown8);
		this->Configuration->Controls->Add(this->walkersXnumUpDown8);
		this->Configuration->Controls->Add(this->walkersZnumUpDown7);
		this->Configuration->Controls->Add(this->walkersYnumUpDown7);
		this->Configuration->Controls->Add(this->walkersXnumUpDown7);
		this->Configuration->Controls->Add(this->walkersZnumUpDown6);
		this->Configuration->Controls->Add(this->walkersYnumUpDown6);
		this->Configuration->Controls->Add(this->walkersXnumUpDown6);
		this->Configuration->Controls->Add(this->walkersZnumUpDown5);
		this->Configuration->Controls->Add(this->walkersYnumUpDown5);
		this->Configuration->Controls->Add(this->walkersXnumUpDown5);
		this->Configuration->Controls->Add(this->walkersZnumUpDown4);
		this->Configuration->Controls->Add(this->walkersYnumUpDown4);
		this->Configuration->Controls->Add(this->walkersXnumUpDown4);
		this->Configuration->Controls->Add(this->walkersZnumUpDown3);
		this->Configuration->Controls->Add(this->walkersYnumUpDown3);
		this->Configuration->Controls->Add(this->walkersXnumUpDown3);
		this->Configuration->Controls->Add(this->walkersZnumUpDown2);
		this->Configuration->Controls->Add(this->walkersYnumUpDown2);
		this->Configuration->Controls->Add(this->walkersXnumUpDown2);
		this->Configuration->Controls->Add(this->walkersZnumUpDown1);
		this->Configuration->Controls->Add(this->walkersYnumUpDown1);
		this->Configuration->Controls->Add(this->walkersXnumUpDown1);
		this->Configuration->Controls->Add(this->walkersHideCheckBox10);
		this->Configuration->Controls->Add(this->walkersHideCheckBox9);
		this->Configuration->Controls->Add(this->walkersHideCheckBox8);
		this->Configuration->Controls->Add(this->walkersHideCheckBox7);
		this->Configuration->Controls->Add(this->walkersHideCheckBox6);
		this->Configuration->Controls->Add(this->walkersHideCheckBox5);
		this->Configuration->Controls->Add(this->walkersHideCheckBox4);
		this->Configuration->Controls->Add(this->walkersHideCheckBox3);
		this->Configuration->Controls->Add(this->walkersHideCheckBox2);
		this->Configuration->Controls->Add(this->walkersHideCheckBox1);
		this->Configuration->Controls->Add(this->walkersTitleLabel10);
		this->Configuration->Controls->Add(this->walkersXLabel10);
		this->Configuration->Controls->Add(this->walkersYLabel10);
		this->Configuration->Controls->Add(this->walkersZLabel10);
		this->Configuration->Controls->Add(this->walkersTitleLabel9);
		this->Configuration->Controls->Add(this->walkersXLabel9);
		this->Configuration->Controls->Add(this->walkersYLabel9);
		this->Configuration->Controls->Add(this->walkersZLabel9);
		this->Configuration->Controls->Add(this->walkersTitleLabel8);
		this->Configuration->Controls->Add(this->walkersXLabel8);
		this->Configuration->Controls->Add(this->walkersYLabel8);
		this->Configuration->Controls->Add(this->walkersZLabel8);
		this->Configuration->Controls->Add(this->walkersTitleLabel7);
		this->Configuration->Controls->Add(this->walkersXLabel7);
		this->Configuration->Controls->Add(this->walkersYLabel7);
		this->Configuration->Controls->Add(this->walkersZLabel7);
		this->Configuration->Controls->Add(this->walkersTitleLabel6);
		this->Configuration->Controls->Add(this->walkersXLabel6);
		this->Configuration->Controls->Add(this->walkersYLabel6);
		this->Configuration->Controls->Add(this->walkersZLabel6);
		this->Configuration->Controls->Add(this->walkersTitleLabel5);
		this->Configuration->Controls->Add(this->walkersXLabel5);
		this->Configuration->Controls->Add(this->walkersYLabel5);
		this->Configuration->Controls->Add(this->walkersZLabel5);
		this->Configuration->Controls->Add(this->walkersTitleLabel4);
		this->Configuration->Controls->Add(this->walkersXLabel4);
		this->Configuration->Controls->Add(this->walkersYLabel4);
		this->Configuration->Controls->Add(this->walkersZLabel4);
		this->Configuration->Controls->Add(this->walkersTitleLabel3);
		this->Configuration->Controls->Add(this->walkersXLabel3);
		this->Configuration->Controls->Add(this->walkersYLabel3);
		this->Configuration->Controls->Add(this->walkersZLabel3);
		this->Configuration->Controls->Add(this->walkersTitleLabel1);
		this->Configuration->Controls->Add(this->walkersXLabel1);
		this->Configuration->Controls->Add(this->walkersYLabel1);
		this->Configuration->Controls->Add(this->walkersZLabel1);
		this->Configuration->Controls->Add(this->walkersTitleLabel2);
		this->Configuration->Controls->Add(this->walkersXLabel2);
		this->Configuration->Controls->Add(this->walkersYLabel2);
		this->Configuration->Controls->Add(this->walkersZLabel2);
		this->Configuration->Controls->Add(this->minorAxisIntervalValueText);
		this->Configuration->Controls->Add(this->minorAxisIntervalTitleText);
		this->Configuration->Controls->Add(this->minorAxisIntervalTrackBar);
		this->Configuration->Controls->Add(this->numOfWalkersValueText);
		this->Configuration->Controls->Add(this->axisDomainValueText);
		this->Configuration->Controls->Add(this->axisDomainTitleText);
		this->Configuration->Controls->Add(this->axisDomainTrackBar);
		this->Configuration->Controls->Add(this->simulationTypeComboBox);
		this->Configuration->Controls->Add(this->numOfWalkersTitleText);
		this->Configuration->Controls->Add(this->dimensionText);
		this->Configuration->Controls->Add(this->threeDimRadioButton);
		this->Configuration->Controls->Add(this->twoDimRadioButton);
		this->Configuration->Controls->Add(this->oneDimRadioButton);
		this->Configuration->Controls->Add(this->walkersNumTrackBar);
		this->Configuration->Controls->Add(this->simulationTypeText);
		this->Configuration->Location = System::Drawing::Point(4, 22);
		this->Configuration->Name = L"Configuration";
		this->Configuration->Padding = System::Windows::Forms::Padding(3);
		this->Configuration->Size = System::Drawing::Size(442, 518);
		this->Configuration->TabIndex = 0;
		this->Configuration->Text = L"Configuration";
		this->Configuration->UseVisualStyleBackColor = true;
		// 
		// hideTipCheckBox
		// 
		this->hideTipCheckBox->AutoSize = true;
		this->hideTipCheckBox->Location = System::Drawing::Point(24, 940);
		this->hideTipCheckBox->Name = L"hideTipCheckBox";
		this->hideTipCheckBox->Size = System::Drawing::Size(226, 16);
		this->hideTipCheckBox->TabIndex = 135;
		this->hideTipCheckBox->Text = L"Hide the quick instruction on the top";
		this->hideTipCheckBox->UseVisualStyleBackColor = true;
		this->hideTipCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::hideTipCheckBox_CheckedChanged);
		// 
		// minorAxisHideCheckBox
		// 
		this->minorAxisHideCheckBox->AutoSize = true;
		this->minorAxisHideCheckBox->Enabled = false;
		this->minorAxisHideCheckBox->Location = System::Drawing::Point(297, 292);
		this->minorAxisHideCheckBox->Name = L"minorAxisHideCheckBox";
		this->minorAxisHideCheckBox->Size = System::Drawing::Size(48, 16);
		this->minorAxisHideCheckBox->TabIndex = 134;
		this->minorAxisHideCheckBox->Text = L"hide";
		this->minorAxisHideCheckBox->UseVisualStyleBackColor = true;
		this->minorAxisHideCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::minorAxisHideCheckBox_CheckedChanged);
		// 
		// infiniteStepCheckBox
		// 
		this->infiniteStepCheckBox->AutoSize = true;
		this->infiniteStepCheckBox->Checked = true;
		this->infiniteStepCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
		this->infiniteStepCheckBox->Location = System::Drawing::Point(250, 165);
		this->infiniteStepCheckBox->Name = L"infiniteStepCheckBox";
		this->infiniteStepCheckBox->Size = System::Drawing::Size(88, 16);
		this->infiniteStepCheckBox->TabIndex = 133;
		this->infiniteStepCheckBox->Text = L"infinite step";
		this->infiniteStepCheckBox->UseVisualStyleBackColor = true;
		this->infiniteStepCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::infiniteStepCheckBox_CheckedChanged);
		// 
		// stepCountUpDown
		// 
		this->stepCountUpDown->Enabled = false;
		this->stepCountUpDown->Location = System::Drawing::Point(163, 164);
		this->stepCountUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
		this->stepCountUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->stepCountUpDown->Name = L"stepCountUpDown";
		this->stepCountUpDown->Size = System::Drawing::Size(70, 21);
		this->stepCountUpDown->TabIndex = 132;
		this->stepCountUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
		this->stepCountUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::stepCountUpDown_ValueChanged);
		// 
		// stepCountText
		// 
		this->stepCountText->BackColor = System::Drawing::SystemColors::Window;
		this->stepCountText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->stepCountText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->stepCountText->Location = System::Drawing::Point(24, 157);
		this->stepCountText->Name = L"stepCountText";
		this->stepCountText->ReadOnly = true;
		this->stepCountText->Size = System::Drawing::Size(111, 31);
		this->stepCountText->TabIndex = 131;
		this->stepCountText->Text = L"Step count";
		// 
		// stepSizeUpDown
		// 
		this->stepSizeUpDown->Location = System::Drawing::Point(163, 117);
		this->stepSizeUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
		this->stepSizeUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->stepSizeUpDown->Name = L"stepSizeUpDown";
		this->stepSizeUpDown->Size = System::Drawing::Size(70, 21);
		this->stepSizeUpDown->TabIndex = 130;
		this->stepSizeUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->stepSizeUpDown->ValueChanged += gcnew System::EventHandler(this, &MainForm::stepSizeUpDown_ValueChanged);
		// 
		// stepSizeText
		// 
		this->stepSizeText->BackColor = System::Drawing::SystemColors::Window;
		this->stepSizeText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->stepSizeText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->stepSizeText->Location = System::Drawing::Point(24, 110);
		this->stepSizeText->Name = L"stepSizeText";
		this->stepSizeText->ReadOnly = true;
		this->stepSizeText->Size = System::Drawing::Size(111, 31);
		this->stepSizeText->TabIndex = 129;
		this->stepSizeText->Text = L"Step size";
		// 
		// speedOfWalkersValueText
		// 
		this->speedOfWalkersValueText->BackColor = System::Drawing::SystemColors::Window;
		this->speedOfWalkersValueText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->speedOfWalkersValueText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->speedOfWalkersValueText->Location = System::Drawing::Point(264, 442);
		this->speedOfWalkersValueText->Name = L"speedOfWalkersValueText";
		this->speedOfWalkersValueText->ReadOnly = true;
		this->speedOfWalkersValueText->Size = System::Drawing::Size(57, 31);
		this->speedOfWalkersValueText->TabIndex = 128;
		this->speedOfWalkersValueText->Text = L"1";
		// 
		// speedOfWalkersTitleText
		// 
		this->speedOfWalkersTitleText->BackColor = System::Drawing::SystemColors::Window;
		this->speedOfWalkersTitleText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->speedOfWalkersTitleText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->speedOfWalkersTitleText->Location = System::Drawing::Point(24, 442);
		this->speedOfWalkersTitleText->Name = L"speedOfWalkersTitleText";
		this->speedOfWalkersTitleText->ReadOnly = true;
		this->speedOfWalkersTitleText->Size = System::Drawing::Size(234, 31);
		this->speedOfWalkersTitleText->TabIndex = 127;
		this->speedOfWalkersTitleText->Text = L"Speed of Walkers : ";
		// 
		// walkersSpeedTrackBar
		// 
		this->walkersSpeedTrackBar->BackColor = System::Drawing::SystemColors::Window;
		this->walkersSpeedTrackBar->Location = System::Drawing::Point(24, 479);
		this->walkersSpeedTrackBar->Minimum = 1;
		this->walkersSpeedTrackBar->Name = L"walkersSpeedTrackBar";
		this->walkersSpeedTrackBar->Size = System::Drawing::Size(344, 45);
		this->walkersSpeedTrackBar->TabIndex = 126;
		this->walkersSpeedTrackBar->Value = 1;
		this->walkersSpeedTrackBar->Scroll += gcnew System::EventHandler(this, &MainForm::walkersSpeedTrackBar_Scroll);
		// 
		// walkersZnumUpDown10
		// 
		this->walkersZnumUpDown10->Location = System::Drawing::Point(287, 901);
		this->walkersZnumUpDown10->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown10->Name = L"walkersZnumUpDown10";
		this->walkersZnumUpDown10->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown10->TabIndex = 125;
		// 
		// walkersYnumUpDown10
		// 
		this->walkersYnumUpDown10->Location = System::Drawing::Point(218, 901);
		this->walkersYnumUpDown10->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown10->Name = L"walkersYnumUpDown10";
		this->walkersYnumUpDown10->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown10->TabIndex = 124;
		// 
		// walkersXnumUpDown10
		// 
		this->walkersXnumUpDown10->Location = System::Drawing::Point(148, 901);
		this->walkersXnumUpDown10->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown10->Name = L"walkersXnumUpDown10";
		this->walkersXnumUpDown10->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown10->TabIndex = 123;
		// 
		// walkersZnumUpDown9
		// 
		this->walkersZnumUpDown9->Location = System::Drawing::Point(287, 860);
		this->walkersZnumUpDown9->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown9->Name = L"walkersZnumUpDown9";
		this->walkersZnumUpDown9->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown9->TabIndex = 122;
		// 
		// walkersYnumUpDown9
		// 
		this->walkersYnumUpDown9->Location = System::Drawing::Point(218, 860);
		this->walkersYnumUpDown9->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown9->Name = L"walkersYnumUpDown9";
		this->walkersYnumUpDown9->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown9->TabIndex = 121;
		// 
		// walkersXnumUpDown9
		// 
		this->walkersXnumUpDown9->Location = System::Drawing::Point(148, 860);
		this->walkersXnumUpDown9->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown9->Name = L"walkersXnumUpDown9";
		this->walkersXnumUpDown9->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown9->TabIndex = 120;
		// 
		// walkersZnumUpDown8
		// 
		this->walkersZnumUpDown8->Location = System::Drawing::Point(287, 822);
		this->walkersZnumUpDown8->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown8->Name = L"walkersZnumUpDown8";
		this->walkersZnumUpDown8->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown8->TabIndex = 119;
		// 
		// walkersYnumUpDown8
		// 
		this->walkersYnumUpDown8->Location = System::Drawing::Point(218, 822);
		this->walkersYnumUpDown8->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown8->Name = L"walkersYnumUpDown8";
		this->walkersYnumUpDown8->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown8->TabIndex = 118;
		// 
		// walkersXnumUpDown8
		// 
		this->walkersXnumUpDown8->Location = System::Drawing::Point(148, 822);
		this->walkersXnumUpDown8->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown8->Name = L"walkersXnumUpDown8";
		this->walkersXnumUpDown8->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown8->TabIndex = 117;
		// 
		// walkersZnumUpDown7
		// 
		this->walkersZnumUpDown7->Location = System::Drawing::Point(287, 781);
		this->walkersZnumUpDown7->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown7->Name = L"walkersZnumUpDown7";
		this->walkersZnumUpDown7->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown7->TabIndex = 116;
		// 
		// walkersYnumUpDown7
		// 
		this->walkersYnumUpDown7->Location = System::Drawing::Point(218, 781);
		this->walkersYnumUpDown7->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown7->Name = L"walkersYnumUpDown7";
		this->walkersYnumUpDown7->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown7->TabIndex = 115;
		// 
		// walkersXnumUpDown7
		// 
		this->walkersXnumUpDown7->Location = System::Drawing::Point(148, 781);
		this->walkersXnumUpDown7->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown7->Name = L"walkersXnumUpDown7";
		this->walkersXnumUpDown7->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown7->TabIndex = 114;
		// 
		// walkersZnumUpDown6
		// 
		this->walkersZnumUpDown6->Location = System::Drawing::Point(287, 741);
		this->walkersZnumUpDown6->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown6->Name = L"walkersZnumUpDown6";
		this->walkersZnumUpDown6->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown6->TabIndex = 113;
		// 
		// walkersYnumUpDown6
		// 
		this->walkersYnumUpDown6->Location = System::Drawing::Point(218, 741);
		this->walkersYnumUpDown6->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown6->Name = L"walkersYnumUpDown6";
		this->walkersYnumUpDown6->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown6->TabIndex = 112;
		// 
		// walkersXnumUpDown6
		// 
		this->walkersXnumUpDown6->Location = System::Drawing::Point(148, 741);
		this->walkersXnumUpDown6->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown6->Name = L"walkersXnumUpDown6";
		this->walkersXnumUpDown6->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown6->TabIndex = 111;
		// 
		// walkersZnumUpDown5
		// 
		this->walkersZnumUpDown5->Location = System::Drawing::Point(287, 700);
		this->walkersZnumUpDown5->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown5->Name = L"walkersZnumUpDown5";
		this->walkersZnumUpDown5->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown5->TabIndex = 110;
		// 
		// walkersYnumUpDown5
		// 
		this->walkersYnumUpDown5->Location = System::Drawing::Point(218, 700);
		this->walkersYnumUpDown5->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown5->Name = L"walkersYnumUpDown5";
		this->walkersYnumUpDown5->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown5->TabIndex = 109;
		// 
		// walkersXnumUpDown5
		// 
		this->walkersXnumUpDown5->Location = System::Drawing::Point(148, 700);
		this->walkersXnumUpDown5->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown5->Name = L"walkersXnumUpDown5";
		this->walkersXnumUpDown5->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown5->TabIndex = 108;
		// 
		// walkersZnumUpDown4
		// 
		this->walkersZnumUpDown4->Location = System::Drawing::Point(287, 661);
		this->walkersZnumUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown4->Name = L"walkersZnumUpDown4";
		this->walkersZnumUpDown4->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown4->TabIndex = 107;
		// 
		// walkersYnumUpDown4
		// 
		this->walkersYnumUpDown4->Location = System::Drawing::Point(218, 661);
		this->walkersYnumUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown4->Name = L"walkersYnumUpDown4";
		this->walkersYnumUpDown4->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown4->TabIndex = 106;
		// 
		// walkersXnumUpDown4
		// 
		this->walkersXnumUpDown4->Location = System::Drawing::Point(148, 661);
		this->walkersXnumUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown4->Name = L"walkersXnumUpDown4";
		this->walkersXnumUpDown4->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown4->TabIndex = 105;
		// 
		// walkersZnumUpDown3
		// 
		this->walkersZnumUpDown3->Location = System::Drawing::Point(287, 620);
		this->walkersZnumUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown3->Name = L"walkersZnumUpDown3";
		this->walkersZnumUpDown3->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown3->TabIndex = 104;
		// 
		// walkersYnumUpDown3
		// 
		this->walkersYnumUpDown3->Location = System::Drawing::Point(218, 620);
		this->walkersYnumUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown3->Name = L"walkersYnumUpDown3";
		this->walkersYnumUpDown3->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown3->TabIndex = 103;
		// 
		// walkersXnumUpDown3
		// 
		this->walkersXnumUpDown3->Location = System::Drawing::Point(148, 620);
		this->walkersXnumUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown3->Name = L"walkersXnumUpDown3";
		this->walkersXnumUpDown3->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown3->TabIndex = 102;
		// 
		// walkersZnumUpDown2
		// 
		this->walkersZnumUpDown2->Location = System::Drawing::Point(287, 580);
		this->walkersZnumUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown2->Name = L"walkersZnumUpDown2";
		this->walkersZnumUpDown2->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown2->TabIndex = 101;
		// 
		// walkersYnumUpDown2
		// 
		this->walkersYnumUpDown2->Location = System::Drawing::Point(218, 580);
		this->walkersYnumUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown2->Name = L"walkersYnumUpDown2";
		this->walkersYnumUpDown2->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown2->TabIndex = 100;
		// 
		// walkersXnumUpDown2
		// 
		this->walkersXnumUpDown2->Location = System::Drawing::Point(148, 580);
		this->walkersXnumUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown2->Name = L"walkersXnumUpDown2";
		this->walkersXnumUpDown2->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown2->TabIndex = 99;
		// 
		// walkersZnumUpDown1
		// 
		this->walkersZnumUpDown1->Location = System::Drawing::Point(287, 539);
		this->walkersZnumUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersZnumUpDown1->Name = L"walkersZnumUpDown1";
		this->walkersZnumUpDown1->Size = System::Drawing::Size(50, 21);
		this->walkersZnumUpDown1->TabIndex = 98;
		// 
		// walkersYnumUpDown1
		// 
		this->walkersYnumUpDown1->Location = System::Drawing::Point(218, 539);
		this->walkersYnumUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersYnumUpDown1->Name = L"walkersYnumUpDown1";
		this->walkersYnumUpDown1->Size = System::Drawing::Size(50, 21);
		this->walkersYnumUpDown1->TabIndex = 97;
		// 
		// walkersXnumUpDown1
		// 
		this->walkersXnumUpDown1->Location = System::Drawing::Point(148, 539);
		this->walkersXnumUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
		this->walkersXnumUpDown1->Name = L"walkersXnumUpDown1";
		this->walkersXnumUpDown1->Size = System::Drawing::Size(50, 21);
		this->walkersXnumUpDown1->TabIndex = 96;
		// 
		// walkersHideCheckBox10
		// 
		this->walkersHideCheckBox10->AutoSize = true;
		this->walkersHideCheckBox10->Location = System::Drawing::Point(346, 901);
		this->walkersHideCheckBox10->Name = L"walkersHideCheckBox10";
		this->walkersHideCheckBox10->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox10->TabIndex = 95;
		this->walkersHideCheckBox10->Text = L"hide";
		this->walkersHideCheckBox10->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox10->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox10_CheckedChanged);
		// 
		// walkersHideCheckBox9
		// 
		this->walkersHideCheckBox9->AutoSize = true;
		this->walkersHideCheckBox9->Location = System::Drawing::Point(346, 861);
		this->walkersHideCheckBox9->Name = L"walkersHideCheckBox9";
		this->walkersHideCheckBox9->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox9->TabIndex = 94;
		this->walkersHideCheckBox9->Text = L"hide";
		this->walkersHideCheckBox9->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox9->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox9_CheckedChanged);
		// 
		// walkersHideCheckBox8
		// 
		this->walkersHideCheckBox8->AutoSize = true;
		this->walkersHideCheckBox8->Location = System::Drawing::Point(346, 821);
		this->walkersHideCheckBox8->Name = L"walkersHideCheckBox8";
		this->walkersHideCheckBox8->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox8->TabIndex = 93;
		this->walkersHideCheckBox8->Text = L"hide";
		this->walkersHideCheckBox8->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox8->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox8_CheckedChanged);
		// 
		// walkersHideCheckBox7
		// 
		this->walkersHideCheckBox7->AutoSize = true;
		this->walkersHideCheckBox7->Location = System::Drawing::Point(346, 781);
		this->walkersHideCheckBox7->Name = L"walkersHideCheckBox7";
		this->walkersHideCheckBox7->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox7->TabIndex = 92;
		this->walkersHideCheckBox7->Text = L"hide";
		this->walkersHideCheckBox7->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox7->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox7_CheckedChanged);
		// 
		// walkersHideCheckBox6
		// 
		this->walkersHideCheckBox6->AutoSize = true;
		this->walkersHideCheckBox6->Location = System::Drawing::Point(346, 741);
		this->walkersHideCheckBox6->Name = L"walkersHideCheckBox6";
		this->walkersHideCheckBox6->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox6->TabIndex = 91;
		this->walkersHideCheckBox6->Text = L"hide";
		this->walkersHideCheckBox6->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox6->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox6_CheckedChanged);
		// 
		// walkersHideCheckBox5
		// 
		this->walkersHideCheckBox5->AutoSize = true;
		this->walkersHideCheckBox5->Location = System::Drawing::Point(346, 701);
		this->walkersHideCheckBox5->Name = L"walkersHideCheckBox5";
		this->walkersHideCheckBox5->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox5->TabIndex = 90;
		this->walkersHideCheckBox5->Text = L"hide";
		this->walkersHideCheckBox5->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox5->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox5_CheckedChanged);
		// 
		// walkersHideCheckBox4
		// 
		this->walkersHideCheckBox4->AutoSize = true;
		this->walkersHideCheckBox4->Location = System::Drawing::Point(346, 661);
		this->walkersHideCheckBox4->Name = L"walkersHideCheckBox4";
		this->walkersHideCheckBox4->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox4->TabIndex = 89;
		this->walkersHideCheckBox4->Text = L"hide";
		this->walkersHideCheckBox4->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox4->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox4_CheckedChanged);
		// 
		// walkersHideCheckBox3
		// 
		this->walkersHideCheckBox3->AutoSize = true;
		this->walkersHideCheckBox3->Location = System::Drawing::Point(346, 621);
		this->walkersHideCheckBox3->Name = L"walkersHideCheckBox3";
		this->walkersHideCheckBox3->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox3->TabIndex = 88;
		this->walkersHideCheckBox3->Text = L"hide";
		this->walkersHideCheckBox3->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox3->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox3_CheckedChanged);
		// 
		// walkersHideCheckBox2
		// 
		this->walkersHideCheckBox2->AutoSize = true;
		this->walkersHideCheckBox2->Location = System::Drawing::Point(346, 581);
		this->walkersHideCheckBox2->Name = L"walkersHideCheckBox2";
		this->walkersHideCheckBox2->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox2->TabIndex = 87;
		this->walkersHideCheckBox2->Text = L"hide";
		this->walkersHideCheckBox2->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox2->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox2_CheckedChanged);
		// 
		// walkersHideCheckBox1
		// 
		this->walkersHideCheckBox1->AutoSize = true;
		this->walkersHideCheckBox1->Location = System::Drawing::Point(346, 541);
		this->walkersHideCheckBox1->Name = L"walkersHideCheckBox1";
		this->walkersHideCheckBox1->Size = System::Drawing::Size(48, 16);
		this->walkersHideCheckBox1->TabIndex = 86;
		this->walkersHideCheckBox1->Text = L"hide";
		this->walkersHideCheckBox1->UseVisualStyleBackColor = true;
		this->walkersHideCheckBox1->CheckedChanged += gcnew System::EventHandler(this, &MainForm::walkersHideCheckBox1_CheckedChanged);
		// 
		// walkersTitleLabel10
		// 
		this->walkersTitleLabel10->AutoSize = true;
		this->walkersTitleLabel10->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->walkersTitleLabel10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)),
			static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(200)));
		this->walkersTitleLabel10->Location = System::Drawing::Point(24, 896);
		this->walkersTitleLabel10->Name = L"walkersTitleLabel10";
		this->walkersTitleLabel10->Size = System::Drawing::Size(98, 24);
		this->walkersTitleLabel10->TabIndex = 79;
		this->walkersTitleLabel10->Text = L"Walker 10";
		// 
		// walkersXLabel10
		// 
		this->walkersXLabel10->AutoSize = true;
		this->walkersXLabel10->Location = System::Drawing::Point(134, 902);
		this->walkersXLabel10->Name = L"walkersXLabel10";
		this->walkersXLabel10->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel10->TabIndex = 80;
		this->walkersXLabel10->Text = L"x";
		// 
		// walkersYLabel10
		// 
		this->walkersYLabel10->AutoSize = true;
		this->walkersYLabel10->Location = System::Drawing::Point(204, 902);
		this->walkersYLabel10->Name = L"walkersYLabel10";
		this->walkersYLabel10->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel10->TabIndex = 81;
		this->walkersYLabel10->Text = L"y";
		// 
		// walkersZLabel10
		// 
		this->walkersZLabel10->AutoSize = true;
		this->walkersZLabel10->Location = System::Drawing::Point(273, 902);
		this->walkersZLabel10->Name = L"walkersZLabel10";
		this->walkersZLabel10->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel10->TabIndex = 82;
		this->walkersZLabel10->Text = L"z";
		// 
		// walkersTitleLabel9
		// 
		this->walkersTitleLabel9->AutoSize = true;
		this->walkersTitleLabel9->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(236)),
			static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(125)));
		this->walkersTitleLabel9->Location = System::Drawing::Point(24, 856);
		this->walkersTitleLabel9->Name = L"walkersTitleLabel9";
		this->walkersTitleLabel9->Size = System::Drawing::Size(102, 24);
		this->walkersTitleLabel9->TabIndex = 72;
		this->walkersTitleLabel9->Text = L"Walker 09";
		// 
		// walkersXLabel9
		// 
		this->walkersXLabel9->AutoSize = true;
		this->walkersXLabel9->Location = System::Drawing::Point(134, 862);
		this->walkersXLabel9->Name = L"walkersXLabel9";
		this->walkersXLabel9->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel9->TabIndex = 73;
		this->walkersXLabel9->Text = L"x";
		// 
		// walkersYLabel9
		// 
		this->walkersYLabel9->AutoSize = true;
		this->walkersYLabel9->Location = System::Drawing::Point(204, 862);
		this->walkersYLabel9->Name = L"walkersYLabel9";
		this->walkersYLabel9->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel9->TabIndex = 74;
		this->walkersYLabel9->Text = L"y";
		// 
		// walkersZLabel9
		// 
		this->walkersZLabel9->AutoSize = true;
		this->walkersZLabel9->Location = System::Drawing::Point(273, 862);
		this->walkersZLabel9->Name = L"walkersZLabel9";
		this->walkersZLabel9->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel9->TabIndex = 75;
		this->walkersZLabel9->Text = L"z";
		// 
		// walkersTitleLabel8
		// 
		this->walkersTitleLabel8->AutoSize = true;
		this->walkersTitleLabel8->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(17)),
			static_cast<System::Int32>(static_cast<System::Byte>(140)), static_cast<System::Int32>(static_cast<System::Byte>(206)));
		this->walkersTitleLabel8->Location = System::Drawing::Point(24, 816);
		this->walkersTitleLabel8->Name = L"walkersTitleLabel8";
		this->walkersTitleLabel8->Size = System::Drawing::Size(102, 24);
		this->walkersTitleLabel8->TabIndex = 65;
		this->walkersTitleLabel8->Text = L"Walker 08";
		// 
		// walkersXLabel8
		// 
		this->walkersXLabel8->AutoSize = true;
		this->walkersXLabel8->Location = System::Drawing::Point(134, 822);
		this->walkersXLabel8->Name = L"walkersXLabel8";
		this->walkersXLabel8->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel8->TabIndex = 66;
		this->walkersXLabel8->Text = L"x";
		// 
		// walkersYLabel8
		// 
		this->walkersYLabel8->AutoSize = true;
		this->walkersYLabel8->Location = System::Drawing::Point(204, 822);
		this->walkersYLabel8->Name = L"walkersYLabel8";
		this->walkersYLabel8->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel8->TabIndex = 67;
		this->walkersYLabel8->Text = L"y";
		// 
		// walkersZLabel8
		// 
		this->walkersZLabel8->AutoSize = true;
		this->walkersZLabel8->Location = System::Drawing::Point(273, 822);
		this->walkersZLabel8->Name = L"walkersZLabel8";
		this->walkersZLabel8->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel8->TabIndex = 68;
		this->walkersZLabel8->Text = L"z";
		// 
		// walkersTitleLabel7
		// 
		this->walkersTitleLabel7->AutoSize = true;
		this->walkersTitleLabel7->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(195)));
		this->walkersTitleLabel7->Location = System::Drawing::Point(24, 776);
		this->walkersTitleLabel7->Name = L"walkersTitleLabel7";
		this->walkersTitleLabel7->Size = System::Drawing::Size(103, 24);
		this->walkersTitleLabel7->TabIndex = 58;
		this->walkersTitleLabel7->Text = L"Walker 07";
		// 
		// walkersXLabel7
		// 
		this->walkersXLabel7->AutoSize = true;
		this->walkersXLabel7->Location = System::Drawing::Point(134, 782);
		this->walkersXLabel7->Name = L"walkersXLabel7";
		this->walkersXLabel7->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel7->TabIndex = 59;
		this->walkersXLabel7->Text = L"x";
		// 
		// walkersYLabel7
		// 
		this->walkersYLabel7->AutoSize = true;
		this->walkersYLabel7->Location = System::Drawing::Point(204, 782);
		this->walkersYLabel7->Name = L"walkersYLabel7";
		this->walkersYLabel7->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel7->TabIndex = 60;
		this->walkersYLabel7->Text = L"y";
		// 
		// walkersZLabel7
		// 
		this->walkersZLabel7->AutoSize = true;
		this->walkersZLabel7->Location = System::Drawing::Point(273, 782);
		this->walkersZLabel7->Name = L"walkersZLabel7";
		this->walkersZLabel7->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel7->TabIndex = 61;
		this->walkersZLabel7->Text = L"z";
		// 
		// walkersTitleLabel6
		// 
		this->walkersTitleLabel6->AutoSize = true;
		this->walkersTitleLabel6->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(250)),
			static_cast<System::Int32>(static_cast<System::Byte>(159)), static_cast<System::Int32>(static_cast<System::Byte>(86)));
		this->walkersTitleLabel6->Location = System::Drawing::Point(24, 736);
		this->walkersTitleLabel6->Name = L"walkersTitleLabel6";
		this->walkersTitleLabel6->Size = System::Drawing::Size(102, 24);
		this->walkersTitleLabel6->TabIndex = 51;
		this->walkersTitleLabel6->Text = L"Walker 06";
		// 
		// walkersXLabel6
		// 
		this->walkersXLabel6->AutoSize = true;
		this->walkersXLabel6->Location = System::Drawing::Point(134, 742);
		this->walkersXLabel6->Name = L"walkersXLabel6";
		this->walkersXLabel6->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel6->TabIndex = 52;
		this->walkersXLabel6->Text = L"x";
		// 
		// walkersYLabel6
		// 
		this->walkersYLabel6->AutoSize = true;
		this->walkersYLabel6->Location = System::Drawing::Point(204, 742);
		this->walkersYLabel6->Name = L"walkersYLabel6";
		this->walkersYLabel6->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel6->TabIndex = 53;
		this->walkersYLabel6->Text = L"y";
		// 
		// walkersZLabel6
		// 
		this->walkersZLabel6->AutoSize = true;
		this->walkersZLabel6->Location = System::Drawing::Point(273, 742);
		this->walkersZLabel6->Name = L"walkersZLabel6";
		this->walkersZLabel6->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel6->TabIndex = 54;
		this->walkersZLabel6->Text = L"z";
		// 
		// walkersTitleLabel5
		// 
		this->walkersTitleLabel5->AutoSize = true;
		this->walkersTitleLabel5->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(129)),
			static_cast<System::Int32>(static_cast<System::Byte>(81)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
		this->walkersTitleLabel5->Location = System::Drawing::Point(24, 696);
		this->walkersTitleLabel5->Name = L"walkersTitleLabel5";
		this->walkersTitleLabel5->Size = System::Drawing::Size(103, 24);
		this->walkersTitleLabel5->TabIndex = 44;
		this->walkersTitleLabel5->Text = L"Walker 05";
		// 
		// walkersXLabel5
		// 
		this->walkersXLabel5->AutoSize = true;
		this->walkersXLabel5->Location = System::Drawing::Point(134, 702);
		this->walkersXLabel5->Name = L"walkersXLabel5";
		this->walkersXLabel5->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel5->TabIndex = 45;
		this->walkersXLabel5->Text = L"x";
		// 
		// walkersYLabel5
		// 
		this->walkersYLabel5->AutoSize = true;
		this->walkersYLabel5->Location = System::Drawing::Point(204, 702);
		this->walkersYLabel5->Name = L"walkersYLabel5";
		this->walkersYLabel5->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel5->TabIndex = 46;
		this->walkersYLabel5->Text = L"y";
		// 
		// walkersZLabel5
		// 
		this->walkersZLabel5->AutoSize = true;
		this->walkersZLabel5->Location = System::Drawing::Point(273, 702);
		this->walkersZLabel5->Name = L"walkersZLabel5";
		this->walkersZLabel5->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel5->TabIndex = 47;
		this->walkersZLabel5->Text = L"z";
		// 
		// walkersTitleLabel4
		// 
		this->walkersTitleLabel4->AutoSize = true;
		this->walkersTitleLabel4->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(251)),
			static_cast<System::Int32>(static_cast<System::Byte>(242)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
		this->walkersTitleLabel4->Location = System::Drawing::Point(24, 656);
		this->walkersTitleLabel4->Name = L"walkersTitleLabel4";
		this->walkersTitleLabel4->Size = System::Drawing::Size(103, 24);
		this->walkersTitleLabel4->TabIndex = 37;
		this->walkersTitleLabel4->Text = L"Walker 04";
		// 
		// walkersXLabel4
		// 
		this->walkersXLabel4->AutoSize = true;
		this->walkersXLabel4->Location = System::Drawing::Point(134, 662);
		this->walkersXLabel4->Name = L"walkersXLabel4";
		this->walkersXLabel4->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel4->TabIndex = 38;
		this->walkersXLabel4->Text = L"x";
		// 
		// walkersYLabel4
		// 
		this->walkersYLabel4->AutoSize = true;
		this->walkersYLabel4->Location = System::Drawing::Point(204, 662);
		this->walkersYLabel4->Name = L"walkersYLabel4";
		this->walkersYLabel4->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel4->TabIndex = 39;
		this->walkersYLabel4->Text = L"y";
		// 
		// walkersZLabel4
		// 
		this->walkersZLabel4->AutoSize = true;
		this->walkersZLabel4->Location = System::Drawing::Point(273, 662);
		this->walkersZLabel4->Name = L"walkersZLabel4";
		this->walkersZLabel4->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel4->TabIndex = 40;
		this->walkersZLabel4->Text = L"z";
		// 
		// walkersTitleLabel3
		// 
		this->walkersTitleLabel3->AutoSize = true;
		this->walkersTitleLabel3->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)),
			static_cast<System::Int32>(static_cast<System::Byte>(247)), static_cast<System::Int32>(static_cast<System::Byte>(113)));
		this->walkersTitleLabel3->Location = System::Drawing::Point(24, 616);
		this->walkersTitleLabel3->Name = L"walkersTitleLabel3";
		this->walkersTitleLabel3->Size = System::Drawing::Size(103, 24);
		this->walkersTitleLabel3->TabIndex = 30;
		this->walkersTitleLabel3->Text = L"Walker 03";
		// 
		// walkersXLabel3
		// 
		this->walkersXLabel3->AutoSize = true;
		this->walkersXLabel3->Location = System::Drawing::Point(134, 622);
		this->walkersXLabel3->Name = L"walkersXLabel3";
		this->walkersXLabel3->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel3->TabIndex = 31;
		this->walkersXLabel3->Text = L"x";
		// 
		// walkersYLabel3
		// 
		this->walkersYLabel3->AutoSize = true;
		this->walkersYLabel3->Location = System::Drawing::Point(204, 622);
		this->walkersYLabel3->Name = L"walkersYLabel3";
		this->walkersYLabel3->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel3->TabIndex = 32;
		this->walkersYLabel3->Text = L"y";
		// 
		// walkersZLabel3
		// 
		this->walkersZLabel3->AutoSize = true;
		this->walkersZLabel3->Location = System::Drawing::Point(273, 622);
		this->walkersZLabel3->Name = L"walkersZLabel3";
		this->walkersZLabel3->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel3->TabIndex = 33;
		this->walkersZLabel3->Text = L"z";
		// 
		// walkersTitleLabel1
		// 
		this->walkersTitleLabel1->AutoSize = true;
		this->walkersTitleLabel1->BackColor = System::Drawing::Color::Transparent;
		this->walkersTitleLabel1->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(249)),
			static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(91)));
		this->walkersTitleLabel1->Location = System::Drawing::Point(24, 536);
		this->walkersTitleLabel1->Name = L"walkersTitleLabel1";
		this->walkersTitleLabel1->Size = System::Drawing::Size(98, 24);
		this->walkersTitleLabel1->TabIndex = 16;
		this->walkersTitleLabel1->Text = L"Walker 01";
		// 
		// walkersXLabel1
		// 
		this->walkersXLabel1->AutoSize = true;
		this->walkersXLabel1->Location = System::Drawing::Point(134, 542);
		this->walkersXLabel1->Name = L"walkersXLabel1";
		this->walkersXLabel1->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel1->TabIndex = 17;
		this->walkersXLabel1->Text = L"x";
		// 
		// walkersYLabel1
		// 
		this->walkersYLabel1->AutoSize = true;
		this->walkersYLabel1->Location = System::Drawing::Point(204, 542);
		this->walkersYLabel1->Name = L"walkersYLabel1";
		this->walkersYLabel1->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel1->TabIndex = 19;
		this->walkersYLabel1->Text = L"y";
		// 
		// walkersZLabel1
		// 
		this->walkersZLabel1->AutoSize = true;
		this->walkersZLabel1->Location = System::Drawing::Point(273, 542);
		this->walkersZLabel1->Name = L"walkersZLabel1";
		this->walkersZLabel1->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel1->TabIndex = 21;
		this->walkersZLabel1->Text = L"z";
		// 
		// walkersTitleLabel2
		// 
		this->walkersTitleLabel2->AutoSize = true;
		this->walkersTitleLabel2->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->walkersTitleLabel2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)),
			static_cast<System::Int32>(static_cast<System::Byte>(136)), static_cast<System::Int32>(static_cast<System::Byte>(247)));
		this->walkersTitleLabel2->Location = System::Drawing::Point(24, 576);
		this->walkersTitleLabel2->Name = L"walkersTitleLabel2";
		this->walkersTitleLabel2->Size = System::Drawing::Size(104, 24);
		this->walkersTitleLabel2->TabIndex = 23;
		this->walkersTitleLabel2->Text = L"Walker 02";
		// 
		// walkersXLabel2
		// 
		this->walkersXLabel2->AutoSize = true;
		this->walkersXLabel2->Location = System::Drawing::Point(134, 582);
		this->walkersXLabel2->Name = L"walkersXLabel2";
		this->walkersXLabel2->Size = System::Drawing::Size(12, 12);
		this->walkersXLabel2->TabIndex = 24;
		this->walkersXLabel2->Text = L"x";
		// 
		// walkersYLabel2
		// 
		this->walkersYLabel2->AutoSize = true;
		this->walkersYLabel2->Location = System::Drawing::Point(204, 582);
		this->walkersYLabel2->Name = L"walkersYLabel2";
		this->walkersYLabel2->Size = System::Drawing::Size(12, 12);
		this->walkersYLabel2->TabIndex = 25;
		this->walkersYLabel2->Text = L"y";
		// 
		// walkersZLabel2
		// 
		this->walkersZLabel2->AutoSize = true;
		this->walkersZLabel2->Location = System::Drawing::Point(273, 582);
		this->walkersZLabel2->Name = L"walkersZLabel2";
		this->walkersZLabel2->Size = System::Drawing::Size(12, 12);
		this->walkersZLabel2->TabIndex = 26;
		this->walkersZLabel2->Text = L"z";
		// 
		// minorAxisIntervalValueText
		// 
		this->minorAxisIntervalValueText->BackColor = System::Drawing::SystemColors::Window;
		this->minorAxisIntervalValueText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->minorAxisIntervalValueText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->minorAxisIntervalValueText->Location = System::Drawing::Point(264, 284);
		this->minorAxisIntervalValueText->Name = L"minorAxisIntervalValueText";
		this->minorAxisIntervalValueText->ReadOnly = true;
		this->minorAxisIntervalValueText->Size = System::Drawing::Size(131, 31);
		this->minorAxisIntervalValueText->TabIndex = 15;
		this->minorAxisIntervalValueText->Text = L"1";
		// 
		// minorAxisIntervalTitleText
		// 
		this->minorAxisIntervalTitleText->BackColor = System::Drawing::SystemColors::Window;
		this->minorAxisIntervalTitleText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->minorAxisIntervalTitleText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->minorAxisIntervalTitleText->Location = System::Drawing::Point(24, 284);
		this->minorAxisIntervalTitleText->Name = L"minorAxisIntervalTitleText";
		this->minorAxisIntervalTitleText->ReadOnly = true;
		this->minorAxisIntervalTitleText->Size = System::Drawing::Size(234, 31);
		this->minorAxisIntervalTitleText->TabIndex = 14;
		this->minorAxisIntervalTitleText->Text = L"Minor Axis Interval : ";
		// 
		// minorAxisIntervalTrackBar
		// 
		this->minorAxisIntervalTrackBar->BackColor = System::Drawing::SystemColors::Window;
		this->minorAxisIntervalTrackBar->Location = System::Drawing::Point(24, 324);
		this->minorAxisIntervalTrackBar->Minimum = 1;
		this->minorAxisIntervalTrackBar->Name = L"minorAxisIntervalTrackBar";
		this->minorAxisIntervalTrackBar->Size = System::Drawing::Size(344, 45);
		this->minorAxisIntervalTrackBar->TabIndex = 13;
		this->minorAxisIntervalTrackBar->Value = 1;
		this->minorAxisIntervalTrackBar->Scroll += gcnew System::EventHandler(this, &MainForm::minorAxisIntervalTrackBar_Scroll);
		// 
		// numOfWalkersValueText
		// 
		this->numOfWalkersValueText->BackColor = System::Drawing::SystemColors::Window;
		this->numOfWalkersValueText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->numOfWalkersValueText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->numOfWalkersValueText->Location = System::Drawing::Point(264, 368);
		this->numOfWalkersValueText->Name = L"numOfWalkersValueText";
		this->numOfWalkersValueText->ReadOnly = true;
		this->numOfWalkersValueText->Size = System::Drawing::Size(57, 31);
		this->numOfWalkersValueText->TabIndex = 12;
		this->numOfWalkersValueText->Text = L"10";
		// 
		// axisDomainValueText
		// 
		this->axisDomainValueText->BackColor = System::Drawing::SystemColors::Window;
		this->axisDomainValueText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->axisDomainValueText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->axisDomainValueText->Location = System::Drawing::Point(297, 201);
		this->axisDomainValueText->Name = L"axisDomainValueText";
		this->axisDomainValueText->ReadOnly = true;
		this->axisDomainValueText->Size = System::Drawing::Size(57, 31);
		this->axisDomainValueText->TabIndex = 11;
		this->axisDomainValueText->Text = L"10";
		// 
		// axisDomainTitleText
		// 
		this->axisDomainTitleText->BackColor = System::Drawing::SystemColors::Window;
		this->axisDomainTitleText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->axisDomainTitleText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->axisDomainTitleText->Location = System::Drawing::Point(24, 201);
		this->axisDomainTitleText->Name = L"axisDomainTitleText";
		this->axisDomainTitleText->ReadOnly = true;
		this->axisDomainTitleText->Size = System::Drawing::Size(267, 31);
		this->axisDomainTitleText->TabIndex = 10;
		this->axisDomainTitleText->Text = L"Axis Domain Max Value : ";
		// 
		// axisDomainTrackBar
		// 
		this->axisDomainTrackBar->BackColor = System::Drawing::SystemColors::Window;
		this->axisDomainTrackBar->Location = System::Drawing::Point(24, 241);
		this->axisDomainTrackBar->Maximum = 30;
		this->axisDomainTrackBar->Minimum = 10;
		this->axisDomainTrackBar->Name = L"axisDomainTrackBar";
		this->axisDomainTrackBar->Size = System::Drawing::Size(344, 45);
		this->axisDomainTrackBar->TabIndex = 9;
		this->axisDomainTrackBar->Value = 10;
		this->axisDomainTrackBar->Scroll += gcnew System::EventHandler(this, &MainForm::axisDomainTrackBar_Scroll);
		// 
		// simulationTypeComboBox
		// 
		this->simulationTypeComboBox->FormattingEnabled = true;
		this->simulationTypeComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
			L"Simple multiple random walks", L"Self-avoiding random walks",
				L"Origin to endpoint random walk", L"Return to origin random walk", L"Two random walk intersection", L"Two SAW intersection",
				L"Count self-avoiding random walk"
		});
		this->simulationTypeComboBox->Location = System::Drawing::Point(198, 23);
		this->simulationTypeComboBox->Name = L"simulationTypeComboBox";
		this->simulationTypeComboBox->Size = System::Drawing::Size(211, 20);
		this->simulationTypeComboBox->TabIndex = 7;
		this->simulationTypeComboBox->Text = L"Simple multiple random walks";
		this->simulationTypeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::simulationTypeComboBox_SelectedIndexChanged);
		// 
		// numOfWalkersTitleText
		// 
		this->numOfWalkersTitleText->BackColor = System::Drawing::SystemColors::Window;
		this->numOfWalkersTitleText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->numOfWalkersTitleText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->numOfWalkersTitleText->Location = System::Drawing::Point(24, 368);
		this->numOfWalkersTitleText->Name = L"numOfWalkersTitleText";
		this->numOfWalkersTitleText->ReadOnly = true;
		this->numOfWalkersTitleText->Size = System::Drawing::Size(234, 31);
		this->numOfWalkersTitleText->TabIndex = 6;
		this->numOfWalkersTitleText->Text = L"Number of Walkers : ";
		// 
		// dimensionText
		// 
		this->dimensionText->BackColor = System::Drawing::SystemColors::Window;
		this->dimensionText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->dimensionText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->dimensionText->Location = System::Drawing::Point(24, 64);
		this->dimensionText->Name = L"dimensionText";
		this->dimensionText->ReadOnly = true;
		this->dimensionText->Size = System::Drawing::Size(111, 31);
		this->dimensionText->TabIndex = 5;
		this->dimensionText->Text = L"Dimension";
		// 
		// threeDimRadioButton
		// 
		this->threeDimRadioButton->AutoSize = true;
		this->threeDimRadioButton->Checked = true;
		this->threeDimRadioButton->Location = System::Drawing::Point(353, 71);
		this->threeDimRadioButton->Name = L"threeDimRadioButton";
		this->threeDimRadioButton->Size = System::Drawing::Size(37, 16);
		this->threeDimRadioButton->TabIndex = 4;
		this->threeDimRadioButton->TabStop = true;
		this->threeDimRadioButton->Text = L"3D";
		this->threeDimRadioButton->UseVisualStyleBackColor = true;
		this->threeDimRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::dimRadioButton_CheckedChanged);
		// 
		// twoDimRadioButton
		// 
		this->twoDimRadioButton->AutoSize = true;
		this->twoDimRadioButton->Location = System::Drawing::Point(275, 71);
		this->twoDimRadioButton->Name = L"twoDimRadioButton";
		this->twoDimRadioButton->Size = System::Drawing::Size(37, 16);
		this->twoDimRadioButton->TabIndex = 3;
		this->twoDimRadioButton->TabStop = true;
		this->twoDimRadioButton->Text = L"2D";
		this->twoDimRadioButton->UseVisualStyleBackColor = true;
		this->twoDimRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::dimRadioButton_CheckedChanged);
		// 
		// oneDimRadioButton
		// 
		this->oneDimRadioButton->AutoSize = true;
		this->oneDimRadioButton->Location = System::Drawing::Point(198, 71);
		this->oneDimRadioButton->Name = L"oneDimRadioButton";
		this->oneDimRadioButton->Size = System::Drawing::Size(37, 16);
		this->oneDimRadioButton->TabIndex = 2;
		this->oneDimRadioButton->TabStop = true;
		this->oneDimRadioButton->Text = L"1D";
		this->oneDimRadioButton->UseVisualStyleBackColor = true;
		this->oneDimRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::dimRadioButton_CheckedChanged);
		// 
		// walkersNumTrackBar
		// 
		this->walkersNumTrackBar->BackColor = System::Drawing::SystemColors::Window;
		this->walkersNumTrackBar->Location = System::Drawing::Point(24, 405);
		this->walkersNumTrackBar->Minimum = 1;
		this->walkersNumTrackBar->Name = L"walkersNumTrackBar";
		this->walkersNumTrackBar->Size = System::Drawing::Size(344, 45);
		this->walkersNumTrackBar->TabIndex = 1;
		this->walkersNumTrackBar->Value = 10;
		this->walkersNumTrackBar->Scroll += gcnew System::EventHandler(this, &MainForm::walkersNumTrackBar_Scroll);
		// 
		// simulationTypeText
		// 
		this->simulationTypeText->BackColor = System::Drawing::SystemColors::Window;
		this->simulationTypeText->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->simulationTypeText->Font = (gcnew System::Drawing::Font(L"Permanent Marker", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->simulationTypeText->Location = System::Drawing::Point(24, 18);
		this->simulationTypeText->Name = L"simulationTypeText";
		this->simulationTypeText->ReadOnly = true;
		this->simulationTypeText->Size = System::Drawing::Size(172, 31);
		this->simulationTypeText->TabIndex = 0;
		this->simulationTypeText->Text = L"Simulation Type";
		// 
		// Log
		// 
		this->Log->Controls->Add(this->logTextBox);
		this->Log->Location = System::Drawing::Point(4, 22);
		this->Log->Name = L"Log";
		this->Log->Padding = System::Windows::Forms::Padding(3);
		this->Log->Size = System::Drawing::Size(442, 518);
		this->Log->TabIndex = 1;
		this->Log->Text = L"Log";
		this->Log->UseVisualStyleBackColor = true;
		// 
		// logTextBox
		// 
		this->logTextBox->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->logTextBox->Location = System::Drawing::Point(6, 6);
		this->logTextBox->Name = L"logTextBox";
		this->logTextBox->ReadOnly = true;
		this->logTextBox->Size = System::Drawing::Size(430, 506);
		this->logTextBox->TabIndex = 0;
		this->logTextBox->Text = L"";
		// 
		// Statistics
		// 
		this->Statistics->Controls->Add(this->chart1);
		this->Statistics->Location = System::Drawing::Point(4, 22);
		this->Statistics->Name = L"Statistics";
		this->Statistics->Size = System::Drawing::Size(442, 518);
		this->Statistics->TabIndex = 2;
		this->Statistics->Text = L"Statistics";
		this->Statistics->UseVisualStyleBackColor = true;
		// 
		// chart1
		// 
		chartArea1->Name = L"ChartArea1";
		this->chart1->ChartAreas->Add(chartArea1);
		legend1->Name = L"Legend1";
		this->chart1->Legends->Add(legend1);
		this->chart1->Location = System::Drawing::Point(3, 3);
		this->chart1->Name = L"chart1";
		series1->ChartArea = L"ChartArea1";
		series1->Legend = L"Legend1";
		series1->Name = L"X Positive Move";
		series1->YValuesPerPoint = 2;
		series2->ChartArea = L"ChartArea1";
		series2->Legend = L"Legend1";
		series2->Name = L"X Negative Move";
		series3->ChartArea = L"ChartArea1";
		series3->Legend = L"Legend1";
		series3->Name = L"Y Positive Move";
		series4->ChartArea = L"ChartArea1";
		series4->Legend = L"Legend1";
		series4->Name = L"Y Negative Move";
		series5->ChartArea = L"ChartArea1";
		series5->Legend = L"Legend1";
		series5->Name = L"Z Positive Move";
		series6->ChartArea = L"ChartArea1";
		series6->Legend = L"Legend1";
		series6->Name = L"Z Negative Move";
		this->chart1->Series->Add(series1);
		this->chart1->Series->Add(series2);
		this->chart1->Series->Add(series3);
		this->chart1->Series->Add(series4);
		this->chart1->Series->Add(series5);
		this->chart1->Series->Add(series6);
		this->chart1->Size = System::Drawing::Size(439, 512);
		this->chart1->TabIndex = 0;
		this->chart1->Text = L"chart1";
		// 
		// Result
		// 
		this->Result->Controls->Add(this->resultTextBox);
		this->Result->Location = System::Drawing::Point(4, 22);
		this->Result->Name = L"Result";
		this->Result->Size = System::Drawing::Size(442, 518);
		this->Result->TabIndex = 3;
		this->Result->Text = L"Result";
		this->Result->UseVisualStyleBackColor = true;
		// 
		// resultTextBox
		// 
		this->resultTextBox->BackColor = System::Drawing::SystemColors::Control;
		this->resultTextBox->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->resultTextBox->Location = System::Drawing::Point(6, 6);
		this->resultTextBox->Name = L"resultTextBox";
		this->resultTextBox->ReadOnly = true;
		this->resultTextBox->Size = System::Drawing::Size(430, 506);
		this->resultTextBox->TabIndex = 0;
		this->resultTextBox->Text = L"";
		// 
		// HowToRun
		// 
		this->HowToRun->Controls->Add(this->howToRunTextBox);
		this->HowToRun->Location = System::Drawing::Point(4, 22);
		this->HowToRun->Name = L"HowToRun";
		this->HowToRun->Size = System::Drawing::Size(442, 518);
		this->HowToRun->TabIndex = 4;
		this->HowToRun->Text = L"How to run";
		this->HowToRun->UseVisualStyleBackColor = true;
		// 
		// howToRunTextBox
		// 
		this->howToRunTextBox->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->howToRunTextBox->Location = System::Drawing::Point(6, 6);
		this->howToRunTextBox->Name = L"howToRunTextBox";
		this->howToRunTextBox->ReadOnly = true;
		this->howToRunTextBox->Size = System::Drawing::Size(430, 506);
		this->howToRunTextBox->TabIndex = 0;
		this->howToRunTextBox->Text = resources->GetString(L"howToRunTextBox.Text");
		// 
		// panel1
		// 
		this->panel1->BackColor = System::Drawing::SystemColors::Control;
		this->panel1->Controls->Add(this->playFrameButton);
		this->panel1->Controls->Add(this->stopButton);
		this->panel1->Controls->Add(this->playButton);
		this->panel1->Controls->Add(this->rewindButton);
		this->panel1->Location = System::Drawing::Point(300, 15);
		this->panel1->Name = L"panel1";
		this->panel1->Size = System::Drawing::Size(350, 70);
		this->panel1->TabIndex = 2;
		// 
		// playFrameButton
		// 
		this->playFrameButton->BackColor = System::Drawing::SystemColors::Control;
		this->playFrameButton->FlatAppearance->BorderSize = 0;
		this->playFrameButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->playFrameButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"playFrameButton.Image")));
		this->playFrameButton->Location = System::Drawing::Point(268, 5);
		this->playFrameButton->Name = L"playFrameButton";
		this->playFrameButton->Size = System::Drawing::Size(60, 60);
		this->playFrameButton->TabIndex = 4;
		this->playFrameButton->UseVisualStyleBackColor = false;
		this->playFrameButton->Click += gcnew System::EventHandler(this, &MainForm::playFrameButton_Click);
		this->playFrameButton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// stopButton
		// 
		this->stopButton->BackColor = System::Drawing::SystemColors::Control;
		this->stopButton->FlatAppearance->BorderSize = 0;
		this->stopButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->stopButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"stopButton.Image")));
		this->stopButton->Location = System::Drawing::Point(186, 5);
		this->stopButton->Name = L"stopButton";
		this->stopButton->Size = System::Drawing::Size(60, 60);
		this->stopButton->TabIndex = 2;
		this->stopButton->UseVisualStyleBackColor = false;
		this->stopButton->Click += gcnew System::EventHandler(this, &MainForm::stopButton_Click);
		this->stopButton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// playButton
		// 
		this->playButton->BackColor = System::Drawing::SystemColors::Control;
		this->playButton->FlatAppearance->BorderSize = 0;
		this->playButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->playButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"playButton.Image")));
		this->playButton->Location = System::Drawing::Point(104, 5);
		this->playButton->Name = L"playButton";
		this->playButton->Size = System::Drawing::Size(60, 60);
		this->playButton->TabIndex = 1;
		this->playButton->UseVisualStyleBackColor = false;
		this->playButton->Click += gcnew System::EventHandler(this, &MainForm::playButton_Click);
		this->playButton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// rewindButton
		// 
		this->rewindButton->BackColor = System::Drawing::SystemColors::Control;
		this->rewindButton->FlatAppearance->BorderSize = 0;
		this->rewindButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->rewindButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"rewindButton.Image")));
		this->rewindButton->Location = System::Drawing::Point(22, 5);
		this->rewindButton->Name = L"rewindButton";
		this->rewindButton->Size = System::Drawing::Size(60, 60);
		this->rewindButton->TabIndex = 0;
		this->rewindButton->UseVisualStyleBackColor = false;
		this->rewindButton->Click += gcnew System::EventHandler(this, &MainForm::rewindButton_Click);
		this->rewindButton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// imageList1
		// 
		this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
		this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
		this->imageList1->Images->SetKeyName(0, L"play_button_img");
		this->imageList1->Images->SetKeyName(1, L"pause_button_img");
		// 
		// buildRandPosSimulationButton
		// 
		this->buildRandPosSimulationButton->Location = System::Drawing::Point(950, 628);
		this->buildRandPosSimulationButton->Name = L"buildRandPosSimulationButton";
		this->buildRandPosSimulationButton->Size = System::Drawing::Size(229, 23);
		this->buildRandPosSimulationButton->TabIndex = 3;
		this->buildRandPosSimulationButton->Text = L"Build Simulation with random position";
		this->buildRandPosSimulationButton->UseVisualStyleBackColor = true;
		this->buildRandPosSimulationButton->Click += gcnew System::EventHandler(this, &MainForm::buildRandPosSimulationButton_Click);
		this->buildRandPosSimulationButton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// buildGivenPosSimulationButton
		// 
		this->buildGivenPosSimulationButton->Location = System::Drawing::Point(1185, 628);
		this->buildGivenPosSimulationButton->Name = L"buildGivenPosSimulationButton";
		this->buildGivenPosSimulationButton->Size = System::Drawing::Size(215, 23);
		this->buildGivenPosSimulationButton->TabIndex = 4;
		this->buildGivenPosSimulationButton->Text = L"Build Simulation with given position";
		this->buildGivenPosSimulationButton->UseVisualStyleBackColor = true;
		this->buildGivenPosSimulationButton->Click += gcnew System::EventHandler(this, &MainForm::buildGivenPosSimulationButton_Click);
		this->buildGivenPosSimulationButton->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// quickInstructionTextBox
		// 
		this->quickInstructionTextBox->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->quickInstructionTextBox->Location = System::Drawing::Point(954, 20);
		this->quickInstructionTextBox->Name = L"quickInstructionTextBox";
		this->quickInstructionTextBox->ReadOnly = true;
		this->quickInstructionTextBox->Size = System::Drawing::Size(436, 42);
		this->quickInstructionTextBox->TabIndex = 5;
		this->quickInstructionTextBox->Text = L"Tip : Detailed instructions are in the [How to run] tab page";
		this->quickInstructionTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::MainForm_KeyPress_1);
		// 
		// MainForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(1450, 670);
		this->Controls->Add(this->quickInstructionTextBox);
		this->Controls->Add(this->buildGivenPosSimulationButton);
		this->Controls->Add(this->buildRandPosSimulationButton);
		this->Controls->Add(this->panel1);
		this->Controls->Add(this->controlPanel);
		this->Name = L"MainForm";
		this->Text = L"MAT394_taehoon.kwon_random_walk_simulation";
		this->controlPanel->ResumeLayout(false);
		this->Configuration->ResumeLayout(false);
		this->Configuration->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepCountUpDown))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->stepSizeUpDown))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersSpeedTrackBar))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown10))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown10))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown10))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown9))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown9))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown9))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown8))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown8))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown8))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown7))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown7))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown7))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown6))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown6))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown6))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown5))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown5))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown5))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown4))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown4))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown4))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown3))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown3))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown3))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown2))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown2))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown2))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersZnumUpDown1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersYnumUpDown1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersXnumUpDown1))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->minorAxisIntervalTrackBar))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axisDomainTrackBar))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->walkersNumTrackBar))->EndInit();
		this->Log->ResumeLayout(false);
		this->Statistics->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
		this->Result->ResumeLayout(false);
		this->HowToRun->ResumeLayout(false);
		this->panel1->ResumeLayout(false);
		this->ResumeLayout(false);

	}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		UNREFERENCED_PARAMETER(sender);
		UNREFERENCED_PARAMETER(e);

		if (!canvas)
			return;

		/* Calculate dt */
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		canvas->Update();
		canvas->Render();
		canvas->SwapOpenGLBuffers();
		canvas->HandleKeyEvents();

		update_logTextBox();
		updateChart();
		update_resultTextBox();
		update_QuickInstructionTextBox();
	}

	private: System::Void MainForm_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
	{
		switch (e->KeyChar)
		{
		case (char)119: // 'w'
			canvas->ProcessInput('W', deltaTime);
			e->Handled = true;
			break;
		case (char)115: // 's'
			canvas->ProcessInput('S', deltaTime);
			e->Handled = true;
			break;
		case (char)97: // 'a'
			canvas->ProcessInput('A', deltaTime);
			e->Handled = true;
			break;
		case (char)100: // 'd'
			canvas->ProcessInput('D', deltaTime);
			e->Handled = true;
			break;
		}
	}
	private: System::Void playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (isPlaying)
		{
			playButton->Image = imageList1->Images[0]; // change image to play button image
			isPlaying = false;
		}
		else
		{
			playButton->Image = imageList1->Images[1]; // change image to pause button image
			isPlaying = true;
		}
		canvas->NotifySimulationPlay(isPlaying);
		canvas->SetResultChanged(true);
		unlockControlsWhenBuildClicked(false);
		unlockPositionUpDownControl(false);
	}
	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (isPlaying)
		{
			playButton->Image = imageList1->Images[0]; // change image to play button image
			isPlaying = false;
		}
		canvas->NotifySimulationPlay(isPlaying);
		canvas->ClearSimulation();
		canvas->NotifySimulationChanged();
		
		this->minorAxisHideCheckBox->Checked = false;
		this->rewindButton->Enabled = false;
		this->playButton->Enabled = false;
		this->stopButton->Enabled = false;
		this->playFrameButton->Enabled = false;
		unlockControlsWhenBuildClicked(true);
		unlockPositionUpDownControl(true);
		lockAndUnlockControlsWhenSimulationTypeChanged();
		lockAndUnlockMinorAxisControlWhenDimensionChanged();
		loadChart();

		logTextBox->Text = "";
		resultTextBox->Text = "";
	}
	private: System::Void rewindButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (isPlaying)
		{
			playButton->Image = imageList1->Images[0]; // change image to play button image
			isPlaying = false;
		}
		canvas->NotifySimulationPlay(isPlaying);
		canvas->RewindOneFrame();
	}
	private: System::Void playFrameButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (isPlaying)
		{
			playButton->Image = imageList1->Images[0]; // change image to play button image
			isPlaying = false;
		}
		canvas->NotifySimulationPlay(isPlaying);
		canvas->PlayOneFrame();
	}
	private: System::Void updateWalkersPositionConfig(System::Void)
	{
		if (walkers_num == 10) {
			this->walkersTitleLabel10->Visible = true;
			this->walkersXLabel10    ->Visible = true;
			this->walkersYLabel10    ->Visible = true;
			this->walkersZLabel10    ->Visible = true;
			this->walkersXnumUpDown10->Visible = true;
			this->walkersYnumUpDown10->Visible = true;
			this->walkersZnumUpDown10->Visible = true;
			this->walkersHideCheckBox10->Visible = true;
		}
		else {
			this->walkersTitleLabel10->Visible = false;
			this->walkersXLabel10    ->Visible = false;
			this->walkersYLabel10    ->Visible = false;
			this->walkersZLabel10    ->Visible = false;
			this->walkersXnumUpDown10->Visible = false;
			this->walkersYnumUpDown10->Visible = false;
			this->walkersZnumUpDown10->Visible = false;
			this->walkersHideCheckBox10->Visible = false;
		}
		if (walkers_num >= 9) {
			this->walkersTitleLabel9->Visible = true;
			this->walkersXLabel9    ->Visible = true;
			this->walkersYLabel9    ->Visible = true;
			this->walkersZLabel9    ->Visible = true;
			this->walkersXnumUpDown9->Visible = true;
			this->walkersYnumUpDown9->Visible = true;
			this->walkersZnumUpDown9->Visible = true;
			this->walkersHideCheckBox9->Visible = true;
		}
		else {
			this->walkersTitleLabel9->Visible = false;
			this->walkersXLabel9    ->Visible = false;
			this->walkersYLabel9    ->Visible = false;
			this->walkersZLabel9    ->Visible = false;
			this->walkersXnumUpDown9->Visible = false;
			this->walkersYnumUpDown9->Visible = false;
			this->walkersZnumUpDown9->Visible = false;
			this->walkersHideCheckBox9->Visible = false;
		}
		if (walkers_num >= 8) {
			this->walkersTitleLabel8->Visible = true;
			this->walkersXLabel8    ->Visible = true;
			this->walkersYLabel8    ->Visible = true;
			this->walkersZLabel8    ->Visible = true;
			this->walkersXnumUpDown8->Visible = true;
			this->walkersYnumUpDown8->Visible = true;
			this->walkersZnumUpDown8->Visible = true;
			this->walkersHideCheckBox8->Visible = true;
		}
		else {
			this->walkersTitleLabel8->Visible = false;
			this->walkersXLabel8    ->Visible = false;
			this->walkersYLabel8    ->Visible = false;
			this->walkersZLabel8    ->Visible = false;
			this->walkersXnumUpDown8->Visible = false;
			this->walkersYnumUpDown8->Visible = false;
			this->walkersZnumUpDown8->Visible = false;
			this->walkersHideCheckBox8->Visible = false;
		}
		if (walkers_num >= 7) {
			this->walkersTitleLabel7->Visible = true;
			this->walkersXLabel7    ->Visible = true;
			this->walkersYLabel7    ->Visible = true;
			this->walkersZLabel7    ->Visible = true;
			this->walkersXnumUpDown7->Visible = true;
			this->walkersYnumUpDown7->Visible = true;
			this->walkersZnumUpDown7->Visible = true;
			this->walkersHideCheckBox7->Visible = true;
		}
		else {
			this->walkersTitleLabel7->Visible = false;
			this->walkersXLabel7    ->Visible = false;
			this->walkersYLabel7    ->Visible = false;
			this->walkersZLabel7    ->Visible = false;
			this->walkersXnumUpDown7->Visible = false;
			this->walkersYnumUpDown7->Visible = false;
			this->walkersZnumUpDown7->Visible = false;
			this->walkersHideCheckBox7->Visible = false;
		}
		if (walkers_num >= 6) {
			this->walkersTitleLabel6->Visible = true;
			this->walkersXLabel6    ->Visible = true;
			this->walkersYLabel6    ->Visible = true;
			this->walkersZLabel6    ->Visible = true;
			this->walkersXnumUpDown6->Visible = true;
			this->walkersYnumUpDown6->Visible = true;
			this->walkersZnumUpDown6->Visible = true;
			this->walkersHideCheckBox6->Visible = true;
		}
		else {
			this->walkersTitleLabel6->Visible = false;
			this->walkersXLabel6    ->Visible = false;
			this->walkersYLabel6    ->Visible = false;
			this->walkersZLabel6    ->Visible = false;
			this->walkersXnumUpDown6->Visible = false;
			this->walkersYnumUpDown6->Visible = false;
			this->walkersZnumUpDown6->Visible = false;
			this->walkersHideCheckBox6->Visible = false;
		}
		if (walkers_num >= 5) {
			this->walkersTitleLabel5->Visible = true;
			this->walkersXLabel5    ->Visible = true;
			this->walkersYLabel5    ->Visible = true;
			this->walkersZLabel5    ->Visible = true;
			this->walkersXnumUpDown5->Visible = true;
			this->walkersYnumUpDown5->Visible = true;
			this->walkersZnumUpDown5->Visible = true;
			this->walkersHideCheckBox5->Visible = true;
		}
		else {
			this->walkersTitleLabel5->Visible = false;
			this->walkersXLabel5    ->Visible = false;
			this->walkersYLabel5    ->Visible = false;
			this->walkersZLabel5    ->Visible = false;
			this->walkersXnumUpDown5->Visible = false;
			this->walkersYnumUpDown5->Visible = false;
			this->walkersZnumUpDown5->Visible = false;
			this->walkersHideCheckBox5->Visible = false;
		}
		if (walkers_num >= 4) {
			this->walkersTitleLabel4->Visible = true;
			this->walkersXLabel4    ->Visible = true;
			this->walkersYLabel4    ->Visible = true;
			this->walkersZLabel4    ->Visible = true;
			this->walkersXnumUpDown4->Visible = true;
			this->walkersYnumUpDown4->Visible = true;
			this->walkersZnumUpDown4->Visible = true;
			this->walkersHideCheckBox4->Visible = true;
		}
		else {
			this->walkersTitleLabel4->Visible = false;
			this->walkersXLabel4    ->Visible = false;
			this->walkersYLabel4    ->Visible = false;
			this->walkersZLabel4    ->Visible = false;
			this->walkersXnumUpDown4->Visible = false;
			this->walkersYnumUpDown4->Visible = false;
			this->walkersZnumUpDown4->Visible = false;
			this->walkersHideCheckBox4->Visible = false;
		}
		if (walkers_num >= 3) {
			this->walkersTitleLabel3->Visible = true;
			this->walkersXLabel3    ->Visible = true;
			this->walkersYLabel3    ->Visible = true;
			this->walkersZLabel3    ->Visible = true;
			this->walkersXnumUpDown3->Visible = true;
			this->walkersYnumUpDown3->Visible = true;
			this->walkersZnumUpDown3->Visible = true;
			this->walkersHideCheckBox3->Visible = true;
		}
		else {
			this->walkersTitleLabel3->Visible = false;
			this->walkersXLabel3    ->Visible = false;
			this->walkersYLabel3    ->Visible = false;
			this->walkersZLabel3    ->Visible = false;
			this->walkersXnumUpDown3->Visible = false;
			this->walkersYnumUpDown3->Visible = false;
			this->walkersZnumUpDown3->Visible = false;
			this->walkersHideCheckBox3->Visible = false;
		}
		if (walkers_num >= 2) {
			this->walkersTitleLabel2->Visible = true;
			this->walkersXLabel2    ->Visible = true;
			this->walkersYLabel2    ->Visible = true;
			this->walkersZLabel2    ->Visible = true;
			this->walkersXnumUpDown2->Visible = true;
			this->walkersYnumUpDown2->Visible = true;
			this->walkersZnumUpDown2->Visible = true;
			this->walkersHideCheckBox2->Visible = true;
		}
		else {
			this->walkersTitleLabel2->Visible = false;
			this->walkersXLabel2    ->Visible = false;
			this->walkersYLabel2    ->Visible = false;
			this->walkersZLabel2    ->Visible = false;
			this->walkersXnumUpDown2->Visible = false;
			this->walkersYnumUpDown2->Visible = false;
			this->walkersZnumUpDown2->Visible = false;
			this->walkersHideCheckBox2->Visible = false;
		}
	}
	private: System::Void update_logTextBox(System::Void)
	{
		if (!logTextBox) return;
		if (!canvas->GetLogChanged()) return;

		const char* newLog = canvas->GetLog();
		
		System::String^ systemLog = gcnew System::String(newLog);
		logTextBox->Text = "";
		logTextBox->AppendText(systemLog);

		canvas->SetLogChanged(false);
	}
	private: System::Void update_resultTextBox(System::Void)
	{
		if (!resultTextBox) return;
		if (!canvas->GetResultChanged()) return;
		if (simulationTypeComboBox->SelectedIndex == 0
		 || simulationTypeComboBox->SelectedIndex == 1) {
			resultTextBox->Text = "No result for general simulation test.\n" 
							 + "Try selecting another simulation type.\n";
			canvas->SetResultChanged(false);
			return;
		}

		const char* newResult = canvas->GetResult();
			
		if (std::strcmp(newResult, "") == 0) {
			resultTextBox->Text = "Simulation is not finished yet.\n";
			canvas->SetResultChanged(false);
			return;
		}

		System::String^ systemResult = gcnew System::String(newResult);
		resultTextBox->Text = "";
		resultTextBox->AppendText(systemResult);

		canvas->SetResultChanged(false);
	}
	private: System::Void axisDomainTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		axisDomainValueText->Text = axisDomainTrackBar->Value.ToString();
		canvas->ChangeAxisDomain(axisDomainTrackBar->Value);
	}
	private: System::Void minorAxisIntervalTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		minorAxisInterval = minorAxisIntervalTrackBar->Value;
		minorAxisIntervalValueText->Text = minorAxisIntervalTrackBar->Value.ToString();
		canvas->ChangeMinorAxisInterval(minorAxisInterval);
	}
	private: System::Void minorAxisHideCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (this->minorAxisHideCheckBox->Checked)
			canvas->ChangeMinorAxisInterval(0);
		else
			canvas->ChangeMinorAxisInterval(minorAxisInterval);
	}
	private: System::Void walkersNumTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		walkers_num = walkersNumTrackBar->Value;
		numOfWalkersValueText->Text = walkersNumTrackBar->Value.ToString();
	}
	private: System::Void walkersSpeedTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		speedOfWalkersValueText->Text = walkersSpeedTrackBar->Value.ToString();
		canvas->SetWalkerSpeed(walkersSpeedTrackBar->Value);
	}
	private: System::Void simulationTypeComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
	{
		canvas->ChangeSimulationType(this->simulationTypeComboBox->SelectedIndex);
		canvas->SetResultChanged(true);
		lockAndUnlockControlsWhenSimulationTypeChanged();
	}
	private: System::Void lockAndUnlockControlsWhenSimulationTypeChanged(System::Void)
	{
		switch (this->simulationTypeComboBox->SelectedIndex) {
		case 2: // Origin to endpoint random walk
			this->infiniteStepCheckBox->Checked = false;
			this->infiniteStepCheckBox->Enabled = false;
			this->buildRandPosSimulationButton->Enabled = false;
			this->walkersNumTrackBar->Enabled = true;
			setInitialPositionZero(false);
			break;
		case 3: // Return to origin random walk
			this->infiniteStepCheckBox->Checked = true;
			this->infiniteStepCheckBox->Enabled = true;
			this->buildRandPosSimulationButton->Enabled = false;
			this->walkersNumTrackBar->Enabled = true;
			setInitialPositionZero(false);
			break;
		case 4: // Two random walk intersection
		case 5: // Two SAW intersection
			this->infiniteStepCheckBox->Checked = true;
			this->infiniteStepCheckBox->Enabled = true;
			this->buildRandPosSimulationButton->Enabled = true;
			setInitialPositionZero(false);
			this->walkersXnumUpDown1->Enabled = true;
			this->walkersYnumUpDown1->Enabled = dimension >= 2 ? true : false;
			this->walkersZnumUpDown1->Enabled = dimension == 3 ? true : false;
			this->walkersXnumUpDown2->Enabled = true;
			this->walkersYnumUpDown2->Enabled = dimension >= 2 ? true : false;
			this->walkersZnumUpDown2->Enabled = dimension == 3 ? true : false;
			this->walkersNumTrackBar->Value = walkers_num = 2;
			numOfWalkersValueText->Text = walkersNumTrackBar->Value.ToString();
			this->walkersNumTrackBar->Enabled = false;
			break;
		case 6: // Count self-avoiding random walk
			this->infiniteStepCheckBox->Checked = false;
			this->infiniteStepCheckBox->Enabled = false;
			this->buildRandPosSimulationButton->Enabled = true;
			this->walkersNumTrackBar->Enabled = true;
			setInitialPositionZero(true);
			break;
		default:
			this->infiniteStepCheckBox->Checked = true;
			this->infiniteStepCheckBox->Enabled = true;
			this->buildRandPosSimulationButton->Enabled = true;
			this->walkersNumTrackBar->Enabled = true;
			setInitialPositionZero(true);
			break;
		}
	}
	private: System::Void setInitialPositionZero(System::Boolean enabled)
	{
		this->walkersXnumUpDown1->Value = 0;	
		this->walkersYnumUpDown1->Value = 0;	
		this->walkersZnumUpDown1->Value = 0;	
		this->walkersXnumUpDown2->Value = 0;	
		this->walkersYnumUpDown2->Value = 0;	
		this->walkersZnumUpDown2->Value = 0;	
		this->walkersXnumUpDown3->Value = 0;	
		this->walkersYnumUpDown3->Value = 0;	
		this->walkersZnumUpDown3->Value = 0;	
		this->walkersXnumUpDown4->Value = 0;	
		this->walkersYnumUpDown4->Value = 0;	
		this->walkersZnumUpDown4->Value = 0;	
		this->walkersXnumUpDown5->Value = 0;	
		this->walkersYnumUpDown5->Value = 0;	
		this->walkersZnumUpDown5->Value = 0;	
		this->walkersXnumUpDown6->Value = 0;	
		this->walkersYnumUpDown6->Value = 0;	
		this->walkersZnumUpDown6->Value = 0;	
		this->walkersXnumUpDown7->Value = 0;	
		this->walkersYnumUpDown7->Value = 0;	
		this->walkersZnumUpDown7->Value = 0;	
		this->walkersXnumUpDown8->Value = 0;	
		this->walkersYnumUpDown8->Value = 0;	
		this->walkersZnumUpDown8->Value = 0;	
		this->walkersXnumUpDown9->Value = 0;	
		this->walkersYnumUpDown9->Value = 0;	
		this->walkersZnumUpDown9->Value = 0;	
		this->walkersXnumUpDown10->Value = 0;	
		this->walkersYnumUpDown10->Value = 0;	
		this->walkersZnumUpDown10->Value = 0;
		unlockPositionUpDownControl(enabled);
	}
	private: System::Void unlockPositionUpDownControl(System::Boolean enabled)
	{
		this->walkersXnumUpDown1->Enabled = enabled;
		this->walkersYnumUpDown1->Enabled = dimension>=2 ? enabled : false;
		this->walkersZnumUpDown1->Enabled = dimension==3 ? enabled : false;
		this->walkersXnumUpDown2->Enabled = enabled;
		this->walkersYnumUpDown2->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown2->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown3->Enabled = enabled;
		this->walkersYnumUpDown3->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown3->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown4->Enabled = enabled;
		this->walkersYnumUpDown4->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown4->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown5->Enabled = enabled;
		this->walkersYnumUpDown5->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown5->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown6->Enabled = enabled;
		this->walkersYnumUpDown6->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown6->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown7->Enabled = enabled;
		this->walkersYnumUpDown7->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown7->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown8->Enabled = enabled;
		this->walkersYnumUpDown8->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown8->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown9->Enabled = enabled;
		this->walkersYnumUpDown9->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown9->Enabled = dimension == 3 ? enabled : false;
		this->walkersXnumUpDown10->Enabled = enabled;
		this->walkersYnumUpDown10->Enabled = dimension >= 2 ? enabled : false;
		this->walkersZnumUpDown10->Enabled = dimension == 3 ? enabled : false;
	}
	private: System::Void dimRadioButton_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		/* This function are called twice whenever radio button value changed */

		if (oneDimRadioButton->Checked)
			this->dimension = 1;
		else if (twoDimRadioButton->Checked)
			this->dimension = 2;
		else if (threeDimRadioButton->Checked)
			this->dimension = 3;

		if (isPlaying)
		{
			playButton->Image = imageList1->Images[0]; // change image to play button image
			isPlaying = false;
		}
		canvas->NotifySimulationPlay(isPlaying);
		canvas->ChangeDimension(dimension);
		canvas->InitRandomSimulation(walkers_num, step_size, step_count, infiniteStepCheckBox->Checked, walkersSpeedTrackBar->Value);
		canvas->ClearSimulation();

		this->rewindButton->Enabled = false;
		this->playButton->Enabled = false;
		this->stopButton->Enabled = false;
		this->playFrameButton->Enabled = false;
		lockAndUnlockMinorAxisControlWhenDimensionChanged();
		lockAndUnlockControlsWhenSimulationTypeChanged();
	}
	private: System::Void lockAndUnlockMinorAxisControlWhenDimensionChanged(System::Void)
	{
		switch (this->dimension) {
		case 1:
		case 2:
			this->minorAxisIntervalTrackBar->Value = 1;
			minorAxisIntervalValueText->Text = "1";
			canvas->ChangeMinorAxisInterval(1);
			this->minorAxisIntervalTrackBar->Enabled = false;
			break;
		case 3:
			this->minorAxisIntervalTrackBar->Enabled = true;
			break;
		}
	}
	private: System::Void buildRandPosSimulationButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (isPlaying)
		{
			playButton->Image = imageList1->Images[0]; // change image to play button image
			isPlaying = false;
		}
		canvas->NotifySimulationPlay(isPlaying);
		canvas->InitRandomSimulation(walkers_num, step_size, step_count, infiniteStepCheckBox->Checked, walkersSpeedTrackBar->Value);
		canvas->NotifySimulationChanged();

		this->rewindButton->Enabled = true;
		this->playButton->Enabled = true;
		this->stopButton->Enabled = true;
		this->playFrameButton->Enabled = true;
		updateWalkersPositionValue();
		updateWalkersPositionConfig();
		unlockControlsWhenBuildClicked(false);

		logTextBox->Text = "";
		resultTextBox->Text = "";
	}
	private: System::Void buildGivenPosSimulationButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		if (isPlaying)
		{
			playButton->Image = imageList1->Images[0]; // change image to play button image
			isPlaying = false;
		}
		canvas->NotifySimulationPlay(isPlaying);
		canvas->InitGivenSimulation(walkers_num, step_size, step_count, infiniteStepCheckBox->Checked, walkersSpeedTrackBar->Value, copyWalkersPositionValue());
		canvas->NotifySimulationChanged();

		this->rewindButton->Enabled = true;
		this->playButton->Enabled = true;
		this->stopButton->Enabled = true;
		this->playFrameButton->Enabled = true;
		updateWalkersPositionConfig();
		unlockControlsWhenBuildClicked(false);

		logTextBox->Text = "";
		resultTextBox->Text = "";
	}
	private: System::Void updateWalkersPositionValue(System::Void)
	{
		const std::vector<glm::vec3>& walkers = canvas->GetWalkersPos();

		if (walkers_num == 10) {
			this->walkersXnumUpDown10->Value = Convert::ToInt32(walkers[9].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown10->Value = Convert::ToInt32(walkers[9].z);
				this->walkersZnumUpDown10->Value = Convert::ToInt32(walkers[9].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown10->Value = Convert::ToInt32(-walkers[9].y);
				this->walkersZnumUpDown10->Value = 0;
			}
			else {
				this->walkersYnumUpDown10->Value = 0;
				this->walkersZnumUpDown10->Value = 0;
			}
		}
		if (walkers_num >= 9) {
			this->walkersXnumUpDown9->Value = Convert::ToInt32(walkers[8].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown9->Value = Convert::ToInt32(walkers[8].z);
				this->walkersZnumUpDown9->Value = Convert::ToInt32(walkers[8].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown9->Value = Convert::ToInt32(-walkers[8].y);
				this->walkersZnumUpDown9->Value = 0;
			}
			else {
				this->walkersYnumUpDown9->Value = 0;
				this->walkersZnumUpDown9->Value = 0;
			}
		}
		if (walkers_num >= 8) {
			this->walkersXnumUpDown8->Value = Convert::ToInt32(walkers[7].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown8->Value = Convert::ToInt32(walkers[7].z);
				this->walkersZnumUpDown8->Value = Convert::ToInt32(walkers[7].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown8->Value = Convert::ToInt32(-walkers[7].y);
				this->walkersZnumUpDown8->Value = 0;
			}
			else {
				this->walkersYnumUpDown8->Value = 0;
				this->walkersZnumUpDown8->Value = 0;
			}
		}
		if (walkers_num >= 7) {
			this->walkersXnumUpDown7->Value = Convert::ToInt32(walkers[6].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown7->Value = Convert::ToInt32(walkers[6].z);
				this->walkersZnumUpDown7->Value = Convert::ToInt32(walkers[6].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown7->Value = Convert::ToInt32(-walkers[6].y);
				this->walkersZnumUpDown7->Value = 0;
			}
			else {
				this->walkersYnumUpDown7->Value = 0;
				this->walkersZnumUpDown7->Value = 0;
			}
		}
		if (walkers_num >= 6) {
			this->walkersXnumUpDown6->Value = Convert::ToInt32(walkers[5].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown6->Value = Convert::ToInt32(walkers[5].z);
				this->walkersZnumUpDown6->Value = Convert::ToInt32(walkers[5].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown6->Value = Convert::ToInt32(-walkers[5].y);
				this->walkersZnumUpDown6->Value = 0;
			}
			else {
				this->walkersYnumUpDown6->Value = 0;
				this->walkersZnumUpDown6->Value = 0;
			}
		}
		if (walkers_num >= 5) {
			this->walkersXnumUpDown5->Value = Convert::ToInt32(walkers[4].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown5->Value = Convert::ToInt32(walkers[4].z);
				this->walkersZnumUpDown5->Value = Convert::ToInt32(walkers[4].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown5->Value = Convert::ToInt32(-walkers[4].y);
				this->walkersZnumUpDown5->Value = 0;
			}
			else {
				this->walkersYnumUpDown5->Value = 0;
				this->walkersZnumUpDown5->Value = 0;
			}
		}
		if (walkers_num >= 4) {
			this->walkersXnumUpDown4->Value = Convert::ToInt32(walkers[3].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown4->Value = Convert::ToInt32(walkers[3].z);
				this->walkersZnumUpDown4->Value = Convert::ToInt32(walkers[3].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown4->Value = Convert::ToInt32(-walkers[3].y);
				this->walkersZnumUpDown4->Value = 0;
			}
			else {
				this->walkersYnumUpDown4->Value = 0;
				this->walkersZnumUpDown4->Value = 0;
			}
		}
		if (walkers_num >= 3) {
			this->walkersXnumUpDown3->Value = Convert::ToInt32(walkers[2].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown3->Value = Convert::ToInt32(walkers[2].z);
				this->walkersZnumUpDown3->Value = Convert::ToInt32(walkers[2].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown3->Value = Convert::ToInt32(-walkers[2].y);
				this->walkersZnumUpDown3->Value = 0;
			}
			else {
				this->walkersYnumUpDown3->Value = 0;
				this->walkersZnumUpDown3->Value = 0;
			}
		}
		if (walkers_num >= 2) {
			this->walkersXnumUpDown2->Value = Convert::ToInt32(walkers[1].x);
			if (this->dimension == 3) {
				this->walkersYnumUpDown2->Value = Convert::ToInt32(walkers[1].z);
				this->walkersZnumUpDown2->Value = Convert::ToInt32(walkers[1].y);
			}
			else if (this->dimension == 2) {
				this->walkersYnumUpDown2->Value = Convert::ToInt32(-walkers[1].y);
				this->walkersZnumUpDown2->Value = 0;
			}
			else {
				this->walkersYnumUpDown2->Value = 0;
				this->walkersZnumUpDown2->Value = 0;
			}
		}
		this->walkersXnumUpDown1->Value = Convert::ToInt32(walkers[0].x);
		if (this->dimension == 3) {
			this->walkersYnumUpDown1->Value = Convert::ToInt32(walkers[0].z);
			this->walkersZnumUpDown1->Value = Convert::ToInt32(walkers[0].y);
		}
		else if (this->dimension == 2) {
			this->walkersYnumUpDown1->Value = Convert::ToInt32(-walkers[0].y);
			this->walkersZnumUpDown1->Value = 0;
		}
		else {
			this->walkersYnumUpDown1->Value = 0;
			this->walkersZnumUpDown1->Value = 0;
		}
	}
	private: std::vector<glm::vec3> copyWalkersPositionValue(System::Void)
	{
		std::vector<glm::vec3> init_walkers_pos;

		if (this->dimension == 3) {
			init_walkers_pos.push_back(glm::vec3(
				this->walkersXnumUpDown1->Value,
				this->walkersZnumUpDown1->Value,
				this->walkersYnumUpDown1->Value));

			if (walkers_num >= 2) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown2->Value,
					this->walkersZnumUpDown2->Value,
					this->walkersYnumUpDown2->Value));
			}
			if (walkers_num >= 3) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown3->Value,
					this->walkersZnumUpDown3->Value,
					this->walkersYnumUpDown3->Value));
			}
			if (walkers_num >= 4) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown4->Value,
					this->walkersZnumUpDown4->Value,
					this->walkersYnumUpDown4->Value));
			}
			if (walkers_num >= 5) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown5->Value,
					this->walkersZnumUpDown5->Value,
					this->walkersYnumUpDown5->Value));
			}
			if (walkers_num >= 6) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown6->Value,
					this->walkersZnumUpDown6->Value,
					this->walkersYnumUpDown6->Value));
			}
			if (walkers_num >= 7) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown7->Value,
					this->walkersZnumUpDown7->Value,
					this->walkersYnumUpDown7->Value));
			}
			if (walkers_num >= 8) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown8->Value,
					this->walkersZnumUpDown8->Value,
					this->walkersYnumUpDown8->Value));
			}
			if (walkers_num >= 9) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown9->Value,
					this->walkersZnumUpDown9->Value,
					this->walkersYnumUpDown9->Value));
			}
			if (walkers_num == 10) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown10->Value,
					this->walkersZnumUpDown10->Value,
					this->walkersYnumUpDown10->Value));
			}
		}
		else if (this->dimension == 2) {
			init_walkers_pos.push_back(glm::vec3(
				this->walkersXnumUpDown1->Value,
				-this->walkersYnumUpDown1->Value, 0));

			if (walkers_num >= 2) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown2->Value,
					-this->walkersYnumUpDown2->Value, 0));
			}
			if (walkers_num >= 3) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown3->Value,
					-this->walkersYnumUpDown3->Value, 0));
			}
			if (walkers_num >= 4) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown4->Value,
					-this->walkersYnumUpDown4->Value, 0));
			}
			if (walkers_num >= 5) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown5->Value,
					-this->walkersYnumUpDown5->Value, 0));
			}
			if (walkers_num >= 6) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown6->Value,
					-this->walkersYnumUpDown6->Value, 0));
			}
			if (walkers_num >= 7) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown7->Value,
					-this->walkersYnumUpDown7->Value, 0));
			}
			if (walkers_num >= 8) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown8->Value,
					-this->walkersYnumUpDown8->Value, 0));
			}
			if (walkers_num >= 9) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown9->Value,
					-this->walkersYnumUpDown9->Value, 0));
			}
			if (walkers_num == 10) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown10->Value,
					-this->walkersYnumUpDown10->Value, 0));
			}
		}
		else {
			init_walkers_pos.push_back(glm::vec3(
				this->walkersXnumUpDown1->Value, 0, 0));

			if (walkers_num >= 2) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown2->Value, 0, 0));
			}
			if (walkers_num >= 3) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown3->Value, 0, 0));
			}
			if (walkers_num >= 4) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown4->Value, 0, 0));
			}
			if (walkers_num >= 5) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown5->Value, 0, 0));
			}
			if (walkers_num >= 6) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown6->Value, 0, 0));
			}
			if (walkers_num >= 7) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown7->Value, 0, 0));
			}
			if (walkers_num >= 8) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown8->Value, 0, 0));
			}
			if (walkers_num >= 9) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown9->Value, 0, 0));
			}
			if (walkers_num == 10) {
				init_walkers_pos.push_back(glm::vec3(
					this->walkersXnumUpDown10->Value, 0, 0));
			}
		}
		return init_walkers_pos;
	}
	private: System::Void unlockControlsWhenBuildClicked(System::Boolean enabled)
	{
		this->simulationTypeComboBox->Enabled = enabled;
		this->oneDimRadioButton->Enabled = enabled;
		this->twoDimRadioButton->Enabled = enabled;
		this->threeDimRadioButton->Enabled = enabled;
		this->stepSizeUpDown->Enabled = enabled;
		this->infiniteStepCheckBox->Enabled = enabled;
		this->axisDomainTrackBar->Enabled = enabled;
		this->minorAxisIntervalTrackBar->Enabled = enabled;
		this->minorAxisHideCheckBox->Enabled = !enabled;
		this->walkersNumTrackBar->Enabled = enabled;
		if (enabled == false)
			this->stepCountUpDown->Enabled = enabled;
		else if (infiniteStepCheckBox->Checked == false)
			this->stepCountUpDown->Enabled = enabled;
	}
	private: System::Void walkersHideCheckBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(0);
	}
	private: System::Void walkersHideCheckBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(1);
	}
	private: System::Void walkersHideCheckBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(2);
	}
	private: System::Void walkersHideCheckBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(3);
	}
	private: System::Void walkersHideCheckBox5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(4);
	}
	private: System::Void walkersHideCheckBox6_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(5);
	}
	private: System::Void walkersHideCheckBox7_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(6);
	}
	private: System::Void walkersHideCheckBox8_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(7);
	}
	private: System::Void walkersHideCheckBox9_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(8);
	}
	private: System::Void walkersHideCheckBox10_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		canvas->ToggleWalkerVisibility(9);
	}
	private: System::Void loadChart(System::Void)
	{
		this->chart1->Series->Clear();
		this->chart1->Titles->Clear();

		this->axisLabelList.Add("+X");	this->axisLabelList.Add("-X");
		this->axisLabelList.Add("+Y");	this->axisLabelList.Add("-Y");
		this->axisLabelList.Add("+Z");	this->axisLabelList.Add("-Z");

		/* set initial value of each chart column */
		int points[6] = {0, 0, 0, 0, 0, 0};

		this->chart1->Palette = ChartColorPalette::BrightPastel;
		this->chart1->Titles->Add("Total number of positive and negative move");
		this->chart1->Series->Add("Random move");
		this->chart1->Series["Random move"]->IsVisibleInLegend = false;
		this->chart1->ChartAreas["ChartArea1"]->AxisX->MajorGrid->LineDashStyle = ChartDashStyle::Dot;
		this->chart1->ChartAreas["ChartArea1"]->AxisY->MajorGrid->LineDashStyle = ChartDashStyle::Dot;

		for (int i = 0; i < 6; ++i)
		{
			this->chart1->Series["Random move"]->Points->Add(points[i]);
			this->chart1->Series["Random move"]->Points[i]->Color = i%2 ? Color::IndianRed : Color::CornflowerBlue;
			this->chart1->Series["Random move"]->Points[i]->AxisLabel = this->axisLabelList[i];
			this->chart1->Series["Random move"]->Points[i]->Label = points[i].ToString();
		}
	}
	private: System::Void updateChart(System::Void)
	{
		if (canvas->GetChartUpdate() == false)
			return;

		const std::vector<int>& points = canvas->GetCountOfPosNegMove();

		this->chart1->Series["Random move"]->Points->Clear();

		for (int i = 0; i < 6; ++i)
		{
			this->chart1->Series["Random move"]->Points->Add(points[i]);
			this->chart1->Series["Random move"]->Points[i]->Color = i % 2 ? Color::IndianRed : Color::CornflowerBlue;
			this->chart1->Series["Random move"]->Points[i]->AxisLabel = this->axisLabelList[i];
			this->chart1->Series["Random move"]->Points[i]->Label = points[i].ToString();
		}
		canvas->SetChartUpdate(false);
	}
	private: System::Void infiniteStepCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//if (infiniteStepCheckBox->Checked)
		//	stepCountUpDown->Enabled = false;
		//else
		//	stepCountUpDown->Enabled = true;

		stepCountUpDown->Enabled = !(infiniteStepCheckBox->Checked);
	}
	private: System::Void stepSizeUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		step_size = Convert::ToInt32(stepSizeUpDown->Value);
	}
	private: System::Void stepCountUpDown_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		step_count = Convert::ToInt32(stepCountUpDown->Value);
	}
	private: System::Void initQuickInstruction(System::Void)
	{
		this->tip.Add("Tip : Detailed instructions are in the [How to run] tab page");
		this->tip.Add("Tip : You can hide this tip in the [Configuration] tab page");
		this->tip.Add("Tip : First two simulation types are general simulation type, which you can modify every value of controls");
		this->tip.Add("Tip : Specific simulation type tests lock several controls");
		this->tip.Add("Tip : Specific simulation type test will show the result in [Result] tab page");
		this->tip.Add("Tip : If you want to change the value of disabled controls, try click stop button to clear the simulation.");
		this->tip.Add("Tip : You can change walker speed while running simulation");
		this->tip.Add("Tip : You can hide the walkers dynamically whenever you want to check the overlapped trace path");
		this->tip.Add("Tip : You can move camera by pressing W, A, S, D on the keyboard");
		this->tip.Add("Tip : You can drag the simulation view to rotate camera");
		this->tip.Add("Tip : You can move and rotate camera at the same time");
	}
	private: System::Void update_QuickInstructionTextBox(System::Void)
	{
		if (!quickInstructionTextBox) return;

		quickInstructionTimeInterval += deltaTime;

		if (quickInstructionTimeInterval > 10) {
			quickInstructionTimeInterval = 0;

			quickInstructionTextBox->Text = this->tip[quickInstructionIndex++];

			if (quickInstructionIndex >= this->tip.Count)
				quickInstructionIndex = 0;
		}
	}
	private: System::Void hideTipCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		this->quickInstructionTextBox->Visible = !(this->hideTipCheckBox->Checked);
	}
};
}
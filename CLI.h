#pragma once
# include <string>
# include <iostream>
# include <fstream>
# include <vector>

# include "Culture.h"
# include "csvRecordCellVar.h"

# include "ProgressBar.h"

// encoding of the commands
enum class string_code {
	exit,
	printCommands,
	startSimulation,
	printParamaters,
	setTotalSteps,
	setPeaks,
	setGeneLength,
	setMaxCellInCulture,
	setDilutionFactor,
	setDilutionPoint,
	setSaveCellReq,
	setNumberOfGeneCopies,
	setLandscapeSeed,
	usePresetGene,
	setSelectionPressure,
	setRelativePressure,
	com_none
};
class CLI{
public:
	CLI();
	
	// getters and setters for variables model
	int getTotalTimeSteps();
	void setTotalTimeSteps(int steps);
	int getTotalPeaksGene();
	void setTotalPeaksGene(int peaks);
	int getGeneLength();
	void setGeneLength(int length);
	double getMaxCellInCulture();
	void setMaxCellsInCulture(double maxCells);
	double getDilutionFactor();
	void setDilutionFactor(double factor);
	double getDilutionPoint();
	void setDilutionPoint(double point);
	double getSaveCellRequirement();
	void setSaveCellRequirement(double requirement);
	int getNumberOfGeneCopies();
	void setNumberOfGeneCopies(int num);
	void setPresetGene(int preset);
	void startSimulation();
	void setSelectionPressure(double pres);
	void setRelativePressure(double relPres);
	
private:
	// helper var for control of cli
	int running = 1;
	// helper methods for control of cli
	void startCLI();
	void processCommand(std::string);
	string_code encode(std::string const& command);
	std::vector<std::string> preprocessCommand(std::string stringCommand);
	void initGenePresets();
	// helper methods for message printing
	void printIntroMessage();
	void printParameters();
	void printCommands();
	std::string cliMessage = "IPDEsim >>> ";

	// objects and params for DE model
	int seed = 1;
	int presetGene = 0;
	int totalTimeSteps = 3000;
	int totalPeaksGene = 10;
	int geneLength = 100;
	int numberOfGenesCopies = 2;
	double maxCellsInCulture = 1000000;
	double dilutionFactor = 1;
	double dilutionPoint = 1;
	double saveCellRequirement = 0.01;
	double selectionPressure = 0.1;
	double relativePressure = 1;

	// gene presets
	std::map<std::string, std::pair<std::vector<std::vector<double>>, std::vector<double>>> presetList;
};


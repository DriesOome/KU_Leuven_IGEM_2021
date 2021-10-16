#pragma once
# include <string>
# include <list>

class csvRecordCellVar{
public:
	csvRecordCellVar(std::string cellID , double fitnessScore, int birthTimeStep, int deadTimeStep, std::list<double> cellNumberHistory);
	~csvRecordCellVar();
	std::string getCellID();
	double getFitnessScore();
	int getBirthTimeStep();
	int getDeathTimeStep();
	std::list<double>* getCellNumberHistory();
private:
	std::string cellID;
	double fitnessScore;
	int birthTimeStep;
	int deathTimeStep;
	std::list<double> cellNumberHistory;
};


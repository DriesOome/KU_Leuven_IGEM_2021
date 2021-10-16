# include "csvRecordCellVar.h"
csvRecordCellVar::csvRecordCellVar(std::string cellID, double fitnessScore, int birthTimeStep, int deadTimeStep, std::list<double> history) {
	this->cellID = cellID;
	this->fitnessScore = fitnessScore;
	this->birthTimeStep = birthTimeStep;
	this->deathTimeStep = deadTimeStep;
	this->cellNumberHistory = history;
}

csvRecordCellVar::~csvRecordCellVar(){
	cellNumberHistory.clear();
}

std::string csvRecordCellVar::getCellID(){
	return this->cellID;
}

double csvRecordCellVar::getFitnessScore(){
	return this->fitnessScore;
}

int csvRecordCellVar::getBirthTimeStep(){
	return this->birthTimeStep;
}

int csvRecordCellVar::getDeathTimeStep(){
	return this->deathTimeStep;
}

std::list<double>* csvRecordCellVar::getCellNumberHistory(){
	return &cellNumberHistory;
}

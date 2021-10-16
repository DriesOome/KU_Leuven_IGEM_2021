#include "Culture.h"


Culture::Culture(){}
Culture::~Culture() {
	for (auto const& i : listCellVariants) {
		delete i.second;
	}
	for (auto const& i : deadCellVariants) {
		delete i.second;
	}
	deadCellVariants.clear();
	listCellVariants.clear();
}
Culture::Culture(double maxCells, double dilFac, double dilPoint, double saveCellReq, double selectionPres, double relativePress){
	this->MAX_CELLS_IN_CULTURE = maxCells;
	this->DILUTION_FACTOR = dilFac;
	this->DILUTION_POINT = dilPoint;
	this->SAVE_CELL_VAR_REQUIREMENT = saveCellReq;
	this->SELECTION_PRESSURE = selectionPres;
	this->SELECTION_PRESSURE_MAXREL = relativePress;
}

void Culture::addCellVariant(CellVariant* cellVariant) {
	if (listCellVariants.insert(std::pair<std::string, CellVariant*>(cellVariant->getGenotype(), cellVariant)).second == 0) { delete cellVariant; }
	else{
		if (cellVariant->getFitnessScore() > maxFitness) {
			maxFitness = cellVariant->getFitnessScore();
		}
	}
	
}

void Culture::killCellVariant(CellVariant* cellVariant){
	listCellVariants.erase(cellVariant->getGenotype());
	if (cellVariant->getTotalNumberOfCellsHistory()*DELTA_T > MAX_CELLS_IN_CULTURE * SAVE_CELL_VAR_REQUIREMENT || cellVariant->isParent()) {
		deadCellVariants.insert(std::pair<std::string, CellVariant*>(cellVariant->getVariantID(), cellVariant));
	}
	else {delete cellVariant;}
}


double Culture::getTotalCellsInCulture(){
	double totalCellCount = 0;
	for (auto const& i : listCellVariants) {
		totalCellCount += i.second->getNumberOfCells();
	}
	return totalCellCount;
}

double Culture::getDeltaT(){
	return DELTA_T;
}

int Culture::getNumberOfCellVariants() {
	return listCellVariants.size();
}

std::map<std::string, CellVariant*>* Culture::getListCellVariants(){
	return &this->listCellVariants;
}


std::map<std::string, CellVariant*>* Culture::getListDeadCellVariants(){
	return &this->deadCellVariants;
}

void Culture::killCulture(){
	while(listCellVariants.size() > 0) {
		killCellVariant((*listCellVariants.begin()).second);
	}
}
void Culture::diluteCulture(){
	using param_t = std::poisson_distribution<int>::param_type;
	for (auto const& i : listCellVariants) {
			double dilutedNumberOfCells = i.second->getNumberOfCells() * DILUTION_FACTOR;
			dilutionDistribution.param(param_t{ dilutedNumberOfCells });
			dilutedNumberOfCells = dilutionDistribution(CultureRandGen);
			if (dilutedNumberOfCells >= 1) {
				i.second->setNumberOfCells(dilutedNumberOfCells);
			}
			else {
				i.second->setNumberOfCells(0);
			}
	}
}


void Culture::createMutants(){
	for (auto& i : listCellVariants) {
		// Determining the number of mutants that are created
		double meanNumberMutations = i.second->getNumberOfCells() * MEAN_MUTATION_RATE * (double)i.second->getLengthTargetGene() * i.second->getGenes()->size()*(1-i.second->getGenes()->at(0)->getNeutralMutationChance())*MEAN_GROWTH_RATE*DELTA_T;
		if (meanNumberMutations > 0) {
			using param_t = std::poisson_distribution<int>::param_type;
			numMutDistribution.param(param_t{ meanNumberMutations });
			int numberOfMutants = numMutDistribution(CultureRandGen);
			for (int j = 0; j < numberOfMutants; j++) {
				this->addCellVariant(i.second->mutateCellVariant(timeStep));
			}
		}		
	}
}

void Culture::growAll(){
	timeStep++;
	double totalCells = getTotalCellsInCulture();
	relativeFitness += (1-relativeFitness / maxFitness) * SELECTION_PRESSURE * SELECTION_PRESSURE_MAXREL * MEAN_GROWTH_RATE * DELTA_T;
	for (auto it = listCellVariants.rbegin(); it != listCellVariants.rend(); it++) {
		if (it->second->getNumberOfCells() >= 1) {
			it->second->grow(DELTA_T, MAX_CELLS_IN_CULTURE, totalCells, relativeFitness, SURVIVAL_RATE);
		}
		else {
			killCellVariant(it->second);
		}
	}
	createMutants();
	if (this->getTotalCellsInCulture() > MAX_CELLS_IN_CULTURE*DILUTION_POINT) {
		this->diluteCulture();
	}
	
}


# include "CellVariant.h"

// static variables
long long int CellVariant::variantCount = 1;

// Constructor
CellVariant::CellVariant(std::string parentID, int p_birthTimeStep, std::vector<Gene*> p_genes, double p_numberOfCells) {
	cellVariantID = parentID + ":" + std::to_string(variantCount++);
	birthTimeStep = p_birthTimeStep;
	genes = p_genes;
	fitnessScore = 0;
	isParentBool = 0;
	for (Gene* gene : genes) {
		fitnessScore = fitnessScore + gene->calculateFitness();
	}
	fitnessScore = fitnessScore / genes.size();
	setNumberOfCells(p_numberOfCells);
}

CellVariant::~CellVariant() {
	numberOfCellsHistory.clear();
	for (Gene* gene : genes) {
		delete gene;
	}
}

// getters and setters
int CellVariant::getVariantCount() {
	return CellVariant::variantCount;
}
std::string CellVariant::getVariantID() {
	return this->cellVariantID;
}
int CellVariant::getBirthTimeStep()
{
	return birthTimeStep;
}
int CellVariant::getLengthTargetGene() {
	return this->genes.at(0)->getLengthGene();
}
double CellVariant::getFitnessScore() {
	return this->fitnessScore;
}
double CellVariant::getNumberOfCells() {
	return this->numberOfCells;
}
double CellVariant::getTotalNumberOfCellsHistory(){
	double total = 0;
	for (double i : numberOfCellsHistory) {
		total += i;
	}
	return total;
}
void CellVariant::setNumberOfCells(double p_numberOfCells) {
	if (p_numberOfCells >= 1) {
		this->numberOfCells = p_numberOfCells;
	}
	else {
		this->numberOfCells = 0;
	}
	numberOfCellsHistory.push_back(numberOfCells); // record history
}

std::list<double>* CellVariant::getNumberOfCellsHistory(){
	return &numberOfCellsHistory;
}
std::string CellVariant::getGenotype() {
	std::string genotype = "";
	for (Gene* gene : genes) {
		genotype = genotype + gene->getGenotype();
	}
	return genotype;
}

void CellVariant::resetVariantCount() {
	variantCount = 1;
}

// methods
void CellVariant::grow(double deltaT, double carryingCap, double totalNumberOfCells, double relativeFitness, double survivalRate) {
	if (relativeFitness < fitnessScore) { relativeFitness = fitnessScore; }
	setNumberOfCells(numberOfCells 
		+ (
			( ( atanh(( fitnessScore-relativeFitness )/relativeFitness) + 1 )/2 ) * numberOfCells * (1 - (totalNumberOfCells / carryingCap) ) * MEAN_GROWTH_RATE 
			- numberOfCells *(1-survivalRate*fitnessScore/relativeFitness)  
		) * deltaT);
}

// creates new mutated cell variant object on the heap and returns the adress
CellVariant* CellVariant::mutateCellVariant(int p_birthTimeStep) {
	this->becameParent();
	int geneToMutate = rand()%genes.size();
	std::vector<Gene*> newGenes;
	for (Gene* gene : genes) {
		newGenes.push_back(new Gene(*gene));
	}
	newGenes.at(geneToMutate)->mutateGene(1);
	CellVariant* cellVar = new CellVariant(this->cellVariantID, p_birthTimeStep, newGenes, 1);
	return cellVar;
}

int CellVariant::isParent(){
	return isParentBool;
}

void CellVariant::becameParent(){
	isParentBool = 1;
}

std::vector<Gene*>* CellVariant::getGenes() {
	return &genes;
}
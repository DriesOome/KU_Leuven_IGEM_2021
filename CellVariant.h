# pragma once
# include <string>
# include <list>
# include <vector>
# include <math.h>
# include <random>
# include "Gene.h"

// helper objects
static std::default_random_engine CellVarRandGen;
// constants
const double MEAN_GROWTH_RATE = 0.083;
const double MEAN_MUTATION_RATE = 0.00005; // mutation chance per nucleotide per generation

class CellVariant{
private:
	static long long int variantCount;
	std::string cellVariantID;
	double fitnessScore;
	std::vector<Gene*> genes;
	double numberOfCells;
	int birthTimeStep;
	std::list<double> numberOfCellsHistory;
	int isParentBool;


public: 
	// constructor
	CellVariant(std::string parentID, int birthTimeStep,  std::vector<Gene*> genes, double numberOfCells);
	~CellVariant();
	// getters and setters
	int getVariantCount();
	std::string getVariantID();
	int getBirthTimeStep();
	int getLengthTargetGene();
	double getFitnessScore();
	double getNumberOfCells();
	double getTotalNumberOfCellsHistory();
	void setNumberOfCells(double numberOfCells);
	std::list<double>* getNumberOfCellsHistory();
	std::vector<Gene*>* getGenes();
	static void resetVariantCount();
	std::string getGenotype();
	// methods
	void grow(double deltaT, double carryingCap, double totalNumberOfCells, double relativeFitness, double deathRate);
	CellVariant* mutateCellVariant(int p_birthTimeStep);
	int isParent();
	void becameParent();
};


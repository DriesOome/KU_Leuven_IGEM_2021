#pragma once
# include <list>
# include <map>
# include <string>
# include <memory>
# include <random>
# include <cmath>
# include <iostream>

// constants
static double MEAN_MAX_FITNESS = 0;
static double SD_FITNESS_ON_MUTATION = 0.01;
static double SD_MAX_FITNESS = 0.5;
static double SD_INTERACTIONS = 0.5;


// helper objects


static std::normal_distribution<double> maxFitDistribution(MEAN_MAX_FITNESS, SD_MAX_FITNESS);
static std::normal_distribution<double> interactionsDistribution(0, SD_INTERACTIONS);
static std::normal_distribution<double> fitMutationDistribution(0, SD_FITNESS_ON_MUTATION);
static std::default_random_engine geneRandGen;
struct FitnessPeak {
	std::string peakID;
	int aminoAcid = 0;
	std::vector<double> fitnessAminoAcid;
};
class Gene{

private:
	int numberOfPeaks;
	int geneLength;
	std::list<FitnessPeak> landscape;
	std::shared_ptr<std::map<std::string, double>> interactions;
	double neutralMutationChance = 0;

	void initGene(Gene* gene, int p_numberOfPeaks, int p_geneLength);
	void calculateNeutralMutationChance();
	// uses numberOfPeaks variable to create peaks with a random maxFitness
	// each peak has a unique identifier
	void generatePeaks();
	void generatePeaks(std::vector<std::vector<double>> peaks);
	// Creates a map which uses the identifiers of the peaks to map interaction values to every pair of peaks
	void generateInteractions();
	void generateInteractions(std::vector<double> interactions);
public:
	Gene(int numberOfPeaks, int geneLength);
	Gene(int numberOfPeaks, int geneLength, int seed);
	Gene(const Gene& g);
	~Gene();
	Gene() = default;
	double calculateFitness();
	void mutateGene(int numMutations);
	void printGene();
	int getLengthGene();
	double getNeutralMutationChance();
	void setLandscape(std::vector<std::vector<double>> peaks, std::vector<double> interactionValues);
	std::string getGenotype();
};


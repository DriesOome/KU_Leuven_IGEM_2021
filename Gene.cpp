#include "Gene.h"
void Gene::initGene(Gene* gene, int p_numberOfPeaks, int p_geneLength) {
	gene->numberOfPeaks = p_numberOfPeaks;
	gene->geneLength = p_geneLength;
	gene->interactions = std::shared_ptr<std::map<std::string, double>>(new std::map<std::string, double>);
	gene->generatePeaks();
	gene->generateInteractions();
	gene->calculateNeutralMutationChance();
}

void Gene::calculateNeutralMutationChance(){
	neutralMutationChance = 1-((double)landscape.size() / geneLength);
}

Gene::Gene(int p_numberOfPeaks, int p_geneLength) {
	initGene(this, p_numberOfPeaks, p_geneLength);
}

Gene::Gene(int p_numberOfPeaks, int p_geneLength, int seed) {
	geneRandGen = std::default_random_engine(seed);
	initGene(this, p_numberOfPeaks, p_geneLength);
}

Gene::Gene(const Gene& g) {
	numberOfPeaks = g.numberOfPeaks;
	geneLength = g.geneLength;
	landscape = g.landscape;
	interactions = std::shared_ptr<std::map<std::string, double>>(g.interactions);
	neutralMutationChance = g.neutralMutationChance;
}

Gene::~Gene(){
	//interactions.~shared_ptr();
}

void Gene::generatePeaks() {
	std::vector<std::vector<double>> peaks;
	for (int i = 0; i < numberOfPeaks; i++) {
		int numberOfPossibleChanges = rand() % 5+2; // THIS NEEDS TO BE ADJUSTED LATER
		std::vector<double> possibleValuesInPeak;
		possibleValuesInPeak.push_back(1);
		for (int j = 1; j < numberOfPossibleChanges; j++) {
			possibleValuesInPeak.push_back(1 + pow(maxFitDistribution(geneRandGen), 2));
		}
		peaks.push_back(possibleValuesInPeak);
	}
	generatePeaks(peaks);
}
void Gene::generatePeaks(std::vector<std::vector<double>> peaks) {
	for (int i = 0; i < peaks.size(); i++) {
		FitnessPeak fitPeak;
		fitPeak.peakID = std::to_string(i);
		fitPeak.fitnessAminoAcid = peaks.at(i);
		landscape.push_back(fitPeak);
	}
}
void Gene::generateInteractions() {
	std::vector<double> interactionValues;
	for (int i = 0; i < numberOfPeaks * (numberOfPeaks - 1) / 2; i++) { interactionValues.push_back(interactionsDistribution(geneRandGen)); }
	generateInteractions(interactionValues);
}
void Gene::generateInteractions(std::vector<double> interactionValues) {
	int count = 0;
	for (int i = 0; i < numberOfPeaks; i++) {
		for (int j = 0; j < numberOfPeaks; j++) {
			if (i != j) {
				if ((*interactions).count(std::to_string(j) + std::to_string(i)) == 0) {
					(*interactions).insert(std::pair<std::string, double>(
						std::to_string(i) + std::to_string(j),
						interactionValues.at(count++)));
				}
				else {
					(*interactions).insert(std::pair<std::string, double>(
						std::to_string(i) + std::to_string(j),
						(*interactions).find(std::to_string(j) + std::to_string(i))->second));
				}
			}
			else {
				(*interactions).insert(std::pair<std::string, double>(std::to_string(i) + std::to_string(j), 0));
			}
		}
	}
}
double Gene::calculateFitness() {
	double resFit = 1;
	for (FitnessPeak peaki : landscape) {
		resFit = resFit * peaki.fitnessAminoAcid.at(peaki.aminoAcid);
		for (FitnessPeak peakj : landscape) {
			resFit = resFit * pow(1.5, interactions->find(peaki.peakID + peakj.peakID)->second * (peaki.fitnessAminoAcid.at(peaki.aminoAcid) - 1) * (peakj.fitnessAminoAcid.at(peakj.aminoAcid) - 1));
 		}
	}
	return resFit;
}
void Gene::mutateGene(int numMutations) {
	for (int i = 0; i < numMutations; i++) {
		int positionToMutate = rand() % landscape.size();
		std::list<FitnessPeak>::iterator it = landscape.begin();
		std::advance(it, positionToMutate);
		it->aminoAcid = rand() % it->fitnessAminoAcid.size();
	}
}

int Gene::getLengthGene() {
	return geneLength;
}

double Gene::getNeutralMutationChance(){
	return neutralMutationChance;
}

void Gene::setLandscape(std::vector<std::vector<double>> peaks, std::vector<double> interactionValues){
		landscape.clear(); interactions->clear();
		numberOfPeaks = peaks.size();
		generatePeaks(peaks);
		generateInteractions(interactionValues);
}

std::string Gene::getGenotype() {
	std::string genotype = "";
	for (FitnessPeak peak : landscape) {
		genotype = genotype + std::to_string(peak.aminoAcid);
	}
	return genotype;
}

void Gene::printGene() {
	std::cout << "Gene stats: \n";
	for (FitnessPeak peak : landscape) {
		double maxFitnessPeak = 0;
		for (int i = 0; i < peak.fitnessAminoAcid.size(); i++) { if (peak.fitnessAminoAcid.at(i) > maxFitnessPeak) { maxFitnessPeak = peak.fitnessAminoAcid.at(i); }}
		std::cout << "peakID: " << peak.peakID << " --- " << "current fitness: " << peak.fitnessAminoAcid.at(peak.aminoAcid) << " --- " << "max fitness: " << maxFitnessPeak << std::endl;
	}
	std::cout << "Interactions: \n";
	for (std::pair<std::string, double> interaction : (*interactions)) {
		std::cout << "InteractionID: " << interaction.first
			<< " --- " << "value: " << interaction.second << std::endl;
	}
	std::cout << "Resulting fitness: " << this->calculateFitness() << std::endl;
}



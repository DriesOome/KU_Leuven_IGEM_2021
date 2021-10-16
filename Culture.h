#pragma once
# include <map>
# include <iostream>
# include <string>
# include <random>
# include <vector>
# include "CellVariant.h"

class Culture{

// helper objects
double MAX_CELLS_IN_CULTURE = 1000000;
double DILUTION_FACTOR = 1; // Percentage by which the culture is diluted
double DILUTION_POINT = 1; // Percentage of MAX_CELLS_IN_CULTURE at which the culture is diluted.
double SURVIVAL_RATE = 1;
double DELTA_T = 0.5;
double SELECTION_PRESSURE = 0.1;
double SELECTION_PRESSURE_MAXREL = 1;
double SAVE_CELL_VAR_REQUIREMENT = 0.001;



std::default_random_engine CultureRandGen;
std::poisson_distribution<int> dilutionDistribution;
std::poisson_distribution<int> numMutDistribution;

private:
 	std::map<std::string, CellVariant*> listCellVariants;
    std::map<std::string, CellVariant*> deadCellVariants;
    int timeStep = 0;
    //ThreadPool pool = ThreadPool(std::thread::hardware_concurrency());
    double maxFitness = 1;
    double relativeFitness = 1;


public:
    Culture();
    Culture(double maxCells, double dilFac, double dilPoint, double saveCellReq, double selectionPressure, double relPress);
    ~Culture();
    void addCellVariant(CellVariant* cellVariant);
    void killCellVariant(CellVariant* cellVariant);
    double getTotalCellsInCulture();
    double getDeltaT();
    void diluteCulture();
    void createMutants();
    void growAll();
    int getNumberOfCellVariants();
    std::map<std::string, CellVariant*>* getListCellVariants();
    std::map<std::string, CellVariant*>* getListDeadCellVariants();
    void killCulture();
};


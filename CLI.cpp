#include "CLI.h"
// cli helper methods
CLI::CLI() {
    initGenePresets();
    startCLI();
}
void CLI::startCLI() {
    printIntroMessage();
    for (std::string line; std::cout << ">>> " && std::getline(std::cin, line); )
    {
        if (!line.empty()) { processCommand(line); }
        if (!running) { break; }
    }

    std::cout << "Goodbye!\n";
}
void CLI::processCommand(std::string command) {
    std::vector<std::string> preprocessedCommand = preprocessCommand(command);
    if (preprocessedCommand.size() == 1) {
        switch (encode(preprocessedCommand.at(0))) {
            case string_code::exit:
                running = 0;
                break;
            case string_code::printCommands:
                printCommands();
                break;
            case string_code::startSimulation:
                startSimulation();
                break;
            case string_code::printParamaters:
                printParameters();
                break;
            default:
                std::cout << cliMessage << "Command not recognised...\n";
        }
    }else{
        switch (encode(preprocessedCommand.at(0))) {
            case string_code::setTotalSteps:
                setTotalTimeSteps(std::stoi(preprocessedCommand.at(1)));
                break;
            case string_code::setPeaks:
                setTotalPeaksGene(std::stoi(preprocessedCommand.at(1)));
                break;
            case string_code::setGeneLength:
                setGeneLength(std::stoi(preprocessedCommand.at(1)));
                break;
            case string_code::setMaxCellInCulture:
                setMaxCellsInCulture(std::stoi(preprocessedCommand.at(1)));
                break;
            case string_code::setDilutionFactor:
                setDilutionFactor(std::stod(preprocessedCommand.at(1)));
                break;
            case string_code::setDilutionPoint:
                setDilutionPoint(std::stod(preprocessedCommand.at(1)));
                break;
            case string_code::setSaveCellReq:
                setSaveCellRequirement(std::stod(preprocessedCommand.at(1)));
                break;
            case string_code::setNumberOfGeneCopies:
                setNumberOfGeneCopies(std::stoi(preprocessedCommand.at(1)));
                break;
            case string_code::usePresetGene:
                setPresetGene(std::stoi(preprocessedCommand.at(1)));
                break;
            case string_code::setSelectionPressure:
                setSelectionPressure(std::stod(preprocessedCommand.at(1)));
                break;
            case string_code::setRelativePressure:
                setRelativePressure(std::stod(preprocessedCommand.at(1)));
                break;
            default:
                std::cout << cliMessage << "Command not recognised...\n";
         }
    }
}
string_code CLI::encode(std::string const& command){
    if (command == "exit") return string_code::exit;
    else if (command == "print_commands") return string_code::printCommands;
    else if (command == "start_simulation" || command == "start") return string_code::startSimulation;
    else if (command == "print_parameters") return string_code::printParamaters;
    else if (command == "set_total_steps") return string_code::setTotalSteps;
    else if (command == "set_num_peaks") return string_code::setPeaks;
    else if (command == "set_gene_length") return string_code::setGeneLength;
    else if (command == "set_max_cells") return string_code::setMaxCellInCulture;
    else if (command == "set_dilution_factor") return string_code::setDilutionFactor;
    else if (command == "set_dilution_point") return string_code::setDilutionPoint;
    else if (command == "set_save_cell_requirement") return string_code::setSaveCellReq;
    else if (command == "set_num_gene_copies") return string_code::setNumberOfGeneCopies;
    else if (command == "use_preset_gene") return string_code::usePresetGene;
    else if (command == "set_selection_pressure") return string_code::setSelectionPressure;
    else if (command == "set_relative_pressure") return string_code::setRelativePressure;
    else return string_code::com_none;
}
std::vector<std::string> CLI::preprocessCommand(std::string stringCommand) {
    std::vector<std::string> command;
    std::string subCommand = "";
    for (auto x : stringCommand){
        if (x == ' ') {
            command.push_back(subCommand);
            subCommand = "";
        }
        else {
            subCommand = subCommand + x;
        }
    }
    command.push_back(subCommand);
    return command;
}
void CLI::initGenePresets() {
    presetList.insert(std::pair<std::string, std::pair<std::vector<std::vector<double>>, std::vector<double>>>(
        "1", // id of preset
        std::pair<std::vector<std::vector<double>>, std::vector<double>>(
            std::vector<std::vector<double>>{ {1, 1.5, 1.2} }, // peaks
            std::vector<double>{}))); // interaction values
    presetList.insert(std::pair<std::string, std::pair<std::vector<std::vector<double>>, std::vector<double>>>(
        "3", // id of preset
        std::pair<std::vector<std::vector<double>>, std::vector<double>>(
            std::vector<std::vector<double>>{ {1, 1.2, 1.5}, { 1, 2.2, 1.7 }, { 1, 1.4, 1.1, 1.5, 1.3 }}, // peaks
            std::vector<double>{-1, 3, -2}))); // interaction values
}

// cli message methods
void CLI::printIntroMessage() {
    std::cout << "Welcome to: \n"
        << " _____ _____  _____  ______    _____ _\n"
        << "|_   _|  __ \\|  __ \\|  ____|  / ____(_)\n"
        << "  | | | |__) | |  | | |__    | (___  _ _ __ ___\n"
        << "  | | |  ___/| |  | |  __ |   \\___ \\| | '_ ` _ \\ \n"
        << " _| |_| |    | |__| | |____   ____) | | | | | | |\n"
        << "|_____|_|    |_____/|______| |_____/|_|_| |_| |_|\n\n";
    std::cout << "Type 'print_commands' to view the list of possible commands\n";
}
void CLI::printParameters() {
    std::cout << cliMessage << "--- The current parameters are: \n"
        << cliMessage << "total time steps: " << totalTimeSteps << "\n"
        << cliMessage << "total peaks in fitness landscape: " << totalPeaksGene << "\n"
        << cliMessage << "gene length: " << geneLength << "\n"
        << cliMessage << "number of gene copies: " << numberOfGenesCopies << "\n"
        << cliMessage << "max cells in culture: " << maxCellsInCulture << "\n"
        << cliMessage << "dilution factor: " << dilutionFactor << "\n"
        << cliMessage << "dilution point: " << dilutionPoint << "\n"
        << cliMessage << "save cell requirement variable: " << saveCellRequirement << "\n"
        << cliMessage << "selection pressure: " << selectionPressure << "\n"
        << cliMessage << "relative selection pressure: " << relativePressure << "\n";

}
void CLI::printCommands() {
    std::cout << cliMessage << "--- The possible commands are: ---\n\n";
    std::cout << "1) start_simulation: \n"
        << "Starts the IPDE simulation with the given parameters\nThe resuslts of the simulation will be stored in a csv file in the same directory as the application" << "\n\n";
    std::cout << "2) exit: \n"
        << "Terminates the program" << "\n\n";
    std::cout << "3) print_parameters: \n"
        << "Prints all parameters with their current values" << "\n\n";
    std::cout << "4) set_total_steps: \n"
        << "The simulation will run the amount of steps given by this command" << "\n\n";
    std::cout << "5) set_num_peaks: \n"
        << "The fitness landscape of the gene will have the number of peaks given by this command\nThe more peaks, the more complex the landscape is" << "\n\n";
    std::cout << "6) set_gene_length: \n"
        << "The gene length repressents the frame where mutations can happen\nA longer mutation frame means more mutations and thus more cell variants" << "\n\n";
    std::cout << "7) set_num_gene_copies: \n"
        << "The amount of ploïdy" << "\n\n";
    std::cout << "8) set_max_cells: \n"
        << "The maximum cells in the culture repressents the carrying capacity of the culture" << "\n\n";
    std::cout << "9) set_dilution_factor: \n"
        << "The dilution factor a number between 0 and 1 which repressents how much the culture is diluted every time\nLower dilution factors mean more dilution and result in more loss of cell variants who are still growing" << "\n\n";
    std::cout << "10) set_dilution_point: \n"
        << "The dilution point is a number between 0 and 1 which repressents the point at which the culture is diluted\nA dilution point with value 1 means the culture is diluted when it reached its carrying capacity" << "\n\n";
    std::cout << "11) set_save_cell_requirement: \n"
        << "Only significant cells are kept in the results to avoid resulting dataframes from getting to large memory-wise\nThe variable is a number between 0 and 1 and repressents the stringency with which significant cells are kept" << "\n\n";
    std::cout << "12) use_preset_gene: \n"
        << "Sets the fitness landscape of the gene to a certain preset\nPossible values are: 1 - 3 - 10" << "\n\n";
    std::cout << "13) set_selection_pressure: \n"
        << "Determines how fast the selection pressure will increase" << "\n\n";
    std::cout << "14) set_relative_pressure: \n"
        << "When equal to x, the selection pressure will grow to a value equal to the fitness of the fittest mutant times x" << "\n\n";

}

// getters and setters
void CLI::setTotalTimeSteps(int steps) {
    if (steps > 0) {
        totalTimeSteps = steps;
    }
    else {
        std::cout << cliMessage << "Value has to be non-zero and positive\n";
    }
}
int CLI::getTotalPeaksGene(){
    return totalPeaksGene;
}
void CLI::setTotalPeaksGene(int peaks){
    if (peaks > 0) {
        totalPeaksGene = peaks;
    }
    else {
        std::cout << cliMessage << "Value has to be non-zero and positive\n";
    }
}
int CLI::getGeneLength(){
    return geneLength;
}
void CLI::setGeneLength(int length){
    if (length > 0) {
        geneLength = length;
    }
    else {
        std::cout << cliMessage << "Value has to be non-zero and positive\n";
    }
}
double CLI::getMaxCellInCulture(){
    return maxCellsInCulture;
}
void CLI::setMaxCellsInCulture(double maxCells){
    if (maxCells > 0) {
        maxCellsInCulture = maxCells;
    }
    else {
        std::cout << cliMessage << "Value has to be non-zero and positive\n";
    }
}
double CLI::getDilutionFactor(){
    return dilutionFactor;
}
void CLI::setDilutionFactor(double factor){
    if (factor > 0 && factor <=1) {
        dilutionFactor = factor;
    }
    else {
        std::cout << cliMessage << "Value has to be higher then 0 and lower then or equal to 1\n";
    }
}
double CLI::getDilutionPoint(){
    return dilutionPoint;
}
void CLI::setDilutionPoint(double point){
    if (point > 0 && point <= 1) {
        dilutionPoint = point;
    }
    else {
        std::cout << cliMessage << "Value has to be higher then 0 and lower or equal to 1\n";
    }
}
double CLI::getSaveCellRequirement(){
    return saveCellRequirement;
}
void CLI::setSaveCellRequirement(double requirement){
    if (requirement > 0 && requirement <= 1) {
        saveCellRequirement = requirement;
    }
    else {
        std::cout << cliMessage << "Value has to be higher then 0 and lower or equal to 1\n";
    }
}
int CLI::getNumberOfGeneCopies(){
    return numberOfGenesCopies;
}
void CLI::setNumberOfGeneCopies(int num){
    if (num > 0) {
        numberOfGenesCopies = num;
    }
    else {
        std::cout << cliMessage << "Value has to be non-zero and positive\n";
    }
}
int CLI::getTotalTimeSteps() {
    return totalTimeSteps;
}
void CLI::setPresetGene(int preset) {
    presetGene = preset;
}
void CLI::setSelectionPressure(double pres) {
    if (pres >= 0 && pres <= 1) {
        selectionPressure = pres;
    }
    else {
        std::cout << cliMessage << "Value has to be higher then or equal to 0 and lower or equal to 1\n";
    }
}

void CLI::setRelativePressure(double relPress){
    if (relPress > 0) {
        relativePressure = relPress;
    }
    else {
        std::cout << cliMessage << "Value has to be higher then 0\n";
    }
}

void CLI::startSimulation() {
    std::cout << "Creating culture" << "\n";
    Culture culture = Culture(maxCellsInCulture, dilutionFactor, dilutionPoint, saveCellRequirement, selectionPressure, relativePressure);
    Gene gene = Gene(totalPeaksGene, geneLength, 1);
    if (presetList.count(std::to_string(presetGene))) {
        gene.setLandscape(presetList.find(std::to_string(presetGene))->second.first, presetList.find(std::to_string(presetGene))->second.second);
    }
    std::vector<Gene*> genes;
    for (int i = 0; i < numberOfGenesCopies; i++) { Gene* copy = new Gene(gene); genes.push_back(copy); };
    gene.printGene();

    std::cout << "Running simulation" << "\n";
    ProgressBar progress = ProgressBar(totalTimeSteps);
    CellVariant::resetVariantCount();
    CellVariant* cellVar = new CellVariant("0", 0, genes, 10000); 
    culture.addCellVariant(cellVar);
    for (int i = 0; i < totalTimeSteps; i++) {
        culture.growAll();
        progress.setMessage("Cell variant count: "+std::to_string(culture.getListCellVariants()->size()));
        progress.updateProgress(i);
    }
    culture.killCulture();
    progress.done();
    // creating dataframe for csv file
    //ThreadPool pool = ThreadPool(24);
    std::cout << "Creating dataframe\n";
    std::list<csvRecordCellVar*> records;
    progress = ProgressBar((*culture.getListDeadCellVariants()).size());
    for (auto const& i : *culture.getListDeadCellVariants()) {
        csvRecordCellVar* record = new csvRecordCellVar(
            i.second->getVariantID() + " genotype: " + i.second->getGenotype(),
            i.second->getFitnessScore(),
            i.second->getBirthTimeStep(),
            i.second->getBirthTimeStep() + i.second->getNumberOfCellsHistory()->size() - 1,
            *(i.second->getNumberOfCellsHistory()));
        records.push_back(record);
        progress.incOneStep();
    }
    progress.done();
    // writing csv file
    std::cout << "Writing csv\n";
    std::ofstream file;
    file.open("./results.csv");
    std::list<csvRecordCellVar*>::iterator it = records.begin();
    // adding column names
    std::cout << "--Writing column names\n";
    file << "time,";
    while (it != records.end()) {
        file << "ID: " << (*it)->getCellID() << " fit: " << (*it)->getFitnessScore();
        if (++it != records.end()) {
            file << ",";
        }
    }
    file << "\n";
    std::cout << "--Writing data\n";
    it = records.begin();
    if (records.begin() != records.end()) { // checking if records is non empty to avoid crash
        progress = ProgressBar(totalTimeSteps);
        for (int i = 0; i < totalTimeSteps; i++) {
            file << i * culture.getDeltaT() << ",";
            while (it != records.end()) {
                double num = 0;
                if ((*it)->getBirthTimeStep() <= i && (*it)->getDeathTimeStep() > i) {
                    num = *((*it)->getCellNumberHistory())->begin();
                    (*it)->getCellNumberHistory()->pop_front();
                }
                file << num;
                if (++it != records.end()) {
                    file << ",";
                }
            }
            file << "\n";
            it = records.begin();
            progress.incOneStep();
        }
        progress.done();

    }
    else {
        std::cout << "--! no data generated !";
    }
    for (csvRecordCellVar* record : records) {
        delete record;
    }
    file.close();
}
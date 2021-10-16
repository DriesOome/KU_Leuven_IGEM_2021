#include "ProgressBar.h"

ProgressBar::ProgressBar(int steps){
    currentStep = 0;
	totalSteps = steps;
}
void ProgressBar::setMessage(std::string newMessage) {
    this->message = newMessage;
}
void ProgressBar::updateProgress(int step){
    int barWidth = 70;
    currentStep = step;
    float progress = (float)step / (float)totalSteps;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " % || "<<message <<"\r";
    std::cout.flush();
}

void ProgressBar::incOneStep(){
    updateProgress(++currentStep);
}

void ProgressBar::done(){
    updateProgress(totalSteps);
    std::cout << std::endl;
}

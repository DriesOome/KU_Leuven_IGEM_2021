#pragma once
# include <iostream>
# include <string>
class ProgressBar{
private:
	int currentStep;
	int totalSteps;
	std::string message = "";
public:
	ProgressBar(int steps);
	void updateProgress(int step);
	void setMessage(std::string newMessage);
	void incOneStep();
	void done();
};


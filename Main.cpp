#include <iostream>
#include <string>
#include "MarkovChain.h"
using namespace std;

enum MenuStage { MAIN, FILE_SELECTION, SEED_INPUT, GENERATED, PROGRAM_TERMINATED};

void printMenu(MenuStage currentStage)
{
	if (currentStage == MAIN)
	{
		std::cout << " " << std::endl;
		std::cout << "Welcome to the Title Generator!" << std::endl;
		std::cout << "1. Select from a list of Genres" << std::endl;
		std::cout << "2. Quit" << std::endl;
	}
	else if (currentStage == FILE_SELECTION)
	{
		std::cout << " " << std::endl;
		std::cout << "Great! Choose one of the following." << std::endl;
		std::cout << "1. Rap / Hip Hop" << std::endl;
		std::cout << "2. Rock" << std::endl;
		std::cout << "3. Country" << std::endl;
		std::cout << "4. Back to Main Menu" << std::endl;
	}
	else if (currentStage == SEED_INPUT)
	{
		std::cout << " " << std::endl;
		std::cout << "What word would you like to generate the text from? Enter ? for a list of the most common words." << std::endl;
	}
	else if (currentStage == GENERATED)
	{
		std::cout << " " << std::endl;
		std::cout << "Want to generate another?" << std::endl;
		std::cout << "1. Back to Main Menu" << std::endl;
		std::cout << "2. Quit" << std::endl;
	}
}

MenuStage processInput(MarkovChain *mc, MenuStage currentStage, std::string userInput)
{
	if (currentStage == MAIN)
	{
		if (userInput == "1")
		{
			return FILE_SELECTION;
		}
		else if (userInput == "2")
		{
			return PROGRAM_TERMINATED;
		}
	}
	else if (currentStage == FILE_SELECTION)
	{
		if (userInput == "1")
		{
			mc->generateFromFile("testFile1.txt");
		}
		else if (userInput == "2")
		{
			mc->generateFromFile("testFile2.txt");
		}
		else if (userInput == "3")
		{
			mc->generateFromFile("testFile3.txt");
		}
		else if (userInput == "4")
		{
			return MAIN;
		}
		if (!mc->isEmpty())
		{
			return SEED_INPUT;
		}
	}
	else if (currentStage == SEED_INPUT)
	{
		if (userInput == "?")
		{
			mc->printMostCommon(10);
			return SEED_INPUT;
		}
		else
		{
			if (mc->generateText(userInput))
			{
				return GENERATED;
			}
			else
			{
				std::cout << "It looks like that word doesn't appear in the file, please try a different one!" << std::endl;
				return SEED_INPUT;
			}
		}
	}
	else if (currentStage == GENERATED)
	{
		if (userInput == "1")
		{
			mc->clearWordList();
			return MAIN;
		}
		if (userInput == "2")
		{
			return PROGRAM_TERMINATED;
		}
	}

	std::cout << "Invalid input please try again!" << std::endl << std::endl;
	return currentStage;

}

int main()
{
	MenuStage currentStage = MAIN;

	MarkovChain *mc = new MarkovChain;
    std::string userInput;

	while(currentStage != PROGRAM_TERMINATED)
    {
		printMenu(currentStage);

		getline(cin, userInput);

		currentStage = processInput(mc, currentStage, userInput);

    }
    return 0;
}

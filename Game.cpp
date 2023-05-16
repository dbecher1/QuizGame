#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "UnusedValue"
//
// Created by debec on 5/16/2023.
//

#include "Game.h"
#include <iostream>
#include <chrono>


void Game::Run() {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::srand(seed);

    loadData();
    presentUserPrompt();

    bool inputReceived = false;

    while(!inputReceived) {
        std::string result;
        std::cin >> result;
        int num;
        try {
            num = std::stoi(result);
        }
        catch (std::out_of_range &e) {
            std::cout << "Error! Input out of range. Please try again with valid input." << std::endl;
            presentUserPrompt();
            continue;
        }
        catch (std::invalid_argument &e) {
            std::cout << "Error! Invalid input. Please try again with valid input." << std::endl;
            presentUserPrompt();
            continue;
        }
        switch (num) {
            case 1: {
                std::cout << "Week 1" << std::endl;
                currentContent = &week1Answers;
                inputReceived = true;
                break;
            }
            case 2: {
                // currentContent = &week2Answers;
                std::cout << "This doesn't exist yet. Breaking... :(" << std::endl;
                inputReceived = true;
                break;
            }
            default: {
                std::cout << "Invalid input! Please try again." << std::endl;
                break;
            }
        }
    }
    bool playGame = true;
    do {
        bool answer = generateAndAskQuestion();
        if (answer) {
            std::cout << "Correct! Would you like another question? (y/n)" << std::endl;
            bool yOrN = yesOrNo(true);
            if (yOrN) {
                continue;
            }
            else {
                playGame = false;
            }
        }
        else {
            std::cout << "Incorrect!\nThe correct answer is: ";
            std::cout << currQuestion.answer << std::endl;
            std::cout << "Would you like to play again? (y/n)" << std::endl;
            bool yOrN = yesOrNo(false);
            if (yOrN) {
                continue;
            }
            else {
                playGame = false;
            }
        }
    } while (playGame);
}

void Game::presentUserPrompt() {
    std::cout << "Welcome! Enter one of the following to select material: " << std::endl;
    for (const auto& week : contentList) {
        std::cout << week.first << ": " << week.second << std::endl;
    }
}

void Game::loadData() {
    // TODO: populate
}

bool Game::generateAndAskQuestion() {

    bool answerCorrect = false;

    int rand1 = std::rand() % currentContent->size();
    currQuestion = currentContent->at(rand1);
    currentIndex = rand1;
    std::string possibleAnswers[4];
    int randIndex = std::rand() % 4;
    possibleAnswers[randIndex] = currQuestion.answer;
    int correctAnswer = randIndex;

    std::set<int> usedIndices;
    usedIndices.emplace(randIndex);

    do {
        int rand2 = std::rand() % Answers.size();
        auto possAnswer = Answers[rand2];
        randIndex = std::rand() % 4;
        bool indexUsed = false;
        for (auto x : usedIndices) {
            if (x == randIndex) {
                indexUsed = true;
                break;
            }
        }
        if (!indexUsed) {
            possibleAnswers[randIndex] = possAnswer;
            usedIndices.emplace(randIndex);
        }
    } while (usedIndices.size() < 4);

    std::cout << currQuestion.text << std::endl;
    int i = 1;
    for (const auto &a : possibleAnswers) {
        std::cout << i << ") " << a << std::endl;
        i++;
    }
    std::cout << "Enter your answer: " << std::endl;

    int num;
    bool input = false;
    while (!input) {
        std::string result;
        std::cin >> result;
        try {
            num = std::stoi(result);
        }
        catch (std::out_of_range &e) {
            std::cout << "Error! Input out of range. Please try again with valid input." << std::endl;
            continue;
        }
        catch (std::invalid_argument &e) {
            std::cout << "Error! Invalid input. Please try again with valid input." << std::endl;
            continue;
        }
        if (num < 1 || num > 4) {
            std::cout << "Error! Input out of range. Please try again with valid input." << std::endl;
            continue;
        }
        else {
            input = true;
        }
    }

    if ((num - 1) == correctAnswer) {
        answerCorrect = true;
    }
    return answerCorrect;
}

bool Game::yesOrNo(bool remove) {
    bool result = true;
    char c;
    std::cin >> c;
    switch (c) {
        case 'y': {
            if (remove) {
                currentContent->erase(currentContent->begin() + currentIndex);
            }
            // remove the question just used from the pool
            break;
        }
        case 'n': {
            result = false;
            break;
        }
        default: {
            std::cout << "Invalid input! Qutting..." << std::endl;
            result = false;
            break;
        }
    }
    return result;
}

bool operator == (Question& val1, Question& val2) {
    return (val1.text == val2.text) && (val1.answer == val2.answer);
}

#pragma clang diagnostic pop
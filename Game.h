//
// Created by debec on 5/16/2023.
//

#ifndef QUIZGAME_GAME_H
#define QUIZGAME_GAME_H

#include <map>
#include <string>
#include <vector>
#include <set>

struct Question {
    std::string text; // actual content of the question
    std::string answer; // self-explanatory
};



class Game {

public:
    Game() = default;
    void Run();
private:
    void loadData();
    void presentUserPrompt();

    bool generateAndAskQuestion();
    bool yesOrNo(bool remove);

    std::map<int, std::string> contentList = {
            {1, "Week 1"},
            {2, "Week 2"}
    };

    std::vector<Question>* currentContent;
    Question currQuestion;
    int currentIndex;
    std::vector<Question> week1Answers = {
            {{"Variability"}, {"Successive observations of a system or phenomenon do not produce exactly the same results"}},
            {{"Outlier"}, {"An observation that differs considerably from the main body of the data"}},
            {{"Statistical thinking"}, {"The process used to describe variability and used to make decisions in the face of it"}},
            {{"Statistical inference"}, {"The process of reasoning from data to a whole population"}},
            {{"Sample"}, {"A subset of the population containing the observed objects or outcomes and the resulting data from these objects or outcomes"}},
            {{"Population"}, {"The entire collection of objects or outcomes about which data are collected"}},
    }; // all the questions and their accompanying answers
    std::vector<Question> week2Answers;
    std::vector<std::string> Answers = {
            {"Successive observations of a system or phenomenon do not produce exactly the same results"},
            {"An observation that differs considerably from the main body of the data"},
            {"The process used to describe variability and used to make decisions in the face of it"},
            {"The process of reasoning from data to a whole population"},
            {"A subset of the population containing the observed objects or outcomes and the resulting data from these objects or outcomes"},
            {"The entire collection of objects or outcomes about which data are collected"}
    }; // a pool of all answers to pick from
};


#endif //QUIZGAME_GAME_H

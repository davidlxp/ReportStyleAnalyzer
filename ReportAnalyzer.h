//
// Created by Xinpeng Liu on 4/30/22.
//

#ifndef REPORTSTYLEANALYZER_REPORTANALYZER_H
#define REPORTSTYLEANALYZER_REPORTANALYZER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "AVL.cpp"

using namespace std;

class ReportAnalyzer {
private:
    // a vector of special symbols to be removed from string, so only words left in the string
    vector<string> symbolToRemove { ",", "!", "?", ".", "\"", ";", ":", "-", " '", "' "};

    // a vector of symbols which represents the ending of a sentence
    vector<string> sentenceEndSymbol {".", "!", "?"};

    // the threshold for identifying if a word is used too often
    float barWordsTooOften = 0.05;

    // the threshold for identifying if the average length of sentences is too long
    int barSentenceTooLong = 10;

    // the threshold for identifying if the average length of words is too long
    int barWordTooLong = 5;

public:

    /**
     * @Brief Function read a text file and save the content to a string
     */
    string readTextFile(string& fileAddress);

    /**
     * @Brief Function convert all characters in a string to lower case
     */
    void lowerString(string& text);

    /**
     * @Brief Function split a text at certain string.
     * @Input "strToSplit" stands for the text to be split. "splitAt" stands
     * for the string pattern where the program should split the string at
     * @Output a vector of strings which split from the text
     * @Example strToSplit = "hey, how are you, I'm good" & splitAt = ","
     * ===> The result is ["hey", "how are you", "I'm good"]
     */
    vector<string> splitString(string strToSplit, string splitAt);

    /**
     * @Brief Function combine a vector of strings to a whole string
     * @Input "listOfString" are partial strings stored in a vector. "connectWith" is
     * a string which to be added between those partial strings to be combined
     * @Output a whole string combined from those partial strings
     * @Example listOfString = ["hey", "how are you", "I'm good"] & connectWith = " "
     * ===> The result is "hey how are you I'm good"
     */
    string combineStrings(vector<string>& listOfString, string connectWith);

    /**
     * @Brief Function remove all special symbols which defined
     * in this class from text string
     * @Example text = "I'm a good man! So I help other."
     * ===> The result is "I'm a good man So I help other"
     */
    void removeSpecialSymbols(string& text);

    /**
     * @Brief Function remove all extra spaces in the string
     * @Example text = "I'm    a good    man"
     * ===> The result is "I'm a good man"
     */
    void removeExtraSpaces(string& text);

    /**
     * @Brief Function clean the input text (string) and extract the cleaned words from it
     * @Example text = "I'm a good man! So I help other."
     * ===> The result is ["i'm", "a", "good", "man", "so", "i", "help", "other"]
     */
    vector<string> extractCleanWords(string text);

    /**
     * @Brief Function extracts sentences from a text file
     * @Example text = "I'm a good man! So I help other."
     * ===> The result is ["I'm a good man!", "So I help other."]
     */
    vector<string> extractSentence(string text);

    /**
     * @Brief Function inserts all words extracted from the text into a AVL tree
     * @Input "words" is a vector of words which extracted from the text file,
     * and "tree" is the tree which we want to insert the words into
     */
    void insertWordsToTree(vector<string>& words, AVLtree<string>& tree);

    /**
     * @Brief Function analyze a report and provide a printed result
     */
    void analyzeReport(string fileAddress);

    /**
     * @Brief A utility function for printing a vector
     */
    void printVector(const vector<string>& vec);

    /**
     * @Brief A function remove empty string from a vector of strings
     */
    void removeEmptyFromVector(vector<string>& vec);

    /**
     * @Brief Function gets total number of words in the provided text
     * @Input An iterator of the tree
     */
    int getWordsNum(tnode<string>*& I);

    /**
     * @Brief Function gets number of unique words in the provided text
     * @Input An iterator of the tree
     */
    int getUniWordsNum(tnode<string>*& I);

    /**
     * @Brief Function gets number of unique words which has more than 3 letters
     * @Input An iterator of the tree
     */
    int getUniMoreThan3LettersNum(tnode<string>*& I);

    /**
     * @Brief Function gets sum of the length of all words appeared in the text
     * @Input An iterator of the tree
     */
    int getTotalLenOfWords(tnode<string>*& I);

    /**
     * @Brief Function fills up a hashmap which contains index (1st letter) of words,
     * and corresponding words which appeared in the text
     * @Input An iterator of the tree, and a hashmap for storing index and words
     */
    void getIndexMapOfWords(tnode<string>*& I, unordered_map<char, string>& map);

    /**
     * @Brief Function gets the total number of words who has more than 3 letters
     * @Input An iterator of the tree
     */
    int getMoreThan3LettersNum(tnode<string>*& I);

    /**
     * @Brief Function gets the words which used too often
     * @Input An iterator of the tree. An vector to store the words which used too often.
     * And, a variable indicates "total number of words which has more than 3 letters" to
     * help with judging if words are used too often
     * @RuleOfTooOften WORDS OF MORE THAN 3 LETTERS THAT ARE USED MORE THAN 5% OF THE TOTAL
     * NUMBER OF WORDS OF MORE THAN 3 LETTERS
     */
    void getWordsUsedTooOften(tnode<string>*& I, vector<string>& wordsTooOften, int& moreThan3LetterNum);


};


#endif //REPORTSTYLEANALYZER_REPORTANALYZER_H

/************************************************************************/
/* Programmer: Xinpeng Liu                                              */
/* Date: May 1, 2022                                                    */
/* Purpose:  The implementation of ReportAnalysis class                 */
/************************************************************************/

#include "ReportAnalyzer.h"

string ReportAnalyzer::readTextFile(string& fileAddress) const
{
    string text;                                                        // final text to be returned

    string line;                                                        // a line of text
    ifstream file(fileAddress);

    if (file.is_open())
    {
        while (getline(file, line))                              // get all lines
            text.append(" ").append(line);

        file.close();
    }
    else
        cout << "Unable to open file";

    return text;
}

void ReportAnalyzer::lowerString(string& text) const
{
    string lowerText;
    for (char c : text)
        lowerText += tolower(c);
    text = lowerText;
}

vector<string> ReportAnalyzer::splitString(string strToSplit, string splitAt) const
{
    vector<string> strPartList;
    int found;                                                          // index where the splitPoint reside
    int len = splitAt.length();                                         // the length of the pattern to split at

    while ((found = strToSplit.find(splitAt)) != string::npos)
    {
        string strPart = strToSplit.substr(0, found);
        strToSplit = strToSplit.substr(found + len);                 // renew the string line
        strPartList.push_back(strPart);                                 // Put partial string into vector
    }
    strPartList.push_back(strToSplit);                                  // put last partial string into the vector
    return strPartList;
}

string ReportAnalyzer::combineStrings(vector<string>& listOfString, string connectWith) const
{
    string out;

    int size = listOfString.size();
    for (int i=0; i<size; ++i) {
        out += listOfString[i];
        if(i!=size-1)
            out += connectWith;
    }
    return out;
}

void ReportAnalyzer::removeSpecialSymbols(string& text) const
{
    vector<string> tempVec;                                 // vector stores partial strings during removing process

    // remove all the symbols
    for (string s : symbolToRemove)
    {
        tempVec = ReportAnalyzer::splitString(text, s);
        text = ReportAnalyzer::combineStrings(tempVec," ");
    }
}

void ReportAnalyzer::removeExtraSpaces(string& text) const
{
    vector<string> tempVec;                                 // vector stores partial strings during removing process
    vector<string> finalVec;                                // vector after removing all the extra spaces

    // filter out the extra spaces from tempVec vector
    tempVec = ReportAnalyzer::splitString(text, " ");
    for (string& s : tempVec)
    {
        if (s != "")
            finalVec.push_back(s);
    }

    text = combineStrings(finalVec, " ");
}

vector<string> ReportAnalyzer::extractCleanWords(string text) const
{
    lowerString(text);                                   // lower case all the characters in the string
    removeSpecialSymbols(text);                          // remove all special symbols
    removeExtraSpaces(text);                             // remove extra spaces from the string

    return splitString(text, " ");          // convert cleaned string to a list of words
}

vector<string> ReportAnalyzer::extractSentence(string text) const
{
    vector<string> vec;                                      // final vector which saves split sentence from text
    vec.push_back(text);                                     // initialize the vector

    vector<string> t1;                                       // temp vectors hold sentence which need further process
    vector<string> t2;

    // 1. extracting the sentences
    for (string s : sentenceEndSymbol)
    {
        for (string& sen : vec)
        {
            // split the string at ending symbol
            t1 = splitString(sen, s);

            // appending the ending symbol to the splitted sentence, expect the last one
            for (int i=0; i<t1.size()-1; ++i)
                t1[i] = t1[i] + s;

            // save all the sentences into temp vector 2
            t2.insert(t2.end(), t1.begin(), t1.end());
        }

        // transfer value to "vec" after splitting based on one ending symbol
        vec = t2;

        // remove all elements from t1 and t2 for the next round
        t1.clear();
        t2.clear();
    }

    // 2. cleaning the sentences
    for (string& sen : vec)                                  // removing extra spaces for all sentences in vector
        removeExtraSpaces(sen);
    removeEmptyFromVector(vec);                           // removing the empty string from the vector

    return vec;
}

void ReportAnalyzer::insertWordsToTree(vector<string>& words, AVLtree<string>& tree) const
{
    for (string& w : words)
        tree.insert(w);
}

void ReportAnalyzer::printVector(const vector<string>& vec) const
{
    for (const string& s : vec)
        cout << s << endl;
}

void ReportAnalyzer::removeEmptyFromVector(vector<string>& vec) const
{
    vector<string> temp;
    for (string& s : vec)
    {
        if (!s.empty())
            temp.push_back(s);
    }
    vec = temp;
}

int ReportAnalyzer::getWordsNum(tnode<string>*& I) const
{
    if (I == nullptr)
        return 0;
    else
        return I->count + getWordsNum(I->left) + getWordsNum(I->right);
}

int ReportAnalyzer::getUniWordsNum(tnode<string>*& I) const
{
    if (I == nullptr)
        return 0;
    else
        return 1 + getUniWordsNum(I->left) + getUniWordsNum(I->right);
}

int ReportAnalyzer::getUniMoreThan3LettersNum(tnode<string>*& I) const
{
    if (I == nullptr)
        return 0;
    else if (I->info.length() > 3)
        return 1 + getUniMoreThan3LettersNum(I->left) + getUniMoreThan3LettersNum(I->right);
    else
        return 0 + getUniMoreThan3LettersNum(I->left) + getUniMoreThan3LettersNum(I->right);
}

int ReportAnalyzer::getTotalLenOfWords(tnode<string>*& I) const
{
    if (I == nullptr)
        return 0;
    else
    {
        int tempLen = I->info.length() * I->count;
        return tempLen + getTotalLenOfWords(I->left) + getTotalLenOfWords(I->right);
    }
}

void ReportAnalyzer::getIndexMapOfWords(tnode<string>*& I, unordered_map<char, string>& map) const
{
    if (I == nullptr)
        return;
    else
    {
        map[I->info[0]] += (I->info + "\n");
        getIndexMapOfWords(I->left, map);
        getIndexMapOfWords(I->right, map);
    }
}

int ReportAnalyzer::getMoreThan3LettersNum(tnode<string>*& I) const
{
    if (I == nullptr)
        return 0;
    else if (I->info.length() > 3)
        return I->count + getMoreThan3LettersNum(I->left) + getMoreThan3LettersNum(I->right);
    else
        return 0 + getMoreThan3LettersNum(I->left) + getMoreThan3LettersNum(I->right);
}

void ReportAnalyzer::getWordsUsedTooOften(tnode<string>*& I, vector<string>& wordsTooOften,
                                          int& moreThan3LetterNum) const
{
    if (I == nullptr)
        return;
    else
    {
        if (I->info.length() > 3 && 1.0 * I->count/moreThan3LetterNum > barWordsTooOften)
            wordsTooOften.push_back(I->info);

        getWordsUsedTooOften(I->left, wordsTooOften, moreThan3LetterNum);
        getWordsUsedTooOften(I->right, wordsTooOften, moreThan3LetterNum);
    }
}

string ReportAnalyzer::getStatsSummary(int& wordsNum, int& uniWordsNum, int& uniMoreThan3LettersNum,
                                       int& avgWordLen, int& avgSentenceLen) const
{
    string statsSummary;

    /* get the statistical summary */
    statsSummary = "<*>------ STATISTICAL SUMMARY ------<*>\n\n";
    statsSummary.append("TOTAL NUMBER OF WORDS: " + to_string(wordsNum) + "\n"
                        + "TOTAL NUMBER OF “UNIQUE” WORDS: " + to_string(uniWordsNum) + "\n"
                        + "TOTAL NUMBER OF “UNIQUE” WORDS OF MORE THAN THREE LETTERS: "
                        + to_string(uniMoreThan3LettersNum) + "\n"
                        + "AVERAGE WORD LENGTH: " + to_string(avgWordLen) + " characters" + "\n"
                        + "AVERAGE SENTENCE LENGTH: " + to_string(avgSentenceLen) + " words" + "\n");

    return statsSummary;
}

string ReportAnalyzer::getStyleWarnings(vector<string>& wordsTooOften, bool sentenceTooLong, bool wordTooLong,
                                      int& avgSentenceLen, int& avgWordLen) const
{
    string styleWarnings;                                   // style warnings

    /* get the style warning */
    styleWarnings = "<*>------ STYLE WARNINGS ------<*>\n\n";
    string styleBegin = styleWarnings;

    if (!wordsTooOften.empty())                              // style warning on "words used too often"
    {
        styleWarnings.append("WORDS USED TOO OFTEN:\n");

        for (int i=0; i<wordsTooOften.size(); ++i)
            styleWarnings.append(to_string(i+1)).append(". ").append(wordsTooOften[i]).append("\n");
    }

    if (sentenceTooLong)                                     // style warning on "sentences avg length is too long"
        styleWarnings.append("AVERAGE SENTENCE LENGTH TOO LONG – " + to_string(avgSentenceLen) + "\n");

    if (wordTooLong)                                         // style warning on "words avg length is too long"
        styleWarnings.append("AVERAGE WORD LENGTH TOO LONG – " + to_string(avgWordLen) + "\n");

    if (styleWarnings == styleBegin)
        styleWarnings.append("The style in your file is great! No warning generated.");

    return styleWarnings;
}

string ReportAnalyzer::getindexUniWords(unordered_map<char, string> indexMap) const
{
    string indexUniWords;                                   // unique words by index

    /* get the words and their index */
    indexUniWords = "<*>------ INDEX OF UNIQUE WORDS ------<*>\n\n";
    for (char x='a'; x<='z'; x++)
    {
        if (indexMap.find(x) != indexMap.end())
        {
            indexUniWords.append("[");
            indexUniWords.push_back(toupper(x));
            indexUniWords.append("]");
            indexUniWords.append("\n");
            indexUniWords.append(indexMap[x]);
            indexUniWords.append("\n");
        }
    }

    return indexUniWords;
}

void ReportAnalyzer::loadContentToFile(string& filePath, string& content) const
{
    ofstream file(filePath);                                 // create file if it's not there
    file << content;                                         // write the content into the file
    file.close();                                            // close the file
}

void ReportAnalyzer::analyzeReport(string fileAddress, string analysisResultPath) const
{
    /* variables related to the analysis */
    AVLtree<string> T;                                      // a tree for storing words for better searching
    int wordsNum;                                           // total number of words
    int uniWordsNum;                                        // number of unique words
    int uniMoreThan3LettersNum;                             // number of unique words that more than three letters
    int totalWordsLength;                                   // total length of all words combined
    unordered_map<char, string> map;                        // map stores index and unique words
    int avgWordLen;                                         // average length of the words
    int avgSentenceLen;                                     // average length of the sentences
    bool wordTooLong;                                       // variable shows whether the avg word length is too long
    bool sentenceTooLong;                                   // variable shows whether the avg word length is too long
    int moreThan3LetterNum;                                 // total number of words that more than three letters
    vector<string> wordsTooOften;                           // vector contains words that are used too often

    /* String of analysis results */
    string statsSummary;                                    // statistical summary
    string styleWarnings;                                   // style warnings
    string indexUniWords;                                   // unique words by index
    string allSummary;                                      // summary of all 3 sections above

    /* read words from file and store them in tree */
    string text = readTextFile(fileAddress);             // read all contents from the text file
    vector<string> words = extractCleanWords(text);    // extract unique words from the text string
    vector<string> sentences = extractSentence(text);  // extract sentences from the text file
    insertWordsToTree(words, T);                     // put all words into a tree
    tnode<string>* I = T.iterator();                        // an iterator of the tree

    /* Use iterator to get words information from tree */
    wordsNum = getWordsNum(I);
    uniWordsNum = getUniWordsNum(I);
    uniMoreThan3LettersNum = getUniMoreThan3LettersNum(I);
    totalWordsLength = getTotalLenOfWords(I);
    getIndexMapOfWords(I, map);
    moreThan3LetterNum = getMoreThan3LettersNum(I);
    getWordsUsedTooOften(I, wordsTooOften, moreThan3LetterNum);

    /* Calculate derived statistics */
    avgWordLen = totalWordsLength / wordsNum;
    avgSentenceLen = wordsNum / sentences.size();
    wordTooLong = avgWordLen > barWordTooLong;
    sentenceTooLong = avgSentenceLen > barSentenceTooLong;

    /* Get analysis results by section */
    statsSummary = getStatsSummary(wordsNum, uniWordsNum, uniMoreThan3LettersNum, avgWordLen, avgSentenceLen);
    styleWarnings = getStyleWarnings(wordsTooOften, sentenceTooLong, wordTooLong, avgSentenceLen, avgWordLen);
    indexUniWords = getindexUniWords(map);

    /* Put together all the analysis results */
    allSummary = "\nFILE NAME: " + fileAddress + "\n\n" + statsSummary + "\n\n" + styleWarnings + "\n\n" + indexUniWords;

    /* Write the analysis result to a file */
    loadContentToFile(analysisResultPath, allSummary);

}





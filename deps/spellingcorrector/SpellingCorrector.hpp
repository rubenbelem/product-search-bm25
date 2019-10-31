/*
* SpellingCorrector.h
*
* Version: 1.6
* Author: Felipe Farinon <felipe.farinon@gmail.com>
* URL: https://scarvenger.wordpress.com/
*
* Changelog:
* 1.6: Adding getSuggestions method to SpellingCorrector (featured implemented by Rúben Belém <rubenbelem@gmail.com>)
*/

#ifndef _SPELLINGCORRECTOR_H_
#define _SPELLINGCORRECTOR_H_

#include <vector>
#include <map>

class SpellingCorrector {
private:
    typedef std::vector<std::string> Vector;
    typedef std::map<std::string, int> Dictionary;

    Dictionary dictionary;

    void edits(const std::string &word, Vector &result);

    void known(Vector &results, Dictionary &candidates);

public:
    void load(const std::string &filename);

    std::string correct(const std::string &word);

    std::vector<std::pair<std::string, int>> getSuggestions(const std::string &word);

    void addWord(const std::string &word);
};

#endif

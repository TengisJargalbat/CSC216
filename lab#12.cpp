#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cctype>
using namespace std;

string preprocessWord(const string& word) {
    string result;
    for (char ch : word) {
        if (!ispunct(ch)) {
            result.push_back(tolower(ch));
        }
    }
    return result;
}

int main() {
    ifstream inFile("input.txt");
    if (!inFile) {
        cerr << "Error opening file" << endl;
        return 1;
    }
    unordered_set<string> commonWords = { "a", "and", "the", "to", "for", "they", "in" };
    unordered_map<string, vector<int>> invertedIndex;
    string word;
    int index = 0;

    while (inFile >> word) {
        string processed = preprocessWord(word);

        if (!processed.empty() && commonWords.find(processed) == commonWords.end()) {
            invertedIndex[processed].push_back(index);
        }
        ++index;
    }
    inFile.close();

    ofstream outFile("inverted_index.txt");
    if (!outFile) {
        cerr << "Error creating file" << endl;
        return 1;
    }

    outFile << "{" << "\n";
    for (auto it = invertedIndex.begin(); it != invertedIndex.end(); ) {
        outFile << "  \"" << it->first << "\": [";
        for (size_t i = 0; i < it->second.size(); i++) {
            outFile << it->second[i];
            if (i != it->second.size() - 1)
                outFile << ", ";
        }
        outFile << "]";
        if (++it != invertedIndex.end())
            outFile << ",";
        outFile << "\n";
    }
    outFile << "}" << "\n";
    outFile.close();

    return 0;
}

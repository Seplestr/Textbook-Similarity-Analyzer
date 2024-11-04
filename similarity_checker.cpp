// Created by Prabhav Pandey on 11/1/2024.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

struct WordFrequency {
    string word;
    double freq;
};

string to_uppercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool is_stop_word(const string& word) {
    static const set<string> stop_words = {"A", "AND", "AN", "OF", "IN", "THE"};
    return stop_words.find(word) != stop_words.end();
}

string remove_non_alnum(const string& word) {
    string cleaned = word;
    cleaned.erase(remove_if(cleaned.begin(), cleaned.end(),
                            [](char c) { return !isalnum(c); }),
                  cleaned.end());
    return cleaned;
}

bool compare_word_frequency(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}

void sort_descending(vector<pair<string, int>>& vec) {
    sort(vec.begin(), vec.end(), compare_word_frequency);
}

struct SimilarPair {
    int file1;
    int file2;
    double similarity;
};

bool compare_similarity(const SimilarPair& a, const SimilarPair& b) {
    return a.similarity > b.similarity;
}

void sort_similar_pairs(vector<SimilarPair>& similar_pairs) {
    sort(similar_pairs.begin(), similar_pairs.end(), compare_similarity);
}

vector<WordFrequency> process_file(const string& filepath) {
    ifstream file(filepath);
    if(!file.is_open()) {
        cerr << "Error opening file: " << filepath << endl;
        return {};
    }

    unordered_map<string, int> word_count;
    int total_words = 0;
    string word;

    while(file >> word) {
        string cleaned_word = remove_non_alnum(word);
        if(cleaned_word.empty()) {
            continue;
        }

        string upper_word = to_uppercase(cleaned_word);
        if(is_stop_word(upper_word)) {
            continue;
        }

        word_count[upper_word]++;
        total_words++;
    }

    file.close();

    vector<pair<string, int>> freq_vec(word_count.begin(), word_count.end());
    sort_descending(freq_vec);

    vector<WordFrequency> top_words;
    int limit = min(100, static_cast<int>(freq_vec.size()));

    for(int i = 0; i < limit; i++) {
        WordFrequency wf;
        wf.word = freq_vec[i].first;
        wf.freq = static_cast<double>(freq_vec[i].second) / total_words;
        top_words.push_back(wf);
    }

    return top_words;
}

double calculate_similarity(const vector<WordFrequency>& list1, const vector<WordFrequency>& list2) {
    double similarity = 0.0;
    int p1 = 0;
    int p2 = 0;

    while(p1 < list1.size() && p2 < list2.size()) {
        if(list1[p1].word == list2[p2].word) {
            similarity += list1[p1].freq;
            p1++;
            p2++;
        }
        else if(list1[p1].word < list2[p2].word) {
            p1++;
        }
        else {
            p2++;
        }
    }

    return similarity;
}

int main() {
    string directory = "D:\\Book-Txt";
    vector<vector<WordFrequency>> all_files_freq;
    vector<string> file_names;

    for(const auto& entry : fs::directory_iterator(directory)) {
        if(entry.is_regular_file() && entry.path().extension() == ".txt") {
            cout << "Processing file: " << entry.path().filename() << endl;
            vector<WordFrequency> freq = process_file(entry.path().string());
            if(!freq.empty()) {
                all_files_freq.push_back(freq);
                file_names.push_back(entry.path().filename().string());
            }
        }
    }

    int num_files = all_files_freq.size();
    if(num_files < 2) {
        cerr << "Not enough files to compare." << endl;
        return 1;
    }

    vector<SimilarPair> similar_pairs;

    for(int i = 0; i < num_files; i++) {
        for(int j = i + 1; j < num_files; j++) {
            double sim = calculate_similarity(all_files_freq[i], all_files_freq[j]);
            SimilarPair sp;
            sp.file1 = i;
            sp.file2 = j;
            sp.similarity = sim;
            similar_pairs.push_back(sp);
        }
    }

    sort_similar_pairs(similar_pairs);

    cout << "\nTop 10 Similar Pairs of Textbooks:\n";
    cout << "-----------------------------------\n";
    int report_limit = (similar_pairs.size() < 10) ? similar_pairs.size() : 10;
    for(int i = 0; i < report_limit; i++) {
        int idx1 = similar_pairs[i].file1;
        int idx2 = similar_pairs[i].file2;
        cout << i+1 << ". \"" << file_names[idx1] << "\" <--> \"" << file_names[idx2]
             << "\" | Similarity Index: " << similar_pairs[i].similarity << "\n";
    }

    return 0;
}

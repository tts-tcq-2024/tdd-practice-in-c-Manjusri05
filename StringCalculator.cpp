#include "StringCalculator.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;



int toInt(const string &s) {
    try {
        return stoi(s);
    } catch (const std::invalid_argument&) {
        return 0; // Ignore non-numeric input
    } catch (const std::out_of_range&) {
        return 0; // Handle very large numbers that might cause out of range errors
    }
}

// Helper function to add a token if it is not empty
void addTokenIfNotEmpty(vector<string> &tokens, const string &str, size_t start, size_t end) {
    if (end > start) {
        tokens.push_back(str.substr(start, end - start));
    }
}

vector<string> split(const string &str, const string &delimiters) {
    vector<string> tokens;
    size_t start = 0;
    while (start < str.size()) {
        size_t end = str.find_first_of(delimiters, start);
        addTokenIfNotEmpty(tokens, str, start, end);
        start = (end == string::npos) ? str.size() : end + 1;
    }
    return tokens;
}




// Helper function to ignore numbers greater than 1000
int filterLargeNumbers(int num) {
    return num > 1000 ? 0 : num;
}

// Function to collect negative numbers from the list
vector<int> collectNegatives(const vector<int> &numbers) {
    vector<int> negatives;
    for (int num : numbers) {
        if (num < 0) {
            negatives.push_back(num);
        }
    }
    return negatives;
}

// Function to create the exception message for negative numbers
string createNegativesMessage(const vector<int> &negatives) {
    stringstream ss;
    ss << "negatives not allowed: ";
    for (size_t i = 0; i < negatives.size(); ++i) {
        if (i > 0) ss << ",";
        ss << negatives[i];
    }
    return ss.str();
}

// Function to check and throw an exception if there are negative numbers.
void checkNegatives(const vector<int> &numbers) {
    vector<int> negatives = collectNegatives(numbers);
    if (!negatives.empty()) {
        throw runtime_error(createNegativesMessage(negatives));
    }
}

// Helper function to check if the input format starts with "//" and has a newline
bool isCustomDelimiterFormat(const string &input) {
    return input.substr(0, 2) == "//" && input.find("\n") != string::npos;
}

pair<string, string> extractCustomDelimiter(const string &input) {
    if (!isCustomDelimiterFormat(input)) {
        return {",\n", input}; // Default delimiters if no valid custom delimiter is found
    }
    size_t delimiterEnd = input.find("\n");
    return {input.substr(2, delimiterEnd - 2), input.substr(delimiterEnd + 1)};
}




vector<int> parseNumbers(const string &numbersStr, const string &delimiters) {
    vector<string> strNumbers = split(numbersStr, delimiters);
    vector<int> numbers;
    for (const string &numStr : strNumbers) {
        if (!numStr.empty()) {
            numbers.push_back(filterLargeNumbers(toInt(numStr)));
        }
    }
    return numbers;
}

int sumNumbers(const vector<int> &numbers) {
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return sum;
}

// Main CalculateAdd function with reduced CCN
int StringCalculator::CalculateAdd(const string &input) {
    if (input.empty()) return 0;
    
    auto [delimiters, numbersStr] = extractCustomDelimiter(input);
    vector<int> numbers = parseNumbers(numbersStr, delimiters);
    checkNegatives(numbers);
    return sumNumbers(numbers);
}

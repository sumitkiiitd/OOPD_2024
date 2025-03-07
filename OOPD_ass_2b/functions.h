#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// Function to check if a string is numeric
bool isNumeric(const string &str);

// Function to split a CSV line into fields based on commas
void splitCSVLine(const string &line, string fields[], int fieldCount);

// Function to split a line based on newlines
void splitLine(const string &line, string fields[], int fieldCount);

// Function to split a string by commas and fill remaining fields with empty strings
void splitString(const string &input, string fields[], int fieldCount);

// Function to check if a username is valid (only letters and spaces)
bool isValidUserName(const string &userName);

// Function to get a specific field from a CSV line by its index
string getField(const string &line, int fieldIndex);

#endif // FUNCTIONS_H

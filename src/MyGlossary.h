#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class MyGlossary {
// No file operations --------------------
	void warning(int = 1);													// Outputs a certain warning.
	enum ordering { bigger, smaller, equal };								// enum type used in checkOrder().
	ordering checkOrder(std::string, std::string);							// Checks whether first string is bigger, smaller or equal to the second string (omitting spaces and hyphens).
	std::string extractTerm(std::string);									// Extracts the term from a string (until first ':').
	bool isInside(std::string str, std::vector<std::string>);				// Checks whether a certain string is contained in a certain vector<string>. Used in repeatedTerms().
	bool isSubString(std::string, std::string);								// Checks whether a certain word is a subset of a string. Used only in relativeSearch().
	std::vector<std::string> mergeSort(const std::vector<std::string> &);	// Sorting algorithm used in sort(). Parameter: vector<string> where each string contains a term, colon, space and definition ("term: definition").
// File operations --------------------
	std::vector<std::string> extractLinesToVector();						// Extract all the lines from the file and stores them in a vector.
	std::vector<std::string> extractTermsToVector();						// Extracts the terms from the file and stores them in a vector<string>.
	void writeToFile(std::vector<std::string>);								// Writes the content of a vector to the file.
public:
	void menu();					// Displays a menu in a console interface showing the main functionalities of this class (MyGlossary) and allowing to work with them in a more friendly and intuitive environment.
// Basic data operations --------------------
	std::string fileName{ "data.txt" };										// file name.
	int lines();															// Number of lines in the file.
// Extracting data operations --------------------
	std::vector<std::string> exactSearch(std::string);		// Searches the lines that defines an exact term. Input: Term name. Output: Vector<string> containing all the exact definitions found for that term.
	std::vector<std::string> relativeSearch(std::string);	// Searches the lines that defines a relative term. Input: Term name. Output: Vector<string> containing all the definitions of terms similar to the input term.
	std::string getLine(int);								// Get a certain line from the file given its position in it (from 1 to lines()).
	std::vector<int> findPosition(std::string);				// Find the position/s of a given term. 
	int numberOfRepetitions(std::string);					// Outputs number of times a term has an entry in the file (i.e. number of repetitions of a term).
	std::vector<std::string> repeatedTerms();				// Searches the terms that are defined more than once. Output: Vector<string> containing two following strings for every repeated term: first, the name of the term; second, the number or repetitions.
// Modifying data operations --------------------
	int addEntry(std::string);								// Add a new line with a term and its definition to the file. Returns 1 if no term is detected.
	int editEntry(int, std::string);						// In the file, changes the content of a certain line with a certain string. Returns 1 if no term is detected. 
	int eraseTerm(std::string);								// Erases the line/s that defines a certain term. Returns number of deleted elements.
	void eraseLine(int);									// Erases a certain line from the file.
	int eraseRepeatedLines();								// If there is one or more sets of lines identical to each other, it deletes all those lines except one for each set. Returns the number or deleted lines.
	void sort();											// Order alphabetically the terms in the file (Rearranges the lines in the file).
// Constructors --------------------
	MyGlossary() = default;									// Default constructor. Makes the class operate on the file called "data.txt".
	MyGlossary(std::string str) : fileName{ str } { }		// Constructor. Allows user to define the file where to operate by entering its name in the initialization of the object.
};

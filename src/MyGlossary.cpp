
#include "MyGlossary.h"

// ----- Interface -----

void MyGlossary::menu() {
	
	std::cout << "\n >>>>>>>>>> GLOSSARY CREATOR <<<<<<<<<\n";

	for (;;) {
		std::cout
			<< "\n Basic data --------------------\n"
			<< "	(1) Name of file:    " << fileName << "\n"
			<< "	(2) Number of terms: " << lines() << "\n"
			<< " Extracting data ---------------\n"
			<< "	(3)  Search term (exact coincidence)\n"
			<< "	(4)  Search term (exact and relative coincidence)\n"
			<< "	(5)  Search by position\n"
			<< "	(6)  Position of a term\n"
			<< "	(7)  Number of terms X\n"
			<< "	(8)  Repeated terms\n"
			<< " Modifying data ----------------\n"
			<< "	(9)  Add new entry\n"
			<< "	(10) Modify an entry\n"
			<< "	(11) Erase entry\n"
			<< "	(12) Erase line X\n"
			<< "	(13) Erase repeated entries\n"
			<< "	(14) Sort alphabetically\n"
			<< " -------------------------------\n"
			<< "	(0)  Exit\n"
			<< " -------------------------------\n";

		int select;
		std::cout << ">> Enter an option (0 - 14): ";
		std::cin >> select;
		std::cout << std::endl;
		std::cin.ignore();	// "cin >> select" takes the entered name, except the final "\n" (newline), and stores it in "select". The "\n" is left in the buffer until the next I/O operation, where it's discarded or consumed. Due to the default functionality of getline(), when flow of control reaches getline(), it tries to read a line but stops immediatly when a newline is encountered. cin.ignore() makes discard the next available characters (i.e. this newline).

		if (select == 0) return;

		if (select == 1) {
			std::string name;
			std::cout << ">> Name of the file to open: ";
			std::getline(std::cin, name);				// std::getline()
			fileName = name;
		}

		if (select == 2) {
			std::cout
				<< ">> Number of entries in \"" << fileName << "\": " << lines() << std::endl;
		}

		if (select == 3) {
			for (;;) {
				std::string term;
				std::cout << ">> Enter term name (0 to exit): ";
				std::getline(std::cin, term);
				if (term == "0") break;

				std::vector<std::string> defs = exactSearch(term);
				std::cout << "\n----- Exact terms: " << defs.size() << " -----\n" << std::endl;
								
				for (int i = 0; i < defs.size(); i++) {
					std::cout << defs[i] << std::endl << std::endl;
				}
			}
		}

		if (select == 4) {
			for (;;) {
				std::string term;
				std::cout << ">> Enter term name (0 to exit): ";
				std::getline(std::cin, term);
				if (term == "0") break;

				std::vector<std::string> exactDefs = exactSearch(term);
				std::vector<std::string> relativeDefs = relativeSearch(term);


				std::cout << "\n----- Exact terms: " << exactDefs.size() << " -----\n" << std::endl;
				for (int i = 0; i < exactDefs.size(); i++) {
					std::cout << exactDefs[i] << std::endl << std::endl;
				}

				std::cout << "----- Similar terms: " << relativeDefs.size() << " -----\n" << std::endl;
				for (int i = 0; i < relativeDefs.size(); i++) {
					std::cout << relativeDefs[i] << std::endl << std::endl;
				}
			}
		}

		if (select == 5) {
			for (;;) {
				int pos;
				std::cout << ">> Enter position number (0 to exit): ";
				std::cin >> pos;

				if (pos == 0) break;
				if (pos < 1 || pos > lines()) warning(3);
				else std::cout << std::endl << getLine(pos) << std::endl << std::endl;
			}
		}

		if (select == 6) {
			for (;;) {
				std::string term;
				std::cout << ">> Enter term name (0 to exit): ";
				std::getline(std::cin, term);

				if (term == "0") break;
				std::vector<int> pos = findPosition(term);
				if (!pos.size()) warning(4);
				else {
					std::cout << std::endl;
					for (int i = 0; i < pos.size(); i++) {
						std::cout << pos[i];
						if (i < pos.size() - 1) std::cout << ", ";
						else if (i == pos.size() - 1) std::cout << std::endl << std::endl;
					}	
				}	
			}
		}

		if (select == 7) {
			for (;;) {
				std::string term;
				std::cout << ">> Enter term name (0 to exit): ";
				std::getline(std::cin, term);

				if (term == "0") break;
				int reps = numberOfRepetitions(term);
				std::cout << std::endl << reps << std::endl << std::endl;
			}
		}

		if (select == 8) {
			std::vector<std::string> reps = repeatedTerms();

			for (int i = 0; i < reps.size(); i += 2) {
				std::cout << reps[i + 1] << " x " << reps[i] << std::endl;
			}
		}

		if (select == 9) {
			for (;;) {
				std::cout << ">> Enter a new entry (0 to exit): \n" << std::endl;
				std::string entry;
				std::getline(std::cin, entry);
				if (entry == "0") break;
				if(addEntry(entry)) warning(2);
				else std::cout << "\n   New entry added\n" << std::endl;
			}
		}

		if (select == 10) {
			for (;;) {
				std::cout << ">> Enter position (0 to exit): ";
				int pos;
				std::cin >> pos;
				if (pos == 0) break;
				std::cin.ignore();

				if (pos < 0 || pos > lines()) {
					warning(3);
					continue;
				}
				
				std::cout << std::endl << getLine(pos) << std::endl << std::endl;
				std::cout << ">> Enter your edited entry (0 to exit): \n" << std::endl;
				std::string edition;
				std::getline(std::cin, edition);
				if (edition == "0") break;
				if(editEntry(pos, edition)) warning(2);
				else std::cout << "\n   Entry edited\n" << std::endl;
			}
		}

		if (select == 11) {
			for (;;) {
				std::cout << ">> Enter term to erase (0 to exit): ";
				std::string term;
				std::getline(std::cin, term);
				if (term == "0") break;

				int count = eraseTerm(term);
				if (count == 0) {
					warning(4);
					continue;
				}
				std::cout << "\n   Deleted entries: " << count << std::endl << std::endl;
			}
		}

		if (select == 12) {
			for(;;){
				std::cout << ">> Enter line position (0 to exit): ";
				int pos;
				std::cin >> pos;

				if (pos == 0) break;
				if (pos < 0 || pos > lines()) {
					warning(3);
					continue;
				}	

				eraseLine(pos);
				std::cout << "\n   Line " << pos << " deleted\n" << std::endl;
			}	
		}

		if (select == 13) {
				std::vector<std::string> entries = extractLinesToVector();
				int i = eraseRepeatedLines();
				std::cout << "   Number of deleted entries: " << i << std::endl;
		}

		if (select == 14) {
			sort();
			std::cout << "   Entries sorted" << std::endl;
		}
	}
}

int MyGlossary::lines() {

	int counter = 0;

	std::ifstream ifile(fileName);
	if (ifile.is_open()) {
		std::string str;
		while (std::getline(ifile, str)) {
			counter++;
		}
	}
	else warning();

	return counter;
}

std::vector<std::string> MyGlossary::exactSearch(std::string term) {

	std::vector<std::string> defs = extractLinesToVector();
	std::vector<std::string> results;

	for (int i = 0; i < defs.size(); i++) {
		if (term == extractTerm(defs[i])) results.push_back(defs[i]);
	}

	return results;
}

std::vector<std::string> MyGlossary::relativeSearch(std::string term) {

	std::string term1 = term;

	// Decompose the "string term" into its component words (groups of characters separated by a white-space or hyphen)
	for (int i = 0; i < term1.size(); i++) if (term1[i] == '-') term1[i] = ' ';

	std::stringstream stream;
	stream << term1;
	std::string word;
	std::vector<std::string> wordsVec;
	while (stream >> word) wordsVec.push_back(word);

	// Find the terms that have any of the previously decomposed words as a subset.
	std::vector<std::string> terms = extractTermsToVector();
	std::vector<std::string> selected;

	for (int i = 0; i < terms.size(); i++) {
		if (isInside(terms[i], selected) || terms[i] == term) continue;
		for (int j = 0; j < wordsVec.size(); j++) {
			if (isSubString(wordsVec[j], terms[i])) {
				selected.push_back(terms[i]);
				break;
			}
		}
	}

	// Store definitions of the term in a vector.
	std::vector<std::string> result, defs;

	for (int i = 0; i < selected.size(); i++) {
		defs = exactSearch(selected[i]);
		for (int j = 0; j < defs.size(); j++) {
			result.push_back(defs[j]);
		}
	}

	return result;
}

std::string MyGlossary::getLine(int line) {

	std::vector<std::string> defs = extractLinesToVector();

	return defs[line - 1];
}

std::vector<int> MyGlossary::findPosition(std::string term) {
	
	std::vector<std::string> defs = extractLinesToVector();
	std::vector<int> pos;

	for (int i = 0; i < defs.size(); i++) {
		if (term == extractTerm(defs[i])) pos.push_back(i+1);
	}

	return pos;
}

int MyGlossary::numberOfRepetitions(std::string term) {

	std::vector<std::string> listTerms = extractTermsToVector();
	int counter = 0;

	for (int i = 0; i < listTerms.size(); i++) {
		if (listTerms[i] == term) counter++;
	}

	return counter;
}

std::vector<std::string> MyGlossary::repeatedTerms() {

	std::vector<std::string> terms = extractTermsToVector();
	std::vector<std::string> repTerms;
	int counter = 1;
	std::stringstream stream;
	std::string numReps;

	for (int i = 0; i < terms.size(); i++) {
		if (isInside(terms[i], repTerms)) continue;		// Avoid counting terms already counted.
		for (int j = i + 1; j < terms.size(); j++) {
			if (terms[i] == terms[j]) counter++;
		}
		if (counter > 1) {
			repTerms.push_back(terms[i]);
			stream << counter;
			stream >> numReps;
			repTerms.push_back(numReps);
			counter = 1;
			stream.clear();		// optional: stream.str(std::string());	(erases content from stream)
		}
	}

	return repTerms;
}

int MyGlossary::addEntry(std::string newEntry) {

	if (extractTerm(newEntry) == "") return 1;

	std::vector<std::string> defs = extractLinesToVector();
	defs.push_back(newEntry);
	writeToFile(defs);
	return 0;
}

int MyGlossary::editEntry(int line, std::string newEntry) {

	if (extractTerm(newEntry) == "") return 1;

	std::vector<std::string> definitions = extractLinesToVector();
	definitions[line - 1] = newEntry;
	writeToFile(definitions);
	
	return 0;
}

int MyGlossary::eraseTerm(std::string term) {

	std::vector<std::string> defs = extractLinesToVector();
	int counter = 0;

	for (int i = 0; i < defs.size(); i++) if (term == extractTerm(defs[i])) {
			defs.erase(defs.begin() + i);
			counter++;
		}

	writeToFile(defs);

	return counter;
}

void MyGlossary::eraseLine(int line) {

	std::vector<std::string> vec = extractLinesToVector();
	vec.erase(vec.begin() + line - 1);
	writeToFile(vec);
}

int MyGlossary::eraseRepeatedLines() {

	int siz = lines();

	std::vector<std::string> defs = extractLinesToVector();
	
	for (int i = 0; i < defs.size(); i++) {
		for (int j = i + 1; j < defs.size(); j++) {
			if (defs[i] == defs[j]) defs.erase(defs.begin() + j);
		}
	}
	
	writeToFile(defs);

	return siz - lines();
}

void MyGlossary::sort() {

	std::vector<std::string> defs = extractLinesToVector();
	std::vector<std::string> sorted = mergeSort(defs);
	writeToFile(sorted);
}

// ----- Implementation -----

void MyGlossary::warning(int a) {
	switch (a) {
	case 1:
		std::cout << "\n   [Can't open file \"" << fileName << "\"]\n" << std::endl;
		break;
	case 2:
		std::cout << "\n   [No term detected]\n" << std::endl;
		break;
	case 3:
		std::cout << "\n   [Position out of range]\n" << std::endl;
		break;
	case 4:
		std::cout << "\n   [Term not found]\n" << std::endl;
	}
}

MyGlossary::ordering MyGlossary::checkOrder(std::string a, std::string b) {

	// Format "string a" (tolower and eliminate spaces and hyphens)
	for (int i = 0; i < a.size(); i++) a[i] = tolower(a[i]);
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == ' ' || a[i] == '-') {
			for (int j = i; j < a.size() - 1; j++) a[j] = a[j + 1];
			a = a.substr(0, a.size() - 1);
		}
	}

	// Format "string b" (tolower and eliminate spaces and hyphens)					
	for (int i = 0; i < b.size(); i++) b[i] = tolower(b[i]);
	for (int i = 0; i < b.size(); i++) {
		if (b[i] == ' ' || b[i] == '-') {
			for (int j = i; j < b.size() - 1; j++) b[j] = b[j + 1];
			b = b.substr(0, b.size() - 1);
		}
	}

	// Chooses the smaller size
	std::size_t siz;
	a.size() < b.size() ? siz = a.size() : siz = b.size();

	// Checks order
	for (int i = 0; i < siz; i++) {
		if (a[i] < b[i]) return smaller;
		else if (a[i] > b[i]) return bigger;
	}

	if (a.size() < b.size()) return smaller;
	else if (a.size() > b.size()) return bigger;
	else return equal;

}

std::string MyGlossary::extractTerm(std::string str) {

	std::string result;
	std::size_t siz = str.size();
	int i = 0;

	for (i; i < siz; i++) {
		if (str[i] == ':' && i != 0 && str[i - 1] != ':' && str[i + 1] == ' ') {	// Rules for terms: Must end with ':' and next character must be a space. The ':' is not considered the ending if it occupies the first position of the term or if there is another ':' at its left. 
			result = str.substr(0, i);
			return result;
		}
	}

	return "";
}

bool MyGlossary::isInside(std::string str, std::vector<std::string> vec) {

	for (int i = 0; i < vec.size(); i++) {
		if (str == vec[i]) return 1;
	}
	return 0;
}

bool MyGlossary::isSubString(std::string word, std::string str) {

	int j = 0;

	for (int i = 0; i < str.size(); i++) {
		if (word[j] == str[i]) j++;
		else j = 0;
		if (j == word.size()) return 1;
	}

	return 0;
}

std::vector<std::string> MyGlossary::mergeSort(const std::vector<std::string> & lins) {

	std::size_t siz = lins.size();
	if (siz < 2) return lins;

	std::vector<std::string> linsA, linsB;
	linsA  = {  lins.begin(),  lins.begin() + siz/2 };
	linsB  = {  lins.begin() +  siz/2, lins.end() };

	linsA = mergeSort(linsA);
	linsB = mergeSort(linsB);

	std::size_t sizA = linsA.size();
	std::size_t sizB = linsB.size();
	std::vector<std::string> result(siz, "");
	int a = 0, b = 0;

	for (int i = 0; i < siz; i++) {
		if ((a < sizA && b < sizB && checkOrder(extractTerm(linsA[a]), extractTerm(linsB[b])) == smaller) || b == sizB) {
			result[i] = linsA[a];
			a++;
		}
		else if ((a < sizA && b < sizB) || a == sizA) {
			result[i] = linsB[b];
			b++;
		}
	}

	return result;
}

std::vector<std::string> MyGlossary::extractLinesToVector() {

	std::vector<std::string> vec;
	std::string str;

	std::ifstream ifile(fileName);
	if (ifile.is_open()) while (std::getline(ifile, str)) vec.push_back(str);
	else warning();

	return vec;
}

std::vector<std::string> MyGlossary::extractTermsToVector() {

	std::vector<std::string> vec;
	std::ifstream ifile(fileName);
	std::string str;

	if (ifile.is_open()) while (std::getline(ifile, str)) vec.push_back(extractTerm(str));
	else warning();

	return vec;
}

void MyGlossary::writeToFile(std::vector<std::string> vec) {
	
	std::ofstream ofile;
	ofile.open(fileName);

	if (ofile.is_open()) {
		for (int i = 0; i < vec.size(); i++) {
			ofile << vec[i];
			if (i < vec.size() - 1) ofile << std::endl;
		}
	}
	else warning();
}
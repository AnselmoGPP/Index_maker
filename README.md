# Index_maker

Useful application with multiple functionalities for creating, managing and modifying lists of terms + definitions (glossaries, indexes, dictionaries, etc.) that are stored in a file.

First of all, let us make some definitions that will be applied here:

- File: File where the "glossary" is stored. This file must be in the same directory as the one where the executable is. 
- Glossary: Any list of "terms" with their corresponding "definitions". Each term + definition is an "entry".
- Term: Compound of one or more words and/or symbols. The term ends with a colon (:). The terms are the first element in any "entry". Any term starts at the beggining of an "entry" and ends just before an "ending semicolon" is encountered.
- Definition: Line of text containing information relative to the "term". It starts with the "ending semicolon" + white-space, and finishes when an end-of-line is encountered.
- Entry: Each line of text found in the "file" is an entry and contains a "term" and a "definition". Each entry ends with an end-of-line, except the last entry of the "file".
- Ending colon: For a colon to be considered an ending colon it must satisfy some conditions:
  - It must not be the first character of an "entry".
  - The previous character must not be another colon.
  - The next character must be a white-space.

The executable file shows a menu with the following options:

0) Exit: Close the application.
1) Name of file: Define the name of the file where you are going to work on.
2) Number of terms: Shows the number of entries contained in the file.
3) Search term (exact coincidence): Enter a term and the program will search for all the entries containing an exact coincidence of that term and will show all of them.
4) Search term (exact and relative coincidence): Enter a term and the program will search for all the entries containing an exact coincidence of that term and all the entries containing a relative coincidence of that term (entries whose terms contains any word from the entered term) and will show all of them.
5) Search by position: Enter the number of the position of an entry in the file (starts at 1) and the program will show that entry.
6) Position of a term: Enter a term and program will show all the positions of all the entries that contains that term.
7) Number of terms X: Enter a term and the program will show the numbers of the positions of all the entries containing that term.
8) Repeated terms: Shows a list of all the terms that are in the file more than once (their definitions may or may not differ) and the number of repetitions of each term.
9) Add new entry: Enter a new entry and the program will store it at the end of the file (a new line is occupied).
10) Modify an entry: Enter a new entry and the number of an existing entry position. The program will overwrite that existing entry with the new entry in the file. 
11) Erase entry: Enter a term and the program will delete the entries that contain that term.
12) Erase line X: Enter the number of an existing entry position and the program will delete that entry in the file.
13) Erase repeated entries: Erases any entry that is repeated one or more times, leaving only one copy of that entry in the file. The repeated terms must be completly identical (term and definition).
14) Sort alphabetically: Shorts alphabetically all the entries in the file based on their corresponding terms.

The source files (.cpp, .h) define the MyGlossary class, which contains the functionalities used in this program. 
Files included:

  - main.cpp:       Entry point of the program. Contains function main().
  - MyGlossary.h:       Contains the definition of class MyGlossary. It includes explanations for every member of the class.
  - MyGlossary.cpp:     Contains the definitions of the members of class MyGlossary.
  - data.txt:           An example file containing a glossary for testing purposes.
#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include "LetterNode.h"
using namespace std;

class WordSearch {

public:
	/**
	 * \brief Wordsearch constructor, takes in the output filename
	 * \param p_fileName The output file name
	 */
	explicit WordSearch(const char * const p_fileName);

	/**
	 * \brief Wordsearch copy constructor
	 * \param p_wordSearch The wordsearch to copy from
	 */
	explicit WordSearch(const WordSearch& p_wordSearch);

	/**
	 * \brief Wordsearch destructor, deletes all heap allocated member
	 */
	~WordSearch();

	// Template methods

	/**
	 * \brief Reads the puzzle file and stores the values in a 2D array member
	 */
	void readSimplePuzzle();

	/**
	 * \brief Reads the dictionary file and stores the values in a vector member
	 */
	void readSimpleDictionary();

	/**
    * \brief Reads in the puzzle file and constructs the advanced linked grid
    */
	void readAdvancedPuzzle();

	/**
    * \brief Calls readSimpleDictionary as the advanced dictionary wasn't implemented
    */
	void readAdvancedDictionary();

	/**
    * \brief Solves the simple puzzle
    */
	void solvePuzzleSimple();

	/**
    * \brief Solves the advanced puzzle
    */
	void solvePuzzleAdvanced();

	/**
	 * \brief Writes results from solving the puzzles to an output text file
	 * \param p_loadTime The time it took to load the puzzle
	 * \param p_solveTime The time it took to solve the puzzle
	 */
	void writeResults(const	double p_loadTime, const double p_solveTime) const;

	// My Methods

	/**
	 * \brief Writes the simple puzzle member to the standard output
	 */
	void writeSimplePuzzle() const;

	/**
	 * \brief Writes the simple dictionary member to the standard output
	 */
	void writeSimpleDic() const;

	/**
	 * \brief Writes the advanced puzzle to the standard output
	 */
	void writeAdvancedPuzzle() const;

	/**
	 * \brief Checks the adjacent rows, columns and diagonals for each letter within the grid
	 */
	bool checkAdjacents(const string& p_word, const int p_startRow, const int p_startColumn);

	/**
	 * \brief Checks the adjacent nodes for the each letter within the structure
	 */
	bool checkAdjacents(const string& p_word, const LetterNode& p_startNode);

	/**
	 * \brief Constructs the linked grid
	 */
	void constructLinkedGrid();

	// Operators
	WordSearch& operator=(const WordSearch& p_wordSearch);

private:

	/**
	* \brief A 2D vector containing the locations for the start of each word in the grid
	*/
	vector<vector<int>> m_wordLocations;

	/**
	* \brief 2D Int vectors for traversing the grid
	*/
	const vector<int> m_directions[8] = {
								//Row, Column
						   vector<int>{-1, 0},
						   vector<int>{-1, 1},
						   vector<int>{ 0, 1},
						   vector<int>{ 1, 1},
						   vector<int>{ 1, 0},
						   vector<int>{ 1,-1},
						   vector<int>{ 0,-1},
						   vector<int>{-1,-1},
	};

	/**
	* \brief A vector containing all the words for the simple dictionary
	*/
	vector<string> m_simpleDic;

	/**
	 * \brief Words which have been found
	 */
	vector<string> m_matchedWords;

	/**
	* \brief A pointer to a 2D Char array, holding all the letters for the simple puzzle grid
	*/
	char** m_simplePuzzle;

	/**
	 * \brief A pointer to the letterNode grid used within the construction of the advanced grid
	 */
	LetterNode** m_letterNodeGrid;

	/**
	 * \brief Head of the advanced grid structure, Head is the top left node of the grid
	 */
	LetterNode* m_head;

	/**
	 * \brief The name of the puzzle grid
	 */
	const char* m_puzzleName = "wordsearch_grid.txt";

	/**
	 * \brief The name of the dictionary
	 */
	const char* m_dictionaryName = "dictionary.txt";

	/**
	* \brief The name of the output file
	*/
	const char* m_outputFileName;

	/**
	 * \brief The size of the puzzle grid
	 */
	int m_simplePuzzleSize;

	/**
	 * \brief The size of the advanced puzzle structure
	 */
	int m_advancedPuzzleSize;

	/**
	* \brief Number of dictionary entries checked
	*/
	int m_DicEntriesChecked;

	/**
	 * \brief Number of Grid cells checked
	 */
	int m_GridCellsChecked;

	/**
	 * \brief Dictionary size
	 */
	int m_dicSize;

	/**
	 * \brief The number of directions to be traversed
	 */
	const int m_dirCount = 8;






};


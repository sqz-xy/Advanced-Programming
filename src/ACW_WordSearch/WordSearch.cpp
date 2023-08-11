// Thomas Beet | 632115

#include "WordSearch.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

/**
 * \brief Constructor for the wordsearch
 * \param p_fileName The output file name
 */
WordSearch::WordSearch(const char* const p_fileName) : m_simplePuzzle(nullptr),
													   m_letterNodeGrid(nullptr),
                                                       m_head(nullptr),
                                                       m_outputFileName(p_fileName),
                                                       m_simplePuzzleSize(0),
                                                       m_advancedPuzzleSize(0),
                                                       m_DicEntriesChecked(0),
                                                       m_GridCellsChecked(0),
                                                       m_dicSize(0)
{
}

/**
 * \brief Copy constructor for the wordsearch
 * \param p_wordSearch The wordsearch to copy
 */
WordSearch::WordSearch(const WordSearch& p_wordSearch) : m_simpleDic(p_wordSearch.m_simpleDic),
                                                         m_simplePuzzle(p_wordSearch.m_simplePuzzle),
                                                         m_letterNodeGrid(nullptr),
                                                         m_head(nullptr),
                                                         m_puzzleName(p_wordSearch.m_puzzleName),
                                                         m_dictionaryName(p_wordSearch.m_dictionaryName),
                                                         m_outputFileName(p_wordSearch.m_outputFileName),
                                                         m_simplePuzzleSize(p_wordSearch.m_simplePuzzleSize),
                                                         m_advancedPuzzleSize(0),
                                                         m_DicEntriesChecked(p_wordSearch.m_DicEntriesChecked),
                                                         m_GridCellsChecked(p_wordSearch.m_GridCellsChecked),
                                                         m_dicSize(0)
{
}

/**
 * \brief Destructor for the wordsearch object\n
 *  - Deletes the Basic grid by iterating through, deleting each sub-array and then the source array at the end
 *	- Clears the basic dictionary
 *	- Deletes the advanced grid by iterating through the 2D array of letterNodes and deleting them
 */
WordSearch::~WordSearch() {

	// Delete the simple puzzle, won't run if the size is 0
	for (int i = 0; i < m_simplePuzzleSize; ++i) 
	{
		delete[] m_simplePuzzle[i];
		m_simplePuzzle[i] = nullptr;
	}
	delete[] m_simplePuzzle;
	m_simplePuzzle = nullptr;

	// Clear the dictionary
	m_simpleDic.clear();

	// Delete the advanced grid, won't run if the size is 0
	for (int i = 0; i < m_advancedPuzzleSize; i++)
	{
		delete[] m_letterNodeGrid[i];
		m_letterNodeGrid[i] = nullptr;
	}
	delete[] m_letterNodeGrid;
	m_letterNodeGrid = nullptr;
}

/**
 * \brief Reads the puzzle grid file and puts the letters into the 2D Array of size n*n class member\n
 * This method also sets the puzzle size member variable
 */
void WordSearch::readSimplePuzzle() {
	ifstream puzzleFile;
	puzzleFile.open(m_puzzleName);

	int gridSize;
	puzzleFile >> gridSize;

	// Initialise the 2D Array
	m_simplePuzzle = new char* [gridSize];
	m_simplePuzzleSize = gridSize;

	// Fill with arrays to create gridSize*gridSize grid
	for (int i = 0; i < gridSize; i++)
		m_simplePuzzle[i] = new char[gridSize];

	// Populate with values from the text file
	for (int i = 0; i < gridSize; i++)
		for (int j = 0; j < gridSize; j++)
			puzzleFile >> m_simplePuzzle[i][j];

	puzzleFile.close();
}

/**
 * \brief Writes the stored, simple, puzzle grid to the standard output
 */
void WordSearch::writeSimplePuzzle() const
{
	for (int i = 0; i < m_simplePuzzleSize; i++)
	{
		cout << endl;
		for (int j = 0; j < m_simplePuzzleSize; j++)
			cout << m_simplePuzzle[i][j];
	}
	cout << endl;
}

/**
 * \brief Reads the dictionary file line by line and adds the words to the vector<string> class member
 */
void WordSearch::readSimpleDictionary() {
	ifstream dicFile;
	string line;

	dicFile.open(m_dictionaryName);

	// Peek through until the end of file
	while (dicFile.peek() != EOF)
	{
		// Get the line
		getline(dicFile, line);
		// Append it to the member vector
		m_simpleDic.push_back(line);
		m_dicSize++;
	}
}

/**
 * \brief Outputs the, simple, dictionary to the console
 */
void WordSearch::writeSimpleDic() const
{
	for (int i = 0; i < m_dicSize; i++)
		cout << m_simpleDic[i] << " ";
	cout << endl;
}

/**
 * \brief Reads in the puzzle file to construct the advanced puzzle, starting with a 2D array of letterNodes\n
 * Then constructing the Linked Grid using that
 */
void WordSearch::readAdvancedPuzzle() {
	ifstream puzzleFile;
	puzzleFile.open(m_puzzleName);

	int gridSize;
	puzzleFile >> gridSize;

	// Initialise the 2D Array
	m_letterNodeGrid = new LetterNode * [gridSize];
	m_advancedPuzzleSize = gridSize;

	// Fill with arrays to create gridSize*gridSize grid
	for (int i = 0; i < gridSize; i++)
		m_letterNodeGrid[i] = new LetterNode[gridSize];

	// Populate with values from the text file, creating a new letterNode for each letter
	for (int i = 0; i < gridSize; i++)
		for (int j = 0; j < gridSize; j++)
		{
			char tempChar;
			puzzleFile >> tempChar;
			const LetterNode tempNode(tempChar, i, j);
			m_letterNodeGrid[i][j] = tempNode;
		}
	puzzleFile.close();
	constructLinkedGrid();
}

/**
 * \brief Constructs the linked grid using a 2D Array of letter nodes
 */
void WordSearch::constructLinkedGrid()
{
	for (int i = 0; i < m_advancedPuzzleSize; i++)
		for (int j = 0; j < m_advancedPuzzleSize; j++)
		{
			// Throws violation, Argued in lab document
			LetterNode* currentNode = &m_letterNodeGrid[i][j];

			if (m_head == nullptr)
				m_head = currentNode;

			for (int y = 0; y < m_dirCount; y++)
			{
				const int xOffset = i + m_directions[y][0];
				const int yOffset = j + m_directions[y][1];

				// Check for out of bounds, if so, set to a nullptr, early exit
				if (xOffset >= m_advancedPuzzleSize || yOffset >= m_advancedPuzzleSize || yOffset < 0 || xOffset < 0)
				{
					currentNode->m_adjacents[y] = nullptr;
					continue;
				}

				// Not out of bounds, set adjacent node
				currentNode->m_adjacents[y] = &m_letterNodeGrid[xOffset][yOffset];
			}
		}
}


/**
 * \brief Writes the advanced grid (Linked Grid structure) to the console
 */
void WordSearch::writeAdvancedPuzzle() const
{
	if (m_head == nullptr)
	{
		cout << "Advanced grid structure not initialized!" << endl;
		return;
	}

	const LetterNode* downNode = m_head;

	while (downNode != nullptr)
	{
		const LetterNode* rightNode = downNode;

		// Traverse right
		while (rightNode != nullptr)
		{
			cout << rightNode->GetLetter();
			rightNode = rightNode->m_adjacents[2]; // Get the next node on the right
		}
		cout << endl;
		// Move down to the node below
		downNode = downNode->m_adjacents[4]; // Get the next node down
	}
}

/**
 * \brief Calls the read simple dictionary as the advanced dictionary hasn't been implemented (Advanced puzzle has been implemented instead)
 */
void WordSearch::readAdvancedDictionary()
{
	readSimpleDictionary();
}

/**
 * \brief Solves the simple puzzle
 */
void WordSearch::solvePuzzleSimple() {
	for (int i = 0; i < m_dicSize; i++)
	{
		m_DicEntriesChecked++;
		bool isFound = false;
		for (int j = 0; j < m_simplePuzzleSize; j++)
		{
			for (int y = 0; y < m_simplePuzzleSize; y++)
			{
				// This cell has been visited so increment the count
				m_GridCellsChecked++;

				// Early exit if the word is already found
				if (isFound)
					break;

				if (m_simplePuzzle[j][y] == m_simpleDic[i][0]) // If the letter is equal to the first letter of the word
				{
					// Early exit if the word is already found
					if (isFound)
						break;

					// Traverse the directions
					if (checkAdjacents(m_simpleDic[i], j, y))
					{
						isFound = true;
						// If word is found, add it to the matched words
						m_matchedWords.push_back(m_simpleDic[i]);
					}

				}
			}
		}

	}
}

/**
 * \brief Checks the adjacents of an array position and traverses that direction if character matches are found
 * \param p_word A reference to the word being checked
 * \param p_startRow The start row of the word
 * \param p_startColumn The start column of the word
 * \return A boolean values as to if the word has been found
 */
bool WordSearch::checkAdjacents(const string& p_word, const int p_startRow, const int p_startColumn)
{
	const int targetLength = static_cast<int>(p_word.length());

	// For each direction
	for (int i = 0; i < m_dirCount; i++)
	{
		// Number of found letters, this was on the inside of the loop
		int foundCount = 1;

		// Initialize the start of the traversal, starting at char 1 of the word
		int rowIndex = p_startRow, columnIndex = p_startColumn, charIndex = 1;

		// Loop Indefinitely 
		while (true)
		{
			// Increment to the next array character for the current direction
			rowIndex += m_directions[i][0];
			columnIndex += m_directions[i][1];

			// This cell has been checked so increment the count, means the method can't be constant
			m_GridCellsChecked++;

			// Check for out of bounds
			if (rowIndex >= m_simplePuzzleSize || columnIndex >= m_simplePuzzleSize || columnIndex < 0 || rowIndex < 0)
				break;

			// If the next character isn't part of the word, then break to next direction
			if (!(m_simplePuzzle[rowIndex][columnIndex] == p_word[charIndex]))
				break;

			// Increment the found count because a correct letter must have been found and start checking the next character in the word
			foundCount++;
			charIndex++;

			// We have found all the letters, return true
			if (foundCount == targetLength)
			{
				m_wordLocations.push_back(vector<int>{p_startRow, p_startColumn});
				return true;
			}
		}
	}
	return false;
}

/**
 * \brief Solves the advanced puzzle
 */
void WordSearch::solvePuzzleAdvanced() {
	if (m_head == nullptr)
	{
		cout << "Advanced grid structure not initialized!" << endl;
		return;
	}

	// For each word traverse the linked grid and check for words if a node matches the first letter of a word
	for (int i = 0; i < m_dicSize; i++)
	{
		m_DicEntriesChecked++;
		LetterNode* downNode = m_head;
		bool isFound = false;

		while (downNode != nullptr)
		{
			// Early exit if the word is already found
			if (isFound)
				break;

			LetterNode* rightNode = downNode;
			// Traverse right
			while (rightNode != nullptr)
			{
				// Cell visited, increment count
				m_GridCellsChecked++;

				// Early exit if the word is already found
				if (isFound)
					break;

				// Check for a letter match
				if (rightNode->m_letter == m_simpleDic[i][0])
				{
					// Begin the search on that cell
					if (checkAdjacents(m_simpleDic[i], *rightNode))
					{
						isFound = true;
						m_matchedWords.push_back(m_simpleDic[i]);
					}
				}
				rightNode = rightNode->m_adjacents[2]; // Get the next node on the right
			}
			// Move down to the node below
			downNode = downNode->m_adjacents[4]; // Get the next node down
		}
	}
}

/**
 * \brief Checks adjacent nodes within the linked grid structure and traverses those directions if character matches are found
 * \param p_word A reference to the word we are looking for
 * \param p_startNode A reference to the starting node for the search
 * \return A boolean value pertaining to if a word has been found
 */
bool WordSearch::checkAdjacents(const string& p_word, const LetterNode& p_startNode)
{
	const int targetLength = static_cast<int>(p_word.size());

	// Loop through the adjacents
	for (int i = 0; i < p_startNode.m_adjacentCount; i++)
	{
		int charIndex = 1, foundCount = 1;

		if (p_startNode.m_adjacents[i] == nullptr)
			continue;

		const LetterNode* currentNode = p_startNode.m_adjacents[i];

		while (currentNode->m_letter == p_word[charIndex])
		{
			foundCount++;
			charIndex++;

			m_GridCellsChecked++;

			// We have found all the letters, return true
			if (foundCount == targetLength)
			{
				m_wordLocations.push_back(vector<int>{p_startNode.m_x, p_startNode.m_y});
				return true;
			}

			// Breaking because the end of the word is on the edge
			if (currentNode->m_adjacents[i] == nullptr)
				break;

			currentNode = currentNode->m_adjacents[i];
		}
	}
	return false;
}

/**
 * \brief Writes the results to a text file using the format detailed in the specification
 * \param p_loadTime The time it took to load in the aspects of the puzzle
 * \param p_solveTime The time it took to solve the puzzle
 */
void WordSearch::writeResults(const double p_loadTime, const double p_solveTime) const {
	vector<string> unmatchedWords;

	// Find unmatched words
	for (int i = 0; i < m_simpleDic.size(); i++)
		if (!(find(m_matchedWords.begin(), m_matchedWords.end(), m_simpleDic[i]) != m_matchedWords.end()))
			unmatchedWords.push_back(m_simpleDic[i]);

	// Create output file
	ofstream outputFile;
	outputFile.open(m_outputFileName);

	// Outputs to the file, with formatting
	outputFile << "NUMBER_OF_WORDS_MATCHED " << m_matchedWords.size() << endl << endl;

	outputFile << "WORDS_MATCHED_IN_GRID" << endl;
	for (int i = 0; i < m_matchedWords.size(); i++)
		outputFile << m_wordLocations[i][1] << " " << m_wordLocations[i][0] << " " << m_matchedWords[i] << endl;

	outputFile << endl;

	outputFile << "WORDS_UNMATCHED_IN_GRID" << endl;
	for (int i = 0; i < unmatchedWords.size(); i++)
		outputFile << unmatchedWords[i] << endl;

	outputFile << endl << "NUMBER_OF_GRID_CELLS_VISITED " << m_GridCellsChecked << endl;
	outputFile << endl << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED " << m_DicEntriesChecked << endl;
	outputFile << endl << "TIME_TO_POPULATE_GRID_STRUCTURE " << p_loadTime << endl;
	outputFile << endl << "TIME_TO_SOLVE_PUZZLE " << p_solveTime << endl;

	outputFile.close();
}

/**
 * \brief Assignment operator for the wordsearch, assigns the members of the parameter to the members of this
 * \param p_wordSearch The wordsearch to assign this to
 * \return a pointer to this
 */
WordSearch& WordSearch::operator=(const WordSearch& p_wordSearch)
{
	if (&p_wordSearch != this)
	{
		m_puzzleName = p_wordSearch.m_puzzleName;
		m_dictionaryName = p_wordSearch.m_dictionaryName;
		m_simplePuzzleSize = p_wordSearch.m_simplePuzzleSize;
		m_outputFileName = p_wordSearch.m_outputFileName;
		m_simplePuzzle = p_wordSearch.m_simplePuzzle;
		m_simpleDic = p_wordSearch.m_simpleDic;
		m_head = p_wordSearch.m_head;
		m_DicEntriesChecked = p_wordSearch.m_DicEntriesChecked;
		m_GridCellsChecked = p_wordSearch.m_GridCellsChecked;
		m_matchedWords = p_wordSearch.m_matchedWords;
		m_wordLocations = p_wordSearch.m_wordLocations;
		m_advancedPuzzleSize = p_wordSearch.m_advancedPuzzleSize;
		m_dicSize = p_wordSearch.m_dicSize;
		m_letterNodeGrid = p_wordSearch.m_letterNodeGrid;
	}

	return *this;
}
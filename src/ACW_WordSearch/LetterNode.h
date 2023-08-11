#pragma once
#include <ostream>
#include <vector>

using namespace std;

class LetterNode
{
	// Throws violation, Justified in lab document
	friend class WordSearch;
public:
	/**
	 * \brief Default constructor
	 */
	LetterNode();

	/**
	 * \brief Constructor using a character
	 * \param p_letter The letter character for the Node
	 * \param p_x The X position of the node relative to the grid
	 * \param p_y The Y position of the node relative to the grid
	 */
	explicit LetterNode(const char p_letter, const int p_x, const int p_y);

	/**
	 * \brief Copy constructor, allows a node to be copied into this
	 * \param p_letterNode The node to copy from
	 */
	explicit LetterNode(const LetterNode &p_letterNode);

	/**
	 * \brief Destructor to delete the node from memory
	 */
	~LetterNode(void);

	/**
	 * \brief Gets the letter of the node, required for the auxiliary operator
	 * \return a character value, pertaining to the nodes character
	 */
	char GetLetter() const;

	/**
	 * \brief Assignment operator overload to allow a nodes values to be assigned to this
	 * \param p_rhs The node to copy from
	 * \return a pointer to this
	 */
	LetterNode& operator=(const LetterNode &p_rhs);


private:
	/**
	* \brief Pointers to adjacent nodes, stored in a vector so they can be looped through.\n
	*Will be built clockwise such that index 0 will be the node above (12 o'clock), index 7 will be above left (11 o'clock)\n
	* 0 = Above\n
	* 1 = Above Right\n
	* 2 = Right\n
	* 3 = Below Right\n
	* 4 = Below\n
	* 5 = Below Left\n
	* 6 = Left\n
	* 7 = Above Left
	*/
	vector<LetterNode*> m_adjacents;

	/**
	 * \brief The letter assigned to the node from the grid
	 */
	char m_letter;

	/**
	 * \brief The X position of the Node within the grid
	 */
	int m_x;

	/**
	 * \brief The Y position of the Node within the grid
	 */
	int m_y;

	/**
	 * \brief The number of adjacents
	 */
	const int m_adjacentCount = 8;
};

/**
 * \brief Output a Letter node to the console, auxiliary
 * \param p_output The output stream
 * \param p_node The node to output
 * \return The output stream
 */
ostream& operator<<(ostream& p_output, const LetterNode& p_node);


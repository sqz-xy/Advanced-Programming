#include "LetterNode.h"

/**
 * \brief Default constructor, sets the size to 8 for each adjacent as there will only ever be 8 directions
 */
LetterNode::LetterNode(): m_letter(0), m_x(0), m_y(0) { m_adjacents.resize(8); }

/**
 * \brief Constructor which takes a character, sets the size to 8 for each adjacent as there will only ever be 8 directions
 */
LetterNode::LetterNode(const char p_letter, const int p_x, const int p_y) : m_letter(p_letter),
																			m_x(p_x),
																			m_y(p_y)
{
	m_adjacents.resize(8);
}

LetterNode::LetterNode(const LetterNode& p_letterNode) : m_adjacents(p_letterNode.m_adjacents),
                                                         m_letter(p_letterNode.m_letter),
														 m_x(p_letterNode.m_x),
                                                         m_y(p_letterNode.m_y),
														 m_adjacentCount(p_letterNode.m_adjacentCount)
{
}

LetterNode::~LetterNode() {}

/**
 * \brief Returns the letter of this
 * \return A char value
 */
char LetterNode::GetLetter() const
{
    return this->m_letter;
}

/**
 * \brief Assignment operator overload 
 * \param p_rhs The node to assign from
 * \return A reference to this
 */
LetterNode& LetterNode::operator=(const LetterNode& p_rhs)
{
    if (&p_rhs != this)
    {
        m_letter = p_rhs.m_letter;
        m_adjacents = p_rhs.m_adjacents;
        m_x = p_rhs.m_x;
        m_y = p_rhs.m_y;
    }
    return *this;
}

/**
 * \brief Allows nodes to be output to the console
 * \param p_output A reference to the output stream
 * \param p_node A reference to the Node to be output
 * \return A reference to the output stream
 */
ostream& operator<<(ostream& p_output, const LetterNode& p_node)
{
    p_output << p_node.GetLetter();
    return  p_output;
}


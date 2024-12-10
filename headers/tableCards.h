
#ifndef TABLECARDS_H
#define TABLECARDS_H

#include <iostream>
#include <vector>
#include "card.h"

/**
 * @class TableCards
 * @brief Class to manage a collection of cards on the table
 */
class TableCards {
    std::vector<Card> cards; ///< The vector of cards on the table

public:

	/**
	 * @brief Default TableCards constructor
	 */
    TableCards();

	/**
	 * @brief TableCards Copy constructor
	 * @param other The TableCards object to copy from.
	 */
    TableCards(const TableCards &other);

	/**
	 * @brief TableCards Destructor
	 */
    ~TableCards();

	/**
	 * @brief Get the cards currently on the table
	 * @return A const reference to the vector of cards on the table
	 */
    [[nodiscard]] const std::vector<Card>& getTableCards() const;

	/**
	 * @brief Assignment operator for TableCards
	 * @param other The TableCards object to copy from
	 * @return A reference to this TableCards object
	 */
    TableCards& operator=(const TableCards &other);

	/**
	 * @brief Add a card to the table
	 * @param card The Card object to add to the table
	 */
    void addCard(const Card& card);

	/**
	 * @brief Clear all the cards from the table
	 *
	 * Removes all cards currently stored in the table
	 */
    void clearTable();

	/**
	 * @brief Overload of the stream insertion operator for TableCards
	 * @param os The output stream to write to
	 * @param table The TableCards object to display
	 * @return The output stream with the TableCards data written to it
	 */
    friend std::ostream& operator<<(std::ostream& os, const TableCards& table);
};

#endif //TABLECARDS_H

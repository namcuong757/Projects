#pragma once

#include <QtWidgets>
#include <deque>
#include <fstream>
#include <POS/UI/Box/ATextBox.hpp>
#include <POS/UI/ErrorNotification.hpp>
//#include <POS/Product.hpp>
#include <dbmanager.h>
#include <template_item.h>
#include <template_transaction.h>

//Container of products that is linked to a text box
// Contains a ::QApplication and a QMainWindow window
class ProductContainer
{

public:

    // Constructors

    // forward to the other constructor while passing null values
    explicit ProductContainer(QWidget& window) noexcept;

    // Sets all variables except the string
    explicit ProductContainer(QWidget& window, int xPos, int yPos, int xSize, int ySize) noexcept;

    // Operations
    void load(const QString& id);

    void save();

    // Accessors

    // add a product to the list, returns the index in the list
//    auto emplace(auto&&... args) -> int;

    // get the number of products in the cart
    int size();

    // add a product to the list
    // returns the index in the list
    int add(Item *product);

    // search in the DB
    int emplaceFromId(const std::vector<QString>& id);

    int addFunds(const std::vector<QString>& id);

    bool pay();

    // remove the product at the index given as parameter
    void remove(int productIndex);

    // remove the product at the index given as parameter
    void removeSelected();

    // clear all the items
    void clear();

    void setReadOnly(bool value);



private:

    // Helpers

    void printTotal();

    void printFunds();



private:

    QWidget& m_window;

    std::deque<Item*> m_products;

    QTableWidget* m_table;
    ATextBox m_totalTextBox;

    std::int64_t m_funds{ 0 };
    ATextBox m_fundsTextBox;

    QString m_id;

};

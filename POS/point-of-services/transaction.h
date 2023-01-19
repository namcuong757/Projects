#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <item.h>
#include <customer.h>
#include <tuple>
#include <passkey.h>
#include <vector>
using std::tuple, std::vector;

class POS;

class Transaction
{

public:
    /* Constructors */

    Transaction(const Transaction& c) :
        ID(c.ID), date(c.date), time(c.time), customerPhone(c.customerPhone), totalCents(c.totalCents),
                  items(c.items), paymentType(c.paymentType), change(c.change), cardNumber(c.cardNumber), cardExpiration(c.cardExpiration), cardCVV(c.cardCVV) {};

    Transaction(int ID=0, QString date="", QString time="", QString customerPhone="", int totalCents=0,
                vector<tuple<Item, int>> items=vector<tuple<Item,int>>(), QString paymentType="", int tender=0, int change=0, int cardNumber=0, int cardExpiration=0, int cardCVV=0)
        : ID(ID), date(date), time(time), customerPhone(customerPhone), totalCents(totalCents),
          items(items), paymentType(paymentType), change(change), cardNumber(cardNumber), cardExpiration(cardExpiration), cardCVV(cardCVV) {};


    /* Member Vars */
    int ID; /* ID of transaction */
    QString date; /* Day which the  transaction takes place */
    QString time;
    QString customerPhone; /* Phone number of the associated customer */
    int totalCents; /* Total cost of cart in cents */
    vector<tuple<Item, int>> items; /* Vector of (sku-string, quantity) tuples */
    QString paymentType;
    int tender;
    int change;
    int cardNumber;
    int cardExpiration;
    int cardCVV;

    void setFinalPrice(int); /* Set final price of cart to certain amount. */
    void addItem(Item, int); /* Add X of a certain item to the cart. Update total if not already set manually */
    void removeItem(Item, int); /* Remove X of a certain to the cart. Update total if not already set manually */
    int contains(const Item&); /* Return how many of a certain item exist in the cart */

    QString itemsAsString();

    bool operator==(const Transaction&); /* Returns cart equality based on ID */
    Transaction operator=(const Transaction&); /* Copy assigns the given cart */

};

#endif // TRANSACTION_H

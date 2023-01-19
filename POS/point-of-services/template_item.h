#ifndef TEMPLATE_ITEM_H
#define TEMPLATE_ITEM_H

#include <QString>

class Item
{

public:

    /* Constructors */
    Item(int sku, int qty=0, int cents=0, QString name="") :
        sku(sku), qty(qty), cents(cents), name(name) {};

    Item(const Item& i) :
        sku(i.sku), qty(i.qty), cents(i.cents), name(i.name) {};

    Item(const Item* i) :
        sku(i->sku), qty(i->qty), cents(i->cents), name(i->name) {};

    int sku;
    int qty;
    int cents;
    QString name;

    Item& operator=(const Item& i)
    {
        if (this != &i)
        {
            sku = i.sku;
            qty = i.qty;
            cents = i.cents;
            name = i.name;
        }
        return *this;
    }
};

#endif // TEMPLATE_ITEM_H

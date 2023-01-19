#ifndef TEMPLATE_CUSTOMER_H
#define TEMPLATE_CUSTOMER_H

#include <QString>

class Customer
{
public:

    /* Constructors */
    Customer(QString phone="", QString name="", QString address="", QString zip="") :
        phone(phone), name(name), address(address), zip(zip) {};

    /* Member Vars */
    QString phone; /* Numeric customer ID (Phone Number) */
    QString name; /* Customer name */
    QString address; /* Customer street address */
    QString zip; /* Customer zip code */
};

#endif // TEMPLATE_CUSTOMER_H

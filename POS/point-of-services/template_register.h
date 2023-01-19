#ifndef TEMPLATE_REGISTER_H
#define TEMPLATE_REGISTER_H

class POS;

class Register
{
public:
    Register(int ID, int cents=20000) :
        ID(ID), centsInDrawer(cents) {}

    int ID; /* ID of register */
    int centsInDrawer; /* Amount of cash in active Register drawer represented in cents */
};

#endif // TEMPLATE_REGISTER_H

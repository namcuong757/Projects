#ifndef NEW_ORDER_VIEW_H
#define NEW_ORDER_VIEW_H
#include <QtWidgets>
#include <QtSql>
#include <dbmanager.h>

class NewOrderView : public QWidget
{
    Q_OBJECT
public:
    NewOrderView(QWidget* parent = nullptr);
private:
    QVBoxLayout* mainLayout;
};
#endif // NEW_ORDER_VIEW_H

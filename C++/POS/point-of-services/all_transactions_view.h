#ifndef ALL_TRANSACTIONS_VIEW_H
#define ALL_TRANSACTIONS_VIEW_H

#include <QtWidgets>
#include <QtSql>
#include <dbmanager.h>
#include <POS/UI/Screen/Home.hpp>
#include "template_transaction.h"
#include "dbmanager.h"
#include <vector>
class All_transactions_view : public QWidget
{
    Q_OBJECT
public:
    All_transactions_view(QWidget* parent = nullptr);
//    ~All_transactions_view(){};/
private:
    QVBoxLayout* mainLayout;

    QTableView *tableView;
    QSqlTableModel *tableModel;

    QString itemFieldNames[4] = {"ID", "Date", "Time", "Phone"}; //"Total", "Items", "Payment", "Tender", "Change", "Card#", "Card_exp", "cvv"};
    QLineEdit *lineEdits [4];
    QLabel *transactionInfoLabels[4];
    QSortFilterProxyModel *filterModels[4];
    //function
    void clearScreen();

    void dropItem(); // optional
    void closeWindow();

    void highlightItem(); // pop the text in different screen

    void filterResults(); // searching
    void selectedTransaction();

public:
signals:
    void objectSent(Transaction selected);

};

#endif // ALL_TRANSACTIONS_VIEW_H

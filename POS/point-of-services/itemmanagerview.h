#ifndef ItemMANAGERVIEW_H
#define ItemMANAGERVIEW_H

#include <QtWidgets>
#include <QtSql>
#include <dbmanager.h>

class ItemManagerView : public QWidget
{
    Q_OBJECT
public:
    ItemManagerView(QWidget* parent = nullptr);

private:
    QVBoxLayout* mainLayout;

    QTableView *tableView;
    QSqlTableModel *tableModel;

    QString itemFieldNames[4] = {"SKU (Search Only)", "Quantity", "Cents", "Name"};
    QLineEdit *lineEdits [4];
    QLabel *itemInfoLabels[4];
    QSortFilterProxyModel *filterModels[4];


    void submitNew();
    void editExisting();
    void clearScreen();

    void dropItem();
    void closeWindow();

    void highlightItem();

    void filterResults();
};

#endif // ItemMANAGERVIEW_H

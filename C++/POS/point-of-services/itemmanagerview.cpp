#include "itemmanagerview.h"

ItemManagerView::ItemManagerView(QWidget* parent)
{

    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    this->setObjectName("main_widget");

    // Title over table
    QLabel* title = new QLabel("Items");
    title->setObjectName("title");
    mainLayout->addWidget(title);

    /* TableView */

    // Create and add to main layout
    tableView = new QTableView();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(tableView);

    // Hide indexes
    tableView->verticalHeader()->hide();

    // Can't directly edit and can only select whole rows at a time
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setSelectionMode(QTableView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Set to a table model
    tableModel = new QSqlTableModel;
    tableModel->setTable("pos_schema.item");
    tableModel->setSort(0, Qt::SortOrder::AscendingOrder);
    tableModel->select();

    connect(tableView, &QTableView::clicked, this, &ItemManagerView::highlightItem);

    /* END TableView */

    // below the tableview is the rest
    QWidget* bottom = new QWidget();
    bottom->setLayout(new QHBoxLayout());
    mainLayout->addWidget(bottom);

    /* ================================================== */

    /* Item Search/Edit Section (Below TableView and on the left) */

    // contains Labels, LineEdits, and Buttons for table management
    QWidget* searchedit = new QWidget();
    searchedit->setLayout(new QHBoxLayout());

    // Container for Labels tell which LineEdits are which
    QWidget* labelsholder = new QWidget();
    labelsholder->setLayout(new QVBoxLayout());
    searchedit->layout()->addWidget(labelsholder);

    // Container for LineEdits used for input
    QWidget* lineeditsholder = new QWidget();
    lineeditsholder->setLayout(new QVBoxLayout());
    searchedit->layout()->addWidget(lineeditsholder);

    // Add Lables and LineEdits and FilterModels
    for (int i = 0; i < 4; ++i)
    {
        // Add Labels
        labelsholder->layout()->addWidget(new QLabel(this->itemFieldNames[i]));

        // Add LineEdits
        lineeditsholder->layout()->addWidget(lineEdits[i] = new QLineEdit());
        connect(lineEdits[i], &QLineEdit::textEdited, this, &ItemManagerView::filterResults);

        // Add/Layer Filters for searching
        filterModels[i] = new QSortFilterProxyModel();
        filterModels[i]->setFilterCaseSensitivity(Qt::CaseInsensitive);
        filterModels[i]->setFilterKeyColumn(i);
        if (i == 0)
            filterModels[i]->setSourceModel(tableModel);
        else
            filterModels[i]->setSourceModel(filterModels[i-1]);
    }

    // Set the TableView model to the last filterModel
    tableView->setModel(filterModels[3]);

    // Quantity and Cents LineEdits can only have digits
    lineEdits[0]->setValidator(new QIntValidator());
    lineEdits[1]->setValidator(new QIntValidator());
    lineEdits[2]->setValidator(new QIntValidator());

    // Container for buttons for search/edit
    QWidget* searcheditbuttons = new QWidget();
    searcheditbuttons->setLayout(new QVBoxLayout());
    searchedit->layout()->addWidget(searcheditbuttons);

    // Button to add new item to db
    QPushButton *submitNewButton = new QPushButton("Submit New");
    submitNewButton->setObjectName("submit_button");
    connect(submitNewButton, &QPushButton::clicked, this, &ItemManagerView::submitNew);
    searcheditbuttons->layout()->addWidget(submitNewButton);

    // Button to edit item which already exits in db
    QPushButton *editExistingButton = new QPushButton("Edit Existing");
    editExistingButton->setObjectName("edit_button");
    connect(editExistingButton, &QPushButton::clicked, this, &ItemManagerView::editExisting);
    searcheditbuttons->layout()->addWidget(editExistingButton);

    // Button to clear LineEdits
    QPushButton* clearButton = new QPushButton("Clear");
    clearButton->setObjectName("cancel_button");
    connect(clearButton, &QPushButton::clicked, this, &ItemManagerView::clearScreen);
    searcheditbuttons->layout()->addWidget(clearButton);

    // Add labels, LineEdits, and buttons to container underneath table view
    searchedit->layout()->setAlignment(labelsholder, Qt::AlignRight);
    searchedit->layout()->setAlignment(lineeditsholder, Qt::AlignLeft);
    searchedit->layout()->setAlignment(searcheditbuttons, Qt::AlignLeft);
    bottom->layout()->addWidget(searchedit);

    labelsholder->setStyleSheet("max-width: 200px;");

    /* END Item Lookup/Edit Section */

    /* ============================================== */

    /* Item Selection Section (Below TableView and on the right) */

    // Container for holding Labels
    QWidget *itemselect = new QWidget();
    itemselect->setLayout(new QHBoxLayout());

    // Container holding read-only text fields
    QWidget *iteminfo = new QWidget();
    iteminfo->setLayout(new QVBoxLayout());
    itemselect->layout()->addWidget(iteminfo);

    // Add Labels which display selected item information
    for (int i=0; i<4; ++i)
    {
        itemInfoLabels[i] = new QLabel("");
        iteminfo->layout()->addWidget(itemInfoLabels[i]);
    }

    // Container holding buttons
    QWidget *itemselectbuttons = new QWidget();
    itemselectbuttons->setLayout(new QVBoxLayout());
    itemselect->layout()->addWidget(itemselectbuttons);

    // Button to attribute the current item to the transaction
    QPushButton *dropButton = new QPushButton("Delete");
    connect(dropButton, &QPushButton::clicked, this, &ItemManagerView::dropItem);
    itemselectbuttons->layout()->addWidget(dropButton);

    // Add item select widget to bottom
    itemselect->layout()->setAlignment(iteminfo, Qt::AlignRight);
    itemselect->layout()->setAlignment(itemselectbuttons, Qt::AlignLeft);
    bottom->layout()->addWidget(itemselect);

    /* END Item Selection Section */


    // button to close item screen
    QWidget* closeButtonHolder = new QWidget;
    closeButtonHolder->setLayout(new QHBoxLayout);
    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, this, &ItemManagerView::closeWindow);
    closeButton->setObjectName("close_button");
    closeButtonHolder->layout()->addWidget(closeButton);
    mainLayout->addWidget(closeButtonHolder);

    clearScreen();

    this->setStyleSheet(
                "QTableView{font: 16px;}"
                "QPushButton{alignment: left; font: bold 14px; min-width:100px; max-width: 500px; min-height:40px; color: white; background-color: rgb(50,83,135);}"
                "QLineEdit{font: 16px; alignment: left; min-height: 40px; min-width: 250px; max-width: 600px;}"
                "QLabel{font: 16px; min-width:250px; max-width: 600px; min-height: 40px;}"
                "#title{font: bold 18px;}"
                "#close_button{alignment: center; min-width:250px;}"
                );
}

void ItemManagerView::submitNew()
{
    //Adding sku functionality as part of getting things into the database so I can test reading from it
    QString
            //sku=lineEdits[0]->text(), //Just comment this out later
            qty=lineEdits[1]->text(),
            cents=lineEdits[2]->text(),
            name=lineEdits[3]->text();

    // No negative quantities
    if (qty.toInt() < 0)
    {
        QMessageBox error;
        error.setText("Item Submission Failure");
        error.setInformativeText("Quantity must be greater than or equal to zero");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // time to add the item
    Item i = Item(0, qty == "" ? 0 : qty.toInt(), cents == "" ? 0 :cents.toInt(), name);
    if (!dbmanager::addItem(i))
    {
        // dbmanager takes care of displaying errors
        return;
    }

    lineEdits[0]->setText("");
    tableModel->select();
    filterResults();
    QModelIndex index = tableView->model()->index(0, 0);
    tableView->selectionModel()->select(index,
                                        QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    highlightItem();
    filterResults();
}

void ItemManagerView::editExisting()
{
    // get the input text from the line edits
    QString sku=lineEdits[0]->text(),
            qty=lineEdits[1]->text(),
            cents=lineEdits[2]->text(),
            name=lineEdits[3]->text();

    // sku number should be 10 digits
    if (sku.length() != 8)
    {
        QMessageBox error;
        error.setText("Item Update Failure");
        error.setInformativeText("SKU number must include 8 digits");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // see if item with given sku number exists in database
    Item* item = dbmanager::getItem(sku.toInt());
    if(item == nullptr)
    {
        //dbmanager handles errors.
        return;
    }


    // actually make the update

    item->qty = qty == "" ? 0 : qty.toInt();
    item->cents = cents == "" ? 0 :cents.toInt();
    item->name = name;
    if(!(dbmanager::updateItem(*item)))
    {
        //dbmanager handles errors.
        return;
    }

    QMessageBox scs;
    scs.setText("Item Update Success");
    scs.setInformativeText("Item " + name + " updated successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();

    tableModel->select();
    filterResults();
    QModelIndex index = tableView->model()->index(0, 0);
    tableView->selectionModel()->select(index,
                                        QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    highlightItem();
    filterResults();
}

void ItemManagerView::clearScreen()
{
    for (int i = 0; i < 4; ++i)
    {
        lineEdits[i]->setText("");
        itemInfoLabels[i]->setText(itemFieldNames[i]);
    }
    itemInfoLabels[0]->setText("SKU");
    lineEdits[0]->setReadOnly(false);
    tableModel->select();
    filterResults();
}

void ItemManagerView::dropItem()
{

    QString sku = itemInfoLabels[0]->text();
    if (sku == "")
        return;

    QString qty = itemInfoLabels[1]->text();
    if (qty.toInt() > 0)
    {
        QMessageBox error;
        error.setText("Item Drop Error");
        error.setInformativeText("Cannot drop items which are still in inventory");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    Item* item = new Item(sku.toInt(), qty.toInt(),
                            itemInfoLabels[2]->text().toInt(),
                            itemInfoLabels[3]->text());
    if (!dbmanager::dropItem(*item))
    {
        return;//Errors are handled in dbmanager.dropItem()
    }
    QMessageBox scs;
    scs.setText("Item Drop Success");
    scs.setInformativeText("Item " + itemInfoLabels[3]->text() + " dropped successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();
    tableModel->select();
    lineEdits[0]->setText("");
}

void ItemManagerView::closeWindow()
{
    this->hide();
}

void ItemManagerView::highlightItem()
{
    auto row = tableView->selectionModel()->selectedRows().begin()->row();
    for (int i = 0; i < 4; ++i)
    {
        auto idx = tableView->model()->index(row, i);
        auto data = tableView->model()->data(idx);
        auto value = data.value<QString>();
        itemInfoLabels[i]->setText(value);
        lineEdits[i]->setText(value);
    }
    lineEdits[0]->setReadOnly(true);
}

void ItemManagerView::filterResults()
{
    for (int i=0; i < 4; ++i)
    {
        filterModels[i]->setFilterFixedString(lineEdits[i]->text());
    }
}

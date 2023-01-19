#include "all_transactions_view.h"

All_transactions_view::All_transactions_view(QWidget* parent)
{
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    this->setObjectName("main_widget");

    // Title over table
    QLabel* title = new QLabel("Transactions");
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
    tableModel->setTable("pos_schema.transaction");
    tableModel->setSort(0, Qt::SortOrder::AscendingOrder);
    tableModel->select();

    connect(tableView, &QTableView::clicked, this, &All_transactions_view::highlightItem);

    /* END TableView */
    // below the tableview is the rest
    QWidget* bottom = new QWidget();
    bottom->setLayout(new QHBoxLayout());
    mainLayout->addWidget(bottom);

    /* ================================================== */

    /* Transaction Search/Edit Section (Below TableView and on the left) */

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
    for (int i = 0; i < 2; ++i)
    {
        // Add Labels
        labelsholder->layout()->addWidget(new QLabel(this->itemFieldNames[i]));

        // Add LineEdits
        lineeditsholder->layout()->addWidget(lineEdits[i] = new QLineEdit());
        connect(lineEdits[i], &QLineEdit::textEdited, this, &All_transactions_view::filterResults);

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
    tableView->setModel(filterModels[1]);

    // Quantity and Cents LineEdits can only have digits
    lineEdits[0]->setValidator(new QIntValidator());
//    lineEdits[1]->setValidator(new QIntValidator());
//    lineEdits[2]->setValidator(new QIntValidator());
//    lineEdits[3]->setValidator(new QIntValidator());
    /*
    lineEdits[4]->setValidator(new QIntValidator());
    lineEdits[5]->setValidator(new QIntValidator());
    lineEdits[6]->setValidator(new QIntValidator());
    lineEdits[7]->setValidator(new QIntValidator());
    lineEdits[8]->setValidator(new QIntValidator());
    lineEdits[9]->setValidator(new QIntValidator());
    lineEdits[10]->setValidator(new QIntValidator());
    lineEdits[11]->setValidator(new QIntValidator());
    */
    // Container for buttons for search/edit
    QWidget* searcheditbuttons = new QWidget();
    searcheditbuttons->setLayout(new QVBoxLayout());
    searchedit->layout()->addWidget(searcheditbuttons);

    // Button to edit item which already exits in db
    QPushButton *editExistingButton = new QPushButton("Edit Order");
    editExistingButton->setObjectName("edit_button");
//    connect(editExistingButton, &QPushButton::clicked, this, &All_transactions_view::openOrderEditor);
    connect(editExistingButton, &QPushButton::clicked, this, &All_transactions_view::selectedTransaction);
    searcheditbuttons->layout()->addWidget(editExistingButton);

    QPushButton *clearScreenButton = new QPushButton("Clear");
    clearScreenButton->setObjectName("clear_button");
    connect(clearScreenButton, &QPushButton::clicked, this, &All_transactions_view::clearScreen);
    searcheditbuttons->layout()->addWidget(clearScreenButton);

    // Add labels, LineEdits, and buttons to container underneath table view
    searchedit->layout()->setAlignment(labelsholder, Qt::AlignRight);
    searchedit->layout()->setAlignment(lineeditsholder, Qt::AlignLeft);
    searchedit->layout()->setAlignment(searcheditbuttons, Qt::AlignLeft);
    bottom->layout()->addWidget(searchedit);
    // Container for holding Labels
    QWidget *transactionselect = new QWidget();
    transactionselect->setLayout(new QHBoxLayout());

    // Container holding read-only text fields
    QWidget *transactioninfo = new QWidget();
    transactioninfo->setLayout(new QVBoxLayout());
    transactionselect->layout()->addWidget(transactioninfo);
    // Labels which display selected customer information
    for (int i=0; i<4; ++i)
    {
        transactionInfoLabels[i] = new QLabel("");
        transactioninfo->layout()->addWidget(transactionInfoLabels[i]);
    }

    // Add item select widget to bottom
    transactionselect->layout()->setAlignment(transactioninfo, Qt::AlignRight);
    bottom->layout()->addWidget(transactionselect);

    // button to close item screen
    QWidget* closeButtonHolder = new QWidget;
    closeButtonHolder->setLayout(new QHBoxLayout);
    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, this, &All_transactions_view::closeWindow);
    closeButton->setObjectName("close_button");
    closeButtonHolder->layout()->addWidget(closeButton);
    mainLayout->addWidget(closeButtonHolder);

    //clearScreen();

    this->setStyleSheet(
                "QTableView{font: 16px;}"
                "QPushButton{alignment: left; font: bold 14px; min-width:100px; max-width: 500px; min-height:40px; color: white; background-color: rgb(50,83,135);}"
                "QLineEdit{font: 16px; alignment: left; min-height: 40px; min-width: 250px; max-width: 600px;}"
                "QLabel{font: 16px; min-width:250px; max-width: 600px; min-height: 40px;}"
                "#title{font: bold 18px;}"
                "#close_button{alignment: center; min-width:250px;}"
                );
}
void All_transactions_view::clearScreen()
{
    for (int i = 0; i < 2; ++i)
    {
        lineEdits[i]->setText("");
        transactionInfoLabels[i]->setText(itemFieldNames[i]);
        lineEdits[i]->setReadOnly(false);
    }
    transactionInfoLabels[0]->setText("SKU");
    tableModel->select();
    filterResults();
}
void All_transactions_view::closeWindow()
{
    this->hide();
}
void All_transactions_view::highlightItem()
{
    auto row = tableView->selectionModel()->selectedRows().begin()->row();
    for (int i = 0; i < 2; ++i)
    {
        auto idx = tableView->model()->index(row, i);
        auto data = tableView->model()->data(idx);
        auto value = data.value<QString>();
        transactionInfoLabels[i]->setText(value);
        lineEdits[i]->setText(value);
        lineEdits[i]->setReadOnly(true);
    }
}
void All_transactions_view::filterResults()
{
    for (int i=0; i < 2; ++i)
    {
        filterModels[i]->setFilterFixedString(lineEdits[i]->text());
    }
}

void All_transactions_view::selectedTransaction()
{
    vector<QString> attrs;
    vector<Item> items;
    auto row = tableView->selectionModel()->selectedRows().begin()->row();

    for (int i = 0; i < 14; ++i)
    {
        auto idx = tableView->model()->index(row, i);
        auto data = tableView->model()->data(idx);
        auto value = data.value<QString>();
        if (i==4)
        {
            if (value == "")
            {
                items = vector<Item>();
                continue;
            }
            QStringList list = value.split("','");
            int i = 1;
            Item *cur;
            for (QString &str : list)
            {
                if (i++ % 2 == 1)
                {
                    cur = dbmanager::getItem(str.toInt());
                }
                else
                {
                    cur->qty = str.toInt();
                    items.push_back(*cur);
                    delete cur;
                    cur = nullptr;
                }
            }
        }
        attrs.push_back(value);
    }

    Transaction selectedTran = Transaction(
                /* id */attrs[0].toInt(), /* date */attrs[1], /* time */attrs[2], /* phone  */attrs[3], items,
            /* subtotal */attrs[5].toInt(), /* sales tax */attrs[6].toInt(), /* total  */attrs[7].toInt(),
             /* pay type */attrs[8], /* tender  */ attrs[9].toInt(), /* change  */attrs[10].toInt(),
             /* card num */attrs[11].toInt(), /* card exp */attrs[12].toInt(), /* card cvv */attrs[13].toInt());

    emit(objectSent(selectedTran));
    clearScreen();
    hide();
}

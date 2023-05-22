#include "customermanagerview.h"

CustomerManagerView::CustomerManagerView(QWidget* parent)
{

    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->setObjectName("main_widget");

    // Title over table
    QLabel* title = new QLabel("Customers");
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
    tableModel->setTable("pos_schema.customer");
    tableModel->setSort(0, Qt::SortOrder::AscendingOrder);
    tableModel->select();

    connect(tableView, &QTableView::clicked, this, &CustomerManagerView::highlightCustomer);

    /* END TableView */

    // below the tableview is the rest
    QWidget* bottom = new QWidget();
    bottom->setLayout(new QHBoxLayout());
    mainLayout->addWidget(bottom);

    /* ================================================== */

    /* Customer Search/Edit Section (Below TableView and on the left) */

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

    // Add Labels and LineEdits and FilterModels
    for (int i = 0; i < 4; ++i)
    {
        // Add Labels
        labelsholder->layout()->addWidget(new QLabel(this->custFieldNames[i]));

        // Add LineEdits
        lineeditsholder->layout()->addWidget(lineEdits[i] = new QLineEdit());
        connect(lineEdits[i], &QLineEdit::textEdited, this, &CustomerManagerView::filterResults);

        // Add and Layer Filters for searching
        filterModels[i] = new QSortFilterProxyModel();
        filterModels[i]->setFilterCaseSensitivity(Qt::CaseInsensitive);
        filterModels[i]->setFilterKeyColumn(i);
        if (i == 0)
            filterModels[i]->setSourceModel(tableModel);
        else
            filterModels[i]->setSourceModel(filterModels[i-1]);
    }

    // Set the TableView model to the last layer of filterModels
    tableView->setModel(filterModels[3]);

    // Phone and ZIP LineEdit can only have digits
    lineEdits[0]->setValidator(new QIntValidator());
    lineEdits[3]->setValidator(new QIntValidator());

    // Container for buttons for search/edit
    QWidget* searcheditbuttons = new QWidget();
    searcheditbuttons->setLayout(new QVBoxLayout());
    searchedit->layout()->addWidget(searcheditbuttons);

    // Button to add new customer to db
    QPushButton *submitNewButton = new QPushButton("Submit New");
    submitNewButton->setObjectName("submit_button");
    connect(submitNewButton, &QPushButton::clicked, this, &CustomerManagerView::submitNew);
    searcheditbuttons->layout()->addWidget(submitNewButton);

    // Button to edit customer which already exits in db
    QPushButton *editExistingButton = new QPushButton("Edit Existing");
    editExistingButton->setObjectName("edit_button");
    connect(editExistingButton, &QPushButton::clicked, this, &CustomerManagerView::editExisting);
    searcheditbuttons->layout()->addWidget(editExistingButton);

    // Button to clear LineEdits
    QPushButton* clearButton = new QPushButton("Clear");
    clearButton->setObjectName("cancel_button");
    connect(clearButton, &QPushButton::clicked, this, &CustomerManagerView::clearScreen);
    searcheditbuttons->layout()->addWidget(clearButton);

    // Add labels, LineEdits, and buttons to container underneath table view
    searchedit->layout()->setAlignment(labelsholder, Qt::AlignRight);
    searchedit->layout()->setAlignment(lineeditsholder, Qt::AlignLeft);
    searchedit->layout()->setAlignment(searcheditbuttons, Qt::AlignLeft);
    bottom->layout()->addWidget(searchedit);

    /* END Customer Lookup/Edit Section */

    /* ============================================== */

    /* Customer Selection Section (Below TableView and on the right) */

    // Container for holding Labels and Buttons
    QWidget *customerselect = new QWidget();
    customerselect->setLayout(new QHBoxLayout());

    // Container holding read-only text fields
    QWidget *customerselectinfo = new QWidget();
    customerselectinfo->setLayout(new QVBoxLayout());
    customerselect->layout()->addWidget(customerselectinfo);

    // Container holding buttons
    QWidget *customerselectbuttons = new QWidget();
    customerselectbuttons->setLayout(new QVBoxLayout());
    customerselect->layout()->addWidget(customerselectbuttons);

    // Labels which display selected customer information
    for (int i=0; i<4; ++i)
    {
        custInfoLabels[i] = new QLabel("");
        customerselectinfo->layout()->addWidget(custInfoLabels[i]);
    }

    // Button to attribute the current customer to the transaction
    QPushButton *selectButton = new QPushButton("Select");
    connect(selectButton, &QPushButton::clicked, this, &CustomerManagerView::selectCustomer);
    customerselectbuttons->layout()->addWidget(selectButton);

    // Add customer select widget to bottom
    customerselect->layout()->setAlignment(customerselectinfo, Qt::AlignRight);
    customerselect->layout()->setAlignment(customerselectbuttons, Qt::AlignLeft);
    bottom->layout()->addWidget(customerselect);

    /* END Customer Selection Section */


    // button to close customer screen
    QWidget* closeButtonHolder = new QWidget;
    closeButtonHolder->setLayout(new QHBoxLayout);
    QPushButton *closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, this, &CustomerManagerView::closeWindow);
    closeButton->setObjectName("close_button");
    closeButtonHolder->layout()->addWidget(closeButton);
    mainLayout->addWidget(closeButtonHolder);

    this->setStyleSheet(
                "QTableView{font: 16px;}"
                "QPushButton{alignment: left; font: bold 14px; min-width:100px; max-width: 500px; min-height:40px; color: white; background-color: rgb(50,83,135);}"
                "QLineEdit{font: 16px; alignment: left; min-height: 40px; min-width: 250px; max-width: 600px;}"
                "QLabel{font: 16px; min-width:250px; max-width: 600px; min-height: 40px;}"
                "#title{font: bold 18px;}"
                "#close_button{alignment: center; min-width:250px;}"
                );
}

void CustomerManagerView::submitNew()
{
    // get text from lineEdits
    QString phone=lineEdits[0]->text(),
            name=lineEdits[1]->text(),
            address=lineEdits[2]->text(),
            zip=lineEdits[3]->text();

    // phone number (if input at all) should be 10 digits
    if (phone.length() != 0 && phone.length() != 10)
    {
        QMessageBox error;
        error.setText("Customer Submission Failure");
        error.setInformativeText("Phone number must include 10 digits");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // zip number (if input at all) should be 5 digits
    if (zip.length() != 0 && zip.length() != 5)
    {
        QMessageBox error;
        error.setText("Customer Submission Failure");
        error.setInformativeText("ZIP number must include 5 digits");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // if given no phone number we can still submit a customer with a name
    if (phone.length() == 0)
    {
        // must have a name in this case
        if (name.length() == 0)
        {
            QMessageBox error;
            error.setText("Customer Submission Failure");
            error.setInformativeText("Must include a phone number or name");
            error.setIcon(QMessageBox::Warning);
            error.setStandardButtons(QMessageBox::Ok);
            error.setBaseSize(600,120);
            error.exec();
            return;
        }

        // see if the name exists
        QSqlQuery check;
        check.prepare("select from pos_schema.customer where phone is null and name = :name");
        check.bindValue(":name", name);
        if (check.size() > 0)
        {
            QMessageBox error;
            error.setText("Customer Submission Failure");
            error.setInformativeText("Customer name already exists");
            error.setIcon(QMessageBox::Warning);
            error.setStandardButtons(QMessageBox::Ok);
            error.setBaseSize(600,120);
            error.exec();
            return;
        }
    }

    // time to insert the customer
    QSqlQuery q;
    q.prepare("insert into pos_schema.customer values(:phone, :name, :address, :zip);");
    q.bindValue(":phone", phone=="" ? NULL : phone);
    q.bindValue(":name", name==""? NULL : name);
    q.bindValue(":address", address==""? NULL : address);
    q.bindValue(":zip", zip==""? NULL : zip);

    if (!q.exec())
    {
        QMessageBox error;
        error.setText("Customer Submission Error");
        error.setInformativeText(q.lastError().text());
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        qDebug() << "Customer Insert Error in func \"submitNew\"" << q.lastError().text();
        return;
    }

    QMessageBox scs;
    scs.setText("Customer Submission Success");
    scs.setInformativeText("Customer " + name + " submitted successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();
    tableModel->select();
}

void CustomerManagerView::editExisting()
{

    // get the input text from the line edits
    QString phone=lineEdits[0]->text(),
            name=lineEdits[1]->text(),
            address=lineEdits[2]->text(),
            zip=lineEdits[3]->text();

    // phone number should be 10 digits
    if (phone.length() != 10)
    {
        QMessageBox error;
        error.setText("Customer Update Failure");
        error.setInformativeText("Phone number must include 10 digits to update customer");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // zip number (if input at all) should be 5 digits
    if (zip.length() != 0 && zip.length() != 5)
    {
        QMessageBox error;
        error.setText("Customer Update Failure");
        error.setInformativeText("ZIP number must include 5 digits");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // see if customer with given phone number exists in database
    QSqlQuery sel;
    sel.prepare("SELECT FROM pos_schema.customer WHERE phone = :phone");
    sel.bindValue(":phone", phone);

    if (!sel.exec())
    {
        QMessageBox error;
        error.setText("Customer Update Error");
        error.setInformativeText(sel.lastError().text());
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        qDebug() << "Customer Selection Error in func \"editExisting\"" << sel.lastError().text();
        return;
    }

    // if customer doesn't exist we have nothing to update
    if (sel.size() == 0)
    {
        QMessageBox error;
        error.setText("Customer Update Failure");
        error.setInformativeText("Customer phone number does not exist. Submit as new instead");
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        return;
    }

    // time to update the customer
    QSqlQuery upd;
    upd.prepare("UPDATE pos_schema.customer "
                "SET phone = :phone, name = :name, address = :address, zip = :zip "
                "WHERE phone = :phone;");
    upd.bindValue(":phone", phone=="" ? NULL : phone);
    upd.bindValue(":name", name==""? NULL : name);
    upd.bindValue(":address", address==""? NULL : address);
    upd.bindValue(":zip", zip==""? NULL : zip);

    if (!upd.exec())
    {
        QMessageBox error;
        error.setText("Customer Update Error");
        error.setInformativeText(sel.lastError().text());
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);
        error.setBaseSize(600,120);
        error.exec();
        qDebug() << "Customer update Error in func \"editExisitng\"" << upd.lastError().text();
        return;
    }

    QMessageBox scs;
    scs.setText("Customer Update Success");
    scs.setInformativeText("Customer " + name + " updated successfully");
    scs.setIcon(QMessageBox::Information);
    scs.setStandardButtons(QMessageBox::Ok);
    scs.setBaseSize(600,120);
    scs.exec();
    tableModel->select();
}

void CustomerManagerView::clearScreen()
{
    // set all text fields to empty strings
    for (int i = 0; i < 4; ++i)
    {
        lineEdits[i]->setText("");
        custInfoLabels[i]->setText(custFieldNames[i]);
    }

    // no customer selected anymore, can type in a phone number again
    lineEdits[0]->setReadOnly(false);

    // reset table and search filter
    tableModel->select();
    filterResults();
}

void CustomerManagerView::selectCustomer()
{
    //TODO : send customer to open order so their phone number can be associated with it
}

void CustomerManagerView::closeWindow()
{
    this->hide();
}

void CustomerManagerView::highlightCustomer()
{
    // get the first selected row (user can only select one at a time anyway)
    auto row = tableView->selectionModel()->selectedRows().begin()->row();

    // set the text fields to the selected record's information
    for (int i = 0; i < 4; ++i)
    {
        auto idx = tableView->model()->index(row, i);
        auto data = tableView->model()->data(idx);
        auto value = data.value<QString>();
        custInfoLabels[i]->setText(value);
        lineEdits[i]->setText(value);
    }

    // dont let user update phone number of record. If they want to change the phone number they can submit them as a new customer.
    lineEdits[0]->setReadOnly(true);
}

void CustomerManagerView::filterResults()
{
    // apply all filter models for all the text in the LineEdits
    for (int i=0; i < 4; ++i)
    {
        filterModels[i]->setFilterFixedString(lineEdits[i]->text());
    }
}

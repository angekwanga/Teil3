#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

namespace bht {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), network("./") // Assuming data files are in current directory
{
    // Create central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Create layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Create search label
    searchLabel = new QLabel("Recherche des arrêts:", this);
    mainLayout->addWidget(searchLabel);
    
    // Create search input field
    searchInputField = new QPlainTextEdit(this);
    searchInputField->setMaximumHeight(50);
    mainLayout->addWidget(searchInputField);
    
    // Create results list view
    resultListView = new QListView(this);
    resultModel = new QStringListModel(this);
    resultListView->setModel(resultModel);
    mainLayout->addWidget(resultListView);
    
    // Set window properties
    setWindowTitle("Recherche d'arrêts GTFS");
    resize(600, 400);
    
    // Connect signals
    connect(searchInputField, &QPlainTextEdit::textChanged, this, &MainWindow::onTextChanged);
}

MainWindow::~MainWindow() {
    // Cleanup if needed
}

void MainWindow::onTextChanged() {
    // Get search text
    QString searchText = searchInputField->toPlainText();
    
    // Search in network
    auto searchResults = network.search(searchText.toStdString());
    
    // Update list model with results
    QStringList resultStrings;
    for (const auto& stop : searchResults) {
        QString stopInfo = QString("%1 [%2]").arg(QString::fromStdString(stop.name)).arg(QString::fromStdString(stop.id));
        resultStrings.append(stopInfo);
    }
    
    resultModel->setStringList(resultStrings);
}

} // namespace bht
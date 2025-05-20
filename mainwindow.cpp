#include "mainwindow.h"
#include <QHeaderView>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Create network instance
    try {
        network = new bht::Network("GTFSShort");
    } catch (const std::exception& e) {
        std::cerr << "Error initializing network: " << e.what() << std::endl;
    }
    
    setupUi();
    loadRoutes();
}

MainWindow::~MainWindow() {
    delete network;
    delete stopsTableModel;
}

void MainWindow::setupUi() {
    // Create central widget and layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);
    
    // Create route selection UI
    QLabel *routeLabel = new QLabel("Route:", centralWidget);
    mainLayout->addWidget(routeLabel);
    
    routeComboBox = new QComboBox(centralWidget);
    mainLayout->addWidget(routeComboBox);
    connect(routeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onRouteSelected);
    
    // Create trip selection UI
    QLabel *tripLabel = new QLabel("Trip:", centralWidget);
    mainLayout->addWidget(tripLabel);
    
    tripComboBox = new QComboBox(centralWidget);
    mainLayout->addWidget(tripComboBox);
    connect(tripComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onTripSelected);
    
    // Create search UI
    QLabel *searchLabel = new QLabel("Search Stops:", centralWidget);
    mainLayout->addWidget(searchLabel);
    
    searchLineEdit = new QLineEdit(centralWidget);
    searchLineEdit->setEnabled(false);
    mainLayout->addWidget(searchLineEdit);
    connect(searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    
    // Create table view
    stopsTableView = new QTableView(centralWidget);
    stopsTableModel = new QStandardItemModel(this);
    stopsTableView->setModel(stopsTableModel);
    
    // Set up table headers
    stopsTableModel->setColumnCount(4);
    stopsTableModel->setHorizontalHeaderLabels({"Nr.", "Name Haltestelle", "Ankunftszeit", "Abfahrtszeit"});
    
    // Configure table view
    stopsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    stopsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    stopsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    stopsTableView->setEnabled(false);
    
    mainLayout->addWidget(stopsTableView);
    
    // Set window title and size
    setWindowTitle("GTFS Explorer");
    resize(800, 600);
}

void MainWindow::loadRoutes() {
    // Get all routes from network
    routes = network->getRoutes();
    
    routeComboBox->clear();
    for (const auto& route : routes) {
        QString displayName = QString::fromStdString(network->getRouteDisplayName(route));
        routeComboBox->addItem(displayName, QString::fromStdString(route.id));
    }
}

void MainWindow::onRouteSelected(int index) {
    if (index < 0) return;
    
    // Get selected route ID
    QString routeId = routeComboBox->itemData(index).toString();
    loadTrips(routeId.toStdString());
    
    // Reset trip selection and disable search/table until a trip is selected
    tripComboBox->setCurrentIndex(-1);
    searchLineEdit->setEnabled(false);
    stopsTableView->setEnabled(false);
    stopsTableModel->removeRows(0, stopsTableModel->rowCount());
}

void MainWindow::loadTrips(const std::string &routeId) {
    // Get trips for selected route
    currentTrips = network->getTripsForRoute(routeId);
    
    tripComboBox->clear();
    for (const auto& trip : currentTrips) {
        QString displayName = QString::fromStdString(network->getTripDisplayName(trip));
        tripComboBox->addItem(displayName, QString::fromStdString(trip.id));
    }
}

void MainWindow::onTripSelected(int index) {
    if (index < 0) {
        searchLineEdit->setEnabled(false);
        stopsTableView->setEnabled(false);
        return;
    }
    
    // Get selected trip ID
    QString tripId = tripComboBox->itemData(index).toString();
    currentTripId = tripId.toStdString();
    
    // Enable search and table view
    searchLineEdit->setEnabled(true);
    stopsTableView->setEnabled(true);
    
    // Load stop times for selected trip
    loadStopTimes(currentTripId);
}

void MainWindow::loadStopTimes(const std::string &tripId) {
    // Get stop times for selected trip
    std::vector<bht::StopTime> stopTimes = network->getStopTimesForTrip(tripId);
    updateStopsTable(stopTimes);
}

void MainWindow::onSearchTextChanged(const QString &text) {
    if (currentTripId.empty()) return;
    
    // Search stop times with filter
    std::vector<bht::StopTime> filteredStopTimes = 
        network->searchStopTimesForTrip(text.toStdString(), currentTripId);
    
    updateStopsTable(filteredStopTimes);
}

void MainWindow::updateStopsTable(const std::vector<bht::StopTime> &stopTimes) {
    // Clear existing table data
    stopsTableModel->removeRows(0, stopsTableModel->rowCount());
    
    // Add rows for each stop time
    for (const auto& stopTime : stopTimes) {
        bht::Stop stop = network->getStopById(stopTime.stopId);
        
        QList<QStandardItem*> rowItems;
        
        // Stop sequence number
        rowItems.append(new QStandardItem(QString::number(stopTime.stopSequence)));
        
        // Stop name
        rowItems.append(new QStandardItem(QString::fromStdString(stop.name)));
        
        // Arrival time
        rowItems.append(new QStandardItem(formatTime(stopTime.arrivalTime)));
        
        // Departure time
        rowItems.append(new QStandardItem(formatTime(stopTime.departureTime)));
        
        // Add row to model
        stopsTableModel->appendRow(rowItems);
    }
}

QString MainWindow::formatTime(const bht::GTFSTime &time) {
    return QString("%1:%2:%3")
        .arg(time.hour, 2, 10, QChar('0'))
        .arg(time.minute, 2, 10, QChar('0'))
        .arg(time.second, 2, 10, QChar('0'));
}
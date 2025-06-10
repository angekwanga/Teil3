#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "network.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRouteSelected(int index);
    void onTripSelected(int index);
    void onSearchTextChanged(const QString &text);

private:
    // GUI elements
    QComboBox *routeComboBox;
    QComboBox *tripComboBox;
    QLineEdit *searchLineEdit;
    QTableView *stopsTableView;
    QStandardItemModel *stopsTableModel;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    // Network data
    bht::Network *network;
    std::vector<bht::Route> routes;
    std::vector<bht::Trip> currentTrips;
    std::string currentTripId;

    // Helper methods
    void setupUi();
    void loadRoutes();
    void loadTrips(const std::string &routeId);
    void loadStopTimes(const std::string &tripId);
    void updateStopsTable(const std::vector<bht::StopTime> &stopTimes);
    QString formatTime(const bht::GTFSTime &time);
};

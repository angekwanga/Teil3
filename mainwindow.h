#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include "network.h"

namespace bht {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTextChanged();

private:
    QPlainTextEdit *searchInputField;
    QLabel *searchLabel;
    QListView *resultListView;
    QStringListModel *resultModel;
    Network network;
};

} // namespace bht
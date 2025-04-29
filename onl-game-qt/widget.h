#pragma once
#include <iostream>
#include "numberdelegate.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>
#include <QTableWidget>
#include "field.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "communicator.h"
#include "application.h"
class Widget : public QWidget
{
    Q_OBJECT

    TCommunicator *comm;

public:

        //Constr destruct
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onStartButtonClicked();
    void onRulesButtonClicked();
    //void connectCellClick(const QTableWidget *table, void (Widget::*handler)(int, int));
    void createTable();
    void createTable_1();
    void checkInput();
    void checkInput_1();
    void createSecondTable();
    void ggwp();
    void lockCell(int row, int column,  bool player_number);


private:
    void The_Game_Row(QTableWidgetItem *item);

        //variables
    bool player_number = true;
    Field Game;
    bool end = false;

        //Check valid of moves
    void checkFirstValid(QTableWidgetItem *item);
    void checkFirstValid_1(QTableWidgetItem *item);
    void checkSecondValid(QTableWidgetItem *item);
    ///
    void The_Game();
    void The_Game_1();
    void create_Secondary_Table();

        //Last changed table item
    QTableWidgetItem *lastModifiedItem = nullptr;

        //Buttons
    QPushButton *next = nullptr;
    QPushButton *thiscomp = nullptr;
    QPushButton *twocomputers = nullptr;
    QPushButton *rules = nullptr;

        //Input numbers
    QLineEdit *numberInput = nullptr;
    QLineEdit *numberInput_2 = nullptr;
    QLineEdit *numberInput_3 = nullptr;

        //TABLES
    QTableWidget *table_first = nullptr;
    QTableWidget *table_second = nullptr;

        //Tables for game
    QTableWidget *table_first_to_second = nullptr;
    QTableWidget *table_second_to_first = nullptr;

        //Other
    void updateNeighborCellFlags(int row, int column,  bool player_number);
    NumberDelegate *delegate = nullptr;
    //QVBoxLayout *layout = nullptr;
};

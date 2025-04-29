#ifndef FIELD_H
#define FIELD_H
#include <QTableWidget>
#include <iostream>
class Field
{
public:
    //Это измененный файл
        //Constr destruct
    Field(int N_size = 9, int D_move = 50, int M_max = 9);
    ~Field();

        //Other functions
    void Redefinition(int N_size, int D_move, int M_max);

        //return variables
    int Get_Moves();
    int Get_Size();
    int Get_MaxNumber();

        //Set values
    void SetPlayerValuesFromTable(QTableWidget* table, bool player_number);
    void SetPlayerValuesFromOther(int **a);
    ///
    void ZeroTables();
        //Check moves
    bool Check_Moves();
    bool Check_validity(bool player_number);
    int Check_Accuracy(bool player_number);
    int GetMax_Accuracy(bool player_number);
    void Make_Move(int row, int col, bool player_number);
    bool Was_Move_Good(int row, int col, bool player_number);
    bool Was_Move_Good_1(int row, int col, bool player_number);
    //int a;
private:
    int Max_Accuracy(bool player_number);
        //TABLES
    int** first_player = nullptr;
    int** second_player = nullptr;

    ///
    int** first_to_second;
    ///
    int** second_to_first;

        //Input variables
    int size = 9;
    int moves = 50;
    int max_number = 9;
    int made_moves = 0;
    int max_fir_accuracy = 0;
    int max_sec_accuracy = 0;
};

#endif // FIELD_H

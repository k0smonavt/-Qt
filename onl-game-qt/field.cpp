#include "field.h"

Field::Field(int N_size, int D_move, int M_max)
{
    size = N_size;
    moves = D_move;
    max_number = M_max;
    first_player = new int * [size];
    for(int i = 0; i < size; ++i) first_player[i] = new int[size];
    second_player = new int * [size];
    for(int i = 0; i < size; ++i) second_player[i] = new int[size];
    first_to_second = new int * [size];
    for(int i = 0; i < size; ++i) first_to_second[i] = new int[size];
    second_to_first = new int * [size];
    for(int i = 0; i < size; ++i) second_to_first[i] = new int[size];
    ZeroTables();
}

Field::~Field()
{
    for (int i = 0; i < size; i++){
        delete[] first_player[i];
    }
    delete[] first_player;

    for (int i = 0; i < size; i++){
        delete[] second_player[i];
    }
    delete[] second_player;
    for (int i = 0; i < size; i++){
        delete[] first_to_second[i];
    }
    delete[] first_to_second;

    for (int i = 0; i < size; i++){
        delete[] second_to_first[i];
    }
    delete[] second_to_first;
}

void Field::Redefinition(int N_size, int D_move, int M_max)
{
    if(first_player != nullptr){
        for (int i = 0; i < size; i++){
            delete[] first_player[i];
        }
        delete[] first_player;
    }
    if(second_player != nullptr){
        for (int i = 0; i < size; i++){
            delete[] second_player[i];
        }
        delete[] second_player;
    }
    size = N_size;
    moves = D_move;
    max_number = M_max;
    first_player = new int * [size];
    for(int i = 0; i < size; ++i) first_player[i] = new int[size];
    second_player = new int * [size];
    for(int i = 0; i < size; ++i) second_player[i] = new int[size];
    first_to_second = new int * [size];
    for(int i = 0; i < size; ++i) first_to_second[i] = new int[size];
    second_to_first = new int * [size];
    for(int i = 0; i < size; ++i) second_to_first[i] = new int[size];
    ZeroTables();
}



int Field::Get_Moves(){
    return this->moves;
}

int Field::Get_Size(){
    return this->size;
}

int Field::Get_MaxNumber(){
    return this->max_number;
}

void Field::SetPlayerValuesFromTable(QTableWidget* table, bool player_number)
{
    if(player_number){
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                QTableWidgetItem* item = table->item(row, col);
                if (item) {
                    if(item->text().toInt() > max_number){
                        first_player[row][col] = max_number;
                    }
                    else{
                        first_player[row][col] = item->text().toInt();
                    }
                }
            }
        }
        max_sec_accuracy = Max_Accuracy(player_number);
    }
    else{
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                QTableWidgetItem* item = table->item(row, col);
                if (item) {
                    if(item->text().toInt() > max_number){
                        second_player[row][col] = max_number;
                    }
                    else{
                        second_player[row][col] = item->text().toInt();
                    }
                }
            }
        }
        max_fir_accuracy = Max_Accuracy(player_number);
    }
}

void Field::SetPlayerValuesFromOther(int **a)
{
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                        second_player[row][col] = **a;
            }
        }
        max_fir_accuracy = Max_Accuracy(1);
}

///
void Field::ZeroTables()
{
    for(int i = 0; i < this->size; ++i){
        for(int j = 0; j < this->size; j++){
            first_player[i][j] = 0;
        }
    }

    for(int i = 0; i < this->size; ++i){
        for(int j = 0; j < this->size; j++){
            second_player[i][j] = 0;
        }
    }
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                //QTableWidgetItem* item = new QTableWidgetItem(" ");
                //first_player[row][col] = item->text().toInt();
                //second_player[row][col] = item->text().toInt();
                first_player[row][col] = 0;
                second_player[row][col] = 0;
            }
        }
}

bool Field::Check_Moves(){
    int each_move = made_moves / 2;
    if(each_move == moves){
        return false;
    }
    else return true;
    return false;
}
bool Field::Check_validity(bool player_number){
    int count = 0;
    if(player_number){
        for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                if (first_player[row][col] != 0){
                    count++;
                }
                }
        }
    }
    else{
        for (int row = 0; row < size; ++row) {
                for (int col = 0; col < size; ++col) {
                if (second_player[row][col] != 0){
                    count++;
                }
                }
        }
    }
    if(count >= this->size) return false;
    else return true;
}


void Field::Make_Move(int row, int col, bool player_number){
    if(player_number){
        first_to_second[row][col] = 1;
    }
    else{
        second_to_first[row][col] = 1;
    }
    made_moves += 1;
}



bool Field::Was_Move_Good(int row, int col, bool player_number){

    int result = 0;
    if(player_number){
        result = first_to_second[row][col] * second_player[row][col];
        if(result != 0) return true;
        else return false;
    }
    else{
        result = second_to_first[row][col] * first_player[row][col];
        if(result != 0) return true;
        else return false;
    }
}

int Field::Max_Accuracy(bool player_number){
    int result = 0;
    if(player_number){
        for(int i=0; i<this->size; i++){
            for(int j=0; j<this->size; j++){
                result += first_player[i][j];
            }
        }
    }
    else{
        for(int i=0; i<this->size; i++){
            for(int j=0; j<this->size; j++){
                result += second_player[i][j];
            }
        }
    }
    return result;
}

int Field::Check_Accuracy(bool player_number){
    int result = 0;
    if(player_number){
        for(int i=0; i<this->size; i++){
            for(int j=0; j<this->size; j++){
                result += first_to_second[i][j] * second_player[i][j];
            }
        }
    }
    else{
        for(int i=0; i<this->size; i++){
            for(int j=0; j<this->size; j++){
                result += second_to_first[i][j] * first_player[i][j];
            }
        }
    }
    return result;
}

int Field::GetMax_Accuracy(bool player_number){
    int result = 0;
    if(player_number){
        result = max_fir_accuracy;
    }
    else{
        result = max_sec_accuracy;
    }
    return result;
}

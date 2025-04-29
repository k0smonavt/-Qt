#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    delegate = new NumberDelegate;
    setMinimumSize(500, 500);
    setMaximumSize(1500, 1500);
    setWindowTitle("Game of Digits");

    rules = new QPushButton("Rules", this);
    rules->setFixedWidth(150);
    rules->move(250, 150);

    // Создаем кнопку "This computer"
    thiscomp = new QPushButton("This computer", this);
    thiscomp->setFixedWidth(150);
    thiscomp->move(250, 150);

    // Создаем кнопку "Multiplayer"
    twocomputers = new QPushButton("Multiplayer", this);
    twocomputers ->setFixedWidth(150);
    twocomputers->move(250, 250);

    // Подключаем сигнал нажатия кнопки к слоту для открытия окна ввода числа
    connect(thiscomp, &QPushButton::clicked, this, &Widget::onStartButtonClicked);

    connect(twocomputers, &QPushButton::clicked, this, &Widget::ggwp);

    // Размещаем кнопку на виджете
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(thiscomp, 0, Qt::AlignHCenter);
    layout->addWidget(twocomputers, 0, Qt::AlignHCenter);
    layout->addWidget(rules, 0, Qt::AlignHCenter);
    setLayout(layout);
}

Widget::~Widget() {
    delete thiscomp;
    delete numberInput;
    delete numberInput_2;
    delete numberInput_3;
    delete table_first;
    delete twocomputers;
    delete rules;
    delete lastModifiedItem;
}

void Widget::ggwp()
{
    //Создаем кнопку Next
    next = new QPushButton("Next", this);
    next->setFixedWidth(150);
    next->move(250, 150);
    // Создаем окно №1 для ввода числа
    numberInput = new QLineEdit(this);
    numberInput->setValidator(new QIntValidator(4, 999, this));
    numberInput->setPlaceholderText("Enter size of field");
    numberInput->setFixedWidth(300);

    // Создаем окно №2 для ввода числа
    numberInput_2 = new QLineEdit(this);
    numberInput_2->setValidator(new QIntValidator(4, 999, this));
    numberInput_2->setPlaceholderText("Enter number of moves");
    numberInput_2->setFixedWidth(300);

    // Создаем окно №3 для ввода числа
    numberInput_3 = new QLineEdit(this);
    numberInput_3->setValidator(new QIntValidator(4, 999, this));
    numberInput_3->setPlaceholderText("Enter max number");
    numberInput_3->setFixedWidth(300);

    // Размещаем окно для ввода числа на виджете
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
    if (layout) {
        layout->addWidget(numberInput, 0, Qt::AlignHCenter);
    }
    if (layout) {
        layout->addWidget(numberInput_2, 0, Qt::AlignHCenter);
    }
    if (layout) {
        layout->addWidget(numberInput_3, 0, Qt::AlignHCenter);
    }
    if (layout) {
        layout->addWidget(next, 0, Qt::AlignHCenter);
    }

    // Подключаем сигнал нажатия Enter в окне ввода к слоту для создания таблицы
    connect(next, &QPushButton::clicked, this, &Widget::checkInput_1);


    // Скрываем кнопки
    thiscomp->hide();
    twocomputers->hide();
    rules->hide();
}

void Widget::checkInput_1()
{
    if (numberInput->text().toInt() < 4 || numberInput->text().toInt() > 9)
    {
        QMessageBox::warning(this, "Message", "Not correct size of field\nReed the rules");
        numberInput->hide();
        numberInput_2->hide();
        numberInput_3->hide();
        next->hide();
        ggwp();
    }
    //else if (numberInput_2->text().toInt() > ((numberInput->text().toInt()*numberInput->text().toInt())/2 + numberInput->text().toInt()%10 + 1))
    else if (numberInput_2->text().toInt() > ((numberInput->text().toInt()*numberInput->text().toInt())/1.6))
    {
        QMessageBox::warning(this, "Message", "Not correct number of moves\nReed the rules");
        numberInput->hide();
        numberInput_2->hide();
        numberInput_3->hide();
        next->hide();
        ggwp();
    }
    else if((numberInput->text() == "" || numberInput_2->text() == "") && numberInput_3->text() == "")
    {
        QMessageBox::warning(this, "Message", "Operand cannot be empty");
        numberInput->hide();
        numberInput_2->hide();
        numberInput_3->hide();
        next->hide();
        ggwp();
    }
    else if(numberInput->text() != "" || numberInput_2->text() != "" || numberInput_3->text() == "")
    {
        numberInput_3->text() = numberInput->text();
        createTable_1();
    }
    else createTable_1();
}

void Widget::createTable_1()
{
    //Пересоздаем поле для вычислений
    Game.Redefinition(numberInput->text().toInt(),numberInput_2->text().toInt(), numberInput_3->text().toInt());
    //Называем окошко
    setWindowTitle("First player");
    int size = Game.Get_Size();
    table_first = new QTableWidget(size, size, this);
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
    if (layout) {
        layout->addWidget(table_first);
    }
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem("0");
            table_first->setItem(row, col, item);
        }
    }
    table_first->setItemDelegate(delegate);
    numberInput->hide();
    numberInput_2->hide();
    numberInput_3->hide();
    next->hide();
    connect(table_first, &QTableWidget::itemChanged, this, &Widget::checkFirstValid_1);
}

void Widget::onStartButtonClicked()
{
    //Создаем кнопку Next
    next = new QPushButton("Next", this);
    next->setFixedWidth(150);
    next->move(250, 150);
    // Создаем окно №1 для ввода числа
    numberInput = new QLineEdit(this);
    numberInput->setValidator(new QIntValidator(4, 999, this));
    numberInput->setPlaceholderText("Enter size of field");
    numberInput->setFixedWidth(300);

    // Создаем окно №2 для ввода числа
    numberInput_2 = new QLineEdit(this);
    numberInput_2->setValidator(new QIntValidator(4, 999, this));
    numberInput_2->setPlaceholderText("Enter number of moves");
    numberInput_2->setFixedWidth(300);

    // Создаем окно №3 для ввода числа
    numberInput_3 = new QLineEdit(this);
    numberInput_3->setValidator(new QIntValidator(4, 999, this));
    numberInput_3->setPlaceholderText("Enter max number");
    numberInput_3->setFixedWidth(300);

    // Размещаем окно для ввода числа на виджете
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
    if (layout) {
        layout->addWidget(numberInput, 0, Qt::AlignHCenter);
    }
    if (layout) {
        layout->addWidget(numberInput_2, 0, Qt::AlignHCenter);
    }
    if (layout) {
        layout->addWidget(numberInput_3, 0, Qt::AlignHCenter);
    }
    if (layout) {
        layout->addWidget(next, 0, Qt::AlignHCenter);
    }

    // Подключаем сигнал нажатия Enter в окне ввода к слоту для создания таблицы
    connect(next, &QPushButton::clicked, this, &Widget::checkInput);


    // Скрываем кнопки
    thiscomp->hide();
    twocomputers->hide();
    rules->hide();
}
void Widget::onRulesButtonClicked()
{

}

void Widget::checkInput()
{
    if (numberInput->text().toInt() < 4 || numberInput->text().toInt() > 9)
    {
        QMessageBox::warning(this, "Message", "Not correct size of field\nReed the rules");
        numberInput->hide();
        numberInput_2->hide();
        numberInput_3->hide();
        next->hide();
        onStartButtonClicked();
    }
    //else if (numberInput_2->text().toInt() > ((numberInput->text().toInt()*numberInput->text().toInt())/2 + numberInput->text().toInt()%10 + 1))
    else if (numberInput_2->text().toInt() > ((numberInput->text().toInt()*numberInput->text().toInt())/1.6))
    {
        QMessageBox::warning(this, "Message", "Not correct number of moves\nReed the rules");
        numberInput->hide();
        numberInput_2->hide();
        numberInput_3->hide();
        next->hide();
        onStartButtonClicked();
    }
    else if((numberInput->text() == "" || numberInput_2->text() == "") && numberInput_3->text() == "")
    {
        QMessageBox::warning(this, "Message", "Operand cannot be empty");
        numberInput->hide();
        numberInput_2->hide();
        numberInput_3->hide();
        next->hide();
        onStartButtonClicked();
    }
    else if(numberInput->text() != "" || numberInput_2->text() != "" || numberInput_3->text() == "")
    {
        numberInput_3->text() = numberInput->text();
        createTable();
    }
    else createTable();
}

void Widget::createTable()
{
    //Пересоздаем поле для вычислений
    Game.Redefinition(numberInput->text().toInt(),numberInput_2->text().toInt(), numberInput_3->text().toInt());
    //Называем окошко
    setWindowTitle("First player");
    int size = Game.Get_Size();
    table_first = new QTableWidget(size, size, this);
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
    if (layout) {
        layout->addWidget(table_first);
    }
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem("0");
            table_first->setItem(row, col, item);
        }
    }
    table_first->setItemDelegate(delegate);
    numberInput->hide();
    numberInput_2->hide();
    numberInput_3->hide();
    next->hide();
    connect(table_first, &QTableWidget::itemChanged, this, &Widget::checkFirstValid);
}

void Widget::createSecondTable()
{
    //Называем окошко
    setWindowTitle("Second player");
    int size = numberInput->text().toInt();
    table_second = new QTableWidget(size, size, this);
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
    if (layout) {
        layout->addWidget(table_second);
    }
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem("0");
            table_second->setItem(row, col, item);
        }
    }
    table_second->setItemDelegate(delegate);
    connect(table_second, &QTableWidget::itemChanged, this, &Widget::checkSecondValid);
}

void Widget::create_Secondary_Table()
{
    int size = Game.Get_Size();
    table_first_to_second = new QTableWidget(size, size, this);
    table_second_to_first = new QTableWidget(size, size, this);


    // Создаем таблицы для игры
    table_first_to_second = new QTableWidget(size, size, this);
    table_second_to_first = new QTableWidget(size, size, this);

    player_number = true;
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Блокировка редактирования
            item->setData(Qt::BackgroundRole, QBrush(Qt::gray)); // Устанавливаем начальный цвет
            table_first_to_second->setItem(row, col, item);
        }
    }
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Блокировка редактирования
            item->setData(Qt::BackgroundRole, QBrush(Qt::gray)); // Устанавливаем начальный цвет
            table_second_to_first->setItem(row, col, item);
        }
    }
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(this->layout());
    if (layout) {
        layout->addWidget(table_first_to_second);
        table_first_to_second->setVisible(false);
    }
    if (layout) {
        layout->addWidget(table_second_to_first);
        table_second_to_first->setVisible(false);
    }
    The_Game();
}

void Widget::checkFirstValid(QTableWidgetItem *item)
{

    if(item!= nullptr) lastModifiedItem = item;
    Game.SetPlayerValuesFromTable(table_first, player_number);
    //table_first->hide();
    if (Game.Check_validity(player_number)) {

        if(item!= nullptr) lockCell(lastModifiedItem->row(), lastModifiedItem->column(), player_number);
    }
    else{
        QMessageBox::warning(this, "Message", "Now the opponent's move");
        table_first->hide();
        player_number = false;
        createSecondTable();
    }
}

void Widget::checkFirstValid_1(QTableWidgetItem *item)
{

    if(item!= nullptr) lastModifiedItem = item;
    Game.SetPlayerValuesFromTable(table_first, player_number);
    //table_first->hide();
    if (Game.Check_validity(player_number)) {

        if(item!= nullptr) lockCell(lastModifiedItem->row(), lastModifiedItem->column(), player_number);
    }
    else{
        QMessageBox::warning(this, "Message", "Now the opponent's move");
        table_first->hide();
        player_number = false;
        The_Game_1();
    }
}



void Widget::checkSecondValid(QTableWidgetItem *item)
{

    if(item!= nullptr) lastModifiedItem = item;
    Game.SetPlayerValuesFromTable(table_second, player_number);
    //table_first->hide();
    if (Game.Check_validity(player_number)) {
        if(item!= nullptr) lockCell(lastModifiedItem->row(), lastModifiedItem->column(), player_number);
    }
    else{
        QMessageBox::warning(this, "Message", "Now the opponent's move");
        table_second->hide();
        player_number = true;
        ///
        create_Secondary_Table();
    }
}

void Widget::lockCell(int row, int column,  bool player_number) {
    if(player_number){
        disconnect(table_first, &QTableWidget::itemChanged, this, &Widget::checkFirstValid);
        QTableWidgetItem* item = table_first->item(row, column);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Блокировка редактирования
        }

        updateNeighborCellFlags(row - 1, column, player_number);
        updateNeighborCellFlags(row + 1, column, player_number);
        updateNeighborCellFlags(row, column - 1, player_number);
        updateNeighborCellFlags(row, column + 1, player_number);
        connect(table_first, &QTableWidget::itemChanged, this, &Widget::checkFirstValid);
    }
    else{
        disconnect(table_second, &QTableWidget::itemChanged, this, &Widget::checkSecondValid);
        QTableWidgetItem* item = table_second->item(row, column);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Блокировка редактирования
        }

        updateNeighborCellFlags(row - 1, column, player_number);
        updateNeighborCellFlags(row + 1, column, player_number);
        updateNeighborCellFlags(row, column - 1, player_number);
        updateNeighborCellFlags(row, column + 1, player_number);
        connect(table_second, &QTableWidget::itemChanged, this, &Widget::checkSecondValid);
    }
}

void Widget::updateNeighborCellFlags(int row, int column,  bool player_number) {
    if(player_number){
        if (row >= 0 && row < Game.Get_Size() && column >= 0 && column < Game.Get_Size()) {
            QTableWidgetItem* item = table_first->item(row, column);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Блокировка редактирования
            }
        }
    }
    else{
        if (row >= 0 && row < Game.Get_Size() && column >= 0 && column < Game.Get_Size()) {
            QTableWidgetItem* item = table_second->item(row, column);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Блокировка редактирования
            }
        }
    }
}

void Widget::The_Game()
{

    if(Game.Check_Moves() && !(end)){
        if(player_number){
            setWindowTitle("First player make move");
            table_first_to_second->setVisible(true);

            // Используем лямбда-функцию для связывания сигнала и слота

            connect(table_first_to_second, &QTableWidget::cellClicked, this, [this](int row, int col){
                // Получаем объект QTableWidgetItem и вызываем метод The_Game_Row
                QTableWidgetItem *item = table_first_to_second->item(row, col);
                if (item->background() == QBrush(Qt::green) || item->background() == QBrush(Qt::red)) {
                    disconnect(table_first_to_second, &QTableWidget::cellClicked, this, nullptr);
                }
                else{
                    if (item) {
                        The_Game_Row(item);
                    }
                }
            });


        }
        else{
            setWindowTitle("Second player make move");
            table_second_to_first->setVisible(true);
            // Используем лямбда-функцию для связывания сигнала и слота
            connect(table_second_to_first, &QTableWidget::cellClicked, this, [this](int row, int col){
                // Получаем объект QTableWidgetItem и вызываем метод The_Game_Row
                QTableWidgetItem *item = table_second_to_first->item(row, col);
                if (item->background() == QBrush(Qt::green) || item->background() == QBrush(Qt::red)) {
                    disconnect(table_second_to_first, &QTableWidget::cellClicked, this, nullptr);
                }
                else{
                    if (item) {
                        The_Game_Row(item);
                    }
                }
            });

        }
    }
    else{
        player_number = true;
        int accuracy_of_first = Game.Check_Accuracy(player_number);
        player_number = false;
        int accuracy_of_second = Game.Check_Accuracy(player_number);
        setWindowTitle("The End!");
        if (accuracy_of_first > accuracy_of_second) {
            QMessageBox::information(this, "Победа!", "Победил первый!");
        } else if(accuracy_of_first < accuracy_of_second) {
            QMessageBox::information(this, "Победа!", "Победил второй!");
        }
        else{
            QMessageBox::information(this, "Победа!", "Ничья!");
        }
    }
}

void Widget::The_Game_1()
{

    if(Game.Check_Moves() && !(end)){
            if(player_number){
                setWindowTitle("First player make move");
                table_first_to_second->setVisible(true);

                // Используем лямбда-функцию для связывания сигнала и слота



                connect(table_first_to_second, &QTableWidget::cellClicked, this, [this](int row, int col){
                    // Получаем объект QTableWidgetItem и вызываем метод The_Game_Row
                    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(recieve(QByteArray)));
                    QTableWidgetItem *item = table_first_to_second->item(row, collumn);
                    if (item->background() == QBrush(Qt::green) || item->background() == QBrush(Qt::red)) {
                        disconnect(table_first_to_second, &QTableWidget::cellClicked, this, nullptr);
                    }
                    else{
                        if (item) {
                            The_Game_Row(item);
                        }
                    }
                });
        }




        }
    else{
        player_number = true;
        int accuracy_of_first = Game.Check_Accuracy(player_number);
        player_number = false;
        int accuracy_of_second = Game.Check_Accuracy(player_number);
        setWindowTitle("The End!");
        if (accuracy_of_first > accuracy_of_second) {
            QMessageBox::information(this, "Победа!", "Победил первый!");
        } else if(accuracy_of_first < accuracy_of_second) {
            QMessageBox::information(this, "Победа!", "Победил второй!");
        }
        else{
            QMessageBox::information(this, "Победа!", "Ничья!");
        }
    }
}

void Widget::The_Game_Row(QTableWidgetItem *item)
{
    int accuracy = 0;
    int row = item->row();
    int col = item->column();

    if(player_number){
        // Меняем цвет ячейки на красный или зеленый

            if (item->background() == QBrush(Qt::gray)) {
                Game.Make_Move(row, col, player_number);
                if(Game.Was_Move_Good(row, col, player_number)){
                    item->setBackground(QBrush(Qt::green));
                }
                else{
                    item->setBackground(QBrush(Qt::red));
                }
            } else {
                //тут надо сделать так чтобы нажатие уже нажатой кнопки не обрабатывалось
            }

            // Меняем значение переменной player_number на противоположное
            player_number = false;

            // Скрываем таблицу

            table_first_to_second->setVisible(false);

            // После смены цвета и переменной можно при необходимости запретить дальнейшие нажатия на кнопки
            //table_first_to_second->setEnabled(false);
            disconnect(table_first_to_second, &QTableWidget::cellClicked, this, nullptr);
            The_Game();
    }
    else{

            if (item->background() == QBrush(Qt::gray)) {
                Game.Make_Move(row, col, player_number);
                if(Game.Was_Move_Good(row, col, player_number)){
                    item->setBackground(QBrush(Qt::green));
                }
                else{
                    item->setBackground(QBrush(Qt::red));
                }
            } else {
                //тут надо сделать так чтобы нажатие уже нажатой кнопки не обрабатывалось
            }

            // Меняем значение переменной player_number на противоположное
            player_number = true;

            // Скрываем таблицу

            table_second_to_first->setVisible(false);
            // После смены цвета и переменной можно при необходимости запретить дальнейшие нажатия на кнопки
            //table_second_to_first->setEnabled(false);
            disconnect(table_second_to_first, &QTableWidget::cellClicked, this, nullptr);
            The_Game();

    }
    accuracy = Game.Check_Accuracy(player_number);
    if(accuracy == Game.GetMax_Accuracy(player_number)){
        end = true;
    }
}

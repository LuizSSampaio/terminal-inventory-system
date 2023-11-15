#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

void mainActions(const SQLite::Database &db);
void viewItems(const SQLite::Database &db);
void addItem(const SQLite::Database &db);
void editItem(const SQLite::Database &db);
void deleteItem(const SQLite::Database &db);

bool applicationIsRunning = true;

int main() {
    for (int i = 0; i < 100; i++) {
        std::cout << " " << "\n";
    }

    std::cout << "Terminal Inventory System" << std::endl;

    SQLite::Database db("inventory.db3", SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
    db.exec(
        "CREATE TABLE IF NOT EXISTS products (name TEXT, price REAL, quantity INTEGER);"
    );

    // ReSharper disable once CppDFALoopConditionNotUpdated
    while (applicationIsRunning) {
        mainActions(db);
    }

    return 0;
}

void mainActions(const SQLite::Database &db) {
    std::cout << "[1] View items" << "\n";
    std::cout << "[2] Add item" << "\n";
    std::cout << "[3] Edit item" << "\n";
    std::cout << "[4] Delete item" << "\n";
    std::cout << "[5] Exit" << "\n";

    std::cout << "Enter your action: ";

    int action = 0;
    std::cin >> action;

    switch (action) {
        case 1:
            viewItems(db);
            break;
        case 2:
            addItem(db);
            break;
        case 3:
            editItem(db);
            break;
        case 4:
            deleteItem(db);
            break;
        case 5:
            applicationIsRunning = false;
            break;
        default:
            std::cout << "Action not found";
            break;
    }

    std::cin.ignore();
    std::cout << "Press ENTER to continue: ";
    std::cin.ignore();
    for (int i = 0; i < 100; i++) {
        std::cout << " " << "\n";
    }
}

void viewItems(const SQLite::Database &db) {
    SQLite::Statement query(db, "SELECT rowid, name, price, quantity FROM products;");
    while (query.executeStep()) {
        std::cout
            << "ID: " << query.getColumn(0)
            << " | Name: " << query.getColumn(1)
            << " | Price: " << query.getColumn(2)
            << " | Quantity: " << query.getColumn(3)
            << std::endl;
    }
}

void addItem(const SQLite::Database &db) {
    std::string name;
    double price;
    int quantity;

    SQLite::Statement querry(db, "INSERT INTO products (name, price, quantity) VALUES (?, ?, ?);");

    std::cout << "Enter the name: ";
    std::cin >> name;
    querry.bind(1, name);

    std::cout << "Enter the price: ";
    std::cin >> price;
    querry.bind(2, price);

    std::cout << "Enter the quantity: ";
    std::cin >> quantity;
    querry.bind(3, quantity);

    querry.exec();
}

void editItem(const SQLite::Database &db) {
    int id;
    std::string name;
    double price;
    int quantity;

    SQLite::Statement querry(db, "UPDATE products SET name = ?, price = ?, quantity = ? WHERE rowid = ?;");

    std::cout << "Enter the id: ";
    std::cin >> id;
    querry.bind(4, id);

    std::cout << "Enter the name: ";
    std::cin >> name;
    querry.bind(1, name);

    std::cout << "Enter the price: ";
    std::cin >> price;
    querry.bind(2, price);

    std::cout << "Enter the quantity: ";
    std::cin >> quantity;
    querry.bind(3, quantity);

    querry.exec();
}

void deleteItem(const SQLite::Database &db) {
    int id;

    SQLite::Statement querry(db, "DELETE FROM products WHERE rowid = ?;");

    std::cout << "Enter the id: ";
    std::cin >> id;
    querry.bind(1, id);

    querry.exec();
}

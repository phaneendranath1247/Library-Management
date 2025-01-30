#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <iomanip> 

using namespace std;

class Book {
    int id;
    string title, author;
    int quantity;

public:
    Book(int id, string title, string author, int quantity) 
        : id(id), title(title), author(author), quantity(quantity) {}

    void display() {
        cout << left << setw(10) << id << setw(20) << title << setw(15) << author 
             << setw(10) << quantity << endl;
    }

    int getId() { return id; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    int getQuantity() { return quantity; }

    void addQuantity(int additional) { quantity += additional; }

    bool borrowBook() {
        if (quantity > 0) {
            quantity--;
            return true;
        }
        return false;
    }

    void returnBook() { quantity++; }

    string serialize() {
        return to_string(id) + "," + title + "," + author + "," + to_string(quantity);
    }

    static Book deserialize(const string& data) {
        int id, quantity;
        string title, author;

        try {
            size_t pos1 = data.find(',');
            size_t pos2 = data.find(',', pos1 + 1);
            size_t pos3 = data.find(',', pos2 + 1);

            id = stoi(data.substr(0, pos1));
            title = data.substr(pos1 + 1, pos2 - pos1 - 1);
            author = data.substr(pos2 + 1, pos3 - pos2 - 1);
            quantity = stoi(data.substr(pos3 + 1));
        } catch (const exception& e) {
            return Book(0, "", "", 0);
        }

        return Book(id, title, author, quantity);
    }
};

class Library {
    vector<Book> books;
    const string bookFile = "books.txt";

public:
    void loadBooks() {
        ifstream file(bookFile);
        if (!file.is_open()) {
            return;
        }

        string line;
        while (getline(file, line)) {
            Book book = Book::deserialize(line);
            if (book.getId() != 0) {
                books.push_back(book);
            }
        }
        file.close();
    }

    void saveBooks() {
        ofstream file(bookFile);
        if (!file) {
            return;
        }

        file << left << setw(10) << "ID" 
             << setw(20) << "Title" 
             << setw(15) << "Author" 
             << setw(10) << "Quantity" << endl;
        file << string(60, '-') << endl;

        for (auto& book : books) {
            file << left << setw(10) << book.getId()
                 << setw(20) << book.getTitle()
                 << setw(15) << book.getAuthor()
                 << setw(10) << book.getQuantity() << endl;
        }
        file.close();
    }

    void addBook() {
        int id;
        cout << "Enter Book ID: ";
        cin >> id;

        for (auto& book : books) {
            if (book.getId() == id) {
                cout << "Book already exists.\n";
                cout << "1. Add more copies\n";
                cout << "2. Cancel\n";
                int choice;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    int additional;
                    cout << "Enter additional copies: ";
                    cin >> additional;
                    book.addQuantity(additional);
                    saveBooks();
                }
                return;
            }
        }

        string title, author;
        int quantity;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Quantity: ";
        cin >> quantity;

        books.emplace_back(id, title, author, quantity);
        saveBooks();
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books available in the library.\n";
            return;
        }
        cout << left << setw(10) << "ID" << setw(20) << "Title" 
             << setw(15) << "Author" << setw(10) << "Quantity" << endl;
        cout << string(60, '-') << endl;
        for (auto& book : books) {
            book.display();
        }
    }

    Book* searchBook(int id) {
        for (auto& book : books) {
            if (book.getId() == id)
                return &book;
        }
        return nullptr;
    }

    void borrowBook() {
        int id;
        cout << "Enter Book ID to Borrow: ";
        cin >> id;
        Book* book = searchBook(id);
        if (book && book->borrowBook()) {
            saveBooks();
        } else {
            cout << "Book not available or not found!\n";
        }
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to Return: ";
        cin >> id;
        Book* book = searchBook(id);
        if (book) {
            book->returnBook();
            saveBooks();
        }
    }
};

int main() {
    Library library;
    library.loadBooks();

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Display Books\n3. Search Book\n4. Borrow Book\n5. Return Book\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            library.addBook();
        } else if (choice == 2) {
            library.displayBooks();
        } else if (choice == 3) {
            int id;
            cout << "Enter Book ID to Search: ";
            cin >> id;
            Book* book = library.searchBook(id);
            if (book) {
                book->display();
            }
        } else if (choice == 4) {
            library.borrowBook();
        } else if (choice == 5) {
            library.returnBook();
        }
    } while (choice != 6);

    library.saveBooks();
    return 0;
}

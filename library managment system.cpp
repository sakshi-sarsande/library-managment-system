#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int bookID;
    string title;
    string author;
    bool isIssued;

    void input() {
        cout << "Enter Book ID: ";
        cin >> bookID;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        isIssued = false;
    }

    void display() {
        cout << bookID << "\t" << title << "\t" << author << "\t";
        if (isIssued)
            cout << "Issued\n";
        else
            cout << "Available\n";
    }
};

void addBook() {
    Book b;
    ofstream file("library.dat", ios::binary | ios::app);
    b.input();
    file.write((char*)&b, sizeof(b));
    file.close();
    cout << "\nBook Added Successfully!\n";
}

void displayBooks() {
    Book b;
    ifstream file("library.dat", ios::binary);
    cout << "\nID\tTitle\tAuthor\tStatus\n";
    cout << "-------------------------------------\n";
    while (file.read((char*)&b, sizeof(b))) {
        b.display();
    }
    file.close();
}

void issueBook() {
    Book b;
    int id;
    fstream file("library.dat", ios::binary | ios::in | ios::out);
    cout << "Enter Book ID to Issue: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.bookID == id && !b.isIssued) {
            b.isIssued = true;
            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));
            cout << "\nBook Issued Successfully!\n";
            file.close();
            return;
        }
    }
    cout << "\nBook not found or already issued!\n";
    file.close();
}

void returnBook() {
    Book b;
    int id;
    fstream file("library.dat", ios::binary | ios::in | ios::out);
    cout << "Enter Book ID to Return: ";
    cin >> id;

    while (file.read((char*)&b, sizeof(b))) {
        if (b.bookID == id && b.isIssued) {
            b.isIssued = false;
            file.seekp(-sizeof(b), ios::cur);
            file.write((char*)&b, sizeof(b));
            cout << "\nBook Returned Successfully!\n";
            file.close();
            return;
        }
    }
    cout << "\nBook not found or not issued!\n";
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
            issueBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            cout << "Exiting Program...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 5);

    return 0;
}

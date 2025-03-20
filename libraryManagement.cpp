#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Book class
class Book {
public:
    int id;
    string title, author;
    bool isIssued;

    Book() {} // Default constructor

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        isIssued = false;
    }
};

// Member class
class Member {
public:
    string name;
    vector<int> borrowedBooks; // Stores book IDs

    Member() {} // Default constructor

    Member(string n) {
        name = n;
    }

    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
    }

    void returnBook(int bookID) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == bookID) {
                borrowedBooks.erase(it);
                break;
            }
        }
    }
};

// Fine system (Assuming a fine of 10 per overdue day)
class FineSystem {
public:
    unordered_map<int, int> overdueDays; // bookID -> overdue days

    void addFine(int bookID, int days) {
        overdueDays[bookID] = days;
    }

    int calculateFine(int bookID) {
        return overdueDays[bookID] * 10;
    }
};

// Library class to manage books and members
class Library {
private:
    unordered_map<int, Book> books;
    unordered_map<int, Member> members;
    FineSystem fineSystem;

public:
    // Add a new book
    void addBook(int id, string title, string author) {
        books[id] = Book(id, title, author);
        cout << "Book added successfully.\n";
    }

    // Remove a book
    void removeBook(int id) {
        if (books.find(id) != books.end()) {
            books.erase(id);
            cout << "Book removed successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    // Search a book by ID
    void searchBook(int id) {
        if (books.find(id) != books.end()) {
            cout << "Book Found: " << books[id].title << " by " << books[id].author << "\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    // Add a new member
    void addMember(int id, string name) {
        members[id] = Member(name);
        cout << "Member added successfully.\n";
    }

    // Remove a member
    void removeMember(int id) {
        if (members.find(id) != members.end()) {
            members.erase(id);
            cout << "Member removed successfully.\n";
        } else {
            cout << "Member not found.\n";
        }
    }

    // Issue a book to a member
    void issueBook(int bookID, int memberID) {
        if (books.find(bookID) == books.end()) {
            cout << "Book not found.\n";
            return;
        }
        if (members.find(memberID) == members.end()) {
            cout << "Member not found.\n";
            return;
        }
        if (books[bookID].isIssued) {
            cout << "Book is already issued.\n";
            return;
        }

        books[bookID].isIssued = true;
        members[memberID].borrowBook(bookID);
        cout << "Book issued successfully.\n";
    }

    // Return a book
    void returnBook(int bookID, int memberID, int overdueDays) {
        if (books.find(bookID) == books.end()) {
            cout << "Book not found.\n";
            return;
        }
        if (members.find(memberID) == members.end()) {
            cout << "Member not found.\n";
            return;
        }

        books[bookID].isIssued = false;
        members[memberID].returnBook(bookID);

        if (overdueDays > 0) {
            fineSystem.addFine(bookID, overdueDays);
            cout << "Book returned late. Fine applied: " << fineSystem.calculateFine(bookID) << "\n";
        } else {
            cout << "Book returned successfully.\n";
        }
    }

    // Display fine for a specific book
    void checkFine(int bookID) {
        if (fineSystem.overdueDays.find(bookID) != fineSystem.overdueDays.end()) {
            cout << "Fine for Book ID " << bookID << " is: " << fineSystem.calculateFine(bookID) << "\n";
        } else {
            cout << "No fine for this book.\n";
        }
    }
};

// Main function
int main() {
    Library lib;
    int choice, bookID, memberID, overdueDays;
    string title, author, name;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n2. Remove Book\n3. Search Book\n";
        cout << "4. Add Member\n5. Remove Member\n6. Issue Book\n";
        cout << "7. Return Book\n8. Check Fine\n9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID, Title, Author: ";
                cin >> bookID;
                cin.ignore();
                getline(cin, title);
                getline(cin, author);
                lib.addBook(bookID, title, author);
                break;
            case 2:
                cout << "Enter Book ID to remove: ";
                cin >> bookID;
                lib.removeBook(bookID);
                break;
            case 3:
                cout << "Enter Book ID to search: ";
                cin >> bookID;
                lib.searchBook(bookID);
                break;
            case 4:
                cout << "Enter Member ID and Name: ";
                cin >> memberID;
                cin.ignore();
                getline(cin, name);
                lib.addMember(memberID, name);
                break;
            case 5:
                cout << "Enter Member ID to remove: ";
                cin >> memberID;
                lib.removeMember(memberID);
                break;
            case 6:
                cout << "Enter Book ID and Member ID to issue: ";
                cin >> bookID >> memberID;
                lib.issueBook(bookID, memberID);
                break;
            case 7:
                cout << "Enter Book ID, Member ID, and Overdue Days: ";
                cin >> bookID >> memberID >> overdueDays;
                lib.returnBook(bookID, memberID, overdueDays);
                break;
            case 8:
                cout << "Enter Book ID to check fine: ";
                cin >> bookID;
                lib.checkFine(bookID);
                break;
            case 9:
                cout << "Exiting system...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}

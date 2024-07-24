#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    Book* left;
    Book* right;

    Book(int id, string title, string author) : id(id), title(title), author(author), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Book* root;

    Book* insert(Book* node, int id, string title, string author) {
        if (node == nullptr) {
            return new Book(id, title, author);
        }
        if (id < node->id) {
            node->left = insert(node->left, id, title, author);
        } else if (id > node->id) {
            node->right = insert(node->right, id, title, author);
        }
        return node;
    }

    Book* search(Book* node, int id) {
        if (node == nullptr || node->id == id) {
            return node;
        }
        if (id < node->id) {
            return search(node->left, id);
        } else {
            return search(node->right, id);
        }
    }

    void inorder(Book* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "ID: " << node->id << ", Title: " << node->title << ", Author: " << node->author << endl;
            inorder(node->right);
        }
    }

    Book* deleteNode(Book* root, int id) {
        if (root == nullptr) return root;
        if (id < root->id) {
            root->left = deleteNode(root->left, id);
        } else if (id > root->id) {
            root->right = deleteNode(root->right, id);
        } else {
            if (root->left == nullptr) {
                Book* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Book* temp = root->left;
                delete root;
                return temp;
            }
            Book* temp = minValueNode(root->right);
            root->id = temp->id;
            root->title = temp->title;
            root->author = temp->author;
            root->right = deleteNode(root->right, temp->id);
        }
        return root;
    }

    Book* minValueNode(Book* node) {
        Book* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

public:
    BST() : root(nullptr) {}

    void insert(int id, string title, string author) {
        root = insert(root, id, title, author);
    }

    void search(int id) {
        Book* result = search(root, id);
        if (result != nullptr) {
            cout << "Book found: ID: " << result->id << ", Title: " << result->title << ", Author: " << result->author << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void display() {
        inorder(root);
    }

    void deleteBook(int id) {
        root = deleteNode(root, id);
    }
};

int main() {
    BST library;
    int choice, id;
    string title, author;

    while (true) {
        cout << "Library Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Display Books\n";
        cout << "4. Delete Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.insert(id, title, author);
                break;
            case 2:
                cout << "Enter book ID to search: ";
                cin >> id;
                library.search(id);
                break;
            case 3:
                library.display();
                break;
            case 4:
                cout << "Enter book ID to delete: ";
                cin >> id;
                library.deleteBook(id);
                break;
            case 5:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


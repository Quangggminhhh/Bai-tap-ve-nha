#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;

class Borrowable {
public:
    virtual void borrow() = 0;
    virtual void returnItem() = 0;
    virtual bool isAvailable() const = 0;
    virtual ~Borrowable() = default;
};

class Book : public Borrowable {
private:
    string title;
    string author;
    string ISBN;
    bool available;
public:
    Book(string t, string a, string i)
        : title(move(t)), author(move(a)), ISBN(move(i)), available(true) {}

    void borrow() override {
        if (available) {
            available = false;
            cout << "Sach '" << title << "' da duoc muon." << endl;
        } else {
            cout << "Sach '" << title << "' khong co san de muon." << endl;
        }
    }

    void returnItem() override {
        available = true;
        cout << "Sach '" << title << "' da duoc tra lai." << endl;
    }

    bool isAvailable() const override {
        return available;
    }

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return ISBN; }
};

class DVD : public Borrowable {
private:
    string title;
    string director;
    int duration;
    bool available;
public:
    DVD(string t, string d, int dur)
        : title(move(t)), director(move(d)), duration(dur), available(true) {}

    void borrow() override {
        if (available) {
            available = false;
            cout << "DVD '" << title << "' da duoc muon." << endl;
        } else {
            cout << "DVD '" << title << "' khong co san de muon." << endl;
        }
    }

    void returnItem() override {
        available = true;
        cout << "DVD '" << title << "' da duoc tra lai." << endl;
    }

    bool isAvailable() const override {
        return available;
    }

    string getTitle() const { return title; }
    string getDirector() const { return director; }
    int getDuration() const { return duration; }
};

class Library {
private:
    vector<unique_ptr<Borrowable>> items;
public:
    void addItem(unique_ptr<Borrowable> item) {
        items.push_back(move(item));
    }

    void borrowItem(const string& title) {
        auto it = find_if(items.begin(), items.end(), [&title](const auto& item) {
            return item->isAvailable() &&
                   (dynamic_cast<Book*>(item.get()) && dynamic_cast<Book*>(item.get())->getTitle() == title ||
                    dynamic_cast<DVD*>(item.get()) && dynamic_cast<DVD*>(item.get())->getTitle() == title);
        });

        if (it != items.end()) {
            (*it)->borrow();
        } else {
            cout << "Khong tim thay muc '" << title << "' trong thu vien." << endl;
        }
    }

    void returnItem(const string& title) {
        auto it = find_if(items.begin(), items.end(), [&title](const auto& item) {
            return (dynamic_cast<Book*>(item.get()) && dynamic_cast<Book*>(item.get())->getTitle() == title ||
                    dynamic_cast<DVD*>(item.get()) && dynamic_cast<DVD*>(item.get())->getTitle() == title);
        });

        if (it != items.end()) {
            (*it)->returnItem();
        } else {
            cout << "Khong tim thay muc '" << title << "' trong thu vien." << endl;
        }
    }
};

int main() {
    Library library;

    library.addItem(unique_ptr<Borrowable>(new Book("Nha Gia Kim", "Paulo Coelho", "978-3-16-148410-0")));
    library.addItem(unique_ptr<Borrowable>(new Book("1984", "George Orwell", "978-0-452-28423-4")));

    library.addItem(unique_ptr<Borrowable>(new DVD("Inception", "Christopher Nolan", 148)));
    library.addItem(unique_ptr<Borrowable>(new DVD("The Matrix", "Lana Wachowski, Lilly Wachowski", 136)));

    library.borrowItem("Nha Gia Kim");
    library.returnItem("Nha Gia Kim");

    library.borrowItem("Inception");
    library.returnItem("Inception");

    library.borrowItem("Khong ton tai");

    return 0;
}


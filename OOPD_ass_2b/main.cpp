#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstring>
#include <cctype>
#include <limits>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;
int ID = 1;
const int MAX_ITEMS = 500; // Maximum number of items in the library
class LibraryItem
{
public:
   
    virtual void printDetails() const = 0;
    virtual ~LibraryItem() {}
};

class Book : public LibraryItem
{
private:
    int ID;
    int book_id;
    int isbn;
    string title;
    string authors;
    int original_publication_year;
    bool borrowed;
    // double average_rating;
    // int  ratings_count;
public:
    // Constructor
    Book() : book_id(0), isbn(0), title(""), authors(""), original_publication_year(0) {}
    Book(int ID, int book_id, int isbn, const string &title, const string &authors, int original_publication_year)
        : ID(ID), book_id(book_id), isbn(isbn), title(title), authors(authors), original_publication_year(original_publication_year)
    {
    }

    // Getter functions
    int getID() const
    {
        return ID;
    }
    void setID(int id)
    {
        ID = id;
    }

    int getBookID() const
    {
        return book_id;
    }

    void setBookID(int bookid)
    {
        book_id = bookid;
    }

    int getISBN() const
    {
        return isbn;
    }
    void setISBN(int Isbn)
    {
        isbn = Isbn;
    }

    string getTitle() const
    {
        return title;
    }

    void setTitle(const string &newTitle)
    {
        title = newTitle;
    }

    string getAuthors() const
    {
        return authors;
    }
    void setAuthors(const string &newAuthor)
    {
        authors = newAuthor;
    }
    int getPublicationYear() const
    {
        return original_publication_year;
    }
    void setPublicationYear(int year)
    {
        original_publication_year = year;
    }
    bool isBorrowed() const
    {
        return borrowed;
    }
    void setBorrowed(bool status)
    {
        borrowed = status;
    }

    void printDetails() const override
    {
        cout << "ID: " << ID << "\nBook_id: " << book_id << "\nISBN: " << isbn << "\nTitle: " << title << "\nAuthors: " << authors << "\nPublication Year: "
             << original_publication_year << "\n";
    }
};

class PublicationRank : public LibraryItem
{
private:
    int ID;
    string publication;
    int rank;
    double totalPaid;
    bool borrowed;

public:
    // Constructor
    PublicationRank(int ID, const string &publication, int rank, double totalPaid)
        : ID(ID), publication(publication), rank(rank), totalPaid(totalPaid) {}

    int getID() const
    {
        return ID;
    }
    string getPublication() const
    {
        return publication;
    }
    int getrank() const
    {
        return rank;
    }
    double gettotalPaid() const
    {
        return totalPaid;
    }
    bool isBorrowed() const
    {
        return borrowed;
    }
    void setBorrowed(bool status)
    {
        borrowed = status;
    }
    void printDetails() const override
    {
        cout << "ID: " << ID << "\nPublication Name: " << publication << "\nRank: " << rank << "\nTotal Paid: " << totalPaid << "\n";
    }
};

class Journals : public LibraryItem
{
private:
    int ID;
    string title;

public:
    // Constructor
    Journals(int ID, const string &title)
        : ID(ID), title(title)
    {
    }
    int getID() const
    {
        return ID;
    }
    string getTitle() const
    {
        return title;
    }
    void printDetails() const override
    {
        cout << "ID: " << ID << "\nJournal Title: " << title << "\n";
    }
};

class User
{
private:
    string name;
    bool isTeacher;
    static const int MAX_BORROWED_BOOKS = 3; // Maximum number of books a user can borrow
    int borrowedCount;

public:
    Book *borrowedBooks[MAX_BORROWED_BOOKS];
    PublicationRank *borrowedbooks[MAX_BORROWED_BOOKS];
    Journals *borrowedJournals[MAX_BORROWED_BOOKS];
    time_t borrowedDates[MAX_BORROWED_BOOKS];
    User() : name(""), isTeacher(false), borrowedCount(0)
    {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i)
        {
            borrowedBooks[i] = nullptr;
        }
    }
    User(const string &name, bool isTeacher) : name(name), isTeacher(isTeacher)
    {
        borrowedCount = 0;
    }
    // User(const string& name, bool isTeacher = false) : name(name), isTeacher(isTeacher) {}

    string getName() const
    {
        return name;
    }

    bool isTeacherUser() const
    {
        return isTeacher;
    }
    int getBorrowedCount() const
    {
        return borrowedCount;
    }
    int getMaxBorrowedBooks() const
    {
        return MAX_BORROWED_BOOKS;
    }
    void incrementBorrowedCount()
    {
        borrowedCount++;
    }
    // Function to check if a book is currently borrowed by the user
    bool isBookBorrowed(Book *book) const
    {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i)
        {
            if (borrowedBooks[i] == book)
            {
                return true;
            }
        }
        return false;
    }
    bool canBorrowMoreBooks() const
    {
        return getBorrowedCount() < MAX_BORROWED_BOOKS;
    }

    void borrowJournal(Journals* journal, time_t borrowTime) {
        borrowedJournals[borrowedCount] = journal;
        borrowedDates[borrowedCount] = borrowTime;
        borrowedCount++;
    }

    // Function to get the last borrow time for a specific book
    time_t getLastBorrowTime(const Book *book) const
    {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i)
        {
            if (borrowedBooks[i] == book)
            {
                return borrowedDates[i];
            }
        }
        return 0; 
    }
    // Function to set the last borrow time for a specific book
    void setLastBorrowTime(const Book *book, time_t borrowTime)
    {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i)
        {
            if (borrowedBooks[i] == book)
            {
                borrowedDates[i] = borrowTime;
                return; 
            }
        }
    }
    time_t getLastBorrowPubTime(const PublicationRank *publicationRank) const
    {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i)
        {
            if (borrowedbooks[i] == publicationRank)
            {
                return borrowedDates[i];
            }
        }
        return 0; 
    }
    void setLastBorrowPubTime(const PublicationRank *publicationRank, time_t borrowTime)
    {
        for (int i = 0; i < MAX_BORROWED_BOOKS; ++i)
        {
            if (borrowedbooks[i] == publicationRank)
            {
                borrowedDates[i] = borrowTime;
                return; 
            }
        }
    }
};

class Library
{
private:
    LibraryItem *libraryItems[MAX_ITEMS];
    int itemCount;
    int nextBookId;
    int totalCopies;

    User students[100]; 
    int studentCount = 0;

    User teachers[50]; 
    int teacherCount = 0;
    LibraryItem *library1[MAX_ITEMS];
    int itemCount1;
    LibraryItem *library2[MAX_ITEMS];
    int itemCount2;
    LibraryItem *library3[MAX_ITEMS];
    int itemCount3;

public:
    Library() : itemCount(0), studentCount(0), teacherCount(0)
    {
        nextBookId = 100;
        totalCopies = 1;
        itemCount1=0;
        itemCount2=0;
        itemCount3=0;
    }
    // Library() : libraryItems{}, itemCount(0), students{}, studentCount(0), teachers{}, teacherCount(0), nextBookId(100) {}

    int getStudentCount() const
    {
        return studentCount;
    }
    int getTeacherCount() const
    {
        return teacherCount;
    }
    int getTotalUsers() const
    {
        return studentCount + teacherCount;
    }

    int getTotalItems() const
    {
        return itemCount;
    }

    void addItem(LibraryItem *item)
    {
        if (itemCount < MAX_ITEMS)
        {
            libraryItems[itemCount] = item;
            itemCount++;
        }
        else
        {
            cout << "Library is full. Cannot add more items." << endl;
        }
    }
    void addItemToLibrary1(LibraryItem *item)
    {
        if (itemCount1 < MAX_ITEMS)
        {
            library1[itemCount1++] = item;
        }
    }

    // Add a LibraryItem to library2
    void addItemToLibrary2(LibraryItem *item)
    {
        if (itemCount2 < MAX_ITEMS)
        {
            library2[itemCount2++] = item;
        }
    }

    // Add a LibraryItem to library3
    void addItemToLibrary3(LibraryItem *item)
    {
        if (itemCount3 < MAX_ITEMS)
        {
            library3[itemCount3++] = item;
        }
    }

    void printAllItems() const
    {
        for (int i = 0; i < itemCount; ++i)
        {
            if (libraryItems[i])
            {
                libraryItems[i]->printDetails();
                cout << "------------------------\n";
            }
        }
    }
    
   void printBooksInRange(int startID, int endID) const
{
    for (int i = 0; i < itemCount; ++i)
    {
        Book *book = dynamic_cast<Book*>(libraryItems[i]);
        if (book && book->getID() >= startID && book->getID() <= endID)
        {
            book->printDetails();
            cout << "------------------------\n";
        }
    }
}

          
    void printJournalsInRange(int startID, int endID) const
{
    for (int i = 0; i < itemCount; ++i)
    {
        Journals *book = dynamic_cast<Journals*>(libraryItems[i]);
        if (book && book->getID() >= startID && book->getID() <= endID)
        {
            book->printDetails();
            cout << "------------------------\n";
        }
    }
}
void printPublicationsInRange(int startID, int endID) const
{
    for (int i = 0; i < itemCount; ++i)
    {
        PublicationRank *book = dynamic_cast<PublicationRank*>(libraryItems[i]);
        if (book && book->getID() >= startID && book->getID() <= endID)
        {
            book->printDetails();
            cout << "------------------------\n";
        }
    }
}

    Book *getBookByID(int bookID) const
    {
        for (int i = 0; i < itemCount; i++)
        {
            Book *book = dynamic_cast<Book *>(libraryItems[i]);
            if (book && book->getBookID() == bookID)
            {
                return book; 
            }
        }
        return nullptr; 
    }
    Book *getBookByIsbn(int bookIsbn) const
    {
        for (int i = 0; i < itemCount; i++)
        {
            Book *book = dynamic_cast<Book *>(libraryItems[i]);
            if (book && book->getISBN() == bookIsbn)
            {
                return book; 
            }
        }
        return nullptr; 
    }
    void searchBooksByAuthor(const string &bookAuthor, Book *matchingBooks[], int &matchingCount);
    void searchBooksByTitle(const string &bookAuthor, Book *matchingBooks[], int &matchingCount);
    void searchPublication(const string &bookAuthor, PublicationRank *matchingBooks[], int &matchingCount);
    void searchJournal(const string &bookAuthor, Journals *matchingBooks[], int &matchingCount);

    void registerUser(const string &name, bool isTeacher)
    {
        if (isTeacher)
        {
            teachers[teacherCount++] = User(name, true);
            cout << "Registered as a Teacher." << endl;
        }
        else
        {
            students[studentCount++] = User(name, false);
            cout << "Registered as a Student." << endl;
        }
        cout << "-------------------------" << endl;
    }

    void showAllRegisteredUsers()
    {
        cout << "Registered Students:" << endl;
        for (int i = 0; i < studentCount; ++i)
        {
            cout << students[i].getName() << endl;
        }

        cout << "Registered Teachers:" << endl;
        for (int i = 0; i < teacherCount; ++i)
        {
            cout << teachers[i].getName() << endl;
        }
        cout << "-------------------------" << endl;
    }

    bool isEqualIgnoreCase(const string &str1, const string &str2)
    {
        // Compare two strings case-insensitively
        if (str1.size() != str2.size())
        {
            return false;
        }

        for (size_t i = 0; i < str1.size(); ++i)
        {
            if (tolower(str1[i]) != tolower(str2[i]))
            {
                return false;
            }
        }

        return true;
    }

    // Function to add a new book to the library
    void addBook(int isbn, const string &author, const string &title, int originalPublicationYear)
    {
        if (itemCount >= MAX_ITEMS)
        {
            cout << "The library is full. Cannot add more books." << endl;
            return;
        }

        Book *newBook = new Book();
        newBook->setID(ID++);
        newBook->setBookID(nextBookId++);
        newBook->setISBN(isbn);
        newBook->setAuthors(author);
        newBook->setTitle(title);
        newBook->setPublicationYear(originalPublicationYear);

        // Add the new book to the library
        // libraryItems[itemCount++] = newBook;
        addItem(newBook);

        cout << "Added book with ID " << newBook->getBookID() << " to the library." << endl;
    }

    bool borrowBook(const string &userName, int bookIdToBorrow);
    bool returnBook(Book *book);
    bool borrowPublication(const string &userName, int publicationID);
    bool returnPub(PublicationRank *publicationRank);
    bool borrowJournal(const string &userName, int title);
    void displayBorrowed();
    void purchaseSubscriptions(double budget, int threshold);

    virtual ~Library() {} 
};

void Library ::searchBooksByAuthor(const string &bookAuthor, Book *matchingBooks[], int &matchingCount)
{
    matchingCount = 0;

    // Convert the search term to lowercase for case-insensitive matching
    string searchAuthorLower = bookAuthor;
    for (char &c : searchAuthorLower)
    {
        c = tolower(c);
    }

    for (int i = 0; i < itemCount; i++)
    {
        Book *book = dynamic_cast<Book *>(libraryItems[i]);
        if (book)
        {
            string bookAuthorLower = book->getAuthors();
            for (char &c : bookAuthorLower)
            {
                c = tolower(c);
            }
            if (bookAuthorLower.find(searchAuthorLower) != string::npos)
            {
                matchingBooks[matchingCount++] = book; // Found a book with a matching author name
            }
        }
    }
}

void Library ::searchBooksByTitle(const string &bookAuthor, Book *matchingBooks[], int &matchingCount)
{
    matchingCount = 0;
    string searchAuthorLower = bookAuthor;
    for (char &c : searchAuthorLower)
    {
        c = tolower(c);
    }

    for (int i = 0; i < itemCount; i++)
    {
        Book *book = dynamic_cast<Book *>(libraryItems[i]);
        if (book)
        {
            string bookAuthorLower = book->getTitle();
            for (char &c : bookAuthorLower)
            {
                c = tolower(c);
            }
            if (bookAuthorLower.find(searchAuthorLower) != string::npos)
            {
                matchingBooks[matchingCount++] = book; 
            }
        }
    }
}
void Library ::searchPublication(const string &bookAuthor, PublicationRank *matchingBooks[], int &matchingCount)
{
    matchingCount = 0;
    string searchAuthorLower = bookAuthor;
    for (char &c : searchAuthorLower)
    {
        c = tolower(c);
    }

    for (int i = 0; i < itemCount; i++)
    {
        PublicationRank *publicationRank = dynamic_cast<PublicationRank *>(libraryItems[i]);
        if (publicationRank)
        {
            string bookAuthorLower = publicationRank->getPublication();
            for (char &c : bookAuthorLower)
            {
                c = tolower(c);
            }
            if (bookAuthorLower.find(searchAuthorLower) != string::npos)
            {
                matchingBooks[matchingCount++] = publicationRank; 
            }
        }
    }
}
void Library ::searchJournal(const string &bookAuthor, Journals *matchingBooks[], int &matchingCount)
{
    matchingCount = 0;
    string searchAuthorLower = bookAuthor;
    for (char &c : searchAuthorLower)
    {
        c = tolower(c);
    }

    for (int i = 0; i < itemCount; i++)
    {
        Journals *journal = dynamic_cast<Journals *>(libraryItems[i]);
        if (journal)
        {
            string bookAuthorLower = journal->getTitle();
            for (char &c : bookAuthorLower)
            {
                c = tolower(c);
            }
            if (bookAuthorLower.find(searchAuthorLower) != string::npos)
            {
                matchingBooks[matchingCount++] = journal; 
            }
        }
    }
}

bool Library::borrowBook(const string &userName, int bookIdToBorrow)
{
    User *user = nullptr;
    for (int i = 0; i < studentCount; ++i)
    {
        if (isEqualIgnoreCase(students[i].getName(), userName))
        {
            user = &students[i];
            cout << "Registered as a Student." << endl;
            cout << "-----------------------------" << endl;
            break;
        }
    }

    if (!user)
    {
        for (int i = 0; i < teacherCount; ++i)
        {
            if (isEqualIgnoreCase(teachers[i].getName(), userName))
            {
                user = &teachers[i];
                cout << "Registered as a Teacher." << endl;
                cout << "-----------------------------" << endl;
                break;
            }
        }
    }

    if (!user)
    {
        cout << "User not found." << endl;
        return false;
    }

    Book *bookToBorrow = nullptr;
    cout<<"Book not found in library, request has been sent to nearby library and delivered to you in 7 days"<<endl<<"-------------------------------" << endl;
    std:: this_thread::sleep_for(chrono::seconds(7));
    // Find the book by book ID
    for (int i = 0; i < itemCount; ++i)
    {
        Book *book = dynamic_cast<Book *>(libraryItems[i]);
        if (book && book->getBookID() == bookIdToBorrow)
        {
            bookToBorrow = book;
            int id= book->getID();
            if (id>=100 && id <=132)
            cout<<"Book borrowed Libraray 1 "<<endl<<"-------------------------------" << endl; 
            else if (id>=133 && id<=166)
            cout<<"Book borrowed Libraray 2 "<<endl<<"-------------------------------" << endl;
            else
            cout<<"Book borrowed Libraray 3 "<<endl<<"-------------------------------" << endl;
            break;
        }
    }

    if (!bookToBorrow)
    {
        cout << "Book not found." << endl;
        return false;
    }

    if (user->getBorrowedCount() >= user->getMaxBorrowedBooks())
    {
        cout << userName << " has reached the maximum number of borrowed books." << endl;
        return false;
    }

    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    cout << "Current local time: " << buffer << endl;

    int returnPeriod = (user->isTeacherUser()) ? 180 : 30; //(assume 1 day=1 sec)

    // Check if the book is available for borrowing (not borrowed within the return period)
    if (now - user->getLastBorrowTime(bookToBorrow) >= returnPeriod || !bookToBorrow->isBorrowed())
    {
        // Check if there are available copies of the book to borrow
        if (totalCopies > 0)
        {
            user->borrowedBooks[user->getBorrowedCount()] = bookToBorrow;
            user->borrowedDates[user->getBorrowedCount()] = now;
            user->setLastBorrowTime(bookToBorrow, now);
            user->incrementBorrowedCount();

            bookToBorrow->setBorrowed(true);

            totalCopies--;

            cout << userName << " has borrowed the book: " << bookToBorrow->getTitle() << endl;
            // Schedule the book to be returned after the return period
            thread returnThread([this, bookToBorrow, returnPeriod]()
                                {
                                    this_thread::sleep_for(chrono::seconds(returnPeriod));
                                    returnBook(bookToBorrow); // Call the returnBook function after the return period
                                });
            returnThread.detach(); // Detach the thread to run in the background
            return true;
        }
        else
        {
            cout << "No available copies of the book." << endl;
            return false;
        }
    }
    else
    {
        cout << "The book is not available for borrowing yet." << endl;
        return false;
    }
}
bool Library::returnBook(Book *book)
{
    if (book->isBorrowed())
    {
        book->setBorrowed(false);
        totalCopies++;
        cout << "\nBook returned: " << book->getTitle() << endl;
         time_t now = time(nullptr);
        struct tm *timeinfo = localtime(&now);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
         cout << "Current local time: " << buffer << endl;
        return true;
    }
    else
    {
        cout << "\nBook not borrowed or not found." << endl;
        return false;
    }
}

bool Library::borrowPublication(const string &userName, int publication)
{
    User *user = nullptr;
    for (int i = 0; i < studentCount; ++i)
    {
        if (isEqualIgnoreCase(students[i].getName(), userName))
        {
            user = &students[i];
            cout << "Registered as a Student." << endl;
            cout << "-----------------------------" << endl;
            break;
        }
    }

    if (!user)
    {
        for (int i = 0; i < teacherCount; ++i)
        {
            if (isEqualIgnoreCase(teachers[i].getName(), userName))
            {
                user = &teachers[i];
                cout << "Registered as a Teacher." << endl;
                cout << "-----------------------------" << endl;
                break;
            }
        }
    }

    if (!user)
    {
        cout << "User not found." << endl;
        return false;
    }

    PublicationRank *pubToBorrow = nullptr;
    cout<<"Book not found in library, request has been sent to nearby library and delivered to you in 7 days"<<endl<<"-------------------------------" << endl;
     std:: this_thread::sleep_for(chrono::seconds(7));
    for (int i = 0; i < itemCount; ++i)
    {
        PublicationRank *publicationRank = dynamic_cast<PublicationRank *>(libraryItems[i]);
        if (publicationRank && publicationRank->getID()==publication)
        {
            pubToBorrow = publicationRank;
            int id=publicationRank->getID();
            if (id>=198 && id<=223)
            cout<<" Book borrowed Library 1 "<<endl<<"-------------------------------" << endl;
            else if (id>=224 && id<=250)
            cout<<" Book borrowed Library 2 "<<endl<<"-------------------------------" << endl;
            else
            cout<<" Book borrowed Library 3 "<<endl<<"-------------------------------" << endl;
            break;
        }
    }

    if (!pubToBorrow)
    {
        cout << "Publication not found." << endl;
        return false;
    }

    if (user->getBorrowedCount() >= user->getMaxBorrowedBooks())
    {
        cout << userName << " has reached the maximum number of borrowed books." << endl;
        return false;
    }
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    cout << "Current local time: " << buffer << endl;

    int returnPeriod = (user->isTeacherUser()) ? 180: 30;

    if (now - user->getLastBorrowPubTime(pubToBorrow) >= returnPeriod || !pubToBorrow->isBorrowed())
    {
        if (totalCopies > 0)
        {
            user->borrowedbooks[user->getBorrowedCount()] = pubToBorrow;
            user->borrowedDates[user->getBorrowedCount()] = now;
            user->setLastBorrowPubTime(pubToBorrow, now);
            user->incrementBorrowedCount();

            pubToBorrow->setBorrowed(true);

            totalCopies--;

            cout << userName << " has borrowed the magazine: " << pubToBorrow->getPublication() << endl;
            thread returnThread([this, pubToBorrow, returnPeriod]()
                                {
                                    this_thread::sleep_for(chrono::seconds(returnPeriod));
                                    returnPub(pubToBorrow); 
                                });
            returnThread.detach();
            return true;
        }
        else
        {
            cout << "No available copies of the book." << endl;
            return false;
        }
    }
    else
    {
        cout << "The magazine is not available for borrowing yet." << endl;
        return false;
    }
}
bool Library::returnPub(PublicationRank *publicationRank)
{
    if (publicationRank->isBorrowed())
    {
        publicationRank->setBorrowed(false);
        totalCopies++;
        cout << "\nBook returned: " << publicationRank->getPublication() << endl;
         time_t now = time(nullptr);
        struct tm *timeinfo = localtime(&now);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
       cout << "Current local time: " << buffer << endl;
        return true;
    }
    else
    {
        cout << "\nBook not borrowed or not found." << endl;
        return false;
    }
}

bool Library::borrowJournal(const string &userName, int title)
{
    User *user = nullptr;
    for (int i = 0; i < studentCount; ++i)
    {
        if (isEqualIgnoreCase(students[i].getName(), userName))
        {
            user = &students[i];
            cout << "Registered as a Student." << endl;
            cout << "-----------------------------" << endl;
            break;
        }
    }

    if (!user)
    {
        for (int i = 0; i < teacherCount; ++i)
        {
            if (isEqualIgnoreCase(teachers[i].getName(), userName))
            {
                user = &teachers[i];
                cout << "Registered as a Teacher." << endl;
                cout << "-----------------------------" << endl;
                break;
            }
        }
    }

    if (!user)
    {
        cout << "User not found." << endl;
        return false;
    }

    Journals *journalToBorrow = nullptr;
    for (int i = 0; i < itemCount; ++i)
    {
        Journals *journals = dynamic_cast<Journals *>(libraryItems[i]);
        if (journals && journals->getID()== title)
        {
            journalToBorrow = journals;
            int id =journals->getID();
            if (id>=1 && id <=33)
            cout<<"Borrowed Library 1 "<<endl<<"-------------------------------" << endl;
            else if (id>=34 && id <=66)
            cout<<"Borrowed Library 2  "<<endl<<"-------------------------------" << endl;
            else
            cout<<"Borrowed Library 3  "<<endl<<"-------------------------------" << endl;
            break;
        }
    }

    if (!journalToBorrow)
    {
        cout << "Journals not found." << endl;
        return false;
    }


    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    cout << "Current local time: " << buffer << endl;


        // user->borrowedJournals[user->getBorrowedCount()] = journalToBorrow;
        // user->borrowedDates[user->getBorrowedCount()] = time(nullptr);
        // //user->incrementBorrowedCount();
        // cout << userName << " has borrowed the book: " << journalToBorrow->getTitle() << endl;
        // return true;
        user->borrowJournal(journalToBorrow, now);

        cout << userName << " wants to borrow the journal: " << journalToBorrow->getTitle() << endl;
        return true;
    
}

void Library ::displayBorrowed()
{
    int journalCounts[100] = {0}; // maximum of 100 different journal IDs

    for (int i = 0; i < studentCount; ++i)
    {
        for (int j = 0; j < students[i].getBorrowedCount(); ++j)
        {
            int journalID = students[i].borrowedJournals[j]->getID();
            journalCounts[journalID]++;
        }
    }

    for (int i = 0; i < teacherCount; ++i)
    {
        for (int j = 0; j < teachers[i].getBorrowedCount(); ++j)
        {
            int journalID = teachers[i].borrowedJournals[j]->getID();
            journalCounts[journalID]++;
        }
    }

    // Display the borrowed journals with counts
    for (int i = 0; i < 100; ++i)
    {
        if (journalCounts[i] > 0)
        {
            cout << "Journal ID " << i << ": Count " << journalCounts[i] << endl;
        }
    }
}
void Library:: purchaseSubscriptions(double budget, int threshold) {
        int journalCounts[100] = {0}; // Assuming a maximum of 100 different journal IDs

        // Calculate the counts of borrowed journals
        for (int i = 0; i < studentCount; ++i) {
            for (int j = 0; j < students[i].getBorrowedCount(); ++j) {
                int journalID = students[i].borrowedJournals[j]->getID();
                journalCounts[journalID]++;
            }
        }

        for (int i = 0; i < teacherCount; ++i) {
            for (int j = 0; j < teachers[i].getBorrowedCount(); ++j) {
                int journalID = teachers[i].borrowedJournals[j]->getID();
                journalCounts[journalID]++;
            }
        }

        // Subscribe to journals whose count exceeds the threshold and fits within the budget
        double subscriptionCost = 1000.0; 
        for (int i = 0; i < 100; ++i) {
            if (journalCounts[i] > threshold) {
                int subscriptionsToPurchase = journalCounts[i] - threshold;
                double cost = subscriptionsToPurchase * subscriptionCost;

                if (cost <= budget) {
                    // Purchase the subscriptions
                    cout << "Purchased " << subscriptionsToPurchase << " subscriptions for Journal ID " << i << " for $" << cost << endl;
                    budget -= cost;
                } else {
                    cout << "Insufficient budget to purchase subscriptions for Journal ID " << i << endl;
                }
            }
        }
    }
bool isNumeric(const string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// Function to split a CSV line into fields based on commas
void splitCSVLine(const string &line, string fields[], int fieldCount)
{
    stringstream ss(line);
    for (int i = 0; i < fieldCount; i++)
    {
        getline(ss, fields[i], ',');
    }
}
void splitLine(const string &line, string fields[], int fieldCount)
{
    stringstream ss(line);
    for (int i = 0; i < fieldCount; i++)
    {
        getline(ss, fields[i]);
    }
}

void splitString(const string &input, string fields[], int fieldCount)
{
    istringstream ss(input);
    string field;
    int index = 0;

    while (index < fieldCount && getline(ss, field, ','))
    {
        fields[index++] = field;
    }

    while (index < fieldCount)
    {
        fields[index++] = ""; 
    }
}

bool isValidUserName(const string &userName)
{
    if (userName.empty())
    {
        return false;
    }

    for (char ch : userName)
    {
        if (!isalpha(ch) && !isspace(ch))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    Library library;
    // int ID = 1;

      // Opening journal.csv
    ifstream journalFile("journals.csv");
    if (journalFile.is_open())
    {
        string line;
        // Read and discard the header line
       // getline(journalFile, line);

        while (getline(journalFile, line))
        {
            // Define an array to store fields

            const int fieldCount = 2;
            string fields[fieldCount];

            // Parse CSV line into fields
            splitLine(line, fields, fieldCount);

            if (fieldCount >= 2)
            {
                string title = fields[0];

                Journals *journal = new Journals(ID, title);
                // journal-> printDetails();
                // cout << "------------------------\n";
                library.addItem(journal);
                ID++;
                //library.addItemToLibrary1(journal);  
            }
        }

        journalFile.close();
    }
    else
    {
        cerr << "Failed to open journals.csv\n";
    }
    //  Opening book.csv
    ifstream bookFile("books.csv");
    if (bookFile.is_open())
    {
        string line;
        // Read and discard the header line
        getline(bookFile, line);
        while (getline(bookFile, line))
        {
            const int fieldCount = 24;
            string fields[fieldCount];
            if (fieldCount >= 24) {
            int book_id, isbn;
            string title, authors;
            double original_publication_year;

            istringstream ss(line);
            ss >> book_id; 
            for (int i = 0; i < 5; ++i)
            {
                ss.ignore(256, ','); // Ignore fields until the next comma
            }
            ss >> isbn; // Read isbn until the next comma
            ss.ignore(256, ',');
            ss.ignore(256, ',');
            if (line.find("\"") != string::npos)
            {
                ss >> quoted(authors);
            }
            else
            {

                getline(ss, authors, ',');
            }
            ss.ignore(256, ',');
            ss >> original_publication_year;
            ss.ignore(256, ',');
            ss.ignore(256, ',');
            //getline(ss, title, ',');
            if (fields[9].find("\"") != string::npos)
            {
                ss >> quoted(title);
            }
            else
            {

                getline(ss, title, ',');
                ss.ignore(256, ',');
            }

            Book *book = new Book(ID, book_id, isbn, title, authors, original_publication_year);
            // book->printDetails();
            // cout << "------------------------\n";
            library.addItem(book);
            ID++;
            //library.addItemToLibrary2(book);  
         }

        }
        bookFile.close();
    }
    else
    {
        cerr << "Failed to open books.csv\n";
    }

    // opening publicatin_rank.csv

    ifstream publicationFile("publications_rank.csv");
    if (publicationFile.is_open())
    {
        string line;
        // Read and discard the header line
        getline(publicationFile, line);

        while (getline(publicationFile, line))
        {
            // Define an array to store fields
            const int fieldCount = 11;
            string fields[fieldCount];

            // Parse CSV line into fields
            splitCSVLine(line, fields, fieldCount);

            if (fieldCount >= 11)
            {
                string publication = fields[0];
                int rank = stoi(fields[1]);
                double totalPaid = stod(fields[2]);

                PublicationRank *publicationRank = new PublicationRank(ID, publication, rank, totalPaid);

                // publicationRank-> printDetails();
                // cout << "------------------------\n";
                library.addItem(publicationRank);
                ID++;
                //library.addItemToLibrary3(publicationRank);  
            }
        }
        publicationFile.close();
    }
    else
    {
        cerr << "Failed to open publications_rank.csv\n";
    }
  
    // library.printAllItems();

    int choice;
    do
    {
        cout << "Menu:" << endl;
        cout << "1. Register as a Student" << endl;
        cout << "2. Register as a Teacher" << endl;
        cout << "3. Search any item" << endl;
        cout << "4. Borrow any item" << endl;
        cout << "5. Purchase a book" <<endl;
        cout << "6. Show all item lists" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Register as a Student
            string userName;
            do
            {
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, userName);

                if (!isValidUserName(userName))
                {
                    cout << "Invalid input. Please enter a valid name." << endl;
                }
            } while (!isValidUserName(userName));

            library.registerUser(userName, false); // Register as a student
            library.showAllRegisteredUsers();
            break;
        }
        case 2:
        {
            // Register as a Teacher
            string userName;
            do
            {
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, userName);

                if (!isValidUserName(userName))
                {
                    cout << "Invalid input. Please enter a valid name." << endl;
                }
            } while (!isValidUserName(userName));

            library.registerUser(userName, true); // Register as a teacher
            library.showAllRegisteredUsers();
            break;
        }
        case 3:
        {
            int choice;
            char phy, book;
            cout << "For physical items, press 'Y' or 'y' otherwise for electronic items:" << endl;
            cin >> phy;
            if (phy == 'Y' || phy == 'y')
            {
                cout << "For book, type 'Y' or 'y', otherwise for magazines :" << endl;
                cin >> book;
                if (book == 'Y' || book == 'y')
                {
                    cout << "Book can be search by:  \n1. Book ID \n2. ISBN \n3. Author's Name \n4. Title \nEnter your choice:";
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                    {
                        // Search for a Book by book_id
                        int bookIdToSearch;
                        bool validInput = false;
                        do
                        {
                            cout << "Enter the book_id to search: ";

                            // Try to read the input as an integer
                            if (cin >> bookIdToSearch)
                            {
                                validInput = true;
                            }
                            else
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                // Clear the input buffer to handle invalid input
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (!validInput);

                        Book *foundBook = library.getBookByID(bookIdToSearch);
                        if (foundBook != nullptr)
                        {   
                            
                            cout << "Book Found!!!!!!!!!!!!:\nID: "<<foundBook->getID()<<"\nTitle: " << foundBook->getTitle() << "\nISBN: " << foundBook->getISBN() << "\nAuthours: "
                                 << foundBook->getAuthors() << "\nPublication Year: " << foundBook->getPublicationYear() << endl;
                            cout << "-----------------------\n";
                            
                                /*int id= foundBook->getID();
                                if (id>=100 && id <=132)
                                cout<<"Book found Library 1  "<<endl;
                                else if (id>=133 && id<=166)
                                cout<<"Book found Library 2  "<<endl;   
                                else
                                cout<<"Book found Library 3   "<<endl; 
                              cout << "\nID: "<<foundBook->getID(); 
                            cout << "\nTitle: " << foundBook->getTitle() << "\nISBN: " << foundBook->getISBN() << "\nAuthours: "
                                 << foundBook->getAuthors() << "\nPublication Year: " << foundBook->getPublicationYear() << endl;
                            cout << "-----------------------\n";*/
                        }
                        else
                        {
                            cout << "Book not found." << endl;
                        }
                        break;
                    }
                    case 2:
                    {
                        // Search for a Book by ISBN
                        int ISBNToSearch;
                        bool validInput = false;
                        do
                        {
                            cout << "Enter the ISBN to search: ";

                            // Try to read the input as an integer
                            if (cin >> ISBNToSearch)
                            {
                                validInput = true;
                            }
                            else
                            {
                                cout << "Invalid input. Please enter a valid integer." << endl;
                                // Clear the input buffer to handle invalid input
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (!validInput);

                        Book *foundBook = library.getBookByIsbn(ISBNToSearch);
                        if (foundBook != nullptr)
                        {   
                            cout << "Book Found!!!!!!!!!!!!:\nID: "<<foundBook->getID()<<"\nTitle: " << foundBook->getTitle() << "\nISBN: " << foundBook->getISBN() << "\nAuthours: "
                                 << foundBook->getAuthors() << "\nPublication Year: " << foundBook->getPublicationYear() << endl;
                            cout << "-----------------------\n";
                            
                            /*int id= foundBook->getID();
                                if (id>=100 && id <=132)
                                cout<<"Book found Library 1  "<<endl;
                                else if (id>=133 && id<=166)
                                cout<<"Book found Library 2  "<<endl;   
                                else
                                cout<<"Book found Library 3  "<<endl; 
                                cout << "\nID: "<<foundBook->getID();
                            cout << "\nTitle: " << foundBook->getTitle() << "\nISBN: " << foundBook->getISBN() << "\nAuthours: "
                                 << foundBook->getAuthors() << "\nPublication Year: " << foundBook->getPublicationYear() << endl;
                            cout << "-----------------------\n";*/
                        }
                        else
                        {
                            cout << "Book not found." << endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        // Search for a Book by Author's Name
                        string authorNameToSearch;
                        do
                        {
                            cout << "Enter the author name to search: ";
                            cin.ignore();
                            getline(cin, authorNameToSearch);

                            if (!isValidUserName(authorNameToSearch))
                            {
                                cout << "Invalid input. Please enter a valid name." << endl;
                            }
                        } while (!isValidUserName(authorNameToSearch));

                        const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                        Book *matchingBooks[maxMatchingBooks];
                        int matchingCount = 0;

                        library.searchBooksByAuthor(authorNameToSearch, matchingBooks, matchingCount);

                        if (matchingCount > 0)
                        {
                            cout << "Books by " << authorNameToSearch << ":" << endl;
                            cout << "--------------------------------\n";
                            for (int i = 0; i < matchingCount; i++)
                            {   cout << "ID: "<<matchingBooks[i]->getID();
                                cout << "\nBookID: " << matchingBooks[i]->getBookID() << "\nTitle: " << matchingBooks[i]->getTitle() << "\nISBN: " << matchingBooks[i]->getISBN() << endl;
                                cout << "Author Name: " << matchingBooks[i]->getAuthors() << endl;
                                cout << "--------------------------------\n";
                            }
                        }
                        else
                        {
                            cout << "No books by " << authorNameToSearch << " found." << endl;
                        }
                        break;
                    }
                    case 4:
                    {
                        // Search for a Book by its Title
                        string Title;
                        do
                        {
                            cout << "Enter the Title to search: ";
                            cin.ignore();
                            getline(cin, Title);

                            if (!isValidUserName(Title))
                            {
                                cout << "Invalid input. Please enter a valid name." << endl;
                            }
                        } while (!isValidUserName(Title));

                        const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                        Book *matchingBooks[maxMatchingBooks];
                        int matchingCount = 0;

                        library.searchBooksByTitle(Title, matchingBooks, matchingCount);

                        if (matchingCount > 0)
                        {
                            cout << "Books by " << Title << ":" << endl;
                            cout << "--------------------------------\n";
                            for (int i = 0; i < matchingCount; i++)
                            {   cout << "ID: "<<matchingBooks[i]->getID();
                                cout << "\nBookID: " << matchingBooks[i]->getBookID() << "\nTitle: " << matchingBooks[i]->getTitle() << "\nISBN: " << matchingBooks[i]->getISBN() << endl;
                                cout << "Author Name: " << matchingBooks[i]->getAuthors() << endl;
                                cout << "--------------------------------\n";
                            }
                        }
                        else
                        {
                            cout << "No books by " << Title << " found." << endl;
                        }
                        break;
                    }
                    }
                }
                else
                {
                    string magazine;
                    do
                    {
                        cout << "Enter the name of magzine you want to search:";
                        cin.ignore();
                        getline(cin, magazine);

                        if (!isValidUserName(magazine))
                        {
                            cout << "Invalid input. Please enter a valid name." << endl;
                        }
                    } while (!isValidUserName(magazine));

                    const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                    PublicationRank *matchingBooks[maxMatchingBooks];
                    int matchingCount = 0;

                    library.searchPublication(magazine, matchingBooks, matchingCount);

                    if (matchingCount > 0)
                    {
                        cout << "Magazine by " << magazine << ":" << endl;
                        cout << "--------------------------------\n";
                        for (int i = 0; i < matchingCount; i++)
                        {   cout <<"Id: "<<matchingBooks[i]->getID() <<endl;
                            cout << "Publication: " << matchingBooks[i]->getPublication() << "\nRank: " << matchingBooks[i]->getrank() << "\nTotal Paid: " << matchingBooks[i]->gettotalPaid() << endl;
                            cout << "--------------------------------\n";
                        }
                    }
                    else
                    {
                        cout << "No Publication by " << magazine << " found." << endl;
                    }
                    break;
                }
            } // to check physical item
            else
            {
                cout << "Electronic items" << endl;
                string magazine;
                do
                {
                    cout << "Enter the name of journal you want to search: ";
                    cin.ignore();
                    getline(cin, magazine);

                    if (!isValidUserName(magazine))
                    {
                        cout << "Invalid input. Please enter a valid name." << endl;
                    }
                } while (!isValidUserName(magazine));

                const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                Journals *matchingBooks[maxMatchingBooks];
                int matchingCount = 0;

                library.searchJournal(magazine, matchingBooks, matchingCount);

                if (matchingCount > 0)
                {
                    cout << "Journal by " << magazine << ":" << endl;
                    cout << "--------------------------------\n";
                    for (int i = 0; i < matchingCount; i++)
                    {
                        cout << "ID: " << matchingBooks[i]->getID() << "\nTitle: " << matchingBooks[i]->getTitle() << endl;
                        cout << "--------------------------------\n";
                    }
                }
                else
                {
                    cout << "No Journal by " << magazine << " found." << endl;
                }
                break;
            }
            break;
        } // case 3 to search items
        case 4:
        {
            char phy, book;
            cout << "For physical items, press 'Y' or 'y' otherwise for electronic items:" << endl;
            cin >> phy;
            if (phy == 'Y' || phy == 'y')
            {
                cout << "For book, type 'Y' or 'y', otherwise for magazines :" << endl;
                cin >> book;
                if (book == 'Y' || book == 'y')
                {

                    string userNameToBorrow;
                    int bookIdToBorrow;
                    do
                    {
                        cout << "Enter your name: ";
                        cin.ignore();
                        getline(cin, userNameToBorrow);

                        if (!isValidUserName(userNameToBorrow))
                        {
                            cout << "Invalid input. Please enter a valid name." << endl;
                        }
                    } while (!isValidUserName(userNameToBorrow));

                    bool validInput = false;
                    do
                    {
                        cout << "Enter the book_id to borrow: ";

                        // Try to read the input as an integer
                        if (cin >> bookIdToBorrow)
                        {
                            validInput = true;
                        }
                        else
                        {
                            cout << "Invalid input. Please enter a valid integer." << endl;
                            // Clear the input buffer to handle invalid input
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    } while (!validInput);

                    if (library.borrowBook(userNameToBorrow, bookIdToBorrow))
                    {     
                        // Book successfully borrowed
                    }
                    else
                    {
                        // Error message already printed in the borrowBook function
                    }
                    break;
                }

                else
                {

                    string userNameToBorrow;
                    int publicationID;
                    do
                    {
                        cout << "Enter your name: ";
                        cin.ignore();
                        getline(cin, userNameToBorrow);

                        if (!isValidUserName(userNameToBorrow))
                        {
                            cout << "Invalid input. Please enter a valid name." << endl;
                        }
                    } while (!isValidUserName(userNameToBorrow));

                    bool validInput = false;
                    do
                    {
                        cout << "Enter the id to borrow Magazine: ";

                        // Try to read the input as an integer
                        if (cin >> publicationID)
                        {
                            validInput = true;
                        }
                        else
                        {
                            cout << "Invalid input. Please enter a valid integer." << endl;
                            // Clear the input buffer to handle invalid input
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    } while (!validInput);

                    if (library.borrowPublication(userNameToBorrow, publicationID))
                    {
                        // Book successfully borrowed
                    }
                    else
                    {
                        // Error message already printed in the borrowBook function
                    }
                    break;
                }
            }
            else
            {
                string userNameToBorrow;
                int titleID;
                do
                {
                    cout << "Enter your name: ";
                    cin.ignore();
                    getline(cin, userNameToBorrow);

                    if (!isValidUserName(userNameToBorrow))
                    {
                        cout << "Invalid input. Please enter a valid name." << endl;
                    }
                } while (!isValidUserName(userNameToBorrow));

                bool validInput = false;
                    do
                    {
                        cout << "Enter the id to borrow Journals: ";
                        if (cin >> titleID)
                        {
                            validInput = true;
                        }
                        else
                        {
                            cout << "Invalid input. Please enter a valid integer." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    } while (!validInput);

                if (library.borrowJournal(userNameToBorrow, titleID))
                {
                    // Book successfully borrowed
                }
                else
                {
                    // Error message already printed in the borrowBook function
                }
                
                library.displayBorrowed();
                double budget=1500;
                int threshold = 2;
                library.purchaseSubscriptions(budget, threshold);
                break;
            }
            break;
        } // case 4 ends
        case 5:
        {

            string author, title;
            int originalPublicationYear;

            int isbn;
            bool validInput = false;
            do
            {
                cout << "Enter the ISBN : ";

                // Try to read the input as an integer
                if (cin >> isbn)
                {
                    validInput = true;
                }
                else
                {
                    cout << "Invalid input. Please enter a valid integer." << endl;
                    // Clear the input buffer to handle invalid input
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!validInput);

            do
            {
                cout << "Enter the author name : ";
                cin.ignore();
                getline(cin, author);

                if (!isValidUserName(author))
                {
                    cout << "Invalid input. Please enter a valid name." << endl;
                }
            } while (!isValidUserName(author));

            do
            {
                cout << "Enter the title of book: ";
                cin.ignore();
                getline(cin, title);

                if (!isValidUserName(title))
                {
                    cout << "Invalid input. Please enter a valid name." << endl;
                }
            } while (!isValidUserName(title));

            while (true)
            {
                cout << "Enter the year of publication: ";
                if (cin >> originalPublicationYear && originalPublicationYear >= 1900 && originalPublicationYear <= 2023)
                {
                    if (cin.peek() == '\n')
                    {
                        // Valid input
                        break;
                    }
                }
                cout << "Invalid input. Please enter an integer originalPublicationYear between 1990 to 2023." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            library.addBook(isbn, author, title, originalPublicationYear);
            break;
        }
        case 6:
            //library.printAllItems();
            //Journals *journal = new Journals(ID, title);
            //journal->printDetails();

            cout<<"!!!!!!!!! Library 1 !!!!!!!!!!"<<endl;
            cout<<"------------------------------"<<endl;
            library.printJournalsInRange(1, 33);
            library.printBooksInRange(100, 132);
            library.printPublicationsInRange(198, 223);
            cout<<"------------------------------"<<endl;
            cout<<"!!!!!!!!! Library 2 !!!!!!!!!!"<<endl;
            cout<<"------------------------------"<<endl;
            library.printJournalsInRange(34, 66);
            library.printBooksInRange(133, 166);
            library.printPublicationsInRange(224, 250);
            cout<<"!!!!!!!!! Library 3 !!!!!!!!!!"<<endl;
            cout<<"------------------------------"<<endl;
            library.printJournalsInRange(67, 99);
            library.printBooksInRange(167, 200);
            library.printPublicationsInRange(251, 280);
            break;
        case 7:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);
    return 0;
}
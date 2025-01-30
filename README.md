# Library-Management
This Library Management System is a C++ console application that allows users to manage books efficiently. The project focuses on adding, displaying, searching, borrowing, and returning books while ensuring data persistence using file handling.

Key Features & Functionality

Adding Books:

Users can add books with unique IDs, titles, authors, and quantities.
If a book with the same ID exists, the user can increase its quantity instead of re-entering all details.

Displaying Books:

The system displays books in a well-structured tabular format using setw for proper alignment.

Searching for a Book:

Users can search for a book by its ID to retrieve its details.

Borrowing & Returning Books:

Borrowing a book decreases its quantity.
Returning a book increases its quantity.

File Handling for Persistent Storage:

Books are stored in a books.txt file.

The system loads books on startup and saves changes on exit, ensuring data is not lost between sessions.


Project Flow:

On launch, the system loads books from the file.
The user selects an option (add, display, search, borrow, return, or exit).
Any modifications (adding/borrowing/returning) are saved automatically.
On exiting, the system writes the updated book list to books.txt.

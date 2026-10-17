import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        ArrayList<Book> books = new ArrayList<>();

        // Sample books
        books.add(new Book("Harry Potter", 1, "Fantasy", false));
        books.add(new Book("Monster", 2, "Thriller", false));
        books.add(new Book("That time I reincarnated as a Slime", 3, "Fantasy", false));
        books.add(new Book("Konosuba", 4, "Fantasy", false));
        books.add(new Book("Linear Algebra", 5, "Non-Fiction", false));

        Member[] members = new Member[100];

        int memberCount = 0;

        Member currentMember = null;

        boolean programRunning = true;

        while (programRunning) {

            currentMember = null;

            System.out.println("\n==============================");
            System.out.println("       LIBRARY SYSTEM");
            System.out.println("==============================");
            System.out.println("[1] Log in");
            System.out.println("[2] Register");
            System.out.println("[3] Exit");
            System.out.print("Choose an option: ");

            int loginChoice;

            try {
                loginChoice = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid input.");
                continue;
            }

            if (loginChoice == 1) {

                System.out.println("\n===== LOG IN =====");

                System.out.print("Input first name: ");
                String fName = scanner.nextLine();

                System.out.print("Input last name: ");
                String lName = scanner.nextLine();

                Member foundMember = null;
                for (int i = 0; i < memberCount; i++) {

                    if (members[i].fName.equalsIgnoreCase(fName)
                            && members[i].lName.equalsIgnoreCase(lName)) {

                        foundMember = members[i];
                        break;
                    }
                }
                if (foundMember == null) {

                    System.out.println(
                            "\nMember not found. Please register first."
                    );

                    continue;
                }

                currentMember = foundMember;

                System.out.println(
                        "\nWelcome back, "
                        + currentMember.fName + " "
                        + currentMember.lName + "!"
                );
            }
            else if (loginChoice == 2) {

                System.out.println("\nREGISTER");

                if (memberCount >= members.length) {

                    System.out.println(
                            "Member database is full."
                    );

                    continue;
                }

                System.out.print("Input first name: ");
                String fName = scanner.nextLine();

                System.out.print("Input last name: ");
                String lName = scanner.nextLine();
                boolean alreadyRegistered = false;

                for (int i = 0; i < memberCount; i++) {

                    if (members[i].fName.equalsIgnoreCase(fName)
                            && members[i].lName.equalsIgnoreCase(lName)) {

                        alreadyRegistered = true;
                        break;
                    }
                }

                if (alreadyRegistered) {

                    System.out.println(
                            "\nMember already exists. Please log in."
                    );

                    continue;
                }

                System.out.print("Input email: ");
                String email = scanner.nextLine();

                int memberId = memberCount + 1;

                Member newMember =
                        new Member(fName, lName, email, memberId);

                members[memberCount] = newMember;

                memberCount++;

                currentMember = newMember;

                System.out.println(
                        "\nRegistration successful!"
                );

                System.out.println(
                        "Your Member ID is: "
                        + currentMember.id
                );

                System.out.println(
                        "Welcome, "
                        + currentMember.fName + " "
                        + currentMember.lName + "!"
                );
            }
            else if (loginChoice == 3) {

                System.out.println(
                        "\nThank you for using the Library System!"
                );

                programRunning = false;
                break;
            }
            else {

                System.out.println(
                        "Invalid choice. Please choose 1-3."
                );

                continue;
            }

            boolean loggedIn = true;

            while (loggedIn && programRunning) {

                System.out.println("\n==============================");
                System.out.println("         MAIN MENU");
                System.out.println("==============================");

                System.out.println(
                        "Logged in as: "
                        + currentMember.fName + " "
                        + currentMember.lName
                );

                System.out.println();

                System.out.println("[1] Display all books");
                System.out.println("[2] Search book");
                System.out.println("[3] Borrow book");
                System.out.println("[4] Return a book");
                System.out.println("[5] Add a book");
                System.out.println("[6] Display borrowed books");
                System.out.println("[7] Log out");
                System.out.println("[8] Exit");

                System.out.print("Choose an option: ");

                int choice;

                try {
                    choice = Integer.parseInt(scanner.nextLine());
                } catch (NumberFormatException e) {

                    System.out.println(
                            "Invalid input. Please enter a number."
                    );

                    continue;
                }


                switch (choice) {

                    case 1:

                        System.out.println(
                                "\n===== ALL BOOKS ====="
                        );

                        if (books.isEmpty()) {

                            System.out.println(
                                    "There are no books in the library."
                            );

                        } else {

                            for (Book book : books) {

                                System.out.println(
                                        "ID: " + book.id
                                        + " | Title: " + book.title
                                        + " | Genre: " + book.genre
                                        + " | Status: "
                                        + (book.isBorrowed
                                        ? "Borrowed"
                                        : "Available")
                                );
                            }
                        }

                        break;

                    case 2:

                        System.out.print(
                                "\nEnter book title to search: "
                        );

                        String searchTitle =
                                scanner.nextLine();

                        boolean found = false;

                        for (Book book : books) {

                            if (book.title
                                    .toLowerCase()
                                    .contains(
                                            searchTitle.toLowerCase()
                                    )) {

                                System.out.println(
                                        "\nBook found!"
                                );

                                System.out.println(
                                        "ID: " + book.id
                                );

                                System.out.println(
                                        "Title: " + book.title
                                );

                                System.out.println(
                                        "Genre: " + book.genre
                                );

                                System.out.println(
                                        "Status: "
                                        + (book.isBorrowed
                                        ? "Borrowed"
                                        : "Available")
                                );

                                found = true;
                            }
                        }

                        if (!found) {

                            System.out.println(
                                    "Book not found."
                            );
                        }

                        break;


                    case 3:

                        System.out.print(
                                "\nEnter the ID of the book to borrow: "
                        );

                        int borrowId;

                        try {

                            borrowId =
                                    Integer.parseInt(
                                            scanner.nextLine()
                                    );

                        } catch (NumberFormatException e) {

                            System.out.println(
                                    "Invalid ID."
                            );

                            break;
                        }

                        Book bookToBorrow = null;

                        for (Book book : books) {

                            if (book.id == borrowId) {

                                bookToBorrow = book;
                                break;
                            }
                        }

                        if (bookToBorrow == null) {

                            System.out.println(
                                    "Book not found."
                            );

                        } else if (bookToBorrow.isBorrowed) {

                            System.out.println(
                                    "That book is already borrowed."
                            );

                        } else {

                            if (currentMember
                                    .borrowBook(
                                            bookToBorrow.title
                                    )) {

                                bookToBorrow.isBorrowed = true;
                            }
                        }

                        break;

                    case 4:

                        System.out.print(
                                "\nEnter the ID of the book to return: "
                        );

                        int returnId;

                        try {

                            returnId =
                                    Integer.parseInt(
                                            scanner.nextLine()
                                    );

                        } catch (NumberFormatException e) {

                            System.out.println(
                                    "Invalid ID."
                            );

                            break;
                        }

                        Book bookToReturn = null;

                        for (Book book : books) {

                            if (book.id == returnId) {

                                bookToReturn = book;
                                break;
                            }
                        }

                        if (bookToReturn == null) {

                            System.out.println(
                                    "Book not found."
                            );

                        } else if (!bookToReturn.isBorrowed) {

                            System.out.println(
                                    "That book is not currently borrowed."
                            );

                        } else {

                            if (currentMember
                                    .returnBook(
                                            bookToReturn.title
                                    )) {

                                bookToReturn.isBorrowed = false;
                            }
                        }

                        break;


                    case 5:

                        System.out.println(
                                "\nADD BOOK"
                        );

                        System.out.print(
                                "Enter book ID: "
                        );

                        int newId;

                        try {

                            newId =
                                    Integer.parseInt(
                                            scanner.nextLine()
                                    );

                        } catch (NumberFormatException e) {

                            System.out.println(
                                    "Invalid ID."
                            );

                            break;
                        }

                        // Check if ID already exists
                        boolean idExists = false;

                        for (Book book : books) {

                            if (book.id == newId) {

                                idExists = true;
                                break;
                            }
                        }

                        if (idExists) {

                            System.out.println(
                                    "A book with that ID already exists."
                            );

                            break;
                        }

                        System.out.print(
                                "Enter book title: "
                        );

                        String newTitle =
                                scanner.nextLine();

                        System.out.print(
                                "Enter book genre: "
                        );

                        String newGenre =
                                scanner.nextLine();

                        Book newBook =
                                new Book(
                                        newTitle,
                                        newId,
                                        newGenre,
                                        false
                                );

                        books.add(newBook);

                        System.out.println(
                                "Book '" + newTitle
                                + "' has been successfully added!"
                        );

                        break;


                    case 6:

                        System.out.println(
                                "\nBORROWED BOOKS"
                        );

                        if (!currentMember
                                .isBorrowingBooks()) {

                            System.out.println(
                                    "You have no borrowed books."
                            );

                        } else {

                            for (
                                    String book
                                    : currentMember.borrowedBooks
                            ) {

                                if (book != null) {

                                    System.out.println(
                                            "- " + book
                                    );
                                }
                            }
                        }

                        break;


                    case 7:

                        System.out.println(
                                "\nLogging out..."
                        );


                        currentMember = null;

                        loggedIn = false;

                        break;


                    case 8:

                        System.out.println(
                                "\nThank you for using "
                                + "the Library System!"
                        );

                        loggedIn = false;
                        programRunning = false;

                        break;


                    default:

                        System.out.println(
                                "Invalid choice. "
                                + "Please choose 1-8."
                        );
                }
            }
        }

        scanner.close();
    }
}


class Book {

    String title;
    int id;
    String genre;
    boolean isBorrowed;


    Book() {

        title = " ";
        id = 0;
        genre = " ";
        isBorrowed = false;
    }


    Book(String title) {

        this.title = title;
        isBorrowed = false;
    }


    Book(
            String title,
            int id,
            String genre,
            boolean isBorrowed
    ) {

        this.title = title;
        this.id = id;
        this.genre = genre;
        this.isBorrowed = isBorrowed;
    }
}


class Member {

    String fName;
    String lName;
    String email;
    boolean isMember;
    int id;

    String[] borrowedBooks;


    Member(
            String fName,
            String lName,
            String email,
            int id
    ) {

        this.fName = fName;
        this.lName = lName;
        this.email = email;
        this.id = id;

        this.borrowedBooks = new String[5];

        this.isMember = true;
    }


    public boolean borrowBook(String bookTitle) {

        if (!isMember) {

            System.out.println(
                    "Not a member yet!"
            );

            return false;
        }

        int count = 0;

        for (String book : borrowedBooks) {

            if (book != null) {
                count++;
            }
        }

        if (count >= 5) {

            System.out.println(
                    "Only 5 borrowed books per person."
            );

            return false;
        }

        for (int i = 0;
             i < borrowedBooks.length;
             i++) {

            if (borrowedBooks[i] == null) {

                borrowedBooks[i] = bookTitle;

                System.out.println(
                        "Book '" + bookTitle
                        + "' has been borrowed by "
                        + fName + " " + lName
                );

                return true;
            }
        }

        System.out.println(
                "Book '" + bookTitle
                + "' cant be borrowed."
        );

        return false;
    }
    public boolean returnBook(String bookTitle) {

        if (!isMember) {

            System.out.println(
                    "Not a member!"
            );

            return false;
        }

        for (int i = 0;
             i < borrowedBooks.length;
             i++) {

            if (
                    borrowedBooks[i] != null
                    && borrowedBooks[i]
                    .equalsIgnoreCase(bookTitle)
            ) {

                borrowedBooks[i] = null;

                System.out.println(
                        "Book '" + bookTitle
                        + "' has been returned by "
                        + fName + " " + lName
                );

                return true;
            }
        }

        System.out.println(
                "Book '" + bookTitle
                + "' was not found in the list "
                + "of borrowed books."
        );

        return false;
    }


    public boolean isBorrowingBooks() {

        for (String book : borrowedBooks) {

            if (book != null) {

                return true;
            }
        }

        return false;
    }
}
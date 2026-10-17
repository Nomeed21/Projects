package Library;

public class Member {
    String fName;
    String lName;
    String email;
    boolean isMember;
    int id;
    String[] borrowedBooks;

    Member(String fName, String lName, String email, int id) {
        this.fName = fName;
        this.lName = lName;
        this.email = email;
        this.id = id;
        this.borrowedBooks = new String[5];
        this.isMember = true;
    }

    public boolean borrowBook(String bookTitle) {
        if (!isMember) {
            System.out.println("Not a member yet!");
            return false;
        }

        int count = 0;
        for (String book : borrowedBooks) {
            if (book != null) {
                count++;
            }
        }

        if (count >= 5) {
            System.out.println("Only 5 borrowed books per person");
            return false;
        }

        for (int i = 0; i < borrowedBooks.length; i++) {
            if (borrowedBooks[i] == null) {
                borrowedBooks[i] = bookTitle;
                System.out.println("Book '" + bookTitle + "' has been borrowed by " + fName + " " + lName);
                return true;
            }
        }

        System.out.println("Book '" + bookTitle + "' could not be borrowed.");
        return false;
    }

    public boolean returnBook(String bookTitle) {
        if (!isMember) {
            System.out.println("Not a member!");
            return false;
        }

        for (int i = 0; i < borrowedBooks.length; i++) {
            if (borrowedBooks[i] != null && borrowedBooks[i].equals(bookTitle)) {
                borrowedBooks[i] = null;
                System.out.println("Book '" + bookTitle + "' has been returned by " + fName + " " + lName);
                return true;
            }
        }

        System.out.println("Book '" + bookTitle + "' was not found in the list of borrowed books.");
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
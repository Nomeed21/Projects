package Library;

public class Book {
    String title;
    int id;
    String genre;
    boolean isBorrowed;

    Book(){
        title = " ";
        id = 0;
        genre = " ";
        isBorrowed = false;
    }
    Book(String title) {
        this.title = title;
        isBorrowed = true;
    }
    Book(String title,
    int id,
    String genre,
    boolean isBorrowed){
        this.title = title;
        this.id = id;
        this.genre = genre;
        this.isBorrowed = isBorrowed;
    }
}

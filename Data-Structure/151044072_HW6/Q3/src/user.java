import java.util.Scanner;

public class user {
    /**
     * user interface
     * @param book books in library
     */
    public void userInterface(Books book){
        Scanner scanner = new Scanner(System.in);
        int choose;
        do {
            System.out.println("1 - Book Name");
            System.out.println("2 - Author Name");
            System.out.println("0 - Exit");

            Scanner scan = new Scanner(System.in);
            System.out.print("Choose : ");
            choose = scan.nextInt();
            switch(choose) {
                case 1:
                    System.out.print("Book name : ");
                    String books = scanner.nextLine();  // Read user input
                    book.SearchBook(books);
                    // code block
                    break;
                case 2:         System.out.print("Author name : ");
                    String author = scanner.nextLine();  // Read user input
                    book.SearchAuthor(author);
                    // code block
                    break;
            }

        }while (choose != 0);
    }
}

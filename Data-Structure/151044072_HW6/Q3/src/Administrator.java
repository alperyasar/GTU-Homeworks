import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

public class Administrator{
    private String password;

    /**
     * assign autamatic password
     */
    Administrator(){
        password = "admin";
    }

    /**
     * Administrator interface
     * @param book books in library
     */
    public void adminInterface(Books book){

        Scanner scanner = new Scanner(System.in);
        System.out.print("password : ");
        String password = scanner.nextLine();  // Read user input
        if(password.compareTo(this.password) == 0){

            int choose;
            do {
                System.out.println("1 - Search Book Name");
                System.out.println("2 - Search Author Name");
                System.out.println("3 - Add New Book");
                System.out.println("4 - Remove Book");
                System.out.println("5 - Update information");
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
                    case 3:
                        System.out.print("Book name : ");
                        books = scanner.nextLine();  // Read user input
                        System.out.print("Author name : ");
                        author = scanner.nextLine();
                        book.add(author,books);
                        // code block
                        break;
                    case 4:
                        remove(book);
                        break;
                }

            }while (choose != 0);
        }
        else System.out.println("Wrong Password!");
    }

    /**
     * remove a book in specified location
     * @param book books in library
     */
    private void remove(Books book){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Book Location : ");
        String location = scanner.nextLine();  // Read user input
        int found = 0;
        // check all author, book with location
        for (Map.Entry<String, Map<String, Set<String>>> entry : book.map.entrySet()) {
            String author = entry.getKey();
            Map<String,Set<String>> entry2 = entry.getValue();
            // for search name of book
            for (Map.Entry<String,Set<String>> entry3: entry2.entrySet()){
                String nameOfBook = entry3.getKey();
                Set<String> set = entry3.getValue();
                //check locations
                for (String s : set) {
                    //if location is found remove location
                    if (s.compareTo(location) == 0){
                        set.remove(location);
                        // when book is deleted check the library has
                        // another book with same name
                        //if no remove book from library system
                        if (set.isEmpty()){
                            entry2.remove(nameOfBook);
                            // if there is no book belonging to this author
                            // remove him/her from system
                            if(entry2.isEmpty()){
                                book.map.remove(author);
                            }
                            // when author has anothr books in the library
                            else {
                                book.map.remove(author);
                                book.map.put(author,entry2);
                            }
                        }
                        // when author has just 1 book in libray remove
                        else {
                            entry2.put(nameOfBook,set);
                            book.map.put(author,entry2);
                        }
                        found = 1;
                        break;
                    }
                }
                if (found == 1){
                    break;
                }
            }
            if (found == 1){
                break;
            }
        }

    }


}

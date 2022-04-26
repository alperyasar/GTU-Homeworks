import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Books book = new Books();
        Administrator admin = new Administrator();
        user us = new user();
        book.print();
        int choose;
        do {
            System.out.println("1 - User");
            System.out.println("2 - Admin");
            System.out.println("0 - Exit");

            Scanner scan = new Scanner(System.in);
            System.out.print("Choose : ");
            choose = scan.nextInt();
            switch(choose) {
                case 1:
                    us.userInterface(book);
                    // code block
                    break;
                case 2:
                    admin.adminInterface(book);
                    // code block
                    break;
            }

        }while (choose != 0);
        book.print();
    }
}

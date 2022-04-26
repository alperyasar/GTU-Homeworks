import java.util.Scanner;

public class User {
    /**
     * user interface
     */
    public void userInterface(SkipList<Package> test){
        Scanner scanner = new Scanner(System.in);
        int choose;
        do {
            System.out.println("1 - Search");
            System.out.println("0 - Exit");

            Scanner scan = new Scanner(System.in);
            System.out.print("Choose : ");
            choose = scan.nextInt();
            switch(choose) {
                case 1:
                    search(test);
                    // code block
                    break;
            }

        }while (choose != 0);
    }

    private void search(SkipList<Package> test){
        Scanner scanner = new Scanner(System.in);
        System.out.println("1 - Search by name all contains");
        System.out.println("2 - Search by name and version");


        System.out.print("Choose : ");
        int choose = scanner.nextInt();
        switch(choose) {
            case 1: System.out.print("Enter : ");
                scanner.nextLine();
                String name = scanner.nextLine();
                System.out.println(test.contains(new Package(name)));
                break;
            case 2:System.out.print("Enter name: ");
                scanner.nextLine();
                name = scanner.nextLine();
                System.out.print("Enter version: ");
                String version = scanner.nextLine();
                System.out.println(test.contains(new Package(name,version)));
                // code block
                break;
        }


    }
}

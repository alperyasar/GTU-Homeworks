import java.util.Scanner;

public class Administrator {
    private String password;

    /**
     * assign autamatic password
     */
    Administrator(){
        password = "admin";
    }

    /**
     * Administrator interface
     */
    public void adminInterface(SkipList<Package> test){

        Scanner scanner = new Scanner(System.in);
        System.out.print("password : ");
        String password = scanner.nextLine();  // Read user input
        if(password.compareTo(this.password) == 0){

            int choose;
            do {
                System.out.println("1 - Add");
                System.out.println("2 - Delete");
                System.out.println("3 - Update");
                System.out.println("4 - Search");
                System.out.println("0 - Exit");

                Scanner scan = new Scanner(System.in);
                System.out.print("Choose : ");
                choose = scan.nextInt();
                switch(choose) {
                    case 1:
                        add(test);
                        // code block
                        break;
                    case 2:
                        delete(test);
                        // code block
                        break;
                    case 3:
                        update(test);
                        // code block
                        break;
                    case 4:
                        search(test);
                        // code block
                }

            }while (choose != 0);
        }
        else System.out.println("Wrong Password!");
    }
    private void add(SkipList<Package> test){
        Scanner scanner = new Scanner(System.in);
        System.out.print("enter package name: ");
        String name = scanner.nextLine();

        System.out.print("enter package version: ");
        String version = scanner.nextLine();

        System.out.print("enter package quantity: ");
        int quantity = scanner.nextInt();

        System.out.print("enter package price: ");
        double price = scanner.nextDouble();

        test.add(new Package(name, version, quantity, price));

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
    private void delete(SkipList<Package> test){
        Scanner scanner = new Scanner(System.in);
        System.out.print("enter package name: ");
        String name = scanner.nextLine();


        System.out.print("enter package version: ");
        String version = scanner.nextLine();


       Package newPackage = test.find(new Package(name,version));
       if (newPackage.getQuantity() == 1){
           test.remove(newPackage);
       }
       else {
           test.remove(newPackage);
           newPackage.decreaseQuantity();
           test.add(newPackage);
       }

    }
    private void update(SkipList<Package> test){
        System.out.println("What package do you want update?");
        Scanner scanner = new Scanner(System.in);
        System.out.print("enter package name: ");
        String name = scanner.nextLine();

        System.out.print("enter package version: ");
        String version = scanner.nextLine();


        Package newPackage = test.find(new Package(name,version));
        test.remove(newPackage);

        System.out.print("Do you want change name [Y] for yes or [N] for no : ");
        String choose = scanner.nextLine();

        if (choose.equalsIgnoreCase("Y")){
            newPackage.changeName(scanner.nextLine());
        }
        System.out.print("Do you want change version [Y] for yes or [N] for no : ");
        choose = scanner.nextLine();

        if (choose.equalsIgnoreCase("Y")){
            newPackage.changeVersion(scanner.nextLine());
        }
        System.out.print("Do you want change quantity [Y] for yes or [N] for no : ");
        choose = scanner.nextLine();

        if (choose.equalsIgnoreCase("Y")){
            newPackage.changeQuantity(scanner.nextInt());
        }
        System.out.print("Do you want change price [Y] for yes or [N] for no : ");
        scanner.nextLine();
        choose = scanner.nextLine();

        if (choose.equalsIgnoreCase("Y")){

            newPackage.changePrice(scanner.nextDouble());
        }
            test.add(newPackage);

    }
}

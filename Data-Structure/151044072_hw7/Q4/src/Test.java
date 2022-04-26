import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        SkipList<Package> test = new SkipList<Package>();
        Administrator admin = new Administrator();
        User user = new User();
        test.add(new Package("Adobe Photoshop", "6.0" , 3, 179.90));
        test.add(new Package("Adobe Photoshop", "6.2" , 1, 199.90));
        test.add(new Package("Norton", "4.5" , 7, 129.90));
        test.add(new Package("Norton", "5.5" , 4, 179.90));
        test.add(new Package("Adobe Flash", "3.3" , 3, 79.90));
        test.add(new Package("Adobe Flash", "4.0" , 3, 109.90));

        System.out.println(test.toString());
        System.out.println(test.find(new Package("Adobe Flash")));
        System.out.println(test.find(new Package("Adobe Flash","4.0")));
        System.out.println(test.contains(new Package("Pho")));
        int choose;
        Scanner scanner = new Scanner(System.in);
        do {
            System.out.println("1 - Administrator");
            System.out.println("2 - User");
            System.out.print("Choose : ");
            choose = scanner.nextInt();
            switch(choose) {
                case 1:
                    admin.adminInterface(test);
                    // code block
                    break;
                case 2:
                    user.userInterface(test);
                    // code block

            }

        }while(choose != 0);
    }
}

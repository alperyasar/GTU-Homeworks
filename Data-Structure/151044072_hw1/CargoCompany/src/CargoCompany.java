/**
 * <h1>CARGO COMPANY!</h1>
 * The automation system for a cargo company has users such as
 * administrators, branch employees, transportation personnel
 * and customers.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-02-24
 */
import java.util.Scanner;  // Import the Scanner class

public class CargoCompany {

    public static void printMenu(){
/**
 * This method is used to print user interface.
 * Select which user will use the program.
 */
        System.out.print("\n\n\n\n\n\n----------------- USER INTERFACE -----------------\n" +
                "1 - Administrator\n" +
                "2 - Branch Employee\n" +
                "3 - Transportation Employee\n" +
                "4 - Customer\n" +
                "0 - Exit\n" +
                "choose : ");
    }

    public static void main(String[] args) {
        administrators adm = new administrators();
        branch [] brc = new branch[1];
        brc[0] = new branch();
        String [] scanString = new String[4];
        int packSize = 0;
        int branchSize = 1;
        shipments [] pack = new shipments[1];

        Scanner inp = new Scanner(System.in);  // Create a Scanner object
        Scanner inp2 = new Scanner(System.in);  // Create a Scanner object

        int userChoose;  // Read user input
        int adminChoose;
        do{
            printMenu();
            userChoose = inp.nextInt();

            if(userChoose == 1){
                /*admin menu */
                adm.adminMenu();
                adminChoose = inp2.nextInt();  // Read user input
                if(adminChoose > 2 ){
                    System.out.print("choose branch : ");
                    int i = inp2.nextInt();
                    brc[i-1] = adm.branchSetting(brc[i-1],adminChoose);
                }
                else if(adminChoose == 1){
                    branchSize++;
                    branch [] tempBranch = new branch[branchSize];
                    for(int i = 0; i< branchSize-1; i++){
                        tempBranch[i] = new branch(brc[i]);
                    }
                    tempBranch[branchSize-1] = new branch();
                    brc = tempBranch;

                }
                else if(adminChoose == 2){
                    System.out.print("choose branch for delete : ");
                    int j = inp2.nextInt();
                    int k = 0;
                    branchSize--;
                    branch [] tempBranch = new branch[branchSize];
                    for(int i = 0; i< branchSize+1; i++){
                        if(i!=j-1){
                            tempBranch[k] = new branch(brc[i]);
                            k++;
                        }

                    }
                    brc = tempBranch;

                }
                System.out.println(branchSize);
            }

            if(userChoose == 2){
                /* Branch Employee menu */
                System.out.print("choose branch : ");
                int i = inp2.nextInt();
                brc[i].branchPage();
                int j = inp2.nextInt();
                if(j == 1 ){
                    System.out.print("Enter Package trackingNumber ");
                    int k = inp2.nextInt();
                    System.out.println("enter 3 for Leave from branch");
                    System.out.println("Enter 2 for Arrive to branc");
                    pack[k-1].whereTo = inp.nextInt();
                }
                if(j == 2 ){
                    System.out.print("Enter Tracking number for delete : ");
                    int l = inp2.nextInt();
                    int k = 0;
                    packSize--;
                    shipments [] temp = new shipments[packSize];
                    for(int m = 0; m< packSize+1; m++){
                        if(m!=l-1){
                            temp[k] = new shipments(pack[m]);
                            k++;
                        }

                    }
                    pack = temp;
                }

            }

            if(userChoose == 3){
                /*Transportation personnel menu*/
                System.out.print("Enter Package trackingNumber ");
                int k = inp2.nextInt();
                System.out.println("Enter 2 for Arrive to branc");
                System.out.println("enter 4 for DELIVERED");
                pack[k-1].whereTo = inp.nextInt();
            }

            if(userChoose == 4){
                /*user menu*/
                customerPage();

                userChoose = inp.nextInt();
                if(userChoose == 1){
                    System.out.print("Please enter treaking number : ");
                    int trakingNumber = inp2.nextInt();
                    for (int i = 0 ; i< packSize ; i++) {
                        if(pack[i].trackingNumber == trakingNumber){
                            pack[i].printShipments();
                        }
                    }

                }

                if(userChoose == 2){
                    packSize++;

                    if(packSize > 1){
                        shipments [] temp = new shipments[packSize];

                        for(int i = 0; i< packSize-1; i++){
                            temp[i] = new shipments(pack[i]);
                        }
                        temp[packSize-1] = new shipments(packSize);
                        pack = temp;
                    }
                    else
                        pack[packSize-1] = new shipments(packSize);
                }


            }
        }while(userChoose != 0);
    }
    public static void customerPage(){
        System.out.print("\n\n\n\n\n\n----------------- CUSTOMER INTERFACE -----------------\n" +
                "1 - Shipment Tracking\n" +
                "2 - Send Package\n" +
                "Choose : ");

    }


}
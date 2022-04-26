import java.util.Scanner;

public class shipments {
    String senderName;
    String senderSurname;
    String recieverName;
    String recieverSurname;

    int whereTo;/* 1 - Take pack from customer
				   2 - Arrive to branch
				   3 - Leave Branch
				   4 - Delivered*/
    public int trackingNumber;

    public shipments(){
/**
 * Constructor for first shipment
 */
        trackingNumber = 0;
    }

    public shipments(int numb){
/**
 * This constructor for assing info shipment.
 * The customer giving your own and reciver
 * information about shipment.
 * @param scanString for scanning informations.
 * @return shipments object for assign.
 */
        Scanner inp = new Scanner(System.in);  // Create a Scanner object
        String [] scanString = new String[5];

        System.out.print("Sender name : ");
        scanString[0] = inp.nextLine();
        System.out.print("Sender surname : ");
        scanString[1] = inp.nextLine();
        System.out.print("Reviever name : ");
        scanString[2] = inp.nextLine();
        System.out.print("Reciever surname : ");
        scanString[3] = inp.nextLine();

        this.senderName = scanString[0];
        this.senderSurname = scanString[1];
        this.recieverName = scanString[2];
        this.recieverSurname = scanString[3];
        this.trackingNumber = numb;
        this.whereTo = 1;


        System.out.println("Your Trackin number : " + numb + "\n\n");
    }
    public shipments(shipments temp){
/**
 * This constructor for assing shipment object
 * to another shipment object.
 * @return shipments object for assign.
 */

        this.senderName = temp.senderName;
        this.senderSurname = temp.senderSurname;
        this.recieverName = temp.recieverName;
        this.recieverSurname = temp.recieverSurname;
        this.trackingNumber = temp.trackingNumber;
        this.whereTo = temp.whereTo;

    }
    public void printShipments(){
/**
 * When the customer entering tracking number
 * this method showing informations about package
 * and they see where the package.
 */
        System.out.print("Info About " + trackingNumber +
                "\nSender : " + senderName + " " + senderSurname +
                "\nReciever : " + recieverName + " " + recieverSurname +
                "\nWhere : ");
        if(whereTo == 1 ){
            System.out.println("Taken pack from customer");
        }
        if(whereTo == 2 ){
            System.out.println("Arrive to branch");
        }
        if(whereTo == 3 ){
            System.out.println("Leave from branch");
        }
        if(whereTo == 4 ){
            System.out.println("DELIVERED");
        }
    }
}

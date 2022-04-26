package Cargo;

import java.util.Scanner;

public class shipments {
    protected String senderName;
    protected String senderSurname;
    protected String recieverName;
    protected String recieverSurname;

    protected int whereTo;/* 1 - Take pack from customer
				   2 - Arrive to branch
				   3 - Leave Branch
				   4 - Delivered*/
    public int trackingNumber;
    /**
     * Constructor for first shipment
     */
    public shipments(){

        trackingNumber = 0;
    }
    public void changeInfo(int numb){
        whereTo = numb;
    }

    /**
     * This constructor for assing info shipment.
     * The customer giving your own and reciver
     * information about shipment.
     * @param numb
     */
    public shipments(int numb){

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
        this.trackingNumber = ++numb;
        this.whereTo = 1;


        System.out.println("Your Trackin number : " + numb + "\n\n");
    }

    /**
     * This constructor for assing shipment object
     * to another shipment object.
     * @param temp for assign shipment
     */
    public shipments(shipments temp){

        this.senderName = temp.senderName;
        this.senderSurname = temp.senderSurname;
        this.recieverName = temp.recieverName;
        this.recieverSurname = temp.recieverSurname;
        this.trackingNumber = temp.trackingNumber;
        this.whereTo = temp.whereTo;

    }

    /**
     * When the customer entering tracking number
     * this method showing informations about package
     * and they see where the package.
     */
    public void printShipments(){

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
    public int numb(){
        return trackingNumber;
    }
}

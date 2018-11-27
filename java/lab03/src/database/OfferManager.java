package database;


import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Scanner;

 class OfferManager
{
    private Scanner consoleInput = new Scanner(System.in);
    private ArrayList<ExcursionOffer> offers = new ArrayList<>();
    private Controller controller;

     int createOffer() throws ParseException {
        System.out.println("Trip begins: <format: yyyy-MM-dd> ");
        String dateBegin = consoleInput.nextLine();
        if( dateBegin.length() == 0){
            System.out.println();
        }
        System.out.println("Trip ends: <format: yyyy-MM-dd> ");
        String dateFinish = consoleInput.nextLine();
        System.out.println("Trip short description: ");
        String description = consoleInput.nextLine();
        System.out.println("Trip destination:  ");
        String destination = consoleInput.nextLine();
        System.out.println("Maximal quantity of participants: ");
        int participantLimit = Integer.valueOf(consoleInput.nextLine());
        this.offers.add(new ExcursionOffer(dateBegin,dateFinish,description,destination,participantLimit) );
        return 0;
    }

     void setController(Controller controller) {
        this.controller = controller;
    }

    public ArrayList<ExcursionOffer> getOffers() {
        return offers;
    }

    int updateOffer() throws ParseException {

        printPossibleOffers();
        System.out.println("Type offer id: ");
        int offerId = this.consoleInput.nextInt();
        this.consoleInput.nextLine();//consume newline
        if(offerId >= offers.size() || offerId < 0 )
            return 5; // out of range
        System.out.println("Trip begins: <format: yyyy-MM-dd> [Empty line to omit]");
        String dateBegin = consoleInput.nextLine();
        if( dateBegin.length() > 0 )
            if( !Controller.validateDate(dateBegin) )
                return 1;
            else
                this.offers.get(offerId).setTermBegin(dateBegin);
        System.out.println("Trip ends: <format: yyyy-MM-dd> [Empty line to omit]");
        String dateFinish = consoleInput.nextLine();
        if( dateFinish.length() > 0 )
            if( Controller.validateDate(dateFinish) )
                return 1;
            else
                this.offers.get(offerId).setTermFinish(dateFinish);
        System.out.println("Trip short description: [Empty line to omit]");
        String description = consoleInput.nextLine();
        if( description.length() > 0 )
            this.offers.get(offerId).setDescription(description);
        System.out.println("Trip destination:  [Empty line to omit]");
        String destination = consoleInput.nextLine();
        if( destination.length() > 0 )
            this.offers.get(offerId).setDestination(destination);
        System.out.println("Maximal quantity of participants: [Empty line to omit]");
        int participantLimit = consoleInput.nextInt();
        consoleInput.nextLine(); // consume newline
        if( dateBegin.length() > 0 )
            this.offers.get(offerId).setPlaceQuantity(participantLimit);
        return 0;
    }


     int removeOffer()
     {
         printPossibleOffers();
        System.out.println("Type offer id: ");
        int offerId = this.consoleInput.nextInt();
        this.consoleInput.nextLine(); //consume newline
        if(offerId >= offers.size()  || offerId < 0 )
            return 5; // out of range
        this.offers.remove(offerId);

        return 0;
    }

    private void printPossibleOffers() {
         System.out.println("Accessible offers: ");
         int i = 0;
        for (ExcursionOffer of: this.offers) {
            System.out.println( "Offer id: " + String.valueOf(i) +  ", destination : " + of.getDestination() );
            i++;
        }
    }

    ExcursionOffer searchForIndex(int idx){
        for (ExcursionOffer offer : this.offers) {
            if( offer.getId() == idx)
                return offer;
        }
        return null;

    }

     int printOffers() {
        System.out.println("Show offers sorted by: ");
        System.out.println("1.Begin date of excursion ");
        System.out.println("2.Destination");
        System.out.println("3.Place quantity");
        System.out.println("[Default print without criteria]");
        int criteria = this.consoleInput.nextInt();
         this.consoleInput.nextLine(); //consume newline
        int direction;
        switch (criteria){
            case 1:
                System.out.println("1.ASC\n2.DSC ");
                direction= this.consoleInput.nextInt();
                this.consoleInput.nextLine(); //consume newline
                if(direction == 1)
                    this.offers.sort(ExcursionOffer::compareDateASC);
                else if (direction == 2)
                    this.offers.sort(ExcursionOffer::compareDateDSC);
                break;
            case 2:
                System.out.println("1.ASC\n2.DSC ");
                direction= this.consoleInput.nextInt();
                this.consoleInput.nextLine(); //consume newline
                if(direction == 1)
                    this.offers.sort(ExcursionOffer::compareDirectionASC);
                else if (direction == 2)
                    this.offers.sort(ExcursionOffer::compareDirectionDSC);
                break;
            case 3:
                System.out.println("1.ASC\n2.DSC ");
                direction= this.consoleInput.nextInt();
                this.consoleInput.nextLine(); //consume newline
                if(direction == 1)
                    this.offers.sort(ExcursionOffer::comparePlaceASC);
                else if (direction == 2)
                    this.offers.sort(ExcursionOffer::comparePlaceDSC);
                break;
        }

        this.offers.forEach(o -> System.out.println( o.toString() ) );
        return 0;
    }
    void exportToDatabase(String fileName) throws IOException {

        // if there wasn't be for my java laboratories where i know how data looks,
        // if it hasn't been for that i probably would use json
        BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        // write last active id
        writer.write(String.valueOf(ExcursionOffer.getUniqueID()) );
        writer.write("\n");
        // write data size
        writer.write( String.valueOf( this.offers.size() ) );
        writer.write("\n");
        // write all data
        this.offers.forEach((of) ->{
            try {
                writer.write( of.toDatabaseFormat() );
            } catch (IOException e) {
                System.out.println("Error during writing");
                controller.setError_code(2);
            }
        });
        writer.close();
     }

     void importFromDatabase(String fileName) throws IOException, ParseException {
         this.offers = new ArrayList<>();
         ExcursionOffer.setUniqueID(0);
         String line;
         BufferedReader reader = new BufferedReader(new FileReader(fileName));
         // get unique id
         int uniqueId  = Integer.valueOf(reader.readLine());
         // get data size
         int size =  Integer.valueOf(reader.readLine());
         // get data
         int i = 0;

         while( (line = reader.readLine() ) != null ){
             String[] data = line.split(",");
             this.offers.add( new ExcursionOffer( Long.parseLong(data[0]),
                                                  Long.parseLong(data[1]),
                                                  data[2],
                                                  data[3],
                                                  Integer.valueOf(data[4])) );
            this.offers.get(i).setId(Integer.valueOf(data[5]));
            if( i == size  ) break;
            i++;
         }
         ExcursionOffer.setUniqueID( uniqueId );
         controller.setError_code(0);
         reader.close();
     }
}

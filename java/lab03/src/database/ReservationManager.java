package database;

import java.io.*;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Scanner;

class ReservationManager{

    private Scanner consoleInput = new Scanner(System.in);
    private Controller controller;
    private ArrayList<reservationDescriptor> reservations;

    // ones created reservation group should exist till the offer exist
    // when offer gets deleted reservation should be vanished
    private static class reservationDescriptor{
        ArrayList<Reservation> reservations = new ArrayList<>();
        int placeTaken = 0;
        static private int uniqueId = 0 ;
        private int id;
        private ExcursionOffer offerRef;
        reservationDescriptor(Reservation _reservation,ExcursionOffer _offer, int initialMembersCount){
            this.reservations.add(_reservation);
            this.offerRef  = _offer;
            this.placeTaken += initialMembersCount;
            this.id = uniqueId;

            uniqueId++;
        }
        reservationDescriptor(ArrayList<Reservation>  _reservation,ExcursionOffer _offer, int initialMembersCount){
            this.reservations = _reservation;
            this.offerRef = _offer;
            this.placeTaken += initialMembersCount;
            this.id = uniqueId;
            uniqueId++;
        }
        int getId()
        {
            return id;
        }

        int getPlaceTaken() {
            return placeTaken;
        }

       static int getUniqueId() {
            return uniqueId;
        }

        static void setUniqueId(int uniqueId) {
            reservationDescriptor.uniqueId = uniqueId;
        }

        void update(Reservation _reservation, int membersCount){
            this.reservations.add(_reservation);
            this.placeTaken += membersCount;

        }

        ExcursionOffer getOfferRef() {
            return offerRef;
        }

        ArrayList<Reservation> getReservations() {
            return reservations;
        }

        int comparePopularity(reservationDescriptor reservation){
            return Integer.compare(this.placeTaken, reservation.placeTaken);
        }
        String toDatabaseFormat(){
            String fmt = "";
            fmt += String.valueOf( this.offerRef.getId() ) +","+ String.valueOf(this.reservations.size() ) +"\n";
            for (Reservation r: this.reservations) {
                fmt += r.toDatabaseFormat();
            }
            fmt += String.valueOf(this.placeTaken) + "\n";

            return fmt;
        }

    }

    void validateReservations() {
        this.reservations.forEach((reservation_group) ->{
            for(int i =0 ; i < reservation_group.getReservations().size(); i++){
                Reservation res = reservation_group.getReservations().get(i);
                res.isReservationExpired();

                if( res.getStatus() == Reservation.STATUS.resignation ||
                        res.getStatus() == Reservation.STATUS.expired){
                    reservation_group.getReservations().remove(res);
                    i--;
                }
            }
        });
    }

    ArrayList<reservationDescriptor> getReservations() {
        return reservations;
    }

    void setController(Controller controller) {
        this.controller = controller;
        reservations = new ArrayList<>();
    }

    int createReservation() throws ParseException {


        System.out.println("Main person details: ");
        System.out.println("Name:");
        String name = consoleInput.nextLine();
        System.out.println("Surname:");
        String surname = consoleInput.nextLine();
        Client headPerson = new Client(name,surname);
        System.out.println("Excursion id: ");
        int excursionId = consoleInput.nextInt();
        this.consoleInput.nextLine(); //consume newline
        ExcursionOffer tripOfferCopy = this.controller.searchForOffer(excursionId);
        if(tripOfferCopy == null) {
            return 1; // object not found
        }
        System.out.println("Additional members count: ");
        int additionalMemberCount = consoleInput.nextInt();
        this.consoleInput.nextLine(); //consume newline
        ArrayList<Client> members = new ArrayList<>();
        for (int i = 0 ; i < additionalMemberCount; i++){
            System.out.println("Name:");
            name = consoleInput.nextLine();
            System.out.println("Surname:");
            surname = consoleInput.nextLine();
            members.add( new Client(name,surname) );
        }

        System.out.println("Pay time expires: <format: yyyy-MM-dd> ");
        String payDay = consoleInput.nextLine();
        if(!Controller.validateDate(payDay))
            return 1;
        // search in current reservations, if offer was added
        int index = this.searchForExistingOffer(excursionId);
        if(index == -1)
            this.reservations.add(new reservationDescriptor(
                  new Reservation( headPerson, members, payDay, Reservation.STATUS.established, Controller.getLocalTime()  ),
                    tripOfferCopy,additionalMemberCount + 1) ); //additionalMemberCount + 1  == all members count + head person
        else{
            this.reservations.get(index).update(
                    new Reservation( headPerson, members, payDay, Reservation.STATUS.established, Controller.getLocalTime()  )
                    , additionalMemberCount + 1);
        }
        return 0;
    }

    int payForReservation() {
        this.updateStatus(Reservation.STATUS.paid);
        return 0;
    }

    int discardReservation() {
        this.updateStatus(Reservation.STATUS.resignation);
        return 0;
    }

    private int updateStatus(Reservation.STATUS s){
        // print all reservation to inform user
        printReservations();

        System.out.println("Choose excursion group: [-1 to abort]");
        int groupIndex = consoleInput.nextInt();
        this.consoleInput.nextLine(); //consume newline
        System.out.println("Reservation Id: [-1 to abort]");
        int reservationIndex = consoleInput.nextInt();
        this.consoleInput.nextLine(); //consume newline
        if(groupIndex < 0  || reservationIndex < 0 || groupIndex > this.reservations.size() )
            return 5; // operation aborted

        for(Reservation reservation : this.reservations.get(groupIndex).getReservations() ){

            if( reservationIndex == reservation.getId() )
                reservation.setStatus(s, Controller.getLocalTime() );
        }
        return 0;
    }

    private int searchForExistingOffer(int idx){

        int i =0;
        for (reservationDescriptor offer : this.reservations) {
            if( offer.getOfferRef().getId() == idx)
                return i; // index of array list position
            i++;
        }
        return -1; // if object doesn't exist return -1
    }

    void printReservations(){
        for (reservationDescriptor reservationGroup : this.reservations ){
            System.out.println("Group id:" + reservationGroup.getId() );
            System.out.println( "Excursion ID:" + reservationGroup.getOfferRef().getId());
            for (Reservation reservation : reservationGroup.getReservations() ){
                System.out.println( reservation.toString() );
            }
        }
    }

    int generateStatistic( ){
        int i = 1;
        System.out.println("Option <1> - most attractive offers\nOption <2> - users activity");
        int mode = consoleInput.nextInt();
        this.consoleInput.nextLine(); //consume newline
        switch (mode){
            case 1: // most attractive  offer
                this.reservations.sort( (reservationDescriptor::comparePopularity) );
                System.out.println("Statistic [most attractive offers]");

                for(reservationDescriptor reservation : this.reservations ){
                    System.out.println(String.valueOf(i) +". Excursion to : " + reservation.getOfferRef().getDestination() + " interested members: " + reservation.getPlaceTaken() );
                    i++;
                }
                break;
            case 2: // activity of user in specified period of time like past day / week
                System.out.println("Statistic [ users activity ]");
                System.out.println("Statistic option: <n days>");
                int scope = consoleInput.nextInt();
                this.consoleInput.nextLine(); //consume newline
                this.groupedByDateAndPrint(scope);
                break;
            default:
                return 1;
        }
        return 0;

    }
    void groupedByDateAndPrint(int scope){

        HashMap<Date,Integer> days = new HashMap<>();
        int scopeCopy = scope;
        Integer value;
        // last activity
        Date LA;
        // group all
        for(reservationDescriptor reservation : this.reservations){
            reservation.getReservations().sort(Reservation::compareLastModification);
            for( Reservation r : reservation.getReservations() ){
                if(scope < 0)
                    break;
                LA  = r.getLastActivity();
                value = days.get(LA);
                if(value == null){
                    days.put( LA, 1 );
                    scope--;
                }else{
                 days.put( LA,value + 1 );
                }
            }
            scope = scopeCopy;
        }
        System.out.println("Last activity in "+ scopeCopy + " days");
        days.forEach((Date key, Integer v) ->{
            System.out.println("Day: " + key.toString() + ", users activity: " + v.toString() );
        });
    }

    void exportToDatabase(String fileName) throws IOException {

        BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        // save unique ID
        writer.write( String.valueOf(reservationDescriptor.getUniqueId() ));
        writer.write("\n");
        // save size of reservation container witch is how many group reservation were created
        writer.write( String.valueOf(this.reservations.size()) );
        writer.write("\n");
        // save data
        // for each reservation group
        try {
            for (reservationDescriptor r_group : this.reservations) {

                // all group are splited by \n
                writer.write(r_group.toDatabaseFormat()); // write data of each group

            }
        } catch (IOException e) {
            controller.setError_code(2);
            e.printStackTrace();
            System.out.println("Error writing");
        }finally {
            writer.close();
        }
    }
    void importFromDatabase(String fileName) throws IOException, ParseException {

        this.reservations = new ArrayList<>();
        reservationDescriptor.setUniqueId(0);
        ArrayList<Reservation> reservationArray = new ArrayList<>();
        ArrayList<Client> ClientArray = new ArrayList<>();

        String line;
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        // get unique id
        int uniqueId  = Integer.valueOf(reader.readLine());
        // get data size
        int size =  Integer.valueOf(reader.readLine());
        // get data
        int i ;
        String data[];
        while( (line = reader.readLine() ) != null ){
            data = line.split(",");
            // get offer  from its id
            ExcursionOffer tripOffer = this.controller.searchForOffer(Integer.valueOf(data[0]));
            //get reservation count for each group
            int reservationCount = Integer.valueOf(data[1]);

            while(reservationCount > 0) {
                line = reader.readLine();
                data = line.split(",");
                int membersCount = Integer.valueOf(data[5]); // get members count
                // read all members
                i=0;
                while(i< membersCount){
                    ClientArray.add( new Client(data[6+i],data[7+i]) );
                    i++;
                }
                // fill reservation with all data
                reservationArray.add( new Reservation( data[0], data[1], ClientArray,
                                    Long.parseLong(data[2]),Integer.valueOf(data[3]),Long.parseLong(data[4] )) );
                reservationCount--;
            }

            //   // get all reservation members and
            int allParticipantsCount =Integer.valueOf( reader.readLine() );
        // time to fill our reservation group with data
            this.reservations.add( new reservationDescriptor( reservationArray,tripOffer,allParticipantsCount ));
            reservationArray = new ArrayList<>();
        }
        reservationDescriptor.setUniqueId(uniqueId);
        reader.close();
    }

}

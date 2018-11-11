package recrutation_system;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;


class ClassManager {
    private ArrayList<School> availableSchools;
    private ArrayList<Student> availableStudents;
    private boolean dataReady = false;
    int points = 0;

    // Priorities in which algorithm will sort students through different schools
    // id 1 = priority consequent from students priorities
    // id 2 = priority consequent from students points
    private Priority[] Priorities = new Priority[]{new Priority(1, true),
                new Priority(2, true)};

    ClassManager() {
        this.availableSchools = new ArrayList<>();
        this.availableStudents = new ArrayList<>();
    }

    ClassManager(ArrayList<School> avSchools, ArrayList<Student> avStudents)
    {
        //  check if data was read
        if (avSchools == null || avStudents == null) {
            System.out.println("Can't init manager. Data corrupted");
            return;
        }
        // check data correctness
        // school can't have 0 available places for students
        // students must have proper school ids in preferences

        dataReady = true;
        this.availableSchools = avSchools;
        this.availableStudents = avStudents;
        // uncomment following line to debug read data
        //this.printData();
    }

    void setPriorities()
    {
        // if no data, break priorities settings
        if(!this.dataReady)
            return;
        // choose right order for algorithm sort
        System.out.println("Choose right priorities order for algorithm");
        System.out.println("Syntax <opcode> <args...>");
        System.out.println("opcode = 1 Swap priorities example 1 2 <-swap priority 1 with 2 ");
        System.out.println("opcode = 2 Toggle priority between enable and disable example 2 1 <-Toggle priority 1 ");

        String [] options = {".Student preferences ", ".Students with most amount of points"};
        // opcode == 1 change position,opcode == 2 toggle;  opcode == 3 exit

        int opcode =2 , arg1, arg2;
        Scanner readUserInput = new Scanner(System.in);
        String line;

        while(opcode != 3) {
            int j =0;
            System.out.println("Priorities: ");
            System.out.println("State:  Name: ");
            for( Priority inst : this.Priorities) {
                System.out.println( "[" + ( (this.Priorities[j].getisActive()) ? "x":" ") +"]     " + String.valueOf(j+1) + options[inst.getid() - 1] );
                j++;
            }
            System.out.println("Type '3' to confirm algorithm priorities: ");
            line = readUserInput.nextLine();
            // split line to arguments
            String[] splitedLine = line.split(" ");
            // filter empty arguments
            splitedLine = Arrays.stream(splitedLine).filter(s -> !s.isEmpty() ).toArray(String[]::new);
            // get instruction code, to execute command
            opcode = Integer.parseInt( splitedLine[0] );
            switch(opcode) {
                // move command
                case 1:
                    if(splitedLine.length < 3) {
                        System.out.println("Incorrect syntax. Should be opcode arg1 arg2");
                        break;
                    }
                    arg1 = Integer.parseInt( splitedLine[1] )-1;
                    arg2 = Integer.parseInt( splitedLine[2] )-1;
                    if (arg1 > 2 || arg2 > 2){
                        System.out.println("Incorrect range");
                        break;
                    }
                    Priority tmp = this.Priorities[arg1];
                    this.Priorities[arg1] = this.Priorities[arg2];
                    this.Priorities[arg2] = tmp;
                    break;
                // toggle command
                case 2:
                    if(splitedLine.length < 2) {
                        System.out.println("Incorrect syntax. Should be opcode arg1");
                        break;
                    }
                    arg1 = Integer.parseInt( splitedLine[1] ) - 1;
                    if (arg1 > 2){
                        System.out.println("Incorrect range");
                        break;
                    }
                    this.Priorities[arg1].setActive(!this.Priorities[arg1].getisActive());
                    break;
                // ignore bad opcodes
                case 3:
                    break;
                default:
                    System.out.println("Incorrect opcode");
                    break;
            }
        }
        readUserInput.close();
    }

    void printData()
    {
        // print all obtained schools
        System.out.println("Schools");
        for (School s : this.availableSchools) {
            System.out.println(s.toString());
        }
        // print all obtained students
        System.out.println("Students: ");
        for (Student s : this.availableStudents) {
            System.out.println(s.toString());
        }
    }

    void printResults()
    {
        this.availableSchools.forEach(school -> {
            System.out.println( "School " + String.valueOf(school.getId()) );
            for (Student student: school.getStudents() ) {
                System.out.println( student.toString() );
            }
        });
    }

    boolean execute()
    {
        if (!dataReady) {
            System.out.println("Can't execute algorithm");
            return false;
        }
        // get first active priority
        Priority prior = null;
        for(int i  = 0; i <  this.Priorities.length; i++){
            if( this.Priorities[i].getisActive() ){
                prior = Priorities[i];
                break;
            }
        }
        // if no available priorities, return with error
        if(prior == null)
            return false;
        System.out.println(prior.getid());
        // choose algorithm path to sort school students
        switch( prior.getid() ) {
            // first sort students by priorities and than check if
            // students have best match in points
            case 1:
                this.divideByPriorities();
                break;
                // first sort students by point, and than fill school with unbind students
            case 2:
                this.divideByPoints();
                break;
        }
        if(availableStudents.size() != 0)
            this.fillSchoolWithUnbindStudents();

        return true;
    }


    private void fillSchoolWithUnbindStudents()
    {
        Student student;
        for (School school: this.availableSchools) {
            for (int i = 0; i < this.availableStudents.size(); i++) {

                student = this.availableStudents.get(i);
                if (!school.limitReached()){
                    this.moveToSchool(school, student);
                    i--;
                }
            }
        }
    }

    private void divideByPoints()
    {
        if(availableStudents.size() == 0)
            return;

        this.availableStudents.sort(Student::compare);
        // if user want to reorder students to get best match
        if(this.Priorities[1].getisActive())
            // sort subgroups
            this.groupAndSortByPriorities();
        this.moveToSchool();
    }
    // function grouping students who have same points quantity
    // than they are sorting by preferences
    private void groupAndSortByPriorities() {
        ArrayList< ArrayList<Student> > studentsGroupedByPoints = new ArrayList<>() ;
        Integer lastPointsAmount = -1;
        int i = -1;
        // create small subgroups of students with same preferences
        for (Student student : this.availableStudents) {
            // create new subgroup when last student has different
            // preference array
            if( !(lastPointsAmount.intValue() ==  student.getpoints()) ) {
                i++;
                lastPointsAmount = student.getpoints();
                studentsGroupedByPoints.add( new ArrayList<>());
            }
            studentsGroupedByPoints.get(i).add(student);
        }
        // create new array for sorted students
        this.availableStudents = new ArrayList<>();

        // for every subgroup sort students by points
        // add sorted students to table
        for (ArrayList<Student> studentGroup : studentsGroupedByPoints) {
            // sort
            studentGroup.sort(Student::comparePrioritySize);
            // add each subgroup to availableStudents array
            availableStudents.addAll(studentGroup);
        }
    }

    // function grouping students who have same preferences
    // than they are sorting by points
    private void groupAndSortByPoints() {
        ArrayList< ArrayList<Student> > studentsGroupedByPreferences = new ArrayList<>() ;
        ArrayList<Integer> lastPreference = new ArrayList<Integer>(0);
        int i = -1;
        // create small subgroups of students with same preferences
        for (Student student : this.availableStudents) {
            // create new subgroup when last student has different
            // preference array
            if( !lastPreference.equals( student.getpreference() ) ) {
                i++;
                lastPreference = student.getpreference();
                studentsGroupedByPreferences.add( new ArrayList<>());
            }
            studentsGroupedByPreferences.get(i).add(student);
        }
        // create new array for sorted students
        this.availableStudents = new ArrayList<>();

        // for every subgroup sort students by points
        // add sorted students to table
        for (ArrayList<Student> studentGroup : studentsGroupedByPreferences) {
            // sort
            studentGroup.sort(Student::compare);
            // add each subgroup to availableStudents array
            availableStudents.addAll(studentGroup);
        }

    }

    private void divideByPriorities()
    {
        if(availableStudents.size() == 0)
            return;
        // sort students by their priorities
        this.availableStudents.sort(Student::comparePrioritySize);
        // if user want to reorder students to get best match
        if(this.Priorities[1].getisActive())
            // sort subgroups
            this.groupAndSortByPoints();
        // move all students to proper schools
        this.moveToSchool();
    }

    private void moveToSchool()
    {
        Student student;
        for (School school : this.availableSchools) {
            for (int i = 0; i < this.availableStudents.size(); i++) {

                student = this.availableStudents.get(i);
                if (student.getpreference().contains(school.getId()) && !school.limitReached()) {
                    moveToSchool(school, student);
                    i--;
                }
            }
            // after school filling, reorder students
            school.sortByPoints();
        }
    }

    private void moveToSchool(School school, Student student)
    {
        school.getStudents().add(student);
        availableStudents.remove(student);
    }

}

/*Project Java*/

import java.util.Random; //Import package to use random 

//Hierarchy's class and the only public class
public class Hierarchy{
    //Auction method/function
    public static void auction(Artifacts[] art, String My_Movement, String My_Condition){
        for(int i=0; i<art.length; i++){ //N = art.length
            art[i].getIndex();                          //Calling method by 
            art[i].getInfo();                           //artifact class to print 
            art[i].evaluate(My_Movement, My_Condition); //what i want
        }
    }
    //Main
    public static void main(String []args){
        int N = Integer.parseInt(args[0]);  //Those 2 its sure that
        String My_Movement = args[1];       //i need them...you cannot skip
        String My_Condition;
        if(args.length == 3){ //If you dont give me a condition of the artifact i have to assign it as blank string
            My_Condition = args[2];
        }else{
            My_Condition = "";
        }
        Random random = new Random();
        Artifacts[] art = new Artifacts[N]; //Making Artifact array
        for(int i=0; i<N; i++){
            int I = random.nextInt(10);                                                                                         //
            int random_artifact = random.nextInt(2);                                                                            //Picking random values 
            int Index = random.nextInt(100), Year = random.nextInt(2022);                                                       //with nextInt to be an integer
            int Lenght = random.nextInt(20), Width = random.nextInt(20), Surface = Lenght*Width, Volume = random.nextInt(50);   //
            String[] random_creator = new String[]{"Pablo Picasso", "Vincent van Gogh", "Leonardo Davanci", "Michelangelo", "Claude Monet"}; //Array of names for the creators
            String[] random_movement = new String[]{"impressionism", "expressionism", "naturalism"}; //Array of what types of movements are valid
            String[] random_condition = new String[]{"bad", "good", "excellent"}; //Array of what conditions are valid
            String[] random_technique = new String[]{"oil", "aquarelle", "tempera"}; //Array of what techniques are valid
            String[] random_material = new String[]{"iron", "stone", "wood"}; //Array of what materials are valid
            String Creator = random_creator[random.nextInt(5)]+I; //Making the CreatorI
            String Movement = random_movement[random.nextInt(3)], Condition = random_condition[random.nextInt(3)]; //Picking 
            String Technique = random_technique[random.nextInt(3)], Material = random_material[random.nextInt(3)]; //random array[i]
            
            if(random_artifact == 0){ //Calling the constructor and assign it to a Artifact[]
                art[i] = new Paintings(Index, Year, Creator, Movement, Condition, Lenght, Width, Technique, Surface);  
            }else{                                                                                                    
                art[i] = new Sculptures(Index, Year, Creator, Movement, Condition, Volume, Material);
            }
        }
        Hierarchy.auction(art, My_Movement, My_Condition);
    }
}

//Artifact's class
class Artifacts{
    private final int index, year;  //Project's
    private final String creator;   //Variables

    //Artifact's Constructor
    Artifacts(int Index, int Year, String Creator){ 
        System.out.println("Creating an instance of Artifact");
        index = Index;      //
        year = Year;        //Initialize
        creator = Creator;  //
    }

    //Project's methods
    protected void getInfo(){System.out.println("The Creator is " + creator + ". The artifact was made in year " + year + ".");}
    protected void getIndex(){System.out.println("The Index number is " + index);}
    protected void evaluate(String Movement, String Condition){} //dummy to have access....artifact->masterpiece->paintings/sculpture
    protected void set_condition(String New_Condition){} //dummy to have access....artifact->masterpiece
}

//Masterpiece's class
class Masterpiece extends Artifacts{
    protected String movement, condition; //Project's variables

    //Masterpiece's Constructor
    Masterpiece(int Index, int Year, String Creator, String Movement, String Condition){ 
        super(Index, Year, Creator);                                //
        System.out.println("Creating an instance of Masterpiece");  //Initialize
        movement = Movement;                                        //
        condition = Condition;                                      //
    }
    
    //Project's methods
    @Override
    protected void getInfo(){
        super.getInfo(); //super = call parent's method 
        System.out.println("Its a " + movement + " art piece and the condition is " + condition + ".");
    }
    @Override
    protected void evaluate(String Movement, String Condition){super.evaluate(Movement, Condition);}
    @Override
    protected void set_condition(String New_Condition){
        condition = New_Condition;
    }
}

//Painting's class
class Paintings extends Masterpiece{
    private final int lenght, width, surface; //Project's
    private final String technique;           //variables

    //Painting's Constructor
    Paintings(int Index, int Year, String Creator, String Movement, String Condition, int Lenght, int Width, String Technique, int Surface){
        super(Index, Year, Creator, Movement, Condition);       //
        System.out.println("Creating an instance of Painting"); //
        lenght = Lenght;                                        //Initialize
        width = Width;                                          //
        technique = Technique;                                  //
        surface = Surface;                                      //
    }

    //Project's methods
    @Override
    protected void getInfo(){
        super.getInfo(); //super = call parent's method 
        System.out.println("This painting is : " + lenght + " meters tall and :" + width + " meters wide with a total area on the wall of : " + surface + " meters.");
        System.out.println("Last but not least the creator used " + technique + " to make this masterpiece.");
    }
    @Override
    protected void evaluate(String Movement, String Condition){
        if(Condition.equals("")){ //If you dont give me the condition when you run the programm i assign it manually
            Condition = "good";
        }
        if(super.movement.equals(Movement)){
            if(Condition.equals("good")){
                if((super.condition.equals(Condition)) || (super.condition.equals("excellent"))){
                    System.out.println("This artifact is Accepted");
                }else{
                    System.out.println("This artifact is Declined");
                }
            }else if((super.condition.equals(Condition))){
                System.out.println("This artifact is Accepted");
            }else{
                System.out.println("This artifact is Declined");
            }
        }else{
            System.out.println("This artifact is Declined");
        }
        System.out.println("---------------------------------------------");
    }
}

//Sculpture's class
class Sculptures extends Masterpiece{
    private int volume;         //Project's
    private String material;    //variables

    //Sculpture's constructor
    Sculptures(int Index, int Year, String Creator, String Movement, String Condition, int Volume, String Material){
        super(Index, Year, Creator, Movement, Condition);           //
        System.out.println("Creating an instance of Sculpture");    //Initialize
        volume = Volume;                                            //
        material = Material;                                        //
    }
    
    //Project's methods
    @Override
    protected void getInfo(){
        super.getInfo(); //super = call parent's method 
        System.out.println("This sculpture is taking " + volume + " meters space and its made by " + material + ".");
    }
    @Override
    protected void evaluate(String Movement, String Condition){
        if(Condition.equals("")){ //If you dont give me the condition when you run the programm i assign it manually
            Condition = "excellent";
        }
        if((super.movement.equals(Movement)) && (super.condition.equals(Condition))){
            System.out.println("This artifact is Accepted");
        }else{
            System.out.println("This artifact is Declined");
        }
        System.out.println("---------------------------------------------");
    }
}
class Vehicle{

    void move(){
        System.out.println("Vehicle is Moving");
    }
}

class Car extends Vehicle{
    @Override 
    void move(){
        System.out.println("Car is moving on the road");
    }
}

class Motorcycle extends Vehicle{
    @Override 
    void move(){
        System.out.println("Motorcycle is moving through traffic");
    }
}

class Bus extends Vehicle{
    @Override 
    void move(){
        System.out.println("Bus is transporting passengers");
    }
}


public class Act2 {
    public static void main(String[] args){
        Vehicle toyota = new Car();
        Vehicle jl = new Bus();
        Vehicle mio = new Motorcycle();

        toyota.move();
        mio.move();
        jl.move();
    }
    
}

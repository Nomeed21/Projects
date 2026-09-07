

import java.util.Scanner;
 class Laptop {
   String brand;
   int width;
   float price;
   String RAM_name;
   String RAM_type;
   String GPU_name;
   String CPU_Name;
   int RAM_size;
   int Storage_Size;
   int CPU_gen;

   Laptop(){
    System.out.println("Enter Laptop Specifications(e.g Brand Name, RAM size, GPU Name");
   }

   Laptop(String brand){
     this.brand = brand;
   }

   Laptop(String brand, float price){
     this.brand = brand;
     this.price = price;
   }
   
   Laptop(String brand, String CPU_name, String GPU_name){
     this.brand = brand;
     this.CPU_Name = CPU_name;
     this.GPU_name = GPU_name;
   }

    Laptop(String brand, String CPU_name, String GPU_name, int Storage_Size){
     this.brand = brand;
     this.CPU_Name = CPU_name;
     this.GPU_name = GPU_name;
     this.Storage_Size = Storage_Size;
   }

   Laptop(String brand, String CPU_name, String GPU_name, int Storage_Size, int width){
     this.brand = brand;
     this.CPU_Name = CPU_name;
     this.GPU_name = GPU_name;
     this.Storage_Size = Storage_Size;
     this.width = width;
   }

   Laptop(String brand,
   int width,
   float price,
   String RAM_name,
   String RAM_type,
   String GPU_name,
   String CPU_Name,
   int RAM_size,
   int Storage_Size,
   int CPU_gen){
        this.brand = brand;
        this.width = width;
        this.price = price;
        this.RAM_name = RAM_name;
        this.RAM_type = RAM_type;
        this.GPU_name = GPU_name;
        this.CPU_Name = CPU_Name;
        this.RAM_size = RAM_size;
        this.Storage_Size = Storage_Size;
        this.CPU_gen = CPU_gen;
   }


   void gaming(){
        System.out.println("The laptop is currently playing games...");
   }

   void editing(){
    System.out.println("The laptop is currently editing videos...");
   }

   void coding(){
    System.out.println("The laptop is currently programming apps...");
   }

   void generation(){
    System.out.println("Generating image...");
   }

   void runApps(){
    System.out.println("The laptop is currently running apps...");
   }

   void status(){
    System.out.println("Brand Name: " + brand);
    System.out.println("CPU Name: " + CPU_Name);
    System.out.println("CPU Generation: " + CPU_gen);
    System.out.println(" GPU Name: " + GPU_name);
    System.out.println("Storage: " + Storage_Size);
    System.out.println("RAM Name: " + RAM_name);
    System.out.println("RAM Type: " + RAM_type);
    System.out.println("RAM Size: "+ RAM_size);
    System.out.println("Width: " + width);
    System.out.println("Laptop price: " + price);
   }

}

public class Main{
    public static void main(String[] args){
        boolean running = true;
        Scanner sc = new Scanner(System.in);
        while(running){
            String brand;
            int width;
            float price;
            String RAM_name;
            String RAM_type;
            String GPU_name;
            String CPU_Name;
            int RAM_size;
            int Storage_Size;
            int CPU_gen;
            int choice;
            choice = 0;

            System.out.println("MENU");
            System.out.println("[1] Brand only");
            System.out.println("[2] Brand and Price");
            System.out.println("[3] Brand, CPU, and GPU");
            System.out.println("[4] Brand, CPU, GPU, and Storage");
            System.out.println("[5] All specs");
            System.out.println("[6] Exit");
            System.out.println("Input choice: ");
            choice = sc.nextInt();
            sc.nextLine();
            switch(choice){
                case 1:
                    System.out.println("Enter brand Name: ");
                    brand = sc.nextLine();
                    Laptop l1 = new Laptop(brand);
                    l1.status();
                    break;

                case 2:
                    System.out.println("Enter brand Name: ");
                    brand = sc.nextLine();
                    System.out.println("Enter price: ");
                    price = sc.nextFloat();
                    Laptop l2 = new Laptop(brand, price);
                    l2.status();
                    break;

                case 3:
                    System.out.println("Enter brand Name: ");
                    brand = sc.nextLine();
                    System.out.println("Enter CPU Name: ");
                    CPU_Name = sc.nextLine();
                    System.out.println("Enter GPU Name: ");
                    GPU_name = sc.nextLine();
                    Laptop l3 = new Laptop(brand, CPU_Name, GPU_name);
                    l3.status();
                    break;

                case 4:
                    System.out.println("Enter brand Name: ");
                    brand = sc.nextLine();
                    System.out.println("Enter CPU Name: ");
                    CPU_Name = sc.nextLine();
                    System.out.println("Enter GPU Name: ");
                    GPU_name = sc.nextLine();
                    System.out.println("Enter Storage: ");
                    Storage_Size = sc.nextInt();
                    Laptop l4 = new Laptop(brand, CPU_Name, GPU_name, Storage_Size);
                    l4.status();
                    break;

                case 5:
                    System.out.println("Enter brand Name: ");
                    brand = sc.nextLine();
                    System.out.println("Enter CPU Name: ");
                    CPU_Name = sc.nextLine();
                    System.out.println("Enter CPU Generation: ");
                    CPU_gen = sc.nextInt();
                    sc.nextLine();
                    System.out.println("Enter GPU Name: ");
                    GPU_name = sc.nextLine();
                    System.out.println("Enter Storage: ");
                    Storage_Size = sc.nextInt();
                    sc.nextLine();
                    System.out.println("Enter laptop price: ");
                    price = sc.nextFloat();
                    sc.nextLine();
                    System.out.println("Enter RAM Name: ");
                    RAM_name = sc.nextLine();
                    System.out.println("Enter RAM Type: ");
                    RAM_type = sc.nextLine();
                    System.out.println("Enter RAM Size: ");
                    RAM_size = sc.nextInt();
                    System.out.println("Enter Width: ");
                    width = sc.nextInt();
                    sc.nextLine();
                    Laptop l5 = new Laptop( brand,width,price,RAM_name,RAM_type,GPU_name,CPU_Name,RAM_size,Storage_Size, CPU_gen);
                    l5.status();
                    break;
                
                case 6:
                    running = false;
                    break;

                default:
                    System.out.print("Invalid choice!");
            }
        }
    }

}
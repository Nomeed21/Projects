package Act1;
public class Laptop {
   String brand;
   int laptop_dimensions;
   float price;
   String RAM_name;
   String RAM_type;
   String GPU_name;
   String CPU_Name;
   int RAM_size;
   int Storage_Size;
   int CPU_gen;

   Laptop(){
    System.out.println("Congrats on your new laptop!");
   }
   Laptop(String brand,
   int laptop_dimensions,
   float price,
   String RAM_name,
   String RAM_type,
   String GPU_name,
   String CPU_Name,
   int RAM_size,
   int Storage_Size,
   int CPU_gen){
        this.brand = brand;
        this.laptop_dimensions = laptop_dimensions;
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

}

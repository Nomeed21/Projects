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

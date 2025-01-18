

/*---------------Software and Board Version----------------*/
String version = "V0.0"; //Software Version, Major.Minor.Patch
String device_name = "Nucleo-NUCLEO-L432KC"; //Board version
/*---------------------------------------------------------*/


/*----------------------------------------------------- commands----------------------------------------------------------------*/
String commands[6] = {"*IDN?",               //get Software and Board Version.
            "exemple_function1 ",           //exemple function 1 that take an argument
            "exemple_function2",          //exemple function 2 that doesn't take an argument     
                      };// add commands only at the end of the array!!!!
/*-----------------------------------------------------------------------------------------------------------------------------------*/



/*-------------------------------------------------------read_serial----------------------------------------------------------------------------*/
/* Reading serial commands from PC.
 *          
 */
 void read_serial(void)
 {
  if(Serial.available())
  {
    String cmd = Serial.readStringUntil('\n');

    if(cmd == commands[0]) //get Software and Board Version
    {
     send_IDN();
    }
    else if(cmd.substring(0, commands[1].length()) == commands[1]) //Do function 1
    { 
      String number = cmd.substring(commands[1].length(), cmd.length()); 
      int n = number.toInt(); // convert to int
      exemple_function1(n);
    }
     else if(cmd == commands[2]) Do function 2   
    {
      exemple_function2();
    }
    else
    {
     Serial.print("INFO: invalid command");
     Serial.print(cmd);
    
    }
  }
 }
/*------------------------------------------------------------functions------------------------------------------------------------------*/


void exemple_function1(int n)
{
  pass
}


void exemple_function2()
{
  pass
}

void send_IDN()
{
  Serial.print("INFO:");
  Serial.print(device_name);
  Serial.print(";");
  Serial.println(version);
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/

void setup() 
{
Serial.begin(115200); 
}

void loop() 
{
read_serial();                     
}

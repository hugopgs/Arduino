

/*---------------Software and Board Version----------------*/
String version = "V1.1.3"; //Software Version, Major.Minor.Patch
String device_name = "Nucleo-NUCLEO-L432KC"; //Board version
/*---------------------------------------------------------*/

/*----------------------------------------------------- Relais trigger pin----------------------------------------------------------------*/
const byte relay7 = PB4;
const byte relay6 = PB5;
const byte relay5 = PA11;
const byte relay4 = PA8; 
const byte relay3 = PB1;
const byte relay2 = PB6;
const byte relay1 = PB7;
const byte relay0 =PB0 ;
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------- State of each pin----------------------------------------------------------------*/
bool STATUS[8]={true,true, true,true,true,true,true,true}; //1: relais NOT triggered, 0: Relais triggered.
/*-----------------------------------------------------------------------------------------------------------------------------------*/




/*----------------------------------------------------- commands----------------------------------------------------------------*/
String commands[6] = {"*IDN?",               //get Software and Board Version.
            "CONFigure:RELAy:ON ",           //Set relay to ON : Trigger the relays pin,(Negative voltage).
            "CONFigure:RELAy:OFF ",          //Set relay to OFF : (Positive voltage).
            "READ:RELAy:Status",            //Get relay status : 1: relay NOT triggered (Positive voltage), 0: Relais triggered (Negative voltage).           
               "CONFigure:RELAy:ALL ON",      //Set All relay to ON : Trigger all  the relais pin,(Negative voltage).
               "CONFigure:RELAy:ALL OFF"     //Set All relay to OFF : (Positive voltage).
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
    else if(cmd.substring(0, commands[1].length()) == commands[1]) //Set relay to ON : Trigger the relays pin,(Negative voltage).
    { 
      String number = cmd.substring(commands[1].length(), cmd.length()); 
      int n = number.toInt(); // convert to int
      set_relay(n, LOW);
    }
    else if(cmd.substring(0, commands[2].length()) == commands[2]) ////Set relay to OFF : (Positive voltage).
    {
      String number = cmd.substring(commands[2].length(), cmd.length());
      int n = number.toInt(); // convert to int
      set_relay(n, HIGH);
    }
     else if(cmd == commands[3]) // //Get relay status : 1: relay NOT triggered (Positive voltage), 0: Relais triggered (Negative voltage).        
    {
      send_relay_status();
    }
    else if (cmd == commands[4])//Set All relay to ON : Trigger all  the relais pin,(Negative voltage).
    {
     set_all(LOW);
     Serial.println("INFO: All relay ON");
    }
    else if (cmd == commands[5]) //Set All relay to OFF : (Positive voltage).
    {
     set_all(HIGH);
     Serial.println("INFO: All relay OFF");
    }
    else
    {
     Serial.print("INFO: invalid command");
     Serial.print(cmd);
    
    }
  }
 }
/*-----------------------------------------------------------------------------------------------------------------------------------*/



/* change the state of one pin
pin [int]:  Position of the pin 
voltage [bool]: state of the pin, LOW or HIGH
*/
void Modif_state(int pin, bool voltage)
{
 pinMode(pin, OUTPUT);
digitalWrite(pin,voltage);
}

/*Set all relay
 * 
 * voltage [bool]: state of the relay. valid values: 0, 1
*/
void set_all(bool voltage)
{
Modif_state(relay0,voltage);
Modif_state(relay1,voltage);
Modif_state(relay2,voltage);
Modif_state(relay3,voltage);
Modif_state(relay4,voltage);
Modif_state(relay5,voltage);
Modif_state(relay6,voltage);
Modif_state(relay7,voltage);
for (int i=0; i<8 ;i++)
  {
   STATUS[i]= voltage;
  }
}

/*Set specific relay
 *
 * relay [int]: relay number. valid values: 0…7
 * status [bool]: state of the relay. valid values: 0, 1
*/
void set_relay(int n, bool voltage)
{
   STATUS[n]= voltage;
   
   if(n == 0) 
    {
     Modif_state(relay0, voltage);
     Serial.print("INFO: relay0 set to ");
     Serial.println(voltage);
    }
    
  
   else if(n == 1) 
    {
     Modif_state(relay1, voltage);
     Serial.print("INFO: relay1 set to ");
     Serial.println(voltage);
     
    }
  
   else if(n == 2) 
    {
     Modif_state(relay2, voltage);
     Serial.print("INFO: relay2 set to ");
     Serial.println(voltage);
    }
  
  else if(n == 3) 
    {
      Modif_state(relay3, voltage);
      Serial.print("INFO: relay3 set to ");
      Serial.println(voltage);
    }
  
  else if(n == 4) 
    {
      Modif_state(relay4, voltage);
      Serial.print("INFO: relay4 set to ");
      Serial.println(voltage);
    }
  
  else if(n == 5) 
    {
      Modif_state(relay5, voltage);
      Serial.print("INFO: relay5 set to ");
      Serial.println(voltage);
    }
  
  else if(n == 6) 
    {
      Modif_state(relay6, voltage);
      Serial.print("INFO: relay6 set to ");
      Serial.println(voltage);
    }
  
  else if(n == 7) 
    {
      Modif_state(relay7, voltage);
      Serial.print("INFO: relay7 set to ");
      Serial.println(voltage);
    }
  
  else
  {
  Serial.println("INFO: index out of range: ");
  }
  
}


/*get specific relay state
 *
 relay [int]: relay number. valid values: 0…7
*/

void send_relay_status()
{
Serial.print("DR0:");
Serial.print(STATUS[0]);
Serial.print(";R1:");
Serial.print(STATUS[1]);
Serial.print(";R2:");
Serial.print(STATUS[2]);
Serial.print(";R3:");
Serial.print(STATUS[3]);
Serial.print(";R4:");
Serial.print(STATUS[4]);
Serial.print(";R5:");
Serial.print(STATUS[5]);
Serial.print(";R6:");
Serial.print(STATUS[6]);
Serial.print(";R7:");
Serial.print(STATUS[7]);
Serial.println("|");
}


void send_IDN()
{
  Serial.print("INFO:");
  Serial.print(device_name);
  Serial.print(";");
  Serial.println(version);
}

void setup() 
{
Serial.begin(115200); 
}

void loop() 
{
read_serial();                     
}

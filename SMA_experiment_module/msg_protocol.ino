// header timestamp data


//Setup message bytes

byte header;
byte timestamp;
byte data;

void msg_sender(int datatype, float dataval){
  Serial.print(datatype);
  Serial.print(",");
  Serial.println(dataval);
}

void msg_handler(){
//  //Read Buffer
//  if (Serial.available() == 5) 
//  {
//    //Read buffer
//    inputByte_0 = Serial.read();
//    delay(100);    
//    inputByte_1 = Serial.read();
//    delay(100);      
//    inputByte_2 = Serial.read();
//    delay(100);      
//    inputByte_3 = Serial.read();
//    delay(100);
//    inputByte_4 = Serial.read();   
//  }
//  //Check for start of Message
//  if(inputByte_0 == 16)
//  {       
//       //Detect Command type
//       switch (inputByte_1) 
//       {
//          case 127:
//             //Set PIN and value
//             switch (inputByte_2)
//            {
//              case 4:
//                if(inputByte_3 == 255)
//                {
//                 // digitalWrite(ledPin_3, HIGH); 
//                  break;
//                }
//                else
//                {
//                  //digitalWrite(ledPin_3, LOW); 
//                  break;
//                }
//              break;
//            } 
//            break;
//          case 128:
//            //Say hello
//            Serial.print("HELLO FROM ARDUINO");
//            break;
//        } 
//        //Clear Message bytes
//        inputByte_0 = 0;
//        inputByte_1 = 0;
//        inputByte_2 = 0;
//        inputByte_3 = 0;
//        inputByte_4 = 0;
//        //Let the PC know we are ready for more data
//        Serial.print("-READY TO RECEIVE");
//  }
}

void send_msg()
{
  msg_sender(LOAD,load_data);
  msg_sender(DISP,disp_data);
  msg_sender(TEMP,temp_data);
  msg_sender(CURRENT,get_current());
  msg_sender(VOLTAGE,get_voltage());
  msg_sender(ALTITUDE,get_altitude());
}


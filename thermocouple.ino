void get_thermocouple_data()
{
//   Serial.print("C = "); 
//   Serial.println(thermocouple.readCelsius());
   temp_data = thermocouple.readCelsius();
   //Serial.print("F = ");
   //Serial.println(thermocouple.readFahrenheit());
}

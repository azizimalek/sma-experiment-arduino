  

float get_voltage()
{
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0; // see text
  vin = vout / (R2/(R1+R2)); 
  //Serial.println(vin,2);
  return vin;
}

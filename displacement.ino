void get_displacement_data()
{
  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  disp_data = sensorValue;
}


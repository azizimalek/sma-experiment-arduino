void task_scheduler_setup(){
  sensor_data_schedule.init();
  pwm_out_schedule.init();
  Serial.println("Initialized scheduler");
  
  sensor_data_schedule.addTask(loadcell_t);
  sensor_data_schedule.addTask(displacement_t);
  sensor_data_schedule.addTask(thermo_t);
  pwm_out_schedule.addTask(pwm_out_t);

  delay(1000);
  
  loadcell_t.enable();
  Serial.println("Enabled Load Cell Sensor");
  displacement_t.enable();
  Serial.println("Enabled Displacement sensor");
  thermo_t.enable();
  Serial.println("Enabled thermocouple sensor");
  pwm_out_t.enable();
  Serial.println("Enabled SMA PWM output");  
}

void loadcellCallback(){
   get_load_cell_data();
}

void displacementCallback(){
  get_displacement_data();
}

void thermoCallback(){
  get_thermocouple_data();
}


void smaCallback(){
 // sma_output();
}


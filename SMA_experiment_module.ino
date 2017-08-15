//--------------------------------------------------------------
//This program is for SMA wire experiment module specialized for
//high altitude balloon application
//Written by Azizi
//Copyright of Robotic Space Technology 2017
//--------------------------------------------------------------

//include library
#include "max6675.h" //for thermocouple
#include "HX711.h"   //for load cell
#include "TaskScheduler.h" //to schedule loop task

// Callback methods prototypes
void loadcellCallback();
void displacementCallback();
void thermoCallback();

//loop task
Task loadcell_t(10, TASK_FOREVER, &loadcellCallback);
Task displacement_t(10, TASK_FOREVER, &displacementCallback);
Task thermo_t(400, TASK_FOREVER, &thermoCallback);

//library declaration
//--------------------------------------------------------------
//Load cell declaration
HX711 scale;

//Thermocouple declaration
int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

//Position potentiomenter
int sensorPin = A5;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
//--------------------------------------------------------------

//Global Variable declaration
float load_data = 0.0;
float temp_data = 0.0;
float disp_data = 0.0;


//Scheduler task
Scheduler sensor_data_schedule;

void setup() {
  Serial.begin(38400);
  load_cell_setup();
  task_scheduler_setup();
}

void loop() {
  sensor_data_schedule.execute();
  Serial.print(load_data);
  Serial.print("\t");
  Serial.print(temp_data);
  Serial.print("\t");
  Serial.println(disp_data);
}

void task_scheduler_setup(){
  sensor_data_schedule.init();
  Serial.println("Initialized scheduler");
  
  sensor_data_schedule.addTask(loadcell_t);
  sensor_data_schedule.addTask(displacement_t);
  sensor_data_schedule.addTask(thermo_t);

  delay(5000);
  
  loadcell_t.enable();
  Serial.println("Enabled Load Cell Sensor");
  displacement_t.enable();
  Serial.println("Enabled Displacement sensor");
  thermo_t.enable();
  Serial.println("Enabled thermocouple sensor");
  
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



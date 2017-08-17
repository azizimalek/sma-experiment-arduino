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
#include "Timer.h"
#include <PID_v1.h>
//#include <VarSpeedServo.h>

// header definition
#define LOAD 1
#define DISP 2
#define TEMP 3
#define CURRENT 4
#define VOLTAGE 5
#define P_CONTROL 6
#define I_CONTROL 7
#define D_CONTROL 8
#define ALTITUDE 9
#define TIME 10

// Callback methods prototypes
void loadcellCallback();
void displacementCallback();
void thermoCallback();
void smaCallback();

//Timer declaration
Timer t_pwm;


//task looping declaration
Task loadcell_t(10, TASK_FOREVER, &loadcellCallback);
Task displacement_t(10, TASK_FOREVER, &displacementCallback);
Task thermo_t(400, TASK_FOREVER, &thermoCallback);
Task pwm_out_t(400, TASK_FOREVER, &smaCallback);

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

//current sensor variable
const int analogIn = A4;
int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module
int RawValue= 0;
int ACSoffset = 2500; 
double Voltage = 0;
double Amps = 0;

//voltage sensor
int analogInput = A6;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; //  
float R2 = 7500.0; // 
int value = 0;

//sma parameter
int sma_pwm = 500;
int sma_pulse = 10; //in microseconds

//SMA out PID parameter
double Setpoint, Input, Output;
double Kp=30, Ki=10, Kd=30;
PID sma_temp_PID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//indicator
int LED_ind_on = 1000;
int LED_ind_off = 500;

//Scheduler task
Scheduler sensor_data_schedule;
Scheduler pwm_out_schedule;

void setup() {
  Serial.begin(38400);
  load_cell_setup();
  task_scheduler_setup();
  //set_pwm_pin();
   pinMode(analogInput, INPUT);
  pwm_setup();

   Input = 0.0;
   Setpoint = 100;
   sma_temp_PID.SetOutputLimits(0, 255);
   sma_temp_PID.SetMode(AUTOMATIC); //start PID

  
}

void loop() {
  sensor_data_schedule.execute();
  pwm_out_schedule.execute();
  msg_sender(LOAD,load_data);
  msg_sender(DISP,disp_data);
  msg_sender(TEMP,temp_data);
  t_pwm.update();
  //analogWrite(3, 255);
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Serial.println(Amps,3);
  value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; // see text
   vin = vout / (R2/(R1+R2)); 
   Serial.println(vin,2);

  Input = temp_data;
  sma_temp_PID.Compute();
  
  
  analogWrite(3, Output);
}

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



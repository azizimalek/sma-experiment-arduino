//--------------------------------------------------------------
//This program is for SMA wire experiment module specialized for
//high altitude balloon application
//Written by Azizi
//Copyright of Robotic Space Technology 2017
//--------------------------------------------------------------

//include library
#include <max6675.h> //for thermocouple
#include <HX711.h>   //for load cell
#include <TaskScheduler.h> //to schedule loop task
#include <Timer.h>
#include <PID_v1.h>
//#include <VarSpeedServo.h>

// header definition
//data definition
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

//pin definition
#define SMA_PIN 3

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
  light_pwm_setup();
  PID_setup();
}

void loop() {
  sensor_data_schedule.execute();
  pwm_out_schedule.execute();
  send_msg();
  t_pwm.update();
  //analogWrite(3, 255);
  Input = temp_data;
  sma_temp_PID.Compute();
  analogWrite(SMA_PIN, Output);
}





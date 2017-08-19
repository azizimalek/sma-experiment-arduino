void pwm_out(int pin, int val)
{
   analogWrite(pin, val);
}

void set_pwm_pin()
{
  pinMode(4, OUTPUT);
}

void sma_output()
{
  pwm_out(4, 2);
  Serial.println("SMA low current");
  
}

void light_pwm_setup()
{
  pinMode(4, OUTPUT);
  t_pwm.every(LED_ind_on, light_pwm_High);
}



void light_pwm_High()
{
  t_pwm.after(LED_ind_off, light_pwm_Low);
  digitalWrite(4,HIGH);
}


void light_pwm_Low()
{
  digitalWrite(4,LOW);
}

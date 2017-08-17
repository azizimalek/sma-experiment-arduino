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

void pwm_setup()
{
  pinMode(4, OUTPUT);
  t_pwm.every(LED_ind_on, pwm_High);
}



void pwm_High()
{
  t_pwm.after(LED_ind_off, pwm_Low);
  digitalWrite(4,HIGH);
}


void pwm_Low()
{
  digitalWrite(4,LOW);
}

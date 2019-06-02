int l1 = 10;  //pin1 of leftMotor
int l2 = 7;  //pin2 of leftMotor

int r1 = 9; //pin1 of rightMotor
int r2 = 8; //pin2 of rightMotor

const int Max = 180;

// pins of IRarray
int p1 =  2;
int p2 =  3;
int p3 =  4;
int p4 =  5;
int p5 =  6;

int a[5];  //array to store sensor values

//PID variables
int error = 0;
int derivative = 0;
int integral = 0;
int lastError = 0;
float pidValue;
//PID constants
float Kp;
float Kd;
float Ki;



void setup()
{
  pinMode(l1, OUTPUT);
  pinMode(l2, LOW);
  pinMode(r1, OUTPUT);
  pinMode(r2, LOW);
  
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);
  pinMode(p4, INPUT);
  pinMode(p5, INPUT);

  Serial.begin(9600);
}


void loop()
{
  
  PID();
  //Serial.println(readSensor());
  
  
}



int readSensor()  //read the position of the bot
{
  for(int i=0; i<5; i++)
  {
    a[i] =!digitalRead(i+3); // read each sensor pin
    //Serial.println(a[i]);
  }
  int Position = (((100*a[0]) + (200*a[1]) + (300*a[2]) + (400*a[3]))/(a[0] + a[1] +a[2] + a[3]));  //average of the scaled sensor values
  return Position;    
  //Serial.println(Position); //print position
}

void PID()
{
  
  
  int pos = readSensor();
  error = pos - 250;
  derivative = error - lastError;
  integral = error + integral;

  lastError = error;

  Kp = 15;
  Kd = 1;
  Ki = 0;

  pidValue = (Kp*error) + (Kd*derivative) + (Ki*integral);

  Serial.println(pidValue);

  //Max = 200; // Maximum speed
  
  if(pidValue > Max)
  {
    pidValue = Max;
  }
  if(pidValue< -Max)
  {
    pidValue = -1*Max;
  }

  
  if(pidValue<0)
  {
    setMotors(Max, Max-pidValue);
  }
  else
  {
    setMotors(Max+pidValue, Max);
  }

  
  
  
  
}

void setMotors(int l, int r)
{
  Serial.println(l);
  Serial.println(r);
  analogWrite(l1,l);
  analogWrite(r1,r);
}

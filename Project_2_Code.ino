//calibrated values for each offset and sensitivity
float offset = 1.65;
float sens = 3.3/32;

float zAcc = 0;
float yAcc = 0;
float yAccPrev = 0; //holds previous values
float xAcc = 0;
float zV = 0;
float yV = 0;
float xV = 0;
int goodCount;
int badCount;
bool up = false;
bool good = true;
bool distRead = false;
float distance;
 
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); //x
  pinMode(A1, INPUT); //y
  pinMode(A2,INPUT); //z
}

void loop() {
  //read accelerometer to monitor direction of movement
  //read acceleration in z
  zV = (analogRead(A2))*(5.0/1023); //get voltage
  zAcc = (zV - offset)/sens;
  Serial.print("Z acceleration is ");
  Serial.println(zV);
  delay(500);
  //read acceleration in y
  yV = (analogRead(A1))*(5.0/1023); //get voltage
  yAccPrev = yAcc; //hold previous value
  yAcc = (yV - offset)/sens;
  Serial.print("Y acceleration is ");
  Serial.println(yV);
  delay(500);
  //read acceleration in x
  xV = (analogRead(A0))*(5.0/1023); //get voltage
  xAcc = (xV - offset)/sens;
  Serial.print("X acceleration is ");
  Serial.println(xV);
  delay(500);
  if (xAcc > 0.3)
  {
    badCount++;
  }

  //Y should not move, else bad rep
  if (abs(yAcc) > 0.3)
  {
    good = false;
  }

  if (abs(zAcc) > 0.9)
  {
    up = false; //down position
    distRead = false; //reset
  }

  while (xAcc < -0.9)
  {
    if(up == false && good == true)
    {
      if (distance < 2) //distance < 2 inches
      {
          if (distRead = false)
          { 
            goodCount++; //good rep completed
            up = true; //up position reached
            good = true; //still a good rep
            distRead = true; //distanc has been read
          }
          if (distRead = true)
          {
            //arm has not gone all the way down
            badCount++;
          }
      }     
    }
    else if(up == true || good == false)
    {
      badCount++;     
      good = true; 
    }
  }
}

/* 
   Read in audio signal and display min, max, and the
   current value being read. Open Serial Monitor to see 
   the values.

   We subtract 409 because we've biased the signal with 2V, 
   so we remove 2V equivalent value from the signal read in.
 */

int soundPin = A0;
signed long sum = analogRead(A0);
signed long minimum = sum;
signed long maximum = sum;
 
void setup()
{
  Serial.begin(115200);
}
 
void loop()
{ 
    sum = analogRead(A0) - 409;

    if(sum < minimum)
      minimum = sum;
     else if(sum > maximum)
      maximum = sum;

    Serial.print("Min = ");
    Serial.print(minimum);
    Serial.print("\tMax = ");
    Serial.print(maximum);
    Serial.print("\tCurrent= ");
    Serial.println(sum);
}

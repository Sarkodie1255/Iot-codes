const int buttonPin=5;
const int ledPin=4;

int buttonState = 0;

void setup() {
 Serial.begin(115200);
 pinMode(buttonPin, INPUT);
 pinMode(ledPin, OUTPUT);


}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if (buttonState == HIGH){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }

}

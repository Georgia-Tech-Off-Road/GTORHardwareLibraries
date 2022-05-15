#define BAUD 115200

#define S1 Serial
#define S2 Serial5

void setup() {
  // put your setup code here, to run once:
  S1.begin(BAUD);
  S2.begin(BAUD);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(S1.available()) {
    S2.write(S1.read());
  }
  while(S2.available()) {
    S1.write(S2.read());
  }
}

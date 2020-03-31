

int x = 2000;

void setup() {
Serial.begin(9600);

byte top = x >> 8;
byte bot = x & 0x00FF;
Serial.println(top);
Serial.println(bot);
Serial.println(x, HEX);


int setpoint = (top << 8) | bot;
Serial.println(setpoint);
}


void loop() {
}

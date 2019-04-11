void setup() {
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWriteFast(13, HIGH);
  digitalWriteFast(14, HIGH);
  digitalWriteFast(15, HIGH);
  digitalWriteFast(16, HIGH);
}

boolean keyState[12][12];
int note;
int channel;

void loop() {
  for (int row = 14; row <= 16; row++) {
    digitalWrite(row, LOW);
    delayMicroseconds(20);
    for (int col = 1; col <= 12; col++) {
      int sensorVal = digitalRead(col);
      if (sensorVal != keyState[row - 14][col - 1]) {
        note = 59 + col + (row - 17) * 12;
        if (!sensorVal) {
          usbMIDI.sendNoteOn(note, 99, 3);
        } else {
          usbMIDI.sendNoteOff(note, 99, 3);
        }
        keyState[row - 14][col - 1] = sensorVal;
      }
    }
    digitalWrite(row, HIGH);
    delayMicroseconds(20);
  }
}

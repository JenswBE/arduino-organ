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
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  digitalWriteFast(13, HIGH);
  digitalWriteFast(14, HIGH);
  digitalWriteFast(15, HIGH);
  digitalWriteFast(16, HIGH);
  digitalWriteFast(17, HIGH);
  digitalWriteFast(18, HIGH);
  digitalWriteFast(19, HIGH);
  digitalWriteFast(20, HIGH);
  digitalWriteFast(21, HIGH);
  digitalWriteFast(22, HIGH);
  digitalWriteFast(23, HIGH);
  digitalWriteFast(24, HIGH);
  digitalWriteFast(25, HIGH);
}

boolean keyState[12][12];
int note;
int channel;

void loop() {
  for (int row = 14; row <= 25; row++) {
    digitalWrite(row, LOW);
    delayMicroseconds(20);
    for (int col = 1; col <= 12; col++) {
      int sensorVal = digitalRead(col);
      if (sensorVal != keyState[row - 14][col - 1]) {
        if (row < 20) {
          channel = 1;
          note = 61 - col - (row - 17) * 12;
        } else {
          channel = 2;
          note = 61 - col - (row - 23) * 12;
        }
        if (!sensorVal) {
          usbMIDI.sendNoteOn(note, 99, channel);
        } else {
          usbMIDI.sendNoteOff(note, 99, channel);
        }
        keyState[row - 14][col - 1] = sensorVal;
      }
    }
    digitalWrite(row, HIGH);
    delayMicroseconds(20);
  }
}

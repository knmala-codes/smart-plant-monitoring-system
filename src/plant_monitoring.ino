void loop() {
  ArduinoCloud.update();
  delay(300); // Delay of amount equal to sampling period

  humidity = dht.readHumidity();      // Get humidity value
  temperature = dht.readTemperature(); // Get temperature value

  soil_Moisture = analogRead(A0);
  soil_Moisture = map(soil_Moisture, 500, 1023, 100, 1);
}

/*
Since Relay is READ_WRITE variable, onRelayChange() is
executed every time a new value is received from IoT Cloud.
*/

void onRelayChange() {
  // Add your code here to act upon Relay change

  if (relay) {
    digitalWrite(D0, HIGH);
  } 
  else {
    digitalWrite(D0, LOW);
  }
}
boolean Auto() {
  if (digitalRead(7) == 0) {
    traverse.stop();
    traverse.move(flipper * 5000);
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    delay(500);
    traverse.setCurrentPosition(0);
    traverse.setSpeed(traverse_speed);
    
    return false;
  }
  else {
    return true;
  }
}


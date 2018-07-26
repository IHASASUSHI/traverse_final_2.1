void Test_Run() {
  winder.setMaxSpeed(winder_speed);
  winder.setSpeed(winder_speed);
  if (traverse.distanceToGo() == 0 && idx == 1) {
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    traverse.moveTo(goal[idx]); // Change dir between goal positions
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    digitalWrite(LED_BUILTIN, idx); // LED off in one direction, LED on in opposite dir
    idx = !idx; //! - logical; !0=1,!1 =0
  }
  if (traverse.distanceToGo() == 0 && idx == 0) {
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    traverse.moveTo(goal[idx]);
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(-traverse_speed);
    digitalWrite(LED_BUILTIN, idx);
    idx = !idx;
  }
}
void Run() {
  if (traverse.distanceToGo() == 0 && idx == 1) {
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    traverse.moveTo(goal[idx]); // Change dir between goal positions
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    digitalWrite(LED_BUILTIN, idx); // LED off in one direction, LED on in opposite dir
    idx = !idx; //! - logical; !0=1,!1 =0
  }
  if (traverse.distanceToGo() == 0 && idx == 0) {
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    traverse.moveTo(goal[idx]);
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(-traverse_speed);
    digitalWrite(LED_BUILTIN, idx);
    idx = !idx;
  }
  if(!winder.isRunning()) {
    traverse.stop();
    Start_spinning = false;
  }
}


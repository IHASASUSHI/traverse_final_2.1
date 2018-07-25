void Manual_Control () {
  if (val[1] == 1) {
    traverse.move(flipper * -100);
    traverse.setSpeed(-2000);
    traverse.setMaxSpeed(-2000);
  }
  if (val[1] == 2) {
    traverse.move(flipper * 100);
    traverse.setSpeed(2000);
    traverse.setMaxSpeed(2000);
  }
  if (val[1] == 3) {
    winder.move(flipper * 100);
  }
  if (val[1] == 4) {
    winder.move(flipper * -100);
  }
  if (val[1] == 5) {
    traverse.setCurrentPosition(0);
    traverse.setSpeed(traverse_speed);
  }
  if (val[1] == 6) {
    Auto_Calibrate = true;
  }
  if (val[1] == 7) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    traverse.moveTo(flipper * u.ival);
  }
}

void Speed_Settings () {
  if (val[1] == 0) {
    traverse.stop();
    winder.stop();
  }
  if (val[1] == 1) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    winder_speed = u.ival;
  }
  if (val[1] == 2) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    traverse_speed = u.ival;
    traverse.stop();
  }
  if (val[1] == 3) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    winder_speed = u.ival;
  }
  if (val[1] == 4) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    traverse_speed = u.ival;
    traverse.stop();
  }
  if (val[1] == 5) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    winder_speed = u.ival;
  }
  if (val[1] == 6) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    traverse_speed = u.ival;
    traverse.stop();
  }
  if (val[1] == 7) {
    traverse.moveTo(goal[1]);
    traverse.setMaxSpeed(traverse_speed);
    traverse.setSpeed(traverse_speed);
    winder.move(Winder_goal);
    winder.setMaxSpeed(winder_speed);
    winder.setSpeed(winder_speed);
    test = true;
  }
  if (val[1] == 8) {
    test = false;
    traverse.stop();
    winder.stop();
  }
}

void Bobbin_Setting() {
  if (val[1] == 1) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    Winder_goal = u.ival / (bobbin_dist_per_rev / ticks_per_rev);
  }
  if (val[1] == 2) {
    u.b[0] = val[5];
    u.b[1] = val[4];
    u.b[2] = val[3];
    u.b[3] = val[2];
    bobbin_length = u.ival;
  }
}



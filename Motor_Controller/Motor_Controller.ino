#define SERIAL_PORT_SPEED 115200
#include "motor_controller.h"
#include <Servo.h>

Servo m1;
Servo m2;
Servo m3;
Servo m4;

MotorController motors;
void setup() {
  Serial.begin(SERIAL_PORT_SPEED);
  motors.init();
  motors.command();
  delay(10000);
}

void loop() {

  
  process();
  m1.write(motors.outputs[M1] + 50);
  m2.write(motors.outputs[M2] + 50);
  m3.write(motors.outputs[M3] + 50);
  m4.write(motors.outputs[M4] + 50);

  
}


void process() {
 
  if (1) {
    compute_motor_outputs();
    adjust_for_bounds();
  } else {
    motors.command_all_off();
  }

  motors.command();
}

void adjust_for_bounds() {
  int16_t motor_fix = 0;
  uint16_t motor_min = motors.outputs[0];
  uint16_t motor_max = motors.outputs[0];

  for(int i = 1; i < 4; i++) {
    if (motors.outputs[i] < motor_min) motor_min = motors.outputs[i];
    if (motors.outputs[i] > motor_max) motor_max = motors.outputs[i];
  }

  if (motor_min < MOTOR_MIN) {
    motor_fix = MOTOR_MIN - motor_min;
  } else if (motor_max > MOTOR_MAX) {
    motor_fix = MOTOR_MAX - motor_max;
  }

  for(int i = 0; i < 4; i++) {
    motors.outputs[i] += motor_fix;
  }
}

void compute_motor_outputs() {

  double m1_r_out = 10;
  double m2_l_out = 10;
  double m3_f_out = 10;
  double m4_b_out =10;

  // double m1_r_out = rc->get(RC_THROTTLE) + pid_outputs[PID_ROLL_RATE];
  // double m2_l_out = rc->get(RC_THROTTLE) - pid_outputs[PID_ROLL_RATE];
  // double m3_f_out = rc->get(RC_THROTTLE) - pid_outputs[PID_PITCH_RATE];
  // double m4_b_out = rc->get(RC_THROTTLE) + pid_outputs[PID_PITCH_RATE];

  motors.outputs[M1] = (int16_t)(m1_r_out + 0.5);
  motors.outputs[M2] = (int16_t)(m2_l_out + 0.5);
  motors.outputs[M3] = (int16_t)(m3_f_out + 0.5);
  motors.outputs[M4] = (int16_t)(m4_b_out + 0.5);


}

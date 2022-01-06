
#include <Arduino.h>
#include <Wire.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <Servo.h>
#include <std_msgs/String.h>


ros::NodeHandle node_handle;

std_msgs::UInt16 tilt_ang_msg, angle_msg;

Servo Tilt_bldc;  // create servo object to control a servo

int ang;

void subscriberCallback(const std_msgs::UInt16& tilt_ang_msg) {
 ang=tilt_ang_msg.data;
 angle_msg.data=tilt_ang_msg.data;
}

ros::Publisher tilt_ang_publisher("angle", &tilt_ang_msg);
ros::Subscriber<std_msgs::UInt16> tilt_ang_subscriber("tilt_ang", &subscriberCallback);


void setup() 
{
  // put your setup code here, to run once:
  Tilt_bldc.attach(10); //attaches the servo on pin 10 to the servo object
  // Tilt_bldc.write(90);  //sets the initial position of the servo to the midpoint within its physical constraints
  Serial.begin(57600);
  node_handle.initNode();
  node_handle.advertise(tilt_ang_publisher);
  node_handle.subscribe(tilt_ang_subscriber);  
}

void loop() {
  // put your main code here, to run repeatedly:
  //tilt_ang_publisher.publish( "El angulo del tilt es: ");
  if (angle_msg.data>1900)
    {angle_msg.data=1900;}
  if (angle_msg.data<1100)
    {angle_msg.data=1100;}
  
    
  tilt_ang_publisher.publish( &angle_msg );
  Tilt_bldc.writeMicroseconds(angle_msg.data);
  node_handle.spinOnce();
  
  // delay(10);
}

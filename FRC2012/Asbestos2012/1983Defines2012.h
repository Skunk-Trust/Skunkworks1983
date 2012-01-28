#ifndef __1983DEFINES_H
#define __1983DEFINES_H

//DriveBase Start
//Air Compressor
#define AIR_COMP_SENSE 14
#define AIR_COMP_CONTROL 8

//Jaguars
#define JAG_PORT_LEFT_1 1
#define JAG_PORT_LEFT_2 2
#define JAG_PORT_RIGHT_1 3
#define JAG_PORT_RIGHT_2 4

//Encoders
#define LEFT_ENCODER_PORT_A 1
#define LEFT_ENCODER_PORT_B 2
#define RIGHT_ENCODER_PORT_A 3
#define RIGHT_ENCODER_PORT_B 4

//PIDs
#define DRIVE_P 0
#define DRIVE_I 0
#define DRIVE_D 0

#define KINECT 0
#define USE_PID 0
//DriveBase End

//Shooter Start
//The target RPM of the shooter wheel
#define TARGET_SHOOT_VELOCITY 0
//Tolerance of the velocity
#define SHOOT_VELOCITY_TOLERANCE 10
//Shooter End

//Tipper Start
#define TIPPER_PORT 5
//Tipper End

//Collector Start
#define COLLECTOR_FEED_VIC 0
#define COLLECTOR_VIC_1 0
#define COLLECTOR_VIC_2 0
//Number of sensed ball storage spots
#define COLLECTOR_SLOT_COUNT 3
//Belt speed
#define COLLECTOR_BELT_SPEED 1.0
//Collector End

//GlyphCamera Start
#define GLYPH_CAMERA_IP "10.19.83.4"

//Low bound of threshold
#define GLYPH_THRESH_R_L 200
#define GLYPH_THRESH_G_L 200
#define GLYPH_THRESH_B_L 200

//High bound of threshold
#define GLYPH_THRESH_R_H 255
#define GLYPH_THRESH_G_H 255
#define GLYPH_THRESH_B_H 255

//GlyphCamera End

#endif

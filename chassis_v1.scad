/*
###########################
# 2014 Micromouse Chassis #
###########################
Author: Darrel Weng

Chassis for 2014 IEEE micromouse competition.
Team: Darrel, Sunil, Ryan, Ethan

Numbers are in units of mm, but unit_scale variable allows
the unit to change.

**********************************************
*** MAKERWARE ASSUMES STL VALUES ARE IN mm ***
**********************************************

*/

// ALL UNITS IN mm
unit_scale 		= 		1;
//================================================================================
// Chassis Parameters
chassis_rad		= 		70*unit_scale;
chassis_height 	= 		5*unit_scale;
battery_dep 		= 		3*unit_scale;
battery_len 		= 		71*unit_scale;
battery_width 	= 		36*unit_scale;
pcb_len 			= 		69.5*unit_scale;
pcb_width 		= 		50.7*unit_scale;
tire_width 		= 		44*unit_scale;
tire_thick 		= 		21*unit_scale;
tire_offset 		= 		8*unit_scale;
screw1_rad		=		(3.0/2)*unit_scale;
screw2_rad		=		(3.5/2)*unit_scale;
ziptie_rad 		=		2.1*unit_scale;
// note that motor & caster measurements are maximum measurements, 
// and only measurements of the part that will on on the chassis
motor_width		=		26.6*unit_scale;
motor_height		=		13.35*unit_scale;
motor_len		=		16.33*unit_scale;
caster_width		=		15.5*unit_scale;
caster_len		=		20.32*unit_scale;
caster_height	=		13.9*unit_scale;
// need motor holes, caster holes, pcb holes; offsets are wrt origin
caster_offset	=		7.366*unit_scale;
motor_offset		=		9*unit_scale;
motor2_offset	=		(8.5*unit_scale)/2;
pcb_xoffset		=		(66*unit_scale)/2;
pcb_yoffset		=		(45.5*unit_scale)/2;
//================================================================================
// Translation Parameters
battery_trans 	= 		[-1*(chassis_rad/2)-(3*unit_scale),0,(battery_dep/2)+(chassis_height-battery_dep)];
cutoff_trans 	= 		[chassis_rad+(7*unit_scale),0,0];
pcbdummy_trans 	= 		[(chassis_rad/2)-(17*unit_scale),0,7*battery_dep];
castdummy_trans	=		[-1*(chassis_rad-(caster_width/2)),0,-1*caster_height/2];
//================================================================================
// Dummy Shapes (comment out for .stl file)
//
//// pcb dummy
//color("blue")
//translate(pcbdummy_trans) 
//cube(size=[pcb_len,pcb_width,battery_dep],center=true);
//
//// motor dummy
//for (i=[0:1]) {
//	color("blue")
//	translate([tire_offset,((i-.5)/abs(i-.5))*(chassis_rad-tire_thick-(motor_len/2)),chassis_height+(motor_height/2)])
//	cube(size=[motor_width,motor_len,motor_height],center=true);
//}
//
//// caster dummy
//color("blue") 
//translate(castdummy_trans)
//cube(size=[caster_width,caster_len,caster_height],center=true);
//================================================================================

// Chassis

difference() {
	// main body
	cylinder(h=chassis_height,r=chassis_rad);
	// battery depression
	translate(battery_trans) 
	cube(size=[battery_width,battery_len,battery_dep],center=true);
	// cut off end
	translate(cutoff_trans) 
	cube(size=[chassis_rad/2,chassis_rad*2,chassis_height*2],center=true);
	// wheel cutouts
	for(i=[0:1]) {
		translate([tire_offset,((i-.5)/abs(i-.5))*(chassis_rad-(tire_thick/2)),chassis_height/2]) 
		cube(size=[tire_width,tire_thick,tire_width],center=true);
	}
	// caster screws
	for (i=[0:1]) {
		translate([-1*((chassis_rad)-(caster_width/2)),((i-.5)/abs(i-.5))*caster_offset,-1*chassis_height])
		cylinder(h=chassis_height*2,r=screw1_rad);
	}
	// motor screws
	for (i=[0:1]){
		for (j=[0:1]) {
			translate([((j-.5)/abs(j-.5))*(motor_offset)+tire_offset,((i-.5)/abs(i-.5))*(chassis_rad-tire_thick-(screw1_rad)-(motor2_offset-screw1_rad)-0.8*unit_scale),-1*chassis_height/2])
			cylinder(h=chassis_height*2,r=screw1_rad);
		}
	}
	// pcb screws
	for (i=[0:1]) {
		for (j=[0:1]) {
			translate([((j-.5)/abs(j-.5))*(pcb_xoffset)+pcbdummy_trans[0],((i-.5)/abs(i-.5))*(pcb_yoffset),0])
			cylinder(h=chassis_height*5,r=screw2_rad);
		}
	}
	// ziptie holes
	for (i=[0:1]) {
		translate([-1*(battery_width/2 + 2*ziptie_rad + (battery_width-2*ziptie_rad)*i),0,0])
		cylinder(h=chassis_height, r=ziptie_rad);
	}
}

/*
 * Malith JDK
 * 27.11.2020
 * Reaction torque observer and Disterbacen observer
 * To compiile the code use gcc "file_name" -lm
 *
 */
#include<stdio.h>
#include<math.h>

// function decleration
void motor();
void dob();
void rtob();
void PID();

// Veriable decleration
float Time = 0.0;				// variables for time based oparation
float dt = 0.000006;			// 6 micro seconds

float Torque_cmd = 3.0;			// variables for system MainLoop
float Theta_double_dot = 0;		// verible for accelaration
float Theta_dot = 0;			// variables related to Speed

float Kt = 0.134;				// variables for Motor - Motor Torque constent
float J = 0.000091;				// Motor innetia
float B = 0.0000021;			// Viscus friction coeffecient - B = 0.0000021
float Tf = 0.001119;			// Static friction
float JTheta_double_dot = 0.0;

float Ia_ref = 0.0;				// Curent for MainLoop
float I_dis = 0.0;
float I_total = 0.0;
float Torque_dis = 0.0;

float Ktn = 0.134;				// variables for Disterbance Observer
float Jn = 0.000091;
float Gdis = 200.0;
float Torque_dis_est = 0.0;
float G_total_dob = 0.0;

float G_total_rtob = 0.0;		// variables for reaction torque observer
float Torque_ext_est = 0.0;

float Torque_error = 0.0;		// variables for PID controller
float Torque_error_total = 0.0;	
float Kp = 7.0;
float Ki = 0.0;
float Kd = 0.0;


int main(){
	FILE *fp = NULL;
	fp = fopen("motor_simulate_data.txt","w");


	for(Time = 0;Time<=15;Time += dt){
		
		Torque_error = Torque_cmd - Torque_ext_est;
		PID();
		Ia_ref = Theta_double_dot*Jn/Ktn; 
		I_total = Ia_ref + I_dis;
		motor();
		dob();
		rtob();
		fprintf(fp,"%f\t %f\t %f\t %f\t %f\n",Time,Theta_dot,Torque_cmd,Torque_dis,Torque_ext_est);

		if (Time >=1){
			Torque_dis = Theta_dot*0.00005;			//this should change according to controler capability
		}
		
	}
	fclose(fp);
	return 0;
}

// Function decleration
void motor(){
	JTheta_double_dot = I_total*Kt - (Torque_dis + Tf + B*Theta_dot);
	Theta_dot = Theta_dot + JTheta_double_dot*dt/J;
}

void dob(){
	G_total_dob = G_total_dob + Gdis*(I_total*Ktn + Jn*Gdis - G_total_dob)*dt;
	Torque_dis_est = G_total_dob - Gdis*Jn;
}

void rtob(){
	G_total_rtob = G_total_rtob + Gdis*(I_total*Ktn + Jn*Gdis -(Tf +B*Theta_dot) - G_total_rtob)*dt;
	Torque_ext_est = G_total_rtob - Jn*Gdis;
}

void PID(){
	Torque_error_total = Torque_error_total + Torque_error*dt;
	Theta_double_dot = Kp*Torque_error + Ki*Torque_error*dt;
}

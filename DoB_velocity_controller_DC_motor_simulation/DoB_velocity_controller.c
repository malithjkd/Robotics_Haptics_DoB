/* Malith JKD
 * 25.11.2020 
 *
 * Simulation of DC motor and DOB based velocity controller 
 * to impliment better cuttent controling PID based corrent controller is 
 * implimented.
 *
 * 
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float t,Tc;
float d0_ref,d0_res,d0_err,d0_errTotal,d0_errPrivious;			//varibles initialisation for anguler velocity
float Kp,Ki,Kd,dd0_k,dd0_p,dd0_d;					//variable initialisation for PID related varible
float Ia,Kt,IaKt,Text,Tf,B,Bd0_res,J,Jdd0_res,dd0_res;			//variabla initialisation for motor related variables
float Tdis_est,Jn,Ktn,Gdis,Temp_total,Temp_new,Temp_old,Idis;		//variable installation for DOB related variableas

void PID();
void Motor();
void DOB();
void RTO();


int main (){

	FILE *fp = NULL;			//activating file oparator for data writting
	fp = fopen("simulation_results.txt","w");

	t = 0;					// Time varible
	Tc = 0.000006;				// Time constent 0.000006

	d0_ref = 200;				// Motor ref speed 200
	d0_res = 0;				// Motor respond
	d0_err = 0;				// Error ref to respond

	//for PID oparation
	d0_errTotal = 0;
	d0_errPrivious = 0;
	Kp = 20.0;				//crigicaly dhamped at kp = 30
	Ki = 0.0000;
	Kd = 0.00001;
	dd0_p = 0.0;
	dd0_k = 0.0;
	dd0_d = 0.0;

	//for Motor model
	Ia = 0.0;
	Kt = 0.134;
	IaKt = 0;
	Text = 0;
	Tf = 0.001119;				// Tf = 0.001119
	J = 0.000091;				// J = 0.000091
	B = 0.0000021;				// B = 0.0000021
	Bd0_res = 0;
	Jdd0_res = 0;
	dd0_res = 0;

	// for Disterbance observer
	Tdis_est = 0;
	Jn = 0.000091;
	Ktn = 0.134;
	Gdis = 200;
	Temp_total = 0;
	Temp_new = 0;
	Temp_old = 0;
	Idis = 0;

	//for Reaction torque observer

	for(t = 0;t<=4;t+=Tc){							//main loop
		PID();
		DOB();
		Motor();
		fprintf(fp,"%f\t %f\t %f\t %f\t\n",t,IaKt,Text,d0_res); 	//Writing data on file
	}

	fclose(fp);
	return 0;
}

void PID(){
	d0_err = d0_ref-d0_res;							//PID fucntion
	dd0_k = Kp*d0_err;

	d0_errTotal = d0_errTotal + d0_err*Tc;
	dd0_p = Ki*d0_errTotal;

	dd0_d = Kd*(d0_err-d0_errPrivious)/Tc;
	d0_errPrivious = d0_err;
}

void Motor(){
	Ia = (dd0_k + dd0_p + dd0_d)*J/Kt;					//input current to the motor
	Ia = Ia+Idis;
	IaKt = Ia*Kt;
	Text = 0.02*sin(10*t);
	//Text = (rand()%400)/100;

	Jdd0_res = IaKt - (Text + Tf+ Bd0_res);
	dd0_res = Jdd0_res/J;
	d0_res = d0_res + (dd0_res*Tc);
	Bd0_res = B*d0_res;
}

void DOB(){									// Disterbance observer
	Temp_new = Ktn*Ia + Jn*Gdis*d0_res;					//
	Temp_total = Temp_total + Gdis*(Temp_new - Temp_total)*Tc;		// y = g*integral(x-y)
	Tdis_est = Temp_total-Jn*Gdis*d0_res;
	Idis = Tdis_est/Ktn;
}












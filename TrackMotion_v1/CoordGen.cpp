#include "CoordGen.h"

CoordGen::CoordGen(double center_x, double center_y, double center_z, double startpoint_x, double startpoint_y, double startpoint_z)
{
	center.x = center_x;
	center.y = center_y;
	center.z = center_z;
	startPoint.x = startpoint_x;
	startPoint.y = startpoint_y;
	startPoint.z = startpoint_z;
	r = sqrt((center_x-startpoint_x)*(center_x-startpoint_x)+(center_y-startpoint_y)*(center_y-startpoint_y));
	theta_i = atan2(startpoint_y-center_y,startpoint_x-center_x);
}
void CoordGen::SetPara(double currentTimeInput)
{

	currentTime = currentTimeInput;
}

void CoordGen::PointGen()
{
	// Calculation according to my notebook
	if (currentTime <= w0/alpha0)
	{
		nPosition.x = center.x+r*cos(theta_i+0.5*alpha0*currentTime*currentTime);
		nPosition.y = center.y+r*sin(theta_i+0.5*alpha0*currentTime*currentTime);
		nVelocity.v_x = -r*alpha0*currentTime*sin(theta_i+0.5*alpha0*currentTime*currentTime);
		nVelocity.v_y = r*alpha0*currentTime*cos(theta_i+0.5*alpha0*currentTime*currentTime);
	}
	else if (currentTime <= tmax)
	{
		nPosition.x = center.x+r*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
		nPosition.y = center.y+r*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
		nVelocity.v_x = -r*w0*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
		nVelocity.v_y = r*w0*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
	}
	else if (currentTime <= tmax+w0/alpha0)
	{
		nPosition.x = center.x+r*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nPosition.y = center.y+r*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nVelocity.v_x = -r*(w0-alpha0*(currentTime-tmax))*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nVelocity.v_y = r*(w0-alpha0*(currentTime-tmax))*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
	}
	else
	{
		nPosition.x = center.x+r*cos(theta_i+alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0));
		nPosition.y = center.y+r*sin(theta_i+alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0));
		nVelocity.v_x = 0;
		nVelocity.v_y = 0;
	}

	// 
	if (currentTime <= v0/a0)
	{
		nPosition.z = startPoint.z + 0.5*a0*currentTime*currentTime;
		nVelocity.v_z = a0*currentTime;
	}
	else if (currentTime <= tmax)
	{
		nPosition.z = startPoint.z + 0.5*a0*pow(v0/a0,2)+v0*(currentTime-v0/a0);
		nVelocity.v_z = v0;
	}
	else if (currentTime <= tmax+v0/a0)
	{
		nPosition.z = startPoint.z + 0.5*a0*pow(v0/a0,2)+v0*(tmax-v0/a0)+0.5*(2.0*v0-(currentTime-tmax)*a0)*(currentTime-tmax);
		nVelocity.v_z = v0-a0*(currentTime-tmax);
	}
	else
	{
		nPosition.z = startPoint.z + a0*pow(v0/a0,2)+v0*(tmax-v0/a0);
		nVelocity.v_z = 0;
	}
}


void CoordGen::PointGen(double height)
{
	// Calculation according to my notebook
	if (currentTime <= w0/alpha0)
	{
		nPosition.x = center.x+r*cos(theta_i+0.5*alpha0*currentTime*currentTime);
		nPosition.y = center.y+r*sin(theta_i+0.5*alpha0*currentTime*currentTime);
		nPosition.z = height*sin(0.5*alpha0*currentTime*currentTime);  //testing
		nVelocity.v_x = -r*alpha0*currentTime*sin(theta_i+0.5*alpha0*currentTime*currentTime);
		nVelocity.v_y = r*alpha0*currentTime*cos(theta_i+0.5*alpha0*currentTime*currentTime);
		nVelocity.v_z = height*alpha0*currentTime*cos(0.5*alpha0*currentTime*currentTime);  //testing 
	}
	else if (currentTime <= tmax)
	{
		nPosition.x = center.x+r*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
		nPosition.y = center.y+r*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
		nPosition.z = height*sin(0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));  //testing
		nVelocity.v_x = -r*w0*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
		nVelocity.v_y = r*w0*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));
		nVelocity.v_z = height*w0*cos(0.5*alpha0*pow(w0/alpha0,2)+w0*(currentTime-w0/alpha0));  //testing
	}
	else if (currentTime <= tmax+w0/alpha0)
	{
		nPosition.x = center.x+r*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nPosition.y = center.y+r*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nPosition.z = height*sin(0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nVelocity.v_x = -r*(w0-alpha0*(currentTime-tmax))*sin(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nVelocity.v_y = r*(w0-alpha0*(currentTime-tmax))*cos(theta_i+0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
		nVelocity.v_z = height*(w0-alpha0*(currentTime-tmax))*cos(0.5*alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0)+0.5*(2.0*w0-(currentTime-tmax)*alpha0)*(currentTime-tmax));
	}
	else
	{
		nPosition.x = center.x+r*cos(theta_i+alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0));
		nPosition.y = center.y+r*sin(theta_i+alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0));
		nPosition.z = height*sin(alpha0*pow(w0/alpha0,2)+w0*(tmax-w0/alpha0));
		nVelocity.v_x = 0.0;
		nVelocity.v_y = 0.0;
		nVelocity.v_z = 0.0;
	}
}
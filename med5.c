#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265359

//convert degrees to radians
double to_radians(double angle) 
{
    return angle * M_PI / 180.0;
}

//converts euler angles (in degrees) to quaternion (x, y, z, w)
void euler_to_quaternion(double roll, double pitch, double yaw,double *qx, double *qy, double *qz, double *qw) 
{
    //first converting all angles to radians
    double r = to_radians(roll);
    double p = to_radians(pitch);
    double y = to_radians(yaw);

    //calculate half angles for formula
    double cr = cos(r / 2);
    double sr = sin(r / 2);
    double cp = cos(p / 2);
    double sp = sin(p / 2);
    double cy = cos(y / 2);
    double sy = sin(y / 2);

    //quaternion formula (x, y, z, w)
    *qw = cr * cp * cy + sr * sp * sy;
    *qx = sr * cp * cy - cr * sp * sy;
    *qy = cr * sp * cy + sr * cp * sy;
    *qz = cr * cp * sy - sr * sp * cy;
}

int main() 
{
    double roll, pitch, yaw;
    double qx, qy, qz, qw;

    //ask user for 3D rotation in euler angles
    printf("enter roll (x), pitch (y), yaw (z) in degrees:\n");
    scanf("%lf %lf %lf", &roll, &pitch, &yaw);

    //convert to martian style quaternion
    euler_to_quaternion(roll, pitch, yaw, &qx, &qy, &qz, &qw);

    //show the 4-number system result
    printf("martian rotation format (quaternion):\n");
    printf("x = %.5f\n", qx);
    printf("y = %.5f\n", qy);
    printf("z = %.5f\n", qz);
    printf("w = %.5f\n", qw);

    return 0;
}
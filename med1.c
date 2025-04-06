#include <stdio.h>
#include <math.h>

// basic function to get distance between two points in 3d
double get_distance(int x, int y, int z) 
{
    return sqrt(x * x + y * y + z * z);
}

// this function shifts the marker position so the rover turns at the right place
void shift_marker_position(int x, int y, int z, int offset) 
{
    printf("camera saw marker at: (%d, %d, %d)\n", x, y, z);

    // shifting the z value since the camera is 55 cm ahead of rover's center
    int new_z = z + offset;

    printf("marker location from rover's center: (%d, %d, %d)\n", x, y, new_z);

    double dist_before = get_distance(x, y, z);
    double dist_after = get_distance(x, y, new_z);

    printf("distance from camera: %.2f cm\n", dist_before);
    printf("distance from rover center: %.2f cm\n", dist_after);
}

int main() 
{
    int x, y;
    const int z = -60;     // fixed distance in front of camera
    const int offset = 55; // camera is 55 cm ahead

    printf("enter x: ");
    scanf("%d", &x);

    printf("enter y: ");
    scanf("%d", &y);

    shift_marker_position(x, y, z, offset);

    return 0;
}
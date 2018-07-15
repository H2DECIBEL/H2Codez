#pragma once

/* channel intensity is represented on a 0 to 1 scale */
struct colour
{
	float alpha = 1.0f;
	float red = 1.0f;
	float green = 1.0f;
	float blue = 1.0f;
};

struct point2d
{
	short x;
	short y;
};
struct real_point2d
{
	float x;
	float y;
};

struct real_point3d
{
	float x;
	float y;
	float z;
};

struct real_vector2d
{
	float i;
	float j;
};

struct real_vector3d
{
	float i;
	float j;
	float k;
};

struct real_euler_angles2d
{
	float yaw;
	float pitch;
};

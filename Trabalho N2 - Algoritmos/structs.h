#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
	char type;
	int direction;
	float x;
	float y;
	int width;
	int height;
		
} Role_t;

typedef struct {
	char type;
	float x;
	float y;
	int width;
	int height;
	char direction;
	int speed;
	
} Projectile_t;

typedef struct {
	
	char **mapPptr;
	int screenWidth;
	int screenHeight;
	int imageSize;
	int width;
	int height;
	int outOfLimitsX;
	int outOfLimitsY;
	
} Map_t;

#endif

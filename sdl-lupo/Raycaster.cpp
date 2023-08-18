#include "Raycaster.h"
#include <iostream>

#define P2 M_PI/2
#define P3 3*M_PI/2

// refactor to adjust angle from game loop and use rays to project 3d, also maybe need to change return type
vec2 Raycaster::drawRays(vec2 pos, float ang) {
	int r, mx, my, mapPos, dof;
	float rx, ry, ra, xo, yo;

	float vx, vy;
	float disVertical = 1000000.0, disHorizontal = 1000000.0;

	ra = ang;

	for (r = 0; r < 1; r++) {

		// --- Vertical Check --- 
		dof = 0; 
		float rTan = tan(-ra);

		if (cos(ra) > 0.001) { // Looking left
			rx = (((int)pos.x >> 6) << 6) + 64;      
			ry = (pos.x - rx) * rTan + pos.y;
			xo = 64; 
			yo = -xo * rTan;
		}

		else if (cos(ra) < -0.001) { // Looking right
			rx = (((int)pos.x >> 6) << 6) - 0.0001; 
			ry = (pos.x - rx) * rTan + pos.y; 
			xo = -64; 
			yo = -xo * rTan;
		} 

		else { // straight up or down
			rx = pos.x; 
			ry = pos.y;
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6; 
			my = (int)(ry) >> 6; 
			mapPos = my * TempMap::mapX + mx;
			if (mapPos > 0 && mapPos < TempMap::mapX * TempMap::mapY && TempMap::map[mapPos] == 1)
			{ 
				dof = 8; 
				disVertical = cos(ra) * (rx - pos.x) - sin(ra) * (ry - pos.y);
			}//hit         
			else { 
				rx += xo; ry += yo; dof += 1; 
			}     
		}
		vx = rx; vy = ry;
		

		// --- Horizontal Check --- 
		dof = 0;
		float aTan = -1 / tan(ra);

		if (ra > M_PI) { // up
			ry = (((int)pos.y >> 6) << 6) - 0.0001;
			rx = (pos.y - ry) * aTan + pos.x;
			yo = -64;
			xo = -yo * aTan;
		}

		if (ra < M_PI) { // down
			ry = (((int)pos.y >> 6) << 6) + 64;
			rx = (pos.y - ry) * aTan + pos.x;
			yo = 64;
			xo = -yo * aTan;
		}

		if (ra == 0 || ra == M_PI) { // Striaght left or right
			rx = pos.x;
			ry = pos.y;
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mapPos = my * TempMap::mapX + mx;
			if (mapPos > 0 && mapPos < TempMap::mapX * TempMap::mapY && TempMap::map[mapPos] == 1)
			{ // hit
				dof = 8;
				disHorizontal = cos(ra) * (rx - pos.x) - sin(ra) * (ry - pos.y);
			}
			else {
				rx += xo; ry += yo; dof += 1;
			}
		}
	}

	// no idea why distances become negative but temp fix here:
	disVertical = abs(disVertical);
	disHorizontal = abs(disHorizontal);

	if (disVertical < disHorizontal) {
		rx = vx;
		ry = vy;
		printf("Vertical Hit %f vs %f\n", disVertical, disHorizontal);
	}
	else {
		printf("Horizontal Hit %f vs %f\n", disHorizontal, disVertical);
	}


	//printf("%f, %f : %f,%f \n", pos.x, pos.y, rx, ry);
	//r.drawLine(pos, { rx, ry });

	return { rx, ry };
}

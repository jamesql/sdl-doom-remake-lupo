#include "Raycaster.h"
#include <iostream>

#define P2 M_PI/2
#define P3 3*M_PI/2


vec2 Raycaster::drawRays(vec2 pos, float ang) {
	int r, mx, my, mapPos, dof;
	float rx, ry, ra, xo, yo;


	ra = ang;

	for (r = 0; r < 1; r++) {
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

		while (dof < 8) {
			mx = (int)rx / 64;
			my = (int)ry / 64;
			mapPos = my * TempMap::mapX + mx;

			if (mapPos < 64 && TempMap::map[mapPos] == 1) {
				dof = 8; // hit wall
			}
			else {
				rx += xo;
				ry += yo;
				dof++;
			}
		}
	}




	//printf("%f, %f : %f,%f \n", pos.x, pos.y, rx, ry);
	//r.drawLine(pos, { rx, ry });

	return { rx, ry };
}

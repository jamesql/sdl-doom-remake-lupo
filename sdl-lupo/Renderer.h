#pragma once

#include <SDL.h>
#include "e_config.h"

namespace Renderer {
	
	struct Color {
		float r;
		float g;
		float b;
		float a;
	};

	struct Point3D {
		float x;
		float y;
		float z;
	};

	struct Triangle {
		int a;
		int b;
		int c;
		Color col;
	};

	struct Quad {
		int a;
		int b;
		int c;
		int d;
		Color col;
	};

	class Mesh {
	public:
		~Mesh();

		Point3D* localVertex;
		int vertices;

		Triangle* triangle;
		int triangles;

		void init(int, int);
		int addVertex(float, float, float);
		int addTriangle(int, int, int);
		void setTriangleColor(int, float, float, float, float);

		void loadPly(const char*);

	};

	class Camera {
	public:
		Point3D pos;
		Point3D ang;

		void locate(float, float, float);
		void move(float, float, float);
		void orient(float, float, float);
		void rotate(float, float, float);
	};

	class RenderObject {
	public:
		RenderObject(Mesh*);
		~RenderObject();

		float x();
		float y();
		float z();

		//User variables
		float vx;
		float vy;
		float vz;

		Mesh* mesh;
		Point3D* vertex;      //Vertex array, vertices in world coordinates

		//These operate on the object vertices
		void locate(float, float, float); //Absolute
		void move(float, float, float); //Relative

		void orient(float, float, float); //Absolute
		void rotate(float, float, float); //Relative

		void size(float, float, float);  //Absolute *
		void scale(float, float, float);  //Relative *


	private:
		Point3D position;     //object position in world coordinates
		Point3D angle;        //object rotion in world coordinates
		Point3D proportion;   //object scale factor
	};

	class Rasterizer {
	public:
		float aspectRatio;
		float focalLength;

		Camera cam;

		int backfaceCull = 0;
		Color clearCol;

		void f_drawQuad(Point3D*, Quad*);
		void f_drawTriangle(Point3D*, Triangle*);
		void f_drawPoint(Point3D*);
		void f_drawLine(Point3D*, Point3D*);

		void f_drawObject(RenderObject*);

		void setDrawColor(int, int, int, int);

		void setDisplay(SDL_Renderer*, int, int);
		void adjustDisplay(int, int);
		void clearDisplay();
		void updateDisplay();

		SDL_Point projection(Point3D*);

	private:
		SDL_Renderer* renderer;


	};

	class Scene {

	};
};

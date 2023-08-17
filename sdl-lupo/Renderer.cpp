#include "Renderer.h"
#include <string.h>
#include <iostream>

#define TYPE_UNKNOWN  0
#define TYPE_ASCII    1
#define TYPE_BINARYLE 2
#define TYPE_BINARYBE 3


namespace Renderer {

    //Mesh
    void Mesh::init(int verts, int tri) {

        localVertex = (Point3D*)calloc(verts, sizeof(Point3D));
        vertices = verts;

        triangles = tri;
        triangle = (Triangle*)calloc(tri, sizeof(Triangle));

    }

    void Mesh::loadPly(const char* filename) {


        SDL_RWops* file = SDL_RWFromFile(filename, "rb");

        Sint64 res_size = SDL_RWsize(file);
        printf("Size: %lld\n", res_size);
        printf("Size: %lld\n", sizeof(*file));

        Uint8 buf[10000];

        if (file != NULL) {
            SDL_RWread(file, buf, res_size, 1);
            SDL_RWclose(file);
        }
        else {
            printf("Load failed.\n");
            return;
        }

        //Check for the PLY magic number
        uint32_t* magic = (uint32_t*)buf;
        if (*magic != 175729776) {
            printf("Not a PLY File.\n");
            return;
        }

        //Determine Data type
        int type = TYPE_UNKNOWN;
        char* test = NULL;

        test = strstr((char*)buf, "format ascii");
        if (test != NULL) {
            type = TYPE_ASCII;
        }

        test = strstr((char*)buf, "format binary_little_endian");
        if (test != NULL) {
            type = TYPE_BINARYLE;
        }

        test = strstr((char*)buf, "format binary_big_endian");
        if (test != NULL) {
            type = TYPE_BINARYBE;
        }

        //Determine data start in the buffer
        char* data = strstr((char*)buf, "end_header") + 11;


        //Determine the vertex structure (only the number at the moment, vertex must be x y z)
        test = strstr((char*)buf, "element vertex ");
        if (test != NULL) {
            test += 15;
        }
        vertices = atoi(test);

        //Determine the face structure (only triangles supported at the moment)
        test = strstr((char*)buf, "element face ");
        if (test != NULL) {
            test += 13;
        }
        triangles = atoi(test);




        //Only supports Binary LE, no big endian support yet.
        if (type == TYPE_BINARYLE) {

            //allocate memory for data
            init(vertices, triangles);


            //Load in vertices
            int pointer = 0;
            for (int i = 0; i < vertices; ++i) {

                float x = (*(float*)&data[pointer]);
                float y = (*(float*)&data[(pointer + 4)]);
                float z = (*(float*)&data[(pointer + 8)]);

                localVertex[i].x = x;
                localVertex[i].y = y;
                localVertex[i].z = z;

                pointer += 4 * 3;  //size of a float * 3
                //printf("Vertex %d:, X:%f, Y:%f, Z:%f\n",i,x,y,z);
            }

            //Load in triangles
            data += pointer;
            pointer = 0;
            for (int i = 0; i < triangles; ++i) {

                if (data[pointer] == 3) {

                    int* a = (int*)&data[pointer + 1];
                    int* b = (int*)&data[pointer + 5];
                    int* c = (int*)&data[pointer + 9];

                    triangle[i].a = *a;
                    triangle[i].b = *b;
                    triangle[i].c = *c;

                    triangle[i].col.r = 1;
                    triangle[i].col.g = 1;
                    triangle[i].col.b = 1;
                    triangle[i].col.a = 1;

                    pointer += 1 + 4 * 3;//1 byte for the list type + the size of an int * 3
                    //printf("Triangle %d:, A:%d, B:%d, C:%d\n",i,*a,*b,*c);
                }


                if (data[pointer] == 4) {

                    //need to support quads
                    /*
                     int a=(int)data[pointer+1];
                     int b=(int)data[pointer+5];
                     int c=(int)data[pointer+9];

                     triangle[i].a = &vertex[a];
                     triangle[i].b = &vertex[b];
                     triangle[i].c = &vertex[c];

                     triangle[i].col.r = 1;
                     triangle[i].col.g = 1;
                     triangle[i].col.b = 1;
                     triangle[i].col.a = 1;
                     */
                    pointer += 1 + 4 * 4;//1 byte for the list type + the size of an int * 4
                }

            }


        }

        //ASCII file type.
        if (type == TYPE_ASCII) {

            //allocate memory for data
            init(vertices, triangles);


            //Load in vertices
            for (int i = 0; i < vertices; ++i) {



                float x = atof(data);
                data = (char*)memchr(data, 0x20, 20) + 1;

                float y = atof(data);
                data = (char*)memchr(data, 0x20, 20) + 1;

                float z = atof(data);
                data = (char*)memchr(data, 0x0A, 20) + 1;

                localVertex[i].x = x;
                localVertex[i].y = y;
                localVertex[i].z = z;


            }

            for (int i = 0; i < triangles; ++i) {

                if (atoi(data) == 3) {
                    data = (char*)memchr(data, 0x20, 20) + 1;


                    int a = atoi(data);
                    data = (char*)memchr(data, 0x20, 20) + 1;

                    int b = atoi(data);
                    data = (char*)memchr(data, 0x20, 20) + 1;

                    int c = atoi(data);
                    data = (char*)memchr(data, 0x0A, 20) + 1;

                    triangle[i].a = a;
                    triangle[i].b = b;
                    triangle[i].c = c;

                    triangle[i].col.r = 1;
                    triangle[i].col.g = 1;
                    triangle[i].col.b = 1;
                    triangle[i].col.a = 1;

                }


                if (atoi(data) == 4) {

                    //need to support quads
                    /*
                     int a=(int)data[pointer+1];
                     int b=(int)data[pointer+5];
                     int c=(int)data[pointer+9];

                     triangle[i].a = &vertex[a];
                     triangle[i].b = &vertex[b];
                     triangle[i].c = &vertex[c];

                     triangle[i].col.r = 1;
                     triangle[i].col.g = 1;
                     triangle[i].col.b = 1;
                     triangle[i].col.a = 1;
                     */

                }

            }





            printf("ASCII\n");

        }





        printf("Object Loaded\n");
    }

    int Mesh::addVertex(float x, float y, float z) {

        ++vertices;

        localVertex = (Point3D*)realloc(localVertex, sizeof(Point3D) * vertices);

        int thisVertex = vertices - 1;

        localVertex[thisVertex].x = x;
        localVertex[thisVertex].y = y;
        localVertex[thisVertex].z = z;

        return thisVertex;
    }

    int Mesh::addTriangle(int a, int b, int c) {

        ++triangles;

        triangle = (Triangle*)realloc(triangle, sizeof(Triangle) * triangles);

        int thisTriangle = triangles - 1;

        triangle[thisTriangle].a = a;
        triangle[thisTriangle].b = b;
        triangle[thisTriangle].c = c;

        return thisTriangle;
    }

    void Mesh::setTriangleColor(int tri, float r, float g, float b, float a) {

        triangle[tri].col.r = r;
        triangle[tri].col.g = g;
        triangle[tri].col.b = b;
        triangle[tri].col.a = a;
    }

    Mesh::~Mesh() {

        //Free up the allocated memory.
        if (localVertex != nullptr) {
            free(localVertex);
        }

        if (triangle != nullptr) {
            free(triangle);
        }

    }

    //Camera
    void Camera::locate(float x, float y, float z) {

        pos.x = x;
        pos.y = y;
        pos.z = z;

    }

    void Camera::move(float x, float y, float z) {

        pos.x += x;
        pos.y += y;
        pos.z += z;

    }

    void Camera::rotate(float xA, float yA, float zA) {

        pos.x += xA;
        pos.y += yA;
        pos.z += zA;

    }

    void Camera::orient(float xA, float yA, float zA) {

        pos.x = xA;
        pos.y = yA;
        pos.z = zA;

    }


    //Object************************************

    RenderObject::RenderObject(Mesh* m) {

        mesh = m;
        vertex = (Point3D*)calloc(mesh->vertices, sizeof(Point3D));  // allocate  memory for the world vertices
        locate(0, 0, 0);
    }

    float RenderObject::x() { return position.x; }
    float RenderObject::y() { return position.y; }
    float RenderObject::z() { return position.z; };


    RenderObject::~RenderObject() {

        //Free up the allocated memory.

        if (vertex != nullptr) {
            free(vertex);
        }

    }

    void RenderObject::locate(float x, float y, float z) {

        position.x = x;
        position.y = y;
        position.z = z;

        //translate all local vertices to world coordinates
        for (int i = 0; i < mesh->vertices; ++i) {
            vertex[i].x = mesh->localVertex[i].x + x;
            vertex[i].y = mesh->localVertex[i].y + y;
            vertex[i].z = mesh->localVertex[i].z + z;
        }

    }

    void RenderObject::move(float x, float y, float z) {

        position.x += x;
        position.y += y;
        position.z += z;

        //translate all vertices relative world coordinates
        for (int i = 0; i < mesh->vertices; ++i) {
            vertex[i].x = vertex[i].x + x;
            vertex[i].y = vertex[i].y + y;
            vertex[i].z = vertex[i].z + z;
        }

    }

    void RenderObject::rotate(float xA, float yA, float zA) {

        angle.x += xA;
        angle.y += yA;
        angle.z += zA;

        float cosa = cos(angle.z);
        float sina = sin(angle.z);

        float cosb = cos(angle.x);
        float sinb = sin(angle.x);

        float cosc = cos(angle.y);
        float sinc = sin(angle.y);

        float Axx = cosa * cosb;
        float Axy = cosa * sinb * sinc - sina * cosc;
        float Axz = cosa * sinb * cosc + sina * sinc;

        float Ayx = sina * cosb;
        float Ayy = sina * sinb * sinc + cosa * cosc;
        float Ayz = sina * sinb * cosc - cosa * sinc;

        float Azx = -sinb;
        float Azy = cosb * sinc;
        float Azz = cosb * cosc;

        for (int i = 0; i < mesh->vertices; ++i) {
            float px = mesh->localVertex[i].x;
            float py = mesh->localVertex[i].y;
            float pz = mesh->localVertex[i].z;

            vertex[i].x = (Axx * px + Axy * py + Axz * pz) + position.x;
            vertex[i].y = (Ayx * px + Ayy * py + Ayz * pz) + position.y;
            vertex[i].z = (Azx * px + Azy * py + Azz * pz) + position.z;
        }

        return;

    }

    void RenderObject::orient(float xA, float yA, float zA) {

        angle.x = xA;
        angle.y = yA;
        angle.z = zA;

        rotate(0, 0, 0);

    }

    //Rasterizer************************************

    SDL_Point Rasterizer::projection(Point3D* point) {

        SDL_Point retval;



        //Camera aware projection
        //retval.x = (int)((camera.position.z * (point->x-camera.position.x)) / (camera.position.z + point->z) + camera.position.x);
        //retval.y = (int)((camera.position.z * (point->y-camera.position.y)) / (camera.position.z + point->z) + camera.position.y);

        //fixed camera
        float z = 1 - (point->z * focalLength);
        retval.x = (int)((point->x / z) * WIDTH);
        retval.y = -(int)((point->y / z) * HEIGHT);

        retval.x = (retval.x + (WIDTH * aspectRatio)) / aspectRatio;
        retval.y += HEIGHT;

        return retval;
    }

    void Rasterizer::f_drawQuad(Point3D* vertex, Quad* quad) {
        SDL_SetRenderDrawColor(renderer, quad->col.r * 255, quad->col.g * 255, quad->col.b * 255, quad->col.a * 255);
        
        SDL_Point tri[5];

        tri[0] = projection(&vertex[quad->a]);
        tri[1] = projection(&vertex[quad->b]);
        tri[2] = projection(&vertex[quad->c]);
        tri[3] = projection(&vertex[quad->d]);

        //Close the loop
        tri[4].x = tri[0].x;
        tri[4].y = tri[0].y;

        SDL_RenderDrawLines(renderer, tri, 4);
    }

    void Rasterizer::f_drawTriangle(Point3D* vertex, Triangle* triangle) {

        SDL_SetRenderDrawColor(renderer, triangle->col.r * 255, triangle->col.g * 255, triangle->col.b * 255, triangle->col.a * 255);

        SDL_Point tri[4];

        tri[0] = projection(&vertex[triangle->a]);
        tri[1] = projection(&vertex[triangle->b]);
        tri[2] = projection(&vertex[triangle->c]);
        tri[3].x = tri[0].x;
        tri[3].y = tri[0].y;

        if (backfaceCull == 1) {
            int test = (tri[0].x * tri[1].y) - (tri[1].x * tri[0].y) + (tri[1].x * tri[2].y) - (tri[2].x * tri[1].y) + (tri[2].x * tri[3].y) - (tri[3].x * tri[2].y) + (tri[3].x * tri[0].y) - (tri[0].x * tri[3].y);
            if (-test < 0) {
                return;
            }
        }

        SDL_RenderDrawLines(renderer, tri, 4);
    }



    void Rasterizer::f_drawObject(RenderObject* object) {

        for (int i = 0; i < object->mesh->triangles; ++i) {
            f_drawTriangle(object->vertex, &object->mesh->triangle[i]);
        }

    }

    void Rasterizer::f_drawPoint(Point3D* vertex) {
        SDL_Point point = projection(vertex);
        SDL_RenderDrawPoint(renderer, point.x, point.y);
    }

    void Rasterizer::f_drawLine(Point3D* a, Point3D* b) {

        SDL_Point pa = projection(a);
        SDL_Point pb = projection(b);

        SDL_RenderDrawLine(renderer, pa.x, pa.y, pb.x, pb.y);
    }

    void Rasterizer::setDrawColor(int r, int g, int b, int a) {

        SDL_SetRenderDrawColor(renderer, r, g, b, a);

    }

    void Rasterizer::setDisplay(SDL_Renderer* rend, int width, int height) {

        renderer = rend;
        adjustDisplay(width, height);
    }

    void Rasterizer::adjustDisplay(int width, int height) {

        //hWidth = width / 2;
        //hHeight = height / 2;
        aspectRatio = (float)WIDTH / (float)HEIGHT;

    }

    void Rasterizer::clearDisplay() {
        // clear buffer
        SDL_SetRenderDrawColor(renderer, clearCol.r * 255, clearCol.g * 255, clearCol.b * 255, 255);
        SDL_RenderClear(renderer);
    }

    void Rasterizer::updateDisplay() {
        SDL_RenderPresent(renderer);
    }
};
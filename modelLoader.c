
#include <stdio.h>

#include "modelLoader.h"


void readOFFFile(const char* file_name, Object3D* obj)
{
    FILE* fp;
    char str[999];                  // a string to use as a buffer
    fp = fopen(file_name, "r");

    if (fp == NULL){
        printf("Error, file could not be opened.\n Press any key to exit ...");
        getchar();
        exit(0);
    }

    // Now ready to load the file

    // 1. Read the first line, which should be 'OFF'
    fscanf(fp, "%s", str);

    if (strcmp(str,"OFF") != 0){
        fclose(fp);
        printf("Error, something wrong with the file format.\n Press any key to exit ...");
        getchar();
        exit(0);

    }

    // 2. Read the number of vertices and faces
    int dump;
    fscanf(fp, "%d", & obj->nvert);       // number of vertices
    fscanf(fp, "%d", & obj->nfaces);      // number of faces
    fscanf(fp, "%d", &dump);        // the third dumpp value (ignore it for now


    // 3. Now let's read the vertices
    obj->vertices = (point3*) malloc((obj->nvert) * sizeof(point3));
    int i;

    for (i=0; i<obj->nvert; i++){
        point3 vertex;
        fscanf(fp, "%f", vertex);       //equivalent to &(vertex[0])
        fscanf(fp, "%f", vertex+1);     //equivalent to &(vertex[1])
        fscanf(fp, "%f", vertex+2);     //equivalent to &(vertex[2])

        (obj->vertices)[i][0] = vertex[0];
        (obj->vertices)[i][1] = vertex[1];
        (obj->vertices)[i][2] = vertex[2];

    }

    // 4. Now let's read the faces
    obj->faces = (Face*) malloc((obj->nfaces) * sizeof(Face));
    for (i=0; i<obj->nfaces; i++){

        Face face;
        fscanf(fp, "%d", &dump);        //this should be 3
        fscanf(fp, "%d", face);       //equivalent to &(vertex[0])
        fscanf(fp, "%d", face+1);     //equivalent to &(vertex[1])
        fscanf(fp, "%d", face+2);     //equivalent to &(vertex[2])

        (obj->faces)[i][0] = face[0];
        (obj->faces)[i][1] = face[1];
        (obj->faces)[i][2] = face[2];
    }
    // All done, make sure to close the opened files and clear unnecessary memory
    fclose(fp);

}

void draw3DShape(Object3D obj)
{
    // for a good shading we need to compute normals (next lecture)
    int i;
    for (i=0; i<obj.nfaces; i++){

        glBegin(GL_LINE_LOOP);
            Face f;
            f[0] = obj.faces[i][0];
            f[1] = obj.faces[i][1];
            f[2] = obj.faces[i][2];

            glVertex3fv(obj.vertices[f[0]]);
            glVertex3fv(obj.vertices[f[1]]);
            glVertex3fv(obj.vertices[f[2]]);

        glEnd();
    }

}

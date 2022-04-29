#include "glut.h"
#include "vector.h"
#include "math.h"


#ifndef GLUT_C
#define GLUT_C

extern pez *sist;
extern int n;
extern double hash_cell_x, hash_cell_y;

void saveScreenshotToFile(char *filename, int windowWidth, int windowHeight) {
    const int numberOfPixels = windowWidth * windowHeight * 3;
    unsigned char pixels[numberOfPixels];

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, windowWidth, windowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

    FILE *outputFile = fopen(filename, "w");
    short header[] = {0, 2, 0, 0, 0, 0, (short) windowWidth, (short) windowHeight, 24};

    fwrite(&header, sizeof(header), 1, outputFile);
    fwrite(pixels, numberOfPixels, 1, outputFile);
    fclose(outputFile);

    printf("Finish writing to file.\n");
}

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++){
        float tita = 2.0f * M_PI * i / num_segments;//get the current angle
        float x = r * cosf(tita);//calculate the x component
        float y = r * sinf(tita);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void

display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    for(int i=0; i<1000; i+=hash_cell_x){
        glBegin(GL_LINES);{
            glVertex2d(i, 0);
            glVertex2d(i,1000);
        }
        glEnd();

    }
    for(int i=0; i<1000; i+=hash_cell_y){
        glBegin(GL_LINES);{
            glVertex2d(0, i);
            glVertex2d(1000,i);
        }
        glEnd();

    }

    glColor3f(0.0f, 0.0f, 1.0f);

    for(int i = 0; i<n; i++){

        glBegin(GL_LINES);{
            glVertex2d(sist[i].pos.x, sist[i].pos.y);
            glVertex2d(sist[i].pos.x+10*cos(sist[i].angulo), sist[i].pos.y+10*sin(sist[i].angulo));
        }
        glEnd();

        glBegin(GL_POINTS);{
            glVertex2d(sist[i].pos.x, sist[i].pos.y);
        }
        glEnd();

    }


    glutSwapBuffers();  //refresca la pantalla
}
void
timercall(int value)
{
    glutTimerFunc(SLEEP_TICKS, timercall, 0);   //el refresco de la pantalla no se realiza hasta que llega a esta funcion
    glutPostRedisplay();
}

void
initGL(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //rojo, azul, verde, transparencia

	glPointSize(5.0);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
	glLineWidth(1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1000, 0.0, 1000, -1.0, 1.0);   //perspectiva, buscar para 3D
	glTranslatef(0.5, 0.5, 0.0);
}

void
glutStuff(int argc, const char *argv[]) //configura el entorno grafico, es la primera que tengo que llamar, en el programa principal, antes de empezar a graficar
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Graficos");
	initGL();
                                        //las anteriores son de memoria, las siguientes son importantes
	glutDisplayFunc(display);           //le tenemos que decir que la funcion que va a graficar se llama "display"
	glutTimerFunc(SLEEP_TICKS, timercall, 0);   //cada cuanto se va a refrescar el grafico,
                                            //timercall es el nombre de la funcion
                                            //como dice sleep_ticks se mide en ticks
}

void
callGlut()
{
    glutMainLoopEvent();    //llama a todas las funciones que tengan que ver con la parte grafica,
//    display();
}

#endif

#include <GL/glut.h>
#include <cstdlib>

const int BOX_SIZE = 30; 
const int ROWS = 7; 

void drawSquare(float x, float y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + BOX_SIZE, y);
    glVertex2f(x + BOX_SIZE, y + BOX_SIZE);
    glVertex2f(x, y + BOX_SIZE);
    glEnd();
    
    glColor3f(0, 0, 0); 
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + BOX_SIZE, y);
    glVertex2f(x + BOX_SIZE, y + BOX_SIZE);
    glVertex2f(x, y + BOX_SIZE);
    glEnd();
}

void drawPyramid() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= i; j++) {
            float r = (rand() % 100) / 100.0f;
            float g = (rand() % 100) / 100.0f;
            float b = (rand() % 100) / 100.0f;
            drawSquare((j - i / 2.0) * BOX_SIZE, i * BOX_SIZE, r, g, b);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-BOX_SIZE / 2.0, -ROWS * BOX_SIZE / 2.0, 0); 
    drawPyramid();
    glPopMatrix();
    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Piramida Bekasi Terbalik Warna-warni");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

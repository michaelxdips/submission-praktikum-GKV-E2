#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. GL_LINE_STRIP (Garis bersambung)
    glColor3f(1, 0, 0); 
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.9, 0.8);
    glVertex2f(-0.7, 0.6);
    glVertex2f(-0.5, 0.8);
    glEnd();

    // 2. GL_LINE_LOOP (Garis membentuk loop)
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4, 0.6);
    glVertex2f(-0.2, 0.8);
    glVertex2f(0.0, 0.6);
    glVertex2f(-0.2, 0.4);
    glEnd();

    // 3. GL_TRIANGLE_FAN (Kipas segitiga)
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.3, 0.6);
    glVertex2f(0.1, 0.4);
    glVertex2f(0.2, 0.3);
    glVertex2f(0.4, 0.3);
    glVertex2f(0.5, 0.4);
    glEnd();

    // 4. GL_TRIANGLE_STRIP (Strip segitiga)
    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-0.9, 0.0);
    glVertex2f(-0.7, 0.2);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.3, 0.2);
    glVertex2f(-0.1, 0.0);
    glEnd();

    // 5. GL_QUADS (Empat sisi / persegi)
    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(0.1, -0.1);
    glVertex2f(0.5, -0.1);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.1, -0.5);
    glEnd();

    // 6. GL_QUAD_STRIP (Strip empat sisi)
    glColor3f(0, 1, 1);
    glBegin(GL_QUAD_STRIP);
    glVertex2f(-0.9, -0.6);
    glVertex2f(-0.7, -0.4);
    glVertex2f(-0.5, -0.6);
    glVertex2f(-0.3, -0.4);
    glVertex2f(-0.1, -0.6);
    glVertex2f(0.1, -0.4);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GLUT Primitives");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


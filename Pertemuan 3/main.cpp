#include <GL/glut.h>
#include <cmath>

// Posisi mobil
float carX = 0.0f;
float carY = -0.15f;
float carSpeed = 0.01f;
float wheelAngle = 0.0f;
bool isMoving = false;
int lastDirection = 0; // 0: none, 1: forward, -1: backward, 2: left, 3: right

void Lingkaran(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void Roda(float cx, float cy, float r, float angle) {
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    // Roda hitam
    glColor3f(0.0f, 0.0f, 0.0f);
    Lingkaran(0.0f, 0.0f, r, 20);
    
    // Velg roda
    glColor3f(0.7f, 0.7f, 0.7f);
    Lingkaran(0.0f, 0.0f, r * 0.6f, 20);
    
    // Jari-jari roda
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 5; i++) {
        float theta = 2.0f * M_PI * i / 5;
        float x = r * 0.9f * cosf(theta);
        float y = r * 0.9f * sinf(theta);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(x, y);
    }
    glEnd();
    
    glPopMatrix();
}

void Kota() {
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.2f); glVertex2f(-0.7f, -0.2f); glVertex2f(-0.7f, 0.3f); glVertex2f(-1.0f, 0.3f);
        glVertex2f(-0.6f, -0.2f); glVertex2f(-0.3f, -0.2f); glVertex2f(-0.3f, 0.5f); glVertex2f(-0.6f, 0.5f);
        glVertex2f(-0.2f, -0.2f); glVertex2f(0.1f, -0.2f); glVertex2f(0.1f, 0.4f); glVertex2f(-0.2f, 0.4f);
        glVertex2f(0.2f, -0.2f); glVertex2f(0.5f, -0.2f); glVertex2f(0.5f, 0.6f); glVertex2f(0.2f, 0.6f);
        glVertex2f(0.6f, -0.2f); glVertex2f(1.0f, -0.2f); glVertex2f(1.0f, 0.3f); glVertex2f(0.6f, 0.3f);
    glEnd();
    
    // Jendela-jendela
    glColor3f(0.8f, 0.8f, 0.4f);
    for (float x = -0.95f; x < 1.0f; x += 0.2f) {
        for (float y = -0.1f; y < 0.6f; y += 0.15f) {
            if (((x > -0.7f && x < -0.6f) || (x > -0.3f && x < -0.2f) || 
                 (x > 0.1f && x < 0.2f) || (x > 0.5f && x < 0.6f)) || y < -0.2f) {
                continue;
            }
            if (((x >= -1.0f && x <= -0.7f) && y > 0.3f) || 
                ((x >= -0.6f && x <= -0.3f) && y > 0.5f) ||
                ((x >= -0.2f && x <= 0.1f) && y > 0.4f) ||
                ((x >= 0.2f && x <= 0.5f) && y > 0.6f) ||
                ((x >= 0.6f && x <= 1.0f) && y > 0.3f)) {
                continue;
            }
            glRectf(x, y, x + 0.1f, y + 0.1f);
        }
    }
}

void Jalan() {
    // Jalan utama
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.4f);
        glVertex2f(1.0f, -0.4f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(-1.0f, 0.0f);
    glEnd();
    
    // Garis tengah jalan
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, -0.2f);
        glVertex2f(1.0f, -0.2f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void Mobil() {
    glPushMatrix();
    glTranslatef(carX, carY, 0.0f);
    
    // Badan mobil
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.4f, 0.0f);
        glVertex2f(0.4f, 0.0f);
        glVertex2f(0.4f, 0.1f);
        glVertex2f(-0.4f, 0.1f);
    glEnd();
    
    // Kabin mobil
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(0.2f, 0.25f);
        glVertex2f(-0.2f, 0.25f);
    glEnd();
    
    // Kaca depan
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.18f, 0.12f);
        glVertex2f(0.18f, 0.12f);
        glVertex2f(0.18f, 0.23f);
        glVertex2f(-0.18f, 0.23f);
    glEnd();
    
    // Lampu depan
    glColor3f(1.0f, 1.0f, 0.0f);
    Lingkaran(0.38f, 0.07f, 0.03f, 10);
    
    // Lampu belakang
    glColor3f(1.0f, 0.0f, 0.0f);
    Lingkaran(-0.38f, 0.07f, 0.03f, 10);
    
    // Roda-roda
    Roda(-0.25f, 0.0f, 0.1f, wheelAngle);
    Roda(0.25f, 0.0f, 0.1f, wheelAngle);
    
    // Efek lampu saat bergerak
    if (isMoving) {
        glColor3f(1.0f, 1.0f, 0.3f);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.4f, 0.05f);
            glVertex2f(0.6f, 0.0f);
            glVertex2f(0.6f, 0.1f);
        glEnd();
    }
    
    glPopMatrix();
}

void Langit() {
    // Langit gradien
    glBegin(GL_QUADS);
        glColor3f(0.2f, 0.2f, 0.8f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3f(0.5f, 0.5f, 0.9f);
        glVertex2f(1.0f, -0.0f);
        glVertex2f(-1.0f, -0.0f);
    glEnd();
    
    // Matahari
    glColor3f(1.0f, 0.8f, 0.0f);
    Lingkaran(0.7f, 0.7f, 0.1f, 30);
    
    // Awan
    glColor3f(1.0f, 1.0f, 1.0f);
    Lingkaran(-0.7f, 0.7f, 0.08f, 20);
    Lingkaran(-0.6f, 0.75f, 0.1f, 20);
    Lingkaran(-0.5f, 0.7f, 0.08f, 20);
    
    Lingkaran(0.1f, 0.6f, 0.07f, 20);
    Lingkaran(0.2f, 0.65f, 0.09f, 20);
    Lingkaran(0.3f, 0.6f, 0.07f, 20);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    Langit();
    Kota();
    Jalan();
    Mobil();
    
    glutSwapBuffers();
}

void update(int value) {
    if (isMoving) {
        // Putar roda
        wheelAngle += 10.0f;
        if (wheelAngle > 360.0f) {
            wheelAngle -= 360.0f;
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void keyboard(unsigned char key, int x, int y) {
    isMoving = true;
    
    switch (key) {
        case 'w':
        case 'W':
            carY += carSpeed;
            lastDirection = 1;
            break;
        case 's':
        case 'S':
            carY -= carSpeed;
            lastDirection = -1;
            break;
        case 'a':
        case 'A':
            carX -= carSpeed;
            lastDirection = 2;
            break;
        case 'd':
        case 'D':
            carX += carSpeed;
            lastDirection = 3;
            break;
        case 27: // ESC
            exit(0);
            break;
    }
    
    // Batasi area mobil
    if (carX < -0.9f) carX = -0.9f;
    if (carX > 0.9f) carX = 0.9f;
    if (carY < -0.4f) carY = -0.4f;
    if (carY > 0.7f) carY = 0.7f;
    
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    isMoving = false;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil dengan Kontrol WASD");
    
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}

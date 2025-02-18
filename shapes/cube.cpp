#include <GL/glut.h> // Include the GLUT header file

// Rotation angle
float angle = 0.0f;

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
}

// Function to draw the cube
void drawCube() {
    glBegin(GL_QUADS); // Begin drawing the cube with 6 quads

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Back face
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Top face
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Bottom face
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Right face
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Left face
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    glEnd(); // End of drawing
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity(); // Reset the model-view matrix

    // Translate and rotate the cube
    glTranslatef(0.0f, 0.0f, -5.0f); // Move the cube back
    glRotatef(angle, 1.0f, 1.0f, 1.0f); // Rotate the cube

    drawCube(); // Draw the cube

    glutSwapBuffers(); // Swap the front and back buffers
}

// Function to update the rotation angle
void update(int value) {
    angle += 2.0f; // Increment the rotation angle
    if (angle > 360) {
        angle -= 360;
    }

    glutPostRedisplay(); // Request a re-render
    glutTimerFunc(16, update, 0); // Call update again in 16ms (~60 FPS)
}

// Function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Set the viewport to cover the new window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix
    glLoadIdentity(); // Reset the projection matrix
    gluPerspective(45.0f, (float)w / (float)h, 1.0f, 200.0f); // Set up a perspective projection
    glMatrixMode(GL_MODELVIEW); // Switch back to the model-view matrix
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set up the display mode
    glutInitWindowSize(800, 600); // Set the window size
    glutCreateWindow("Rotating Cube"); // Create the window with a title

    init(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Register the display function
    glutReshapeFunc(reshape); // Register the reshape function
    glutTimerFunc(25, update, 0); // Register the update function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
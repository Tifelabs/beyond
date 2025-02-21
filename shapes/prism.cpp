#include <GL/glut.h> // Include the GLUT header file

// Rotation angle
float angle = 0.0f;

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
}

// Function to draw the triangular prism
void drawPrism() {
    glBegin(GL_TRIANGLES); // Draw the two triangular bases

    // Base 1 (front triangle)
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex3f( 0.0f,  1.0f,  1.0f); // Top vertex
    glVertex3f(-1.0f, -1.0f,  1.0f); // Bottom left vertex
    glVertex3f( 1.0f, -1.0f,  1.0f); // Bottom right vertex

    // Base 2 (back triangle)
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glVertex3f( 0.0f,  1.0f, -1.0f); // Top vertex
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom left vertex
    glVertex3f( 1.0f, -1.0f, -1.0f); // Bottom right vertex

    glEnd();

    glBegin(GL_QUADS); // Draw the three rectangular faces

    // Face 1 (right face)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glVertex3f( 1.0f, -1.0f,  1.0f); // Bottom right front
    glVertex3f( 1.0f, -1.0f, -1.0f); // Bottom right back
    glVertex3f( 0.0f,  1.0f, -1.0f); // Top back
    glVertex3f( 0.0f,  1.0f,  1.0f); // Top front

    // Face 2 (left face)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glVertex3f(-1.0f, -1.0f,  1.0f); // Bottom left front
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom left back
    glVertex3f( 0.0f,  1.0f, -1.0f); // Top back
    glVertex3f( 0.0f,  1.0f,  1.0f); // Top front

    // Face 3 (bottom face)
    glColor3f(1.0f, 0.0f, 1.0f); // Magenta
    glVertex3f(-1.0f, -1.0f,  1.0f); // Bottom left front
    glVertex3f( 1.0f, -1.0f,  1.0f); // Bottom right front
    glVertex3f( 1.0f, -1.0f, -1.0f); // Bottom right back
    glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom left back

    glEnd();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity(); // Reset the model-view matrix

    // Translate and rotate the prism
    glTranslatef(0.0f, 0.0f, -5.0f); // Move the prism back
    glRotatef(angle, 1.0f, 1.0f, 1.0f); // Rotate the prism

    drawPrism(); // Draw the prism

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
    glutCreateWindow("Rotating Triangular Prism"); // Create the window with a title

    init(); // Initialize OpenGL settings

    glutDisplayFunc(display); // Register the display function
    glutReshapeFunc(reshape); // Register the reshape function
    glutTimerFunc(25, update, 0); // Register the update function

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}
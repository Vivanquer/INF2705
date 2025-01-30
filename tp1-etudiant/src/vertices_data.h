#ifndef VERTICES_DATA_H
#define VERTICES_DATA_H

const GLfloat triVertices[] = {
    -0.5f, -0.5f, 
     0.5f, -0.5f, 
     0.0f,  0.5f  
};

const GLfloat squareVertices[] = {
    -0.5f, -0.5f, // Bottom-left
     0.5f, -0.5f, // Bottom-right
     0.5f,  0.5f, // Top-right
    -0.5f,  0.5f  // Top-left
};

const GLfloat colorTriVertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Bottom-left, red
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom-right, green
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // Top, blue
};

const GLfloat colorSquareVertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Bottom-left, red
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom-right, green
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // Top-right, blue
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f  // Top-left, yellow
};


const GLfloat colorSquareVerticesReduced[] = {
    // First Triangle (Bottom-left to Top-right)
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom-left, red
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom-right, green
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // Top-right, blue

    // Second Triangle (Top-right to Top-left)
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // Top-right (reused)
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // Top-left, yellow
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f   // Bottom-left (reused)
};
const GLubyte indexes[] = {
    0, 1, 2, // First triangle
    2, 3, 0  // Second triangle
};


const GLfloat cubeVertices[] = {
    // +z
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     // -z
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
     // +x
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
     // -x
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
     // +y
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     // -y
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
};

const GLubyte cubeIndexes[] = {
     0,  1,  2,
     1,  3,  2,
    
     4,  5,  6,
     5,  7,  6,
    
     8,  9, 10,
     9, 11, 10,
    
    12, 13, 14,
    13, 15, 14,
    
    16, 17, 18,
    17, 19, 18,
    
    20, 21, 22,
    21, 23, 22,
};

#endif // VERTICES_DATA_H

#ifndef VERTICES_DATA_H
#define VERTICES_DATA_H

const GLfloat triVertices[] = {
    -0.5f, -0.5f, 
     0.5f, -0.5f, 
     0.0f,  0.5f  
};

const GLfloat squareVertices[] = {
    -0.5f, -0.5f, 
     0.5f, -0.5f, 
     0.5f,  0.5f,
    -0.5f,  0.5f  
};

const GLfloat colorTriVertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  
};

const GLfloat colorSquareVertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f  
};


const GLfloat colorSquareVerticesReduced[] = {
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  

     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f   
};
const GLubyte indexes[] = {
    0, 1, 2, 
    2, 3, 0  
};

const GLfloat sharedVertices[] = {
    // triangle
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 
    // square
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
     0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f  
};

const GLubyte squareIndices[] = {
    3, 4, 5,  
    5, 6, 3   
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

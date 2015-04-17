
    #include <GL/glew.h>
    #include <GL/glut.h>  
    #include <GL/gl.h>  
    #include <GL/glu.h>  
     
    #include <stdio.h>  
     
    GLuint program; 
     
    GLint attribute_coord2d; 
     
    char* file_read(const char* filename) 
    { 
      FILE* input = fopen(filename, "rb"); 
      if(input == NULL) return NULL; 
       
      if(fseek(input, 0, SEEK_END) == -1) return NULL; 
      long size = ftell(input); 
      if(size == -1) return NULL; 
      if(fseek(input, 0, SEEK_SET) == -1) return NULL; 
       
      /*if using c-compiler: dont cast malloc's return value*/ 
      char *content = (char*) malloc( (size_t) size +1  );   
      if(content == NULL) return NULL; 
       
      fread(content, 1, (size_t)size, input); 
      if(ferror(input)) { 
        free(content); 
        return NULL; 
      } 
       
      fclose(input); 
      content[size] = '\0'; 
      return content; 
    } 
     
    /** 
     * Display compilation errors from the OpenGL shader compiler 
     */ 
    void print_log(GLuint object) 
    { 
      GLint log_length = 0; 
      if (glIsShader(object)) 
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length); 
      else if (glIsProgram(object)) 
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length); 
      else { 
        fprintf(stderr, "printlog: Not a shader or a program\n"); 
        return; 
      } 
       
      char* log = (char*)malloc(log_length); 
       
      if (glIsShader(object)) 
        glGetShaderInfoLog(object, log_length, NULL, log); 
      else if (glIsProgram(object)) 
        glGetProgramInfoLog(object, log_length, NULL, log); 
       
      fprintf(stderr, "%s", log); 
      free(log); 
    } 
     
    /** 
     * Compile the shader from file 'filename', with error handling 
     */ 
    GLuint create_shader(const char* filename, GLenum type) 
    { 
      const GLchar* source = file_read(filename); 
      if (source == NULL) { 
        fprintf(stderr, "Error opening %s: ", filename); perror(""); 
        return 0; 
      } 
      GLuint res = glCreateShader(type); 
      const GLchar* sources[2] = { 
    #ifdef GL_ES_VERSION_2_0  
        "#version 100\n" 
        "#define GLES2\n", 
    #else  
        "#version 120\n", 
    #endif  
        source }; 
      glShaderSource(res, 2, sources, NULL); 
      free((void*)source); 
       
      glCompileShader(res); 
      GLint compile_ok = GL_FALSE; 
      glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok); 
      if (compile_ok == GL_FALSE) { 
        fprintf(stderr, "%s:", filename); 
        print_log(res); 
        glDeleteShader(res); 
        return 0; 
      } 
       
      return res; 
    } 
     
     
    int init_resources(void) 
    { 
      /* FILLED IN LATER */ 
        GLint compile_ok = GL_FALSE, link_ok = GL_FALSE; 
       
        GLuint vs, fs; 
      if ((vs = create_shader("triangle.v.glsl", GL_VERTEX_SHADER))   == 0) return 0; 
      if ((fs = create_shader("triangle.f.glsl", GL_FRAGMENT_SHADER)) == 0) return 0; 
       program = glCreateProgram(); 
      glAttachShader(program, vs); 
      glAttachShader(program, fs); 
      glLinkProgram(program); 
      glGetProgramiv(program, GL_LINK_STATUS, &link_ok); 
       if (!link_ok) { 
        fprintf(stderr, "glLinkProgram:"); 
        print_log(program); 
       } 
      return 0; 
    } 
       
    void onDisplay() 
    { 
      /* Clear the background as white */ 
      glClearColor(1.0, 1.0, 1.0, 1.0); 
      glClear(GL_COLOR_BUFFER_BIT); 
       
      glUseProgram(program); 
      glEnableVertexAttribArray(attribute_coord2d); 
      GLfloat triangle_vertices[] = { 
         0.0,  0.8, 
        -0.8, -0.8, 
         0.8, -0.8, 
      }; 
      /* Describe our vertices array to OpenGL (it can't guess its format automatically) */ 
      glVertexAttribPointer( 
        attribute_coord2d, // attribute  
        2,                 // number of elements per vertex, here (x,y)  
        GL_FLOAT,          // the type of each element  
        GL_FALSE,          // take our values as-is  
        0,                 // no extra data between each position  
        triangle_vertices  // pointer to the C array  
      ); 
       
      /* Push each element in buffer_vertices to the vertex shader */ 
      glDrawArrays(GL_TRIANGLES, 0, 3); 
      glDisableVertexAttribArray(attribute_coord2d); 
       
      /* Display the result */ 
      glutSwapBuffers(); 
    } 
     
    void free_resources() 
    { 
      glDeleteProgram(program); 
    } 
       
    int main(int argc, char* argv[]) 
    { 
        /* Glut-related initialising functions */ 
        glutInit(&argc, argv); 
        glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH); 
        glEnable(GL_BLEND); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        glutInitWindowSize(640, 480); 
        glutCreateWindow("My First Triangle"); 
       
     
     
        /* Extension wrangler initialising */ 
        GLenum glew_status = glewInit(); 
        if (glew_status != GLEW_OK) 
        { 
            fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status)); 
            return EXIT_FAILURE; 
        } 
       
        /* When all init functions runs without errors, 
        the program can initialise the resources */ 
        if (0 == init_resources()) 
        { 
            /* We can display it if everything goes OK */ 
            glutDisplayFunc(onDisplay); 
            glutMainLoop(); 
        } 
       
        /* If the program exits in the usual way, 
        free resources and exit with a success */ 
        free_resources(); 
        return EXIT_SUCCESS; 
    } 

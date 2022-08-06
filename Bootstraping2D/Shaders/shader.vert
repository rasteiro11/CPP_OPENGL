#version 330                                                                  
                                                                              
layout (location = 0) in vec3 pos;											  
uniform vec3 uniform_color_vec;
//uniform float uniform_green;
//uniform float uniform_blue;
out vec4 vCol;
																			  
void main()                                                                   
{                                                                             
    gl_Position = vec4(pos, 1.0);						  
    vCol = vec4(uniform_color_vec, 1.0);
}

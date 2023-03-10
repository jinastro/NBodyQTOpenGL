#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float offset;
uniform mat4 theMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
//       gl_Position = theMatrix*vec4(aPos.x+offset, aPos.y, aPos.z, 1.0);
       gl_Position = projection*view*model*vec4(aPos.x+offset, aPos.y, aPos.z, 1.0);
       ourColor = aColor;
}

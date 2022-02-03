#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 texCoords;

uniform bool  chaos;
uniform bool  confuse;
uniform bool  shake;
uniform float time;

void main()
{
    gl_Position = vec4(vertex.xy,0.0f, 1.0f);
    texCoords = vertex.zw;

    if(chaos)
    {
        vec2 pos = vec2(texCoords.x + sin(time) * 0.3f,texCoords.y + cos(time) * 0.3f) ;
        texCoords = pos;
    }
    else if(confuse)
    {
        texCoords = vec2(1.0 - texCoords.x, 1.0 - texCoords.y);
    }
    else if(shake)
    {
        gl_Position.x +=cos(time * 10.f) * 0.01f;
        gl_Position.y +=cos(time * 15.f) * 0.01f;
    }
}
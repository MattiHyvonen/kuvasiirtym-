#version 330 core
in vec2 uv;

out vec3 color;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float maara;

void main(){
    vec2 d = vec2(maara, 0);
    color = texture(texture0, uv + d).rgb;
}

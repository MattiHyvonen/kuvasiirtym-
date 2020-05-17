#version 330 core
in vec2 uv;

out vec3 color;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float maara;

void main(){
   float m = maara;
   if(m < 0) m = 0;
   if(m > 1) m = 1;
   vec3 c0 = texture(texture0, uv).rgb;
   vec3 c1 = texture(texture1, uv).rgb;
   
   color = mix(c0, c1, m);
   
}

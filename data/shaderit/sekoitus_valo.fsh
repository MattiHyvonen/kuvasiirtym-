#version 330 core
in vec2 uv;

out vec3 color;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2; //alfakartta. Alfa katsotaan r-kanavasta

uniform float maara;

void main(){

    float m = maara;
    if(m>1) m=1;
    if(m<0) m=0;

    float m2 = maara-1;
    if(m2<0) m2=0;
    if(m2>1) m2=1;
    
    vec3 c0 = texture(texture0, uv).rgb;
    vec3 c1 = texture(texture1, uv).rgb;
    float a = texture(texture2, uv).r;

    a = a*m;

    if(a > 1) a = 1;
    if(a < 0) a = 0;

    vec3 valo = a * c1 * 0.7 * (1-a);
    vec3 sekoitus = mix(c0, c1, a);
    
    color = mix(sekoitus + valo, c1, m2);

}

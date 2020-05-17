#version 330 core
in vec2 uv;

out vec3 color;

uniform sampler2D texture0;
uniform sampler2D texture1; //syrjäytyskartta
uniform sampler2D texture2; //kiertokartta

uniform float maara;


vec2 kierto(vec2 v, float f) {
    float c = cos(f * 6.28318);
    float s = sin(f * 6.28318);
    vec2 v2;
    v2.x = c*v.x - s*v.y;
    v2.y = s*v.x + c*v.y;
    return v2;
}


void main(void){

    vec2 o = vec2(-0.5, -0.5);
    
    vec2 syrjahdys = (texture(texture1, uv).rg + o) * maara;
    
    //otetaan kiertomäärä kiertokartasta
    float kiertomaara = 0;
    
    //kierretään syrjäytystä
    syrjahdys = kierto(syrjahdys, kiertomaara) * 0.04;
    
    vec3 c0 = texture(texture0, uv + syrjahdys).rgb;
    
    color = c0;
}

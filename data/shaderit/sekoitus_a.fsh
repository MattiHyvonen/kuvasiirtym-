#version 330 core
in vec2 uv;

out vec3 color;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2; //alfakartta. Alfa katsotaan r-kanavasta

uniform float maara;

void main(){

    vec3 c0 = texture(texture0, uv).rgb;
    vec3 c1 = texture(texture1, uv).rgb;
    float a = texture(texture2, uv).g;

	float marginaali = 0.015;
	
	//vähenee
	float kirkkaus = pow(1-maara, 5) + 0.025;
	
	//vähenee
	float kirkkaus2 = (1 - maara) * 0.75 + 1;
	
    if(a > maara + marginaali)
        color = c0 * kirkkaus + c1;
    
	else if (a < maara - marginaali)
        color = c1 * kirkkaus2;
	
	else {
		float a_ = (a - maara + marginaali) / (marginaali*2);
		//color = vec3(a_, 1-a_, a_);
		
		vec3 g = c0 * kirkkaus + c1;
		vec3 l = c1 * kirkkaus2;
		
		color = mix(l, g, a_);
		
	}
}

#ifdef GL_ES
precision mediump float;
#endif
uniform float myvar;
uniform vec2 position;
uniform float map[2];
void main(){
	float lightlvl;
	float transparency;
	float xdiff=(gl_FragCoord.x-position.x)*(gl_FragCoord.x-position.x);
	float ydiff=((960-gl_FragCoord.y)-position.y)*((960-gl_FragCoord.y)-position.y);
	float ton=xdiff+ydiff;
	float radius=100;
	


	//lightlvl = 1-(ton/(radius * radius));
	//transparency = ((radius-(sqrt(ton)))*(radius-(sqrt(ton))))/(radius*radius);
	


	//gl_FragColor=vec4(lightlvl, lightlvl, lightlvl, transparency);
	float u_resolution = 1080;
	vec2 st= gl_FragCoord.xy/u_resolution;
	vec2 pos=position/u_resolution;
	
	float pct = distance(st, pos)*8;
	vec3 color=vec3(pct,pct,pct);

	if(1-color.x>0){
		transparency = 0.5;
	}
	else{
		transparency = 0.5-(1-color.x);
		
	}
	


	gl_FragColor = vec4((1-color.x), (1-color.y), (1-color.z),transparency);

	
}
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
	float radius=200;
	
	lightlvl = 1-(ton/(radius * radius));

	
	
	
	
	
	

	

	
	
	

	
	transparency = ((radius*radius)-ton)/(radius*radius);
	// 1/0.1 -- 1/400000
	if(transparency >= 0.5){
		transparency = 0.5;
	}
	

	
	
	if(transparency<=1){
		transparency=(1+((ton/(radius*radius)))-1);
		
		
		
	}
	
	if(transparency <=0.5){
		transparency = 0.5;
	}
	
	
	
	
	
	gl_FragColor=vec4(lightlvl,lightlvl,lightlvl,transparency);
	//gl_FragColor=vec4(lightlvl,lightlvl,lightlvl,map[0]);

	
}
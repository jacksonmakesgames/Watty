precision mediump float;
varying highp vec4 vs_position;
varying highp vec2 vs_uv;
	
varying highp float vs_tid;
varying highp vec4 vs_color;


uniform sampler2D textures_0;
uniform sampler2D textures_1;
uniform sampler2D textures_2;
uniform sampler2D textures_3;
uniform sampler2D textures_4;
uniform sampler2D textures_5;
uniform sampler2D textures_6;
uniform sampler2D textures_7;
uniform sampler2D textures_8;
uniform sampler2D textures_9;
uniform sampler2D textures_10;
uniform sampler2D textures_11;
uniform sampler2D textures_12;
uniform sampler2D textures_13;
uniform sampler2D textures_14;
uniform sampler2D textures_15;


void main(){
	vec4 texColor = vs_color;
	
	if(vs_tid > 0.0){
		int tid = int(vs_tid - 0.5);
		if(tid == 0){
			texColor =  vs_color * texture2D(textures_0, vs_uv);
		}
		else if(tid == 1){
			texColor =  vs_color * texture2D(textures_1, vs_uv);
		}
		else if(tid == 2){
			texColor =  vs_color * texture2D(textures_2, vs_uv);
		}
		else if(tid == 3){
			texColor =  vs_color * texture2D(textures_3, vs_uv);
		}
		else if(tid == 4){
			texColor =  vs_color * texture2D(textures_4, vs_uv);
		}
		else if(tid == 5){
			texColor =  vs_color * texture2D(textures_5, vs_uv);
		}
		else if(tid == 6){
			texColor =  vs_color * texture2D(textures_6, vs_uv);
		}
		else if(tid == 7){
			texColor =  vs_color * texture2D(textures_7, vs_uv);
		}
		else if(tid == 8){
			texColor =  vs_color * texture2D(textures_8, vs_uv);
		}
		else if(tid == 9){
			texColor =  vs_color * texture2D(textures_9, vs_uv);
		}
		else if(tid == 10){
			texColor =  vs_color * texture2D(textures_10, vs_uv);
		}
		else if(tid == 11){
			texColor =  vs_color * texture2D(textures_11, vs_uv);
		}
		else if(tid == 12){
			texColor =  vs_color * texture2D(textures_12, vs_uv);
		}
		else if(tid == 13){
			texColor =  vs_color * texture2D(textures_13, vs_uv);
		}
		else if(tid == 14){
			texColor =  vs_color * texture2D(textures_14, vs_uv);
		}
		else if(tid == 15){
			texColor =  vs_color * texture2D(textures_15, vs_uv);
		}
		else{
			texColor =  vec4(1,0,1,1) ;
		}
	}
		

		
	gl_FragColor = texColor;
}
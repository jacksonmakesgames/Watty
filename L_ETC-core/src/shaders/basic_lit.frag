#version 440 core 

layout (location = 0) out vec4 color; 

uniform vec2 light_pos;	
uniform vec4 col;

in DATA{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
}fs_in;

uniform sampler2D textures[32];

void main(){
	float intensity = .1f + 1.0 / length(fs_in.position.xy - light_pos);
	
	vec4 texColor = fs_in.color;

	if(fs_in.tid > 0){
		int tid = int(fs_in.tid-0.5);
		texColor = fs_in.color * texColor * texture(textures[tid], fs_in.uv);
	}

	color =  vec4(texColor.r * intensity, texColor.g * intensity, texColor.b * intensity, texColor.a);
}


	
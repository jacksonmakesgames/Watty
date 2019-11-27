#version 330 core 

layout (location = 0) out vec4 color; 
uniform vec4 col;
uniform vec3 light_pos;	

uniform float light_radius;
uniform float light_intensity;

in DATA{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
}fs_in;

uniform sampler2D textures[32];



void main(){
	vec4 texColor = fs_in.color;
	//float intensity = .1f + 1.0 / length(fs_in.position - light_pos);

	if(fs_in.tid > 0.0){
		int tid = int(fs_in.tid-0.5);
		texColor =  fs_in.color * texture(textures[tid], fs_in.uv);
	}
	
	
	float x = light_pos.x-fs_in.position.x;
	float y = light_pos.y-fs_in.position.y;
	float z = light_pos.z-fs_in.position.z;
	float val = x*x + y*y + z*z;

	float dst = sqrt(val);
	float intensity = clamp(1.0 - dst / light_radius, 0.0, 1.0) * light_intensity;
	vec4 fragColor = vec4(texColor.r, texColor.g, texColor.b, 1.0)*intensity;

	fragColor.a = texColor.a;
	color = fragColor;
}
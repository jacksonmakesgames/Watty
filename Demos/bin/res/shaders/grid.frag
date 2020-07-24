#version 450 core

layout (location = 0) out vec4 color; 

//Shader Inputs
uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iCellSizePixels;          


#define PI 3.141592

// size of a square in pixel
#define N 9

vec2 fragCoord;

in DATA{
	vec4 position;
	vec4 color;
}fs_in;

void main()
{
	fragCoord = gl_FragCoord.xy;
	fragCoord-=iResolution.xy/2.0;
    
    fragCoord = cos(PI/N*fragCoord);
	color = vec4(1.0f)-0.5*smoothstep(0.9,1.0,max(fragCoord.x,fragCoord.y)) * fs_in.color;
}



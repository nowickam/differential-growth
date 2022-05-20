#version 120

#define MAX_STEPS 1024
#define MIN_DISTANCE 0.01
#define MAX_DISTANCE 100

// these are our textures
uniform sampler2DRect depth;
varying vec2 texCoordVarying;

uniform float width, height;

void main()
{
    float u = gl_FragCoord.x / width;
    float v = gl_FragCoord.y / height;
    vec2 uv = vec2(u, v) * 2. - 1.;
    uv.x *= width/height;
    
    vec4 tex = texture2DRect(depth, gl_FragCoord.xy);
    vec4 color = vec4(1.0);
    
    if(tex.r != 0.0){
        vec4 color1 = vec4(.3, .4, .9, 1.0);
        vec4 color2 = vec4(.7, .6, .2, 1.0);
        color = mix(color1, color2, tex.r);
        color += smoothstep(color2.r-.07, color2.r+.03, color.r);
    }

    gl_FragColor = tex*color;
}

#version 120

// these are our textures
uniform sampler2DRect depth;
varying vec2 texCoordVarying;

uniform float width, height;

vec4 lightBlue = vec4(127., 150., 255., 255.)/255.;
vec4 blue = vec4(.3, .4, .9, 1.0);
vec4 red = vec4(218., 44., 56., 255.)/255.;
vec4 yellow = vec4(.7, .6, .2, 1.0);
vec4 green = vec4(34., 111., 84., 255.)/255.;

void main()
{
    float u = gl_FragCoord.x / width;
    float v = gl_FragCoord.y / height;
    vec2 uv = vec2(u, v) * 2. - 1.;
    uv.x *= width/height;
    
    vec4 tex = texture2DRect(depth, gl_FragCoord.xy);
    vec4 color = vec4(1.0);
    
    if(tex.r != 0.0){
//        vec4 color1 = green;
//        vec4 color2 = red;
        
        vec4 color1 = blue;
        vec4 color2 = yellow;
        
        color = mix(color1, color2, tex.r);
        color += smoothstep(color2.r-.07, color2.r+.03, color.r);
    }

    gl_FragColor = tex*color;
}

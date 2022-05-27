#version 120

#define MAX_STEPS 128
#define MIN_DISTANCE 0.1
#define MAX_DISTANCE 100

// these are our textures
uniform sampler2DRect depth;
varying vec2 texCoordVarying;

uniform float width, height;
uniform float mouseX, mouseY;

vec4 lightBlue = vec4(127., 150., 255., 255.)/255.;
vec4 blue = vec4(.3, .4, .9, 1.0);
vec4 red = vec4(218., 44., 56., 255.)/255.;
vec4 yellow = vec4(.7, .6, .2, 1.0);
vec4 green = vec4(34., 111., 84., 255.)/255.;

float random (vec2 uv) {
  return fract(sin(dot(uv.xy,
                       vec2(12.9898,78.233)))*
      43758.5453123);
  }

float noise(vec2 st){
  vec2 i=floor(st);
  vec2 f=fract(st);
  vec2 u=f*f*(3.-2.*f);
  return mix(mix(random(i+vec2(0.,0.)),random(i+vec2(1.,0.)),u.x),
  mix(random(i+vec2(0.,1.)),random(i+vec2(1.,1.)),u.x),u.y);
}

float map(vec3 p) {
//    return length(p) - 2.0;
    if(texture2DRect(depth, gl_FragCoord.xy).r == 0)
        return 1.0;
    float final = length(p)*(texture2DRect(depth, gl_FragCoord.xy).r);
    final = abs(final*final);
    return final;
}

vec3 getNormal(vec3 p) {
  // sampling around the position p
  vec2 e = vec2(10., 0.);
  float d = map(p);
  vec3 n = d - vec3(map(p - e.xyy), map(p - e.yxy), map(p - e.yyx));

  return normalize(n);
}

float diffuseLighting(vec3 p) {
    float x = mouseX - width/2;
    float y = height/2 - mouseY;
    
    vec3 lightPosition = vec3(x, y, -100.0);

  vec3 light = normalize(lightPosition - p);
  vec3 normal = getNormal(p);

  float diffuse = clamp(dot(light, normal), 0., 1.);

  return diffuse;
}



void main()
{
    float u = gl_FragCoord.x / width;
    float v = gl_FragCoord.y / height;
    vec2 uv = vec2(u, v) * 2. - 1.;
    uv.x *= width/height;
    
//    vec2 uv = gl_FragCoord.xy;
    
    // throw rays from the camera to each pixel
    vec3 rayOrigin = vec3(0., 0., -3.);
    vec3 rayDirection = normalize(vec3(uv, 1.));
    
    float distanceOrigin = 0.;
    float diffuse;
    
    for (int i = 0; i < MAX_STEPS; i++) {
        vec3 position = rayOrigin + distanceOrigin * rayDirection;

        float map = map(position);
        distanceOrigin += map;

        if (distanceOrigin < MIN_DISTANCE || distanceOrigin > MAX_DISTANCE)
          break;

        diffuse = diffuseLighting(position);
    }
    
    distanceOrigin /= 4.0;
    vec3 shape = vec3(1.) * diffuse;
    
    vec4 color;
    vec4 color1 = blue;
    vec4 color2 = yellow;
    color = mix(color1, color2, shape.r - 0.25);
    color += smoothstep(color2.r-.05, color2.r+.01, color.r);
    
    vec4 final = vec4(color.xyz * shape, 1.0);

    gl_FragColor = final;
//    gl_FragColor = vec4(1.);
//    gl_FragColor = texture2DRect(depth, gl_FragCoord.xy);
}

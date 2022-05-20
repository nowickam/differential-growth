#version 120

#define MAX_STEPS 1024
#define MIN_DISTANCE 0.01
#define MAX_DISTANCE 100

// these are our textures
uniform sampler2DRect depth;
varying vec2 texCoordVarying;

uniform float width, height;

float map(vec3 p) {
//    return length(p) - 2.0;
    return texture2DRect(depth, gl_FragCoord.xy * length(p)).r;
}

vec3 getNormal(vec3 p) {
  // sampling around the position p
  vec2 e = vec2(0.1, 0.);
  float d = map(p);
  vec3 n = d - vec3(map(p - e.xyy), map(p - e.yxy), map(p - e.yyx));

  return normalize(n);
}

float diffuseLighting(vec3 p) {
  vec3 lightPosition = vec3(2.0, 2.0, -5.0);

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
    vec4 color = vec4(shape, 1.0);

    gl_FragColor = color;
//    gl_FragColor = vec4(1.);
//    gl_FragColor = texture2DRect(depth, gl_FragCoord.xy);
}

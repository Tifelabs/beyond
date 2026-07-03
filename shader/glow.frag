#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float sdCircle(vec2 p, float r){
    return length(p) - r;
}

float glow(float d, float strength, float thickness){
    return thickness / (abs(d) * strength + 0.001);
}

void main(){
    vec2 st = gl_FragCoord.xy / u_resolution.xy;
    vec2 p = st * 2.0 - 1.0;
    p.x *= u_resolution.x / u_resolution.y;

    vec2 mouse = (u_mouse / u_resolution) * 2.0 - 1.0;
    mouse.x *= u_resolution.x / u_resolution.y;

    float r = 0.45 + 0.02 * sin(u_time * 1.5);
    float d = sdCircle(p, r);

    vec3 glassColor = vec3(0.55, 0.75, 0.85);

    // rim: a bright band just inside the edge (poor-man's fresnel)
    float rim = smoothstep(0.0, -0.08, d) * smoothstep(-0.25, -0.08, d);
    vec3 rimColor = vec3(0.6, 0.95, 1.0) * rim * 1.5;

    // interior refraction shimmer
    float shimmer = sin((p.x + p.y) * 12.0 + u_time * 2.0) * 0.05;
    vec3 interior = glassColor * (0.3 + 0.1 * shimmer);
    interior *= smoothstep(0.0, -0.05, d);

    // outer glow bleeding past the edge
    vec3 glowColor = vec3(0.4, 0.85, 1.0);
    float g = glow(d, 6.0, 0.02);
    vec3 outerGlow = glowColor * g;

    // mouse-driven hotspot inside the glass
    float mouseDist = length(p - mouse);
    float hotspot = smoothstep(0.35, 0.0, mouseDist) * smoothstep(0.0, -0.05, d);
    vec3 hotspotColor = vec3(1.0) * hotspot * 0.6;

    vec3 bg = vec3(0.02, 0.03, 0.05);
    vec3 color = bg + outerGlow + interior + rimColor + hotspotColor;

    gl_FragColor = vec4(color, 1.0);
}
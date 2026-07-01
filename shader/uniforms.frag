#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution; // Canvas size(width and Height)
uniform vec2 u_mouse;      // Mouse position in screen pixels
uniform float u_time;      // Time in seconds since load
uniform vec4 iMouse;       // mouse pixel coords. xy:current zw: click
uniform float iTime;       // Shader playback time(in seconds)


void main(){
    gl_FragColor = vec4(abs(cos(u_time)), 0.0, 0.0, 1.0);
}

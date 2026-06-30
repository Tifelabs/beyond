#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;


vec4 red(){
    return gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}

void main(){
    gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    red();
}

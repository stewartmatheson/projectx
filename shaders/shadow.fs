uniform sampler2D texture;

void main()
{
    // lookup the pixel in the texture
    vec2 res = vec2(1500, 1500);
    float pct = distance(gl_FragCoord.xy / res, vec2(0.5));
    gl_FragColor = vec4(0,0,0, pct);
}


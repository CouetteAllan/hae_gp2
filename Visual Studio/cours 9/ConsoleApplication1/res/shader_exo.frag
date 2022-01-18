//#define NO_TEXTURE
//#define HAS_UNIFORM_COLOR
#define HAS_ADD_COLOR

#ifdef HAS_TEXTURE
uniform sampler2D texture;
#endif

#ifdef HAS_UNIFORM_COLOR
uniform vec4 col;
#endif

#ifdef HAS_ADD_COLOR
uniform vec4 colAdd;
#endif
void main()
{
    // récupère le pixel dans la texture
    #ifdef HAS_TEXTURE
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    #else

    	#ifdef HAS_ADD_COLOR
    	vec4 pixel = vec4(0.0f,0.0f,0.0f,1.0f);
    	#else
    	vec4 pixel = vec4(1.0f,1.0f,1.0f,1.0f);
    	#endif 
    #endif

    #ifdef HAS_UNIFORM_COLOR
    pixel *= col;
    #endif

    #ifdef HAS_ADD_COLOR
    pixel *= colAdd;
    #endif


    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
}
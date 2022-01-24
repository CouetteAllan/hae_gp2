
uniform float dt;

void main()
{
    // transforme la position du vertex
	
	vec4 worldPos = gl_Vertex;
	worldPos.x += 20 * dt;
    gl_Position = gl_ModelViewProjectionMatrix * worldPos;

    // transforme les coordonnées de texture
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // transmet la couleur
    gl_FrontColor = gl_Color;
}
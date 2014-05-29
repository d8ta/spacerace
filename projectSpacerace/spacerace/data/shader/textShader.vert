#version 150 compatibility

out vec2 texCoords;

void main()
{
	// get the texture coords for the fragment shader
	texCoords = gl_MultiTexCoord0.st;

	gl_Position = gl_Vertex;
}

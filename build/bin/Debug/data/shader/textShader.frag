#version 150 compatibility

uniform sampler2D texture;
uniform vec4 color;

in vec2 texCoords;

void main()
{
	// combine the texture color with the background color.
	// Due to the text textures transparent background only the letters will cover the background color.
	gl_FragColor = texture2D(texture, texCoords) * color;
}

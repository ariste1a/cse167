// Vertex shader for per-pixel diffuse shading.The
// teapot is a good object to test this shader, since
// the .obj file includes surface normals.

// The shader computes the unit light direction and unit
// surface normal, which are passed to the fragment
// shader as varying variables.

// The shader also applies repulsion and attraction to light.

#version 120
#extension GL_EXT_gpu_shader4 : require

uniform int useToonShading;
uniform sampler2D tex;

varying vec3 normal, ptHalfVector, dirHalfVector, dirLightDir;

varying vec4 position_cs;
varying vec3 normal_cs;

varying vec4 ptDiffuse, ptAmbient, dirDiffuse, dirAmbient, ecPos, modelPos;

void main()
{	 
	vec4 _newVert = gl_Vertex;

	position_cs = gl_ModelViewMatrix * gl_Vertex;
	normal_cs = gl_NormalMatrix * gl_Normal;

	modelPos = gl_Vertex;

	_newVert = gl_ModelViewMatrix * _newVert;

	vec3 newVert = vec3(_newVert);

	// Note that gl_LightSource, gl_NormalMatrix, and gl_Normal
	// are pre-defined variables that access the current OpenGL
	// state.
	normal = normalize(gl_NormalMatrix * gl_Normal);

	// Point light calculations
	ecPos = _newVert;
	ptHalfVector = (gl_ModelViewMatrix * gl_LightSource[0].halfVector).xyz;
	ptDiffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ptAmbient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

	// Directional light calculations
	dirHalfVector = gl_LightSource[1].halfVector.xyz;
	dirDiffuse = gl_FrontMaterial.diffuse * gl_LightSource[1].diffuse;
	dirAmbient = gl_FrontMaterial.ambient * gl_LightSource[1].ambient;
	dirLightDir = normalize(vec3(gl_ModelViewMatrix * gl_LightSource[1].position));

	_newVert = gl_ProjectionMatrix * _newVert;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;

	// ftransform() is a built-in function that applies all
	// transformations (i.e., modelview and 
	// projection) to a vertex.
	//gl_Position = ftransform();
}

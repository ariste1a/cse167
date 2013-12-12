// Fragment shader for per-pixel diffuse shading. The
// teapot is a good object to test this shader, since
// the .obj file includes surface normals.

// The shader computes the dot product between the unit
// surface normal and light direction, which were 
// passed as varying inputs from the vertex shader. The
// result is multiplied with the vertex color, which is 
// accessed through a pre-defined varying variable.

#version 120
#extension GL_EXT_gpu_shader4 : require

uniform int useToonShading;
uniform sampler2D tex;
uniform vec4 eye;

varying vec3 normal, ptHalfVector, dirHalfVector, dirLightDir;

varying vec4 position_cs;
varying vec3 normal_cs;

varying vec4 ambientGlobal, ptDiffuse, ptAmbient, dirDiffuse, dirAmbient, ecPos, modelPos;

void main()
{	
	gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

	vec3 n, halfV, lightDir;
	float NdotL, NdotHV;
	vec4 color = texture2D(tex, gl_TexCoord[0].st);
	color.xyz *= .5;
	
	color.xyz += ambientGlobal.xyz;

	float att, dist, edge;

	n = normalize(normal);

	// Point light calculations
	lightDir = vec3((gl_ModelViewMatrix * gl_LightSource[0].position) - ecPos);
	
	dist = length(lightDir);
	
	NdotL = max(dot(normalize(n), normalize(lightDir)), 0.0);

	//if (NdotL > 0.0) {
		att = 1.0 / (gl_LightSource[0].constantAttenuation +
			gl_LightSource[0].linearAttenuation * dist +
			gl_LightSource[0].quadraticAttenuation * dist * dist);
				
		color += att * (ptDiffuse * NdotL + ptAmbient);

		halfV = normalize(ptHalfVector);
		NdotHV = max(dot(n, halfV), 0.0);
		color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular *
				pow(NdotHV, gl_FrontMaterial.shininess);

		gl_FragColor.xyz += color.xyz;
	//}
	
	// Directional light calculations
	color = dirAmbient;

	NdotL = max(dot(n, dirLightDir), 0.0);

	//if (NdotL > 0.0) {
		color += dirDiffuse * NdotL;
		halfV = normalize(dirHalfVector);
		NdotHV = max(dot(n, halfV), 0.0);
		color += gl_FrontMaterial.specular *
			gl_LightSource[1].specular *
			pow(NdotHV, gl_FrontMaterial.shininess);
	//}

	gl_FragColor.xyz += color.xyz;
	
	
	// Toon shading
	if (0.5 < useToonShading) {

		int i;
		
		if (abs(gl_FragColor.x - gl_FragColor.y) < .05) {
			gl_FragColor.x = max(gl_FragColor.x, gl_FragColor.y);
			gl_FragColor.y = max(gl_FragColor.x, gl_FragColor.y);
		}

		if (abs(gl_FragColor.y - gl_FragColor.z) < .05) {
			gl_FragColor.y = max(gl_FragColor.y, gl_FragColor.z);
			gl_FragColor.z = max(gl_FragColor.y, gl_FragColor.z);
		}

		if (abs(gl_FragColor.x - gl_FragColor.z) < .05) {
			gl_FragColor.x = max(gl_FragColor.x, gl_FragColor.z);
			gl_FragColor.z = max(gl_FragColor.x, gl_FragColor.z);
		}
		
		for (i = 0; i < 3; ++i) {
			if (gl_FragColor[i] > .9) {
				gl_FragColor[i] = 1;
			//} else if (gl_FragColor[i] > .75) {
				//gl_FragColor[i] = 0.75;
			//} else if (gl_FragColor[i] > .6) {
				//gl_FragColor[i] = 0.6;
			} else if (gl_FragColor[i] > .525) {
				gl_FragColor[i] = 0.525;
			} else if (gl_FragColor[i] > .3) {
				gl_FragColor[i] = 0.3;
			//} else if (gl_FragColor[i] > .15) {
				//gl_FragColor[i] = 0.15;
			//} else if (gl_FragColor[i] > .09) {
				//gl_FragColor[i] = 0.09;
			//} else if (gl_FragColor[i] > .06) {
				//gl_FragColor[i] = 0.06;
			//} else if (gl_FragColor[i] > .03) {
				//gl_FragColor[i] = 0.03;
			} else {
				gl_FragColor[i] = 0.0;
			}
		}
		
		vec3 eyeDir = vec3((eye) - ecPos);
		edge = dot(normalize(n), normalize(eyeDir));
		if (edge > -0.25 && edge < 0.25) {
			gl_FragColor = vec4(0, 0, 0, 1);
		}
	}
}
{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
		{ "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "hdrBuffer", "type" : "tex"},
		{ "name" : "brightnessBuffer", "type" : "tex"}
    ],
    
    "vertex" : "passthrough.vs",
    "fragment" : "bloom_add.fs"
}
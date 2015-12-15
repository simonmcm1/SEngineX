{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
		{ "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "hdrBuffer", "type" : "tex"},
		{ "name" : "brightnessBuffer", "type" : "tex"}
    ],
    
    "vertex" : "passthrough.vp",
    "fragment" : "bloom_add.fp"
}
{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
		{ "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "hdrBuffer", "type" : "tex"},
		{ "name" : "brightnessThreshold", "type" : "float"}
    ],
    
    "vertex" : "passthrough.vp",
    "fragment" : "bloom_brightness.fp"
}
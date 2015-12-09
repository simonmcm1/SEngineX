{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
		{ "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "hdrBuffer", "type" : "tex"},
		{ "name" : "brightnessThreshold", "type" : "float"}
    ],
    
    "vertex" : "passthrough.vs",
    "fragment" : "bloom_brightness.fs"
}
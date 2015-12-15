{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
		{ "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "image", "type" : "tex"},
		{ "name" : "horizontal", "type" : "float"}
    ],
    
    "vertex" : "passthrough.vp",
    "fragment" : "bloom_blur.fp"
}
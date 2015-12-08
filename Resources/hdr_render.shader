{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
		{ "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "exposure", "type" : "float"},
		{ "name" : "hdrBuffer", "type" : "tex"}
    ],
    
    "vertex" : "passthrough.vs",
    "fragment" : "hdr_render.fs"
}
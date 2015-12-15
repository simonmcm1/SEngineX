{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
		{ "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "exposure", "type" : "float"},
		{ "name" : "hdrBuffer", "type" : "tex"}
    ],
    
    "vertex" : "passthrough.vp",
    "fragment" : "hdr_render.fp"
}
{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
        { "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
		{ "name" : "gPosition", "type" : "tex"},
		{ "name" : "gNormal", "type" : "tex"},
		{ "name" : "gAlbedo", "type" : "tex"},
		{ "name" : "gSpecular", "type" : "tex"}
    ],
    
    "vertex" : "passthrough.vs",
    "fragment" : "LIGHTING_deferred.fs"
}
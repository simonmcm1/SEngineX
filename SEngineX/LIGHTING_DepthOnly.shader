{
    "attributes" : [
        { "name" : "position", "type": "float" }
    ],
    
    "uniforms" : [
        {"name" : "_MVP", "type": "matrix"},
        {"name" : "_M", "type": "matrix"},
        {"name" : "_VP", "type": "matrix"}
    ],
    
    "vertex" : "LIGHTING_DepthOnly.vs",
    "fragment" : "LIGHTING_DepthOnly.fs"
}
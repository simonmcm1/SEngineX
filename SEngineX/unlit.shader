{
    "attributes" : [
        { "name" : "position", "type": "float" },
        { "name" : "normal", "type" : "vec3" },
        { "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
        {"name" : "_MVP", "type": "matrix"},
        {"name" : "_M", "type": "matrix"},
        {"name" : "_VP", "type": "matrix"},
        {"name" : "material.color", "type": "vec3"}
    ],
    
    "vertex" : "basic.vs",
    "fragment" : "unlit.fs"
}
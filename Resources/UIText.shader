{
    "attributes" : [
        { "name" : "vertex", "type": "vec4" }
    ],
    
    "uniforms" : [
        {"name" : "_P", "type": "matrix"},
        {"name" : "textColor", "type": "vec3"},
        {"name" : "text", "type": "tex"}
    ],
    
    "vertex" : "UIText.vp",
    "fragment" : "UIText.fp"
}
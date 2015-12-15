{
    "attributes" : [
        { "name" : "position", "type": "vec3" },
        { "name" : "normal", "type" : "vec3" },
        { "name" : "texCoord", "type" : "vec2" }
    ],
    
    "uniforms" : [
        {"name" : "_MVP", "type": "matrix"},
        {"name" : "_M", "type": "matrix"},
        {"name" : "_VP", "type": "matrix"},
        {"name" : "_tiling", "type" : "vec2"},
        {"name" : "material.MainTex", "type": "tex"},
        {"name" : "material.AltTex", "type": "tex"},
        {"name" : "material.Specular", "type": "vec3"},
        {"name" : "material.Shininess", "type": "float"}
    ],
    
    "vertex" : "deferred_basic.vp",
    "fragment" : "deferred_basic.fp"
}
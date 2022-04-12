
namespace OpenGL


-- constant WindowP : PointedType

-- def Window := WindowP.type

-- instance : Inhabited Window := ⟨WindowP.val⟩

@[extern "lean_gl_create_program"]
constant createProgram : (id : UInt32) → IO Unit

import OpenGL
open OpenGL

def main (args : List String) : IO UInt32 := do
  try
    let test := args.getD 0 ""
    match test with
    | s => IO.eprintln s!"Unknown test {s}"
    pure 0
  catch e =>
    IO.eprintln <| "error: " ++ toString e
    pure 1

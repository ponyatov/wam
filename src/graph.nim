## metaprogramming data representation (attributed object graph)

import tables
import strutils

type Object* = ref object of RootObj
  typ*: string                 ## type/class tag
  val*: string                 ## scalar value: name, number, string
  slot*: Table[string, Object] ## attributes = dics = table = associative array
  nest*: seq[Object]           ## nested elements = AST = vector = stack = queue

proc head*(self: Object, prefix: string = ""): string = ## short `<T:V>` header only
  let hdr = prefix & "<" & self.typ & ":" & self.val & ">"
#   hdr &= " @" & toHex(cast[uint](self))
  return hdr

proc pad(self: Object, depth: uint = 0): string =
  "\n" & "\t".repeat(depth)

proc dump*(self: Object,
  dumped: seq = @[], depth: uint = 0,
  prefix: string = ""): string = ## full text tree dump
  result = self.pad(depth) & self.head(prefix)

proc `$`*(self: Object): string =
  self.dump()

type Primitive* = ref object of Object ## primitive type

type Symbol* = ref object of Primitive ## symbol

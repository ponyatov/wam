## Warren's Abstract Machine
## 
## * \[hak\] Hassan Aït-Kaci
## **Warren's Abstract Machine: A Tutorial Reconstruction**
##   * [pdf](wambook.pdf) @ http://wambook.sourceforge.net
##   * https://en.wikipedia.org/wiki/Warren_Abstract_Machine
## * Ehud Sterling, Leon Shapiro **The Art of Prolog**
## * Michael Kifer, Yanhong Annie Liu **Declarative 
##   Logic Programming: Theory, Systems, and Applications**
## * ru: https://github.com/ponyatov/nimbook/wiki/WAM

import sequtils

type Term* = ref object of RootObj ## p.24 (first-order) term
  functor: string

proc `$`*(self: Term): string =
  result = "t:"&self.functor

type Variable* = ref object of Term

proc `$`*(self: Variable): string =
  "v:" & self.functor

type Constant* = ref object of Term

proc `$`*(self: Constant): string =
  "c:" & self.functor

type Structure* = ref object of Term
  terms*: seq[Term] ## subterms

proc `$`*(self: Structure): string =
  result = "s:" & self.functor & "("
  result &= map(self.term, proc (x)=$x).join(",")
  result &= ")"



import logging
let log* = ## console logger
  newConsoleLogger(fmtStr = "[$date $time] - $levelname: ")
addHandler(log)

import os
import memfiles as mmap



proc main*(argv: seq) = ## program entry
  info "WAM init"
  defer: info "WAM fini"
  # args
  for i in pairs(argv):
    info "argv[", i.key, "] = <", i.val, ">"
  # .ini
  info "mmap ", argv[1]
  var src = mmap.open(argv[1])
  defer: src.close()
  # term samples
  info "term ", Term(functor: "a")
  info "struct ", Structure(functor: "b", terms: @[
      Variable(functor: "var"),
      Constant(functor: "const")]
    )


when isMainModule:
  let argv* = ## command line argumens
    @[os.getAppFilename()] & os.commandLineParams()
  main(argv)

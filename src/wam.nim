## Warren's Abstract Machine
## 
## * \[hak\] Hassan Aït-Kaci
## **Warren's Abstract Machine: A Tutorial Reconstruction**
##   * [pdf](wambook.pdf) @ http://wambook.sourceforge.net
##   * https://en.wikipedia.org/wiki/Warren_Abstract_Machine
## * Ehud Sterling, Leon Shapiro **The Art of Prolog**
## * Michael Kifer, Yanhong Annie Liu
## **Declarative Logic Programming: Theory, Systems, and Applications**
## * ru: https://github.com/ponyatov/nimbook/wiki/WAM


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


when isMainModule:
  let argv* = ## command line argumens
    @[os.getAppFilename()] & os.commandLineParams()
  main(argv)

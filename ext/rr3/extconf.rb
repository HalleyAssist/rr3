require 'mkmf'
have_header 'r3/r3.h'
have_library 'r3'
$defs.push("-DHAVE_STRNDUP")
create_makefile 'rr3/rr3'
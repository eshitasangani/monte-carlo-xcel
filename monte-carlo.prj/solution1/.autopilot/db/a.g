#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/ayc62/ece6775/monte-carlo-xcel/monte-carlo.prj/solution1/.autopilot/db/a.g.bc ${1+"$@"}

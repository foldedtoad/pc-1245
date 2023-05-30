##!/bin/bash
#
../../as61860/build/as61860 -gloaxff t61860s
../../asxscn/build/asxscn -x t61860s.lst
../../aslink/build/aslink -nxmu -g addr=0 -g reg=0 -g extrn=0 t61860s
../../asxscn/build/asxscn -xi t61860s.rst
../../ihex2wav/build/ihex2wav -old -o wavefile.wav t61860s.rel
audacity ./wavefile.wav &
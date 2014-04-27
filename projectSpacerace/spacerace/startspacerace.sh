#!/bin/sh
export PATH=$PATH:/Users/danielraudschus/Desktop/spacerace/build/bin:/usr/local/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/Users/danielraudschus/Desktop/spacerace/build/lib:/Users/danielraudschus/Desktop/spacerace/build/lib:/usr/local/lib
spacerace $*
#read -p "Press any key to continue"

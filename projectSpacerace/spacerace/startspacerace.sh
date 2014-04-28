#!/bin/sh
export PATH=$PATH:/Users/danielraudschus/Documents/spacerace/build/bin:/usr/local/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/Users/danielraudschus/Documents/spacerace/build/lib:/Users/danielraudschus/Documents/spacerace/build/lib:/usr/local/lib
spacerace $*
#read -p "Press any key to continue"

require('coffee-script');
require('./demo.coffee');
//This file is used with gdb - Instructions below
//gdb --args node ./examples/debug.js
//gdb> run
//gdb> backtrace

//Debugging "can't load module"
//1624 - 0.6.6
//1558 - 0.6.14
//gdb --args node ./examples/debug.js
//gdb> break node.cc:1558
//gdb> run
//gdb> p/a dlerror()
//gdb> x/s (res)
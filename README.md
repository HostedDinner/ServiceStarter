# Service Starter

This is a simple Application for Windows, which can start a service and stop it. The user must have the right privileges for starting/stopping the service!
This can be done for example in this way: [see Stack Overflow](http://stackoverflow.com/a/18856461/5905665)

It is written in C++ (uses features of C++11) and is small in size.

At the moment the service names are hardcoded in the main file. This will be changed later.
Also there are very less safety fallbacks, if failing, because the code is a little bit messy.

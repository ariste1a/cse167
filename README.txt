Aight, so. 

Stuff in the source files folder are obviously the source files. 

The stuff in the runtime folder however, are the files you'll have to put in the folder where the .exe is generated
(either debug or release, depending what you use). 

Install the missing packages (mainly SDL.lib) like how you installed glut. 
You'll also need glew, which is just glut extended. 

Add them to be used like how you did it with the other libraries. 

I've included them in the repo. 

Remember to make the VS project outside of the local copy of the repo 
so that there isn't gonna be a lot of discrepancy and messy git stuff.


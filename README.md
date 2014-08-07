2D_Engine
=========

A personal C++ research project into 2D game engine development, circa 2009.

Completing this project really helped me embrace object-oriented design principles. I had always been a champion of OOD, but this really struck it home for me. I also got accustomed to creating and using manager-type classes, like a screen manager to handle screen composition and an entity manager to handle the updates and rendering of all in-game entities. It was a very rewarding exercise.

I can't take all the credit however. There was a tutorial I found online that helped me navigate through many coding hurdles and conceptual design choices, but, for the life of me, I can't find it online anymore.

__Note__ that in order for this project to even build (I haven't tested this with the latest versions of Visual Studio), you'll need to download Simple DirectMedia Layer (SDL) at https://www.libsdl.org/download-1.2.php and SDL Image at https://www.libsdl.org/projects/SDL_image/release-1.2.html. You'll need to add the 'include' and 'lib' folders from both of these libraries to the project's 'Additional Include Directories' and 'Additional Library Directories' settings in Visual Studio, respectively.

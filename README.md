# Base-Defender version A01.40
A side scrolling arcade game with defence atributes.

A minimal functioning version of the game in the Alpha stage. Only graphic place holders will be used until all functionality is complete. At that time the game will reach Beta version.
Visual Studio 2015 was used to make this project.
This game requires the latest version of the SFML library. SFML 2.3.2 compiled in static mode, so that DLLs are not used. That means that SFML is compiled into the main exe file. That makes it into a wopping 2.5MB file compaired to when it was 366k and it needed 4.66MB of DLLs. As you can see, this works better as only what it uses is compiled into the exe file.

The Entity class controls and makes the sprite setup easy and is made to be used with any game. It is basicly a very basic 2D acceleration and volicity centric contorller for onscreen movement.

Sprite animation and particle effects will be added in a future version, likily after all game functionality is complete.

This is a remake of a game by the same name that I created using XNA many years ago. This time it can be easily ported to both Linux and Android.

My source files may be used however you like, and are without warrenty. I frankly don't care what you do with them. Just enjoy your life, without worrying about what people do with your creations. My files are copyleft, and without any licence. I think liceces for software are stupid. Just look what kind of mess Java was in because of it. Game on!

The files ResourceHolder.hpp and ResourceHolder.inl are from the book "SFML Game Development". Those are files that store all the textures for game use, so they are loaded once, and kept as a pointer. The licence from the book is included inside the files.

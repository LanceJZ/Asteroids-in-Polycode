Asteroids in Polycode Alpha
===========================

Version Beta 1.40
=================
All visual and audio effects have been implemented. I created some new audio effects just for this version using Bfxr.
Added fixed update for collision detection.
Upped FPS to 240 FPS for core so collisions would be even more accurate.
Changed shot mesh into a box for better collision detection.
Changed dot mesh into one line.
Tweaked speed of game objects for better game play.

Game is complete except for more optimizations and if any bugs are found.
Download and enjoy one of your choice! I’ve included a zip file, and a rar file of the game inside the Release folder. Pick what one works best for you, do the rar if you can, as you can see it is much smaller. Will not run on Windows XP, works on Windows 7, 8, and 10 only.


Version Alpha 1.35
==================
The player now has visual explosion effects, and they are grand. It took me over a day to get it working, and I found a few more bugs to squash, and made some more optimizations while I was at it. The audio effects have been pushed back because adding visual effects took so much longer than I had expected it too.
I'll be working on the audio now, it is the only thing left to do.

Version Alpha 1.30
==================
Now with program icon, visual effects for rocks and ufos. I've also figured out that the save file for debug and release are different, so I have the game check the size of the save file so it should not crash on load anymore.
It took some time and effort to figure out how to manually change the icon file. The resources available are not very clear in how to do so. Polycode does not seem to support that feature yet, so I had to do it manually.

The player ship explosion effects I'll add as soon as I figure out how I'm going to do that. Its lines separate in the original, not as easy as just doing dots.

I'll add the sounds in the next version if all goes as planned. Figuring out how to add an icon took all day, so I ran out of time.

I also changed the locked FPS to 120 for even greater accessory. In testing I had shots pass through the tip of the player ship. That does not happen anymore. Even at that speed CPU usage is still under 2%.
Many optimizations have I done, for performance and efficiency.

Version Alpha 1.20
==================
Now with high score list save. When you get a score that is higher than one on the list you will be able to enter in three letters, just like the original, and it will save your high scores to disk. This requires that the game reside in a folder that is not protected for it to be able to save the game score list, such as your documents. It will not work in Program Files, as that is a protected folder.
I made the screen size smaller, 800 X 720 so it would run on older laptops. In the future it will have selectable screen sizes adjustable in settings, and that will also get saved to a settings file.

Next I'll be adding effects, sound and visual. I'll also be cleaning up the code. I hope you enjoy the game!

==================================================================================================================================================
OpenAL is required, so if you don't have it installed, copy it from the Release folder and place it with the Asteroids.exe file. Recent (Less than six years old) Discrete graphics are required for this game. My laptop with ATI Mobility Radeon HD 5470 Runs it just fine. A directX 11 class card should work just fine. This will change in the future, as I'll add settings so the AA can be adjusted.

This time around I decided to clone Atari Asteroids as best as I could. I actually counted pixels in screen shots to get everything the right shape and scale. I used vector lines to recreate the vector look. I also use mesh collusion for precise collision detection.

Asteroids uses the Polycode framework 0.83 Beta in C++.
This project requires Polycode http://polycode.org a free open source multi platform framework. This is a Visual Studio 2015 project, also free.
Place the Polycode folder beside the Asteroids Solution folder, that is how I have it.

You are free to do whatever you want with the code. I'm not responsable for any damages incurred from running this game.
Thank you and game on.

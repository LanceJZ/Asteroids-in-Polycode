Asteroids in Polycode Alpha
===========================

Version Alpha 1.2

Now with high score list save. When you get a score that is higher than one on the list you will be able to enter in three letters, just like the orginal, and it will save your high scores to disk. This requires that the game reside in a folder that is not protected for it to be able to save the game score list, such as your documents. It will not work in Programe Files, as that is a protected folder.
I made the screen size smaller, 800 X 720 so it would run on older laptops. In the future it will have selectable screen sizes adjustable in settings, and that will also get saved to a settings file.

Next I'll be adding effects, sound and visual. I'll also be cleaning up the code. I hope you enjoy the game!

OpenAL is required, so if you don't have it installed, copy it from the Release folder and place it with the Asteroids.exe file. Recent (Less than six years old) Discreate graphics are required for this game. My laptop with ATI Mobility Radeon HD 5470 Runs it just fine. A directX 11 class card should work just fine. This will change in the future, as I'll add settings so the AA can be adjusted.

This time around I decided to clone Atari Asteroids as best as I could. I actually counted pixels in screen shots to get everything the right shape and scale. I used vector lines to recreate the vector look. I also use mesh collusion for precise collusion detection.

Asteroids uses the Polycode framework 0.83 Beta in C++.
This project requires Polycode http://polycode.org a free open source multi platform framework. This is a Visual Studio 2015 project, also free.
Place the Polycode folder beside the Asteroids Sulution folder, that is how I have it.

You are free to do whatever you want with the code. I'm not responsable for any damages incured from running this game.
Thank you and game on.

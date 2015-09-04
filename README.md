Asteroids in Polycode Alpha
===========================

Asteroids uses the Polycode framework 0.83 Beta in C++.
OpenAL is required, so if you don't have it installed, copy it from the Release folder. Recent Discreate graphics are required for Polycode, so if it can't handle it the game will crash. I don't know what the minimum is yet, my laptop with ATI Mobility Radeon HD 5470 it wont run, but on my A10 APU it runs the release just fine at 1% CPU usage. It was also tested on a recent laptop with discreate GeForce GTX 760m.

Project requires Polycode http://polycode.org a free open source multi platform framework. This is a Visual Studio 2015 project, also free.

This time around I decided to clone Atari Asteroids as best as I could. I actually counted pixels in screen shots to get everything the right shape and scale. I used vector lines to recreate the vector look. I also use mesh collusion for precise collusion detection.

Place the Polycode folder beside the Asteroids Sulution folder, that is how I have it.

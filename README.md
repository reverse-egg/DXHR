![Screenshot of my mod menu](https://github.com/reverse-egg/DXHR/blob/main/DXHRMenu.png)

# DXHR

This is a mod I made utilizing RTTI embedded in Deus Ex: Human Revolution. I wrote ~1,000 lines of C++ for the dll that gets injected into the game and about 100 lines of Python to use as the UI via IPC to send commands to the dll.

# Intent of This Project

This was a very fun project for me to work on. Deus Ex: Human Revolution is one of my favorite single player games ever. It was my favorite pastime as a teen aside from programming.
The stealth, gun mechanics, dialog system and storyline were fresh and so unique from any other game I'd played at the time. 
To this day, despite a lot of newer games having come out since its initial release I still feel the same.

But what do you do once you complete the campaign? Well play it again, find the stuff you missed and make decisions you didn't make before of course! Well, I did that. Many, many a time.
Naturally three of my favorite pastimes ended up melding together. Deus Ex, reverse engineering and programming. It was a new way to look at the game.

So I went into this mostly for fun and learned a LOT along the way as well.

# The Process

It could be best summarized in this manner:

Cheat Engine > Ghidra > Frida

I used Cheat Engine to find the location of variables (Ammo, Health, Energy, etc) then checked what functions modified them. Then I'd load up Ghidra to discern what a function did.
Well, while looking at a particular function I became curious if the game made use of certain functions for strings. Then I saw it in the Symbol Tree. Tons and tons of classes were already defined.
This game had RTTI embedded! MASSIVE Win!

For those that may be unfamiliar RTTI is the magic sauce behind up and downcasting in C++. It allows you to derive a parent or child class from an object at Run Time by embedding a few things such as:
The mangled name and class hierarchy descriptor. These two things alone help *dramatically* speed up reversing. Because from RTTI you can get the name of the class and its inheritance information as well.

# Now I Have Class Info, What's Next?

This then enables me to also identify the virtual function table associated with these classes. Which is great for signature scanning!
So then I can just search for pointers to that classes virtual function table in order to find instances of that class in memory.
Because classes with one or more virtual functions generate a virtual function table and that tables address is the first entry in the class in memory.

An aside: this is also perfect for pointer validation. In modding a lot of pointer manipulation is necessary. 
So I'd find a static pointer chain to the object of interest then compare the virtual function table pointer with the expected value.

# Reversing with Ghidra and Frida

After this came some tinkering with Ghidra in order to discern what certain member methods did. I'd debug the process, see what addresses accessed a variable, figure out the offset from the exe and then go over to Ghidra to analyze it.
To aid me in understanding what these functions were doing I'd write scripts in Frida. Primarily to print out arguments passed to the function as well as return values and in some cases to track function calls up the stack.

# Putting it altogether

After creating a pretty decently thorough cheat table in Cheat Engine I then switched focus to writing my dll to inject. Started out simple. I'd find a static pointer path to class members like health, ammo, etc.
Then I'd print out the address and compare it with my cheat table to ensure I was doing my pointer arithmetic correctly. I also used SEH in order to check pointer readability before accessing them to avoid crashes.

Once I'd validated proper pointer retrieval I'd write functions to modify them.

I ended up splitting these abstractions into three classes: UpgradeDescriptorArrayManager, DXHR, and Cheats.

UpgradeDescriptorArrayManager is pretty esoteric unless you've been reversing Deus Ex. It has an array of UpgradeDescriptor objects. Each one has the name of the Upgrade such as `PrimaryDamageTaken`, `FiringRecoil`, etc and then its value which could be a float, boolean or integer.
The UpgradeDescriptorArrayManager handles reading and writing to these UpgradeDescriptors.

DXHR was an abstraction primarily for pointer retrieval. I have various static offsets to use for pointer traversal. Stepping between various classes to other classes of interest.

Cheats is essentially bringing those two classes together to supply simple to use functions. Such as enabling invincibility, infinite ammo, etc.

# The UI

I initially started out using the Winapi for the UI. However, it quickly became unruly and wasn't worth the added complexity. So I opted to use IPC via a named pipe. 
I'd use Python's Tkinter for the UI and send commands over to the dll via the pipe. And voila! My mod is working.

# This Was Fun!

This was a whole buttload of fun. I enjoyed it almost as much as playing the game. Dissecting things to understand how they work, especially something you love is a great way to make learning fun.
Which was the intent behind this project. Fun and learning.

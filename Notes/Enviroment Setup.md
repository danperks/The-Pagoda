# Editor Setup

Here's a couple ways to setup your C++ enviroment

## With Visual Studio

By far the easiest enviroment is to use Visual Studio. Not only does it come with a compiler, but it's a full blown IDE that contains basically everything you could want in your enviroment.

## Without Visual Studio

This method is my prefered method if you want to avoid needing the full blown Visual Studio IDE. It uses a few seperate tools, but makes smaller C++ compiling simple and easy.

### Editor - VS Code

My editor of choice is VS Code, due to it's integrations and features. Allowing for compatability with VCPKG, Live collaborative coding and many addons to speed up programming, it is my editor of choice. Additionally, it works with any language.

VS Code can be downloaded [here](https://code.visualstudio.com/)

### Compiler - MinGW (G++)

The compiler I use is basically the next best thing besides the Visual Studio. Being a part of a set of compilation tools named MinGW, G++ is the spesific tool I use. It's compilation is done in the terminal, with commands in the format:

```bash
g++ [input file] -o [output file name]
```

Additional parameters can be added on the end for easy setting changes.
You can download MinGW from [here](http://win-builds.org/doku.php)

### Package Manager - VCPKG

One of the most recent additions to C++ is the use of package managers to download libraries. Much like `apt-get` or `pip install`, these download external libraries for use in your code.

To install VCPKG, first start by downloading the .zip from [here](https://github.com/microsoft/vcpkg/archive/master.zip)
Then, extract that .zip into the folder you want to install it in. I would recommend `C:/vcpkg`
Once installed, you need to add it to your path so it can be used from anywhere.
To do this, search `Environment Variables` in the Windows search bar, and choose the first option.
Click the button that says `Environment Variables...` at the bottom of the popup and find `Path` in the top list in the next popup. Click on `Path`, then click the `Edit` button half way down the popup. Click `New` then type in the location of the vcpkg folder you just made. Now it's ready for use.

To use VCPKG, go to a command prompt, and type vcpkg. This should show you if it's working. To search for a package, do `vcpkg search [name]` and to install it, do `vcpkg install [exact name from search]`. This then installs it to the vcpkg folder, spesifcally to `/vcpkg/installed/x86-windows/include`.

### How to Compile

Now, if you want to compile some code, you should do:
`g++ [source file] -o [output filename] -L [vcpkg include folder]`

Add on any extra parameters you may need, for example `-std=c++0x` or `-lws2_32`

## CubePass
### Current version: v3.0.0

CubePass is a lightweight, cross-platform, secure password manager. It works completely offline, so all your data is safely encrypted and stored on your PC. CubePass is very easy to use and works on Windows, Linux and OSX (Linux and OSX currently needs to build the binaries (very,very easy), see below for instructions).

CubePass offers:
* Secure, offline storage of your passwords
* Passwords are saved as "items", this includes the domain (website or software name), username, password and optional notes
* Password database can be exported (Backed up) for later restoration on use on another PC (even other OS)
* Very lightweight
* Easy-to-use interface with lots of help
* Minimal interface - just "write-down" the password and save

No more forgetting your passwords! CubePass is completely free, ad-free and will always stay like that! (But donations are welcome ;)

##Download for Windows:
[![Download CubePass](https://a.fsdn.com/con/app/sf-download-button)](https://sourceforge.net/projects/cubepass/files/latest/download)

###Linux and OSX users
While I'm writing the installer for these two OS's you will have to build the binaries yourself, but this is very easy so don't worry. Follow these steps:

1. Clone (download) the cube-lib repository (located at https://github.com/Cube777/cube-lib, if you have git installed run <code>git clone https://github.com/Cube777/cube-lib</code>) to your PC

2. Follow the building instructions provided by the repo (Read the <code>README.md</code> in it for instructions), use the default options if you can, it makes configuring easier

3. Download and install the Qt 4(or 5) libraries and headers (qtcreator not necessary). Examples:
<pre>Ubuntu (or any Debian-derivative): sudo apt-get install libqt4-dev libqt4-dev-bin qt4-qmake
Arch-linux: sudo pacman -S qt4
Fedora: sudo yum install qt4
</pre>

4. Open the terminal in the folder where you downloaded this repository (Open terminal and run <code>cd /path/to/repository</code>) and run the following commands:
<pre>
cd cubepass
qmake -makefile cubepass.pro
make release
sudo make install
</pre>
5. That's it! You can now run CubePass from the terminal with <code>cubepass</code> or from your applications menu.

###Windows users wishing to build from source
If you don't want to use the installer on SourceForge or want to modify the source, download all the Qt binaries as well as their bin tools (easiest just to use the complete QtCreator suite with MingW), add the bin folder of their "tools" (not QtCreator) folder in the Qt install dir and the MingW bin folder to your PATH variable. Then simply follow the instructions for Linux and OSX above and replace <code>make</code> with <code>mingw32-make</code> (Make sure that you run the CMD window with admin rights otherwise it won't be able to install)

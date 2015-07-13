## CubePass
### Current version: v3.0.0

CubePass is a lightweight, cross-platform, secure password manager. It works complete offline, so all you data is safe encrypted and stored on your PC. CubePass is extremely easy to use and works on Windows, Linux and OSX (Linux and OSX currently needs to build the binaries, see below for instructions). CubePass regularly updated and is open for bug-fixes.


CubePass has the following features:
* Secure, offline storage of your passwords
* Passwords are saved as "items", this includes the domain(website or software name), username, password and optional notes
* Support backups
* Very lightweight
* Easy-to-use interface with lots of help
* Minimal interface - just "write-down" the password and save

No more forgetting your passwords! CubePass is completely free, ad-free and will always stay like that! (Donations welcome ;)

##Download for Windows:
[![Download CubePass](https://a.fsdn.com/con/app/sf-download-button)](https://sourceforge.net/projects/cubepass/files/latest/download)

###Linux and OSX users
While I'm writing the installer for these two OS's you will have to build the binaries yourself, but this is very easy so you have nothing to fear!

1. Clone (download) the cube-lib repository (located at https://github.com/Cube777/cube-lib, if you have git installed run <code>git clone https://github.com/Cube777/cube-lib</code>) to your PC

2. Follow the building instructions provided by the repo (Read the <code>README.md</code> in it for instructions), use the default options if you can, it makes configuring easier

3. Download and install the Qt 4(or 5) libraries and headers (qtcreator not necessary). Examples:
<pre>Ubuntu (or any Debian-derivative): sudo apt-get install build-essential libqt4-dev libqt4-dev-bin qt4-qmake
Arch-linux: sudo pacman -S base-devel qt4
Fedora: sudo yum install make gcc gcc-c++ qt4
</pre>

4. Open the terminal in the folder where you downloaded this repository (Open terminal and run <code>cd /path/to/repository</code>) and run the following commands:
<pre>
qmake -makefile cubepass.pro
make release
sudo make install
</pre>
5. That's it! You cun now run CubePass form the terminal with <code>cubepass</code> or your application menu or launcher.

###Windows users wishing to build from source
If you don't want to use the installed on Sourceforge follow the instructions for Linux and OSX users above, except you will need the complete Qt creator suite available from https://www.qt.io/download-open-source/ and will build from inside QtCreator, not using make.

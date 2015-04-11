## CubePass
### Current version: v2.0.0

CubePass is a lightweight, cross-platform, secure password manager. It works complete offline, so all you data is safe encrypted and stored on your PC. CubePass is extremely easy to use and works on Windows, Linux and OSX (Linux and OSX currently needs to build the binaries, see below for instructions). CubePass regularly updated and is open for bug-fixes.


CubePass has the following features:
* Secure, offline storage of your passwords
* Passwords are saved as "items", this includes the domain(website or software name), username, password and optional notes
* Support backups
* Very lightweight
* Easy-to-use interface with lots of help
* Minimal interface - just "write-down" the password and save

No more forgetting your passwords! CubePass is completely free, ad-free and will always stay like that! (Donations welcome ;)

[![Download CubePass](https://a.fsdn.com/con/app/sf-download-button)](https://sourceforge.net/projects/cubepass/files/latest/download)

###Linux and OSX users
While I'm writing the installer for these two OS's you will have to build the binaries yourself, but this is very easy so you have nothing to fear! 

1. Clone (download) the cube-lib repository (located at https://github.com/Cube777/cube-lib) to your PC

2. Clone (download) this (CubePass) repository to your PC

3. Download and install the Qt libraries along with Qt creator (first look in your respective distro's repositories to check if "Qt creator" isn't listed there, if not go to this link https://www.qt.io/download-open-source/ and download)

4. After Qt has finished installing, open "cubepass.pro" located in the "cubepass" folder of this repository

5. Configure you project (default settings will work)

6. Go to the "Projects" section on the left side of the screen and make sure to change "Debug" to "Release" on right next to "Edit build configuration"

7. Scroll down until you see "Build environment" and click on details

8. Click then on "Add", and type "CUBE-LIB" (without quotes) and press enter

9. Search for "CUBE-LIB" in the list and then double-click on "<VALUE>" right next to it

10. In the value field type the path to the folder where you downloaded the cube-lib repository etc "/home/cube/repos/cube-lib" and press enter when you are done

11. Thats it! Now press the "Build" button (hammer icon) and CubePass will build. IF you used the default build settings your build will be located in the CubePass repository folder (The executable will be named "cubepass"). Just run the executable and thats it! I will write an installer for *nix systems pretty soon so just hold on tight!

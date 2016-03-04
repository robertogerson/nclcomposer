NCL Composer
============
This project is intended to group all NCL Composer related suprojects using 
the git submodules feature. This project does not contain any source code, it 
just uses the abstraction of git submodules to link to git projects where the 
code of each individual NCL Composer's project is available.

Additionally, this project also brings some useful files and scripts related to
code documentation, like Doxyfile, scripts to add the License HEAD to files,
packaging features and so on.

Today, there are three main submodules inside this project:
  * composer-core
  * composer-gui
  * composer-plugins

If you want specific information about one of the above subproject go to its
specfic README file.

Dependencies
============
The main dependency of NCL Composer is:
  * Qt >= 4.7.x

If you want to enable the Run your application on Ginga Virtual Set-top box,
then you should run qmake like this:
  * qmake RUNSSHON=true

By doing so, you have to be installed the following:
  * libssh2
  * libcrypt

Getting Submodules Source Code
==============================
Prerequisites:
 * Git 1.7.x or greater
    Probably you already had git, once you get this project.
 * Qt 4.7.1
     The Qt SDK provides you with most of the required software.

The easistr way to get the all submodules projects required is running:
  $ qmake

in the root directory of composer.git. The first time you run qmake, it will
initialize and update all the submodules, getting all the necessary source code
for compile NCL Composer. By default, every submodule will be checkouted to
branch master.

Otherwise, if you want to do it by yourself you can execute the following 
commands:
  $ git submodule init
  $ git submodule update
  $ git submodule foreach "git checkout master"

Changing and Committing the code 
================================
Even put together in the same root directory, each git project is totally 
independent. So, each change, commit and push must be realized individually to
each submodules.

If you need more information about git submodule these links can be useful:
  - http://kernel.org/pub/software/scm/git/docs/git-submodule.html
  - https://git.wiki.kernel.org/index.php/GitSubmoduleTutorial

Packaging
=========
One of the most important feature of the composer-all project is packaging.

* Generating MSI (Windows installer) package
  To generate the Windows Package installer, you will need the NSIS (Nullsoft
  scriptable install system): http://nsis.sourceforge.net/

  To generate the windows installer, got to win32-nsis directory and run:

  $ qmake
  $ mingw32-make install
  $ makensis composer.nsis

* Generating DEBIAN package
  Before generate the debian package you must update the debian files, inside 
  the debian directory.

  To generate a new debian package, the only thing you need to do is run:
  
  $ ./scripts/deb-package.sh
  
  in your terminal.
  This will generate a composer_x.x.x.deb file one directory behind the root NCL Composer 
  directory. This package is what you need to install on other debian/ubuntu systems.

  You can install it, using dpkg, for example:

  $ dpkg -i composer_x.x.x.deb

//TODO: Mac OS X ???

//TODO: LICENSE

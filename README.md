# SyrupC

A package manager written in C for my distro based on the LFS books, a copy of my other package manager called syrup that's in bash, but this one's in C.

# Installation

```
git clone https://codeberg.org/datwaffledude/syrupC.git
cd syrupC
gcc syrup.c -o syrup
```

# Usage

```
./syrup install package
./syrup remove package
./syrup info package
```

# Features
* Installing
* Removing
* Getting a packages info

# What's broken
* Here be dragons :DDDDDD

# TODO
* [ ] Implement dependency management and resolution, the earlier the better
* [ ] Add a package tracking system and a package database
* [ ] Add more packages, package manager's historically haven't been very useful without packages
* [ ] Add a querying function, to search packages

# Notes

Currently, syrup only searches for packages in the current working directory. If you put it in /usr/bin, better have all your packages there.

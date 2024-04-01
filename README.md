# STMPLSS.EXE
A command line logging utility for DOS.

[Basic Usage](#logging-on-dos) |
[Installation](#installation) |
[Build](#build-steps) |
[Why](#why-though)


## Logging on DOS
STMPLSS.EXE is a subset of the
[Stumpless logger](https://github.com/goatshriek/stumpless-logger), offering
a CLI logging experience tailored to DOS. It provides the ability to log to
stdout, stderr, or a file. The default target is a file named `STMPLSS.LOG`.

```
Usage: STMPLSS.EXE [OPTIONS] message

Arguments:
  message The message to include in log messages.

Options:
      --default          Log to the default log target. This is
                         the default if no options are given.
  -l, --log-file <file>  Log to the given file.
      --stderr           Log to stderr.
      --stdout           Log to stdout.
```


## Installation
The simplest way to install STMPLSS.EXE is to download the executable directly
from the releases page and put it on your system wherever you'd like.

If your system has FDNPKG, you can download the ZIP archive from the releases
page and install it directly with `FDNPKG install STMPLSS.ZIP`. Depending on
your configuration this will add the executable to your path, making it easy
to use.


## Build Steps
Building STMPLSS.EXE is a simple matter of getting and configuring
[stumpless](https://github.com/goatshriek/stumpless), and then compiling it for
DOS.

The `configure-stumpless.sh` script will run CMake on stumpless, generating the
correct configuration for a DOS system. Run it with the path to stumpless
provided as the only argument. The script also adjusts the single file
sources to remove some unsupported compiler features.

Next, you'll need to build the resulting stumpless configuration along with the
`SRC/MAIN.C` file. The release binary is generated using
[FreeDOS](https://www.freedos.org/) with the OpenWatcom compiler. The
`BUILD.BAT` script will run the necessary build steps to compile the executable
and create the FDNPKG package, again making some assumptions that may need to be
adjusted regarding paths.

Keep filesystem name length limitations in mind! We shorten stumpless file
names by removing the vowels.


## Why Though
Because it's April, Fools! At least, that's how this started.

I wanted to do something for April Fools' Day that would actually work, but also
create something interesting, strange, and off the beaten path. I figured that
DOS fit the bill, so I grabbed FreeDOS and set off to build a simple CLI tool
and catch some nostalgia along the way.

I was expecting to wade through decades-old software as I tried to compile and
test things. It wouldn't be the first time: I recently went looking for a JVM
Lua interpreter for a different project, and didn't find anything that wasn't
two years older or more with lots of open and unaddressed issues and pull
requests. Dealing with old projects like this is often painful, and I try to
avoid using them in my own projects. (On a side note, send me a recommendation
if you know of a maintained Lua interpreter for the JVM, I want to
[jam it into Ghidra](https://github.com/goatshriek/ruby-dragon/)).

But not so for DOS! FreeDOS is as active as ever. The latest tool release?
Just a few weeks ago. The last video posted? Only three months ago. It has
network support, a package manager, and even *vim*, which I find especially
delightful, though I used FED instead just to feel a little more DOSsy.
I've heard lots of people say that vim is on virtually every machine, but I
didn't think that extended all the way to *DOS*.

I also made a few
[portability improvements](https://github.com/goatshriek/stumpless/pull/410)
to stumpless along the way. The single file generation came in handy here, and
I made some improvements to it to cut down on generation time and reduce the
overall size. There were also a few minor things that got moved around to
support older compilers. And finally, I ended up adding some configuration
options to support missing headers and smaller filenames. So even if this
project goes unused, it's had a tangible impact on the parent project anyway.

I don't expect anyone to use this particular project, and that's not what this
was about anyway. But that isn't to say that you _shouldn't_ use it: if you want
a CLI logger on DOS, give it a shot! And if you run into problems, let me know!

I won't complain about old, unmaintained projects and then turn around to
abandon this one. Consider it maintained! If you find a problem, open an issue
and I'll look into it. And if you feel especially inspired, open a pull request
to add something yourself! Though the functionality is (severely) limited, I'm
certainly not opposed to improving it. I just won't spend more time until
someone actually asks for it.

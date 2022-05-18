# /g/ battleships

Second code exercise from /g/: battleships with AI.
Using C++ with Simple and Fast Multimedia Library (SFML).

## Installation
**Dependencies**
 - [SFML](https://github.com/SFML/SFML)

```bash
git clone https://github.com/cptchuckles/battleships.git
cd battleships
make all
```

### Platforms
This project runs on Linux, assuming you have a font file living at `/usr/share/fonts/TTF/DejaVuSansMono.ttf`.  If you don't have that font, then go get it and put it at that location.  If you don't want to do that then submit a pull request because It Works On My Machine™.

*(Actually I'm fairly certain that the Unix-style filepath is the only reason this project is not cross-platform.  Feel free to change `main.cpp:110` to load some other font or path and it will probably work.)*

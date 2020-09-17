# X_Enex

[![sampctl](https://img.shields.io/badge/sampctl-X_Enex-2f2f2f.svg?style=for-the-badge)](https://github.com/CnRXoMoX/X_Enex)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

## Installation

Simply install to your project:

```bash
sampctl package install CnRXoMoX/X_Enex
```

Include in your code and begin using the library:

```pawn
#include <X_Enex>
```

## Usage

<!--
Write your code documentation or examples here. If your library is documented in
the source code, direct users there. If not, list your API and describe it well
in this section. If your library is passive and has no API, simply omit this
section.
-->
# Enex_Create(entX, entY, entZ, entAng, exiX, exiY, exiZ, exiAng, worldid, interior)

Usage
```pawn
public OnGamemodeInit()
{
    Enex_Create(207.6328, -61.6965, 1.9766, 179.7099, 286.1490, -40.6444, 1001.5156, 358.6616, 1, 1); // Ammunation near Blueberry
}
```

# Enex_SetIcon(id, iconid)

Usage
```pawn
new id;
    id = Enex_Create();
    Enex_SetIcon(id, 28); // For more icon ids visit the Wiki
```

# Enex_SetName(id, const name[])

Usage
```pawn
new id;
    id = Enex_Create();
    Enex_SetName(id, "Ammunation");
```

# Enex_PlayerIn(playerid)

Get player's interior's name if the Interior have Enex_SetName

# Enex_EnableFreeze(id, bool:status)

Usage
```pawn
new id;
    id = Enex_Create();
    Enex_EnableFreeze(id, true); // Do not add if you don't want Freeze
```

# Enex_Disable(id, bool:status)

Usage
```pawn
new id;
    id = Enex_Create();
    Enex_Disable(id, true) // If you want to Disable the Enex if someone enters player will not be teleported means closed
```

## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```

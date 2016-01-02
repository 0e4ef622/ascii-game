ascii-game
==========

A game similar to super mario bros. You need a physical keyboard to play this since this reads raw data from /dev/input. It *should* work on most linux systems.

Compile with `make`

-----------------------------------------------

If you don't wanna keep running this game as root, you have to add yourself to the `input` group by running

    usermod -a -G input <your-username>

You must log out and log back in for the changes to take effect.

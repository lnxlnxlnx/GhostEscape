valgrind --leak-check=full \
--suppressions=/usr/share/valgrind/sdl.supp \
--suppressions=/usr/share/valgrind/opengl.supp \
./SDLShooter-Linux

valgrind -s --leak-check=full ./SDLShooter-Linux
g++ -I/usr/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT kv-solver.cpp -Wl,-z,relro -lfltk -o kv-solver

INCFLAGS  = -I../ext/include 
LINKFLAGS  = -L../ext/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lGLEW

CFLAGS    = -O3 -std=c++14
CC        = clang++
SRCS      = main.cpp
OBJS      = $(SRCS:.cpp=.o)
PROG      = opengl-test

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)


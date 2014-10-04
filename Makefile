CC			= g++
CFLAGS		= -std=c++11 -Wall `pkg-config --cflags gtkmm-3.0`
LINKFLAGS	= `pkg-config --libs gtkmm-3.0`
SRCS		= main.cpp md5-window.cpp
OBJS		= $(SRCS:.cpp=.o)
PROG		= main.out

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)

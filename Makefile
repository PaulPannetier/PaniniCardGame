# Compilateur
CC := g++
# Compilation
CPPFLAGS := -I include -std=c++11
# Edition des liens
LDFLAGS := -L lib_linux_d
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath='$$ORIGIN/lib'

# LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath='$$ORIGIN/lib'

MAIN=morpion.exe

all: $(MAIN)

%: %.cpp %.hpp
	$(CC) -o $@ $< $(CCFLAGS)

$(MAIN): main.o AssetsManager.o Ball.o Board.o Button.o Card.o CardManager.o CardPlaceInfo.o Collider2D.o Deck.o EventManager.o GameManager.o Hand.o InputManager.o Player.o Time.o
	$(CC) -o $(MAIN) main.o AssetsManager.o Ball.o Board.o Button.o Card.o CardManager.o CardPlaceInfo.o Collider2D.o Deck.o EventManager.o GameManager.o Hand.o InputManager.o Player.o Time.o $(LDFLAGS) $(LDLIBS)

clean:
	rm *.o $(MAIN)

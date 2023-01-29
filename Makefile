# Compilateur
CC := g++
# Compilation
CPPFLAGS := -I include -std=c++11
# Edition des liens
LDFLAGS := -L lib_linux
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath='$$ORIGIN/lib_linux'

# LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath='$$ORIGIN/lib'

MAIN=PaniniCardGame

all: $(MAIN)

%: %.cpp %.hpp
	$(CC) -o $@ $< $(CCFLAGS)

$(MAIN): main.o AssetsManager.o Ball.o Board.o Button.o Card.o CardManager.o CardPlaceInfo.o Collider2D.o Deck.o EventManager.o GameManager.o Hand.o InputManager.o Player.o Time.o Effect.o IncreaseStatAtTurnEffect.o
	$(CC) -o $(MAIN) main.o AssetsManager.o Ball.o Board.o Button.o Card.o CardManager.o CardPlaceInfo.o Collider2D.o Deck.o EventManager.o GameManager.o Hand.o InputManager.o Player.o Time.o Effect.o IncreaseStatAtTurnEffect.o $(LDFLAGS) $(LDLIBS)

clean:
	rm *.o $(MAIN)

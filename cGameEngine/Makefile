BUILD_PATH=bin
OUTPUT_NAME=$(BUILD_PATH)/output
COMPILER=gcc
FLAGS=-lm -lncurses -lpthread -O3 -Wall
CFLAGS=-c -O3 -Wall

all: $(BUILD_PATH)/main.o $(BUILD_PATH)/defs.o $(BUILD_PATH)/Vector2.o $(BUILD_PATH)/GameObject.o $(BUILD_PATH)/Ncurses.o \
		$(BUILD_PATH)/GenericSet.o $(BUILD_PATH)/Vertex.o $(BUILD_PATH)/NcursesRenderer.o $(BUILD_PATH)/OBJLoader.o \
		$(BUILD_PATH)/Matrix22.o $(BUILD_PATH)/Matrix44.o $(BUILD_PATH)/Vector4.o $(BUILD_PATH)/Vector3.o $(BUILD_PATH)/Camera.o \
		$(BUILD_PATH)/BMPLoader.o $(BUILD_PATH)/Quaternion.o $(BUILD_PATH)/FrameBuffer.o $(BUILD_PATH)/Color.o \
		$(BUILD_PATH)/Texture.o $(BUILD_PATH)/Time.o $(BUILD_PATH)/SplashScreen.o $(BUILD_PATH)/Game.o $(BUILD_PATH)/Panel.o
	$(COMPILER) $(FLAGS) $(BUILD_PATH)/main.o $(BUILD_PATH)/defs.o $(BUILD_PATH)/Vector2.o $(BUILD_PATH)/GameObject.o $(BUILD_PATH)/Ncurses.o \
		$(BUILD_PATH)/GenericSet.o $(BUILD_PATH)/Vertex.o $(BUILD_PATH)/NcursesRenderer.o $(BUILD_PATH)/OBJLoader.o $(BUILD_PATH)/Matrix22.o \
		$(BUILD_PATH)/Matrix44.o $(BUILD_PATH)/Vector4.o $(BUILD_PATH)/Vector3.o $(BUILD_PATH)/Camera.o $(BUILD_PATH)/BMPLoader.o \
		$(BUILD_PATH)/Quaternion.o $(BUILD_PATH)/FrameBuffer.o $(BUILD_PATH)/Color.o $(BUILD_PATH)/Texture.o $(BUILD_PATH)/Time.o \
		$(BUILD_PATH)/SplashScreen.o $(BUILD_PATH)/Game.o $(BUILD_PATH)/Panel.o \
		-o $(OUTPUT_NAME)

$(BUILD_PATH)/main.o: main.c
	$(COMPILER) $(CFLAGS) main.c -o $(BUILD_PATH)/main.o

$(BUILD_PATH)/defs.o: defs.c
	$(COMPILER) $(CFLAGS) defs.c -o $(BUILD_PATH)/defs.o

$(BUILD_PATH)/Vector2.o: Vector2.c
	$(COMPILER) $(CFLAGS) Vector2.c -o $(BUILD_PATH)/Vector2.o
	
$(BUILD_PATH)/GameObject.o: GameObject.c
	$(COMPILER) $(CFLAGS) GameObject.c -o $(BUILD_PATH)/GameObject.o

$(BUILD_PATH)/Ncurses.o: NcursesBase.c
	$(COMPILER) $(CFLAGS) NcursesBase.c -o $(BUILD_PATH)/Ncurses.o

$(BUILD_PATH)/GenericSet.o: GenericSet.c
	$(COMPILER) $(CFLAGS) GenericSet.c -o $(BUILD_PATH)/GenericSet.o

$(BUILD_PATH)/Vertex.o: Vertex.c
	$(COMPILER) $(CFLAGS) Vertex.c -o $(BUILD_PATH)/Vertex.o

$(BUILD_PATH)/NcursesRenderer.o: NcursesRenderer.c
	$(COMPILER) $(CFLAGS) NcursesRenderer.c -o $(BUILD_PATH)/NcursesRenderer.o

$(BUILD_PATH)/OBJLoader.o: OBJLoader.c
	$(COMPILER) $(CFLAGS) OBJLoader.c -o $(BUILD_PATH)/OBJLoader.o

$(BUILD_PATH)/Matrix22.o: Matrix22.c
	$(COMPILER) $(CFLAGS) Matrix22.c -o $(BUILD_PATH)/Matrix22.o

$(BUILD_PATH)/Matrix44.o: Matrix44.c
	$(COMPILER) $(CFLAGS) Matrix44.c -o $(BUILD_PATH)/Matrix44.o

$(BUILD_PATH)/Vector4.o: Vector4.c
	$(COMPILER) $(CFLAGS) Vector4.c -o $(BUILD_PATH)/Vector4.o

$(BUILD_PATH)/Vector3.o: Vector3.c
	$(COMPILER) $(CFLAGS) Vector3.c -o $(BUILD_PATH)/Vector3.o

$(BUILD_PATH)/Camera.o: Camera.c
	$(COMPILER) $(CFLAGS) Camera.c -o $(BUILD_PATH)/Camera.o

$(BUILD_PATH)/BMPLoader.o: BMPLoader.c
	$(COMPILER) $(CFLAGS) BMPLoader.c -o $(BUILD_PATH)/BMPLoader.o

$(BUILD_PATH)/Quaternion.o: Quaternion.c
	$(COMPILER) $(CFLAGS) Quaternion.c -o $(BUILD_PATH)/Quaternion.o

$(BUILD_PATH)/FrameBuffer.o: FrameBuffer.c
	$(COMPILER) $(CFLAGS) FrameBuffer.c -o $(BUILD_PATH)/FrameBuffer.o

$(BUILD_PATH)/Color.o: Color.c
	$(COMPILER) $(CFLAGS) Color.c -o $(BUILD_PATH)/Color.o

$(BUILD_PATH)/Texture.o: Texture.c
	$(COMPILER) $(CFLAGS) Texture.c -o $(BUILD_PATH)/Texture.o

$(BUILD_PATH)/Time.o: Time.c
	$(COMPILER) $(CFLAGS) Time.c -o $(BUILD_PATH)/Time.o

$(BUILD_PATH)/SplashScreen.o: SplashScreen.c
	$(COMPILER) $(CFLAGS) SplashScreen.c -o $(BUILD_PATH)/SplashScreen.o

$(BUILD_PATH)/Game.o: Game.c
	$(COMPILER) $(CFLAGS) Game.c -o $(BUILD_PATH)/Game.o

$(BUILD_PATH)/Panel.o: Panel.c
	$(COMPILER) $(CFLAGS) Panel.c -o $(BUILD_PATH)/Panel.o

run: all
	clear
	./$(OUTPUT_NAME)

clean:
	rm $(BUILD_PATH)/*.o $(OUTPUT_NAME)

backup: all
	backup

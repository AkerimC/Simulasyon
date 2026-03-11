CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Klasörler
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Kaynak kodlar ve nesne dosyaları
SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(INC_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Çıktı dosyasının adı
TARGET = $(BUILD_DIR)/simulasyon

# Varsayılan derleme kuralı (make yazıldığında çalışır)
all: $(TARGET)

# Ana programı derleme adımı (.o dosyalarını birleştirir)
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Her bir .c dosyasını .o nesne (object) dosyasına dönüştürme adımı
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Derlenmiş dosyaları temizleme (make clean)
clean:
	rm -rf $(BUILD_DIR)/*

# Hem derleyip hem çalıştırmak için (make run)
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

#!/bin/bash

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}  Skibidi AVX Native Library Builder   ${NC}"
echo -e "${GREEN}  Version: 1.7.1                       ${NC}"
echo -e "${GREEN}========================================${NC}"

echo -e "\n${YELLOW}[1/5] Checking build environment...${NC}"

if ! command -v gcc &> /dev/null; then
    echo -e "${RED}Error: GCC not found.${NC}"
    echo "Please install build-essential: sudo apt update && sudo apt install -y build-essential"
    exit 1
fi

echo -e "\n${YELLOW}[2/5] Detecting CPU capabilities...${NC}"

CPU_FLAGS=$(cat /proc/cpuinfo | grep flags | head -n 1)

if echo "$CPU_FLAGS" | grep -q "avx2"; then
    echo -e "  [+] ${CYAN}AVX2${NC} detected"
else
    echo -e "  [-] ${RED}AVX2${NC} not detected (Performance will be limited)"
fi

if echo "$CPU_FLAGS" | grep -q "avx512f"; then
    echo -e "  [+] ${CYAN}AVX-512F${NC} detected (High Performance Mode)"
    echo "$CPU_FLAGS" | grep -q "avx512vl" && echo -e "  [+] ${CYAN}AVX-512VL${NC} detected"
    echo "$CPU_FLAGS" | grep -q "avx512bw" && echo -e "  [+] ${CYAN}AVX-512BW${NC} detected"
    echo "$CPU_FLAGS" | grep -q "avx512dq" && echo -e "  [+] ${CYAN}AVX-512DQ${NC} detected"
else
    echo -e "  [-] ${YELLOW}AVX-512${NC} not detected (Using AVX2 or Scalar fallback)"
fi

echo -e "\n${YELLOW}[3/5] Creating output directories...${NC}"
mkdir -p build/linux-x86_64
rm -f build/linux-x86_64/libskibidi_avx.so

echo -e "\n${YELLOW}[4/5] Compiling for Linux x86_64...${NC}"

GCC_FLAGS="-O3 -fPIC -shared -flto -march=native -std=gnu11"
WARN_FLAGS="-Wall -Wextra -Wno-unused-parameter"
LINK_FLAGS="-Wl,-O1 -Wl,--as-needed -Wl,--no-undefined -pthread"

echo "Command: gcc $GCC_FLAGS ..."

gcc $GCC_FLAGS $WARN_FLAGS $LINK_FLAGS \
    -o build/linux-x86_64/libskibidi_avx.so \
    ./skibidi_avx.c

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Build successful: build/linux-x86_64/libskibidi_avx.so${NC}"
else
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

echo -e "\n${YELLOW}[5/5] Verifying build artifacts...${NC}"

LIB_FILE="build/linux-x86_64/libskibidi_avx.so"

FILE_SIZE=$(du -h "$LIB_FILE" | cut -f1)
echo -e "Library Size: ${CYAN}$FILE_SIZE${NC}"

echo "Checking exported symbols:"
nm -D "$LIB_FILE" | grep " T skibidi_" | sed 's/^/  /'

echo "Dependencies:"
ldd "$LIB_FILE" | sed 's/^/  /'

echo -e "\n${GREEN}========================================${NC}"
echo -e "${GREEN}  Ready for Skibidi!                    ${NC}"
echo -e "${GREEN}========================================${NC}"

if grep -qi microsoft /proc/version 2>/dev/null; then
    WIN_PATH=$(wslpath -w "$(pwd)/build/linux-x86_64/libskibidi_avx.so" 2>/dev/null || echo "N/A")
    echo -e "\n${YELLOW}WSL detected. Windows path:${NC}"
    echo -e "${CYAN}$WIN_PATH${NC}"
fi
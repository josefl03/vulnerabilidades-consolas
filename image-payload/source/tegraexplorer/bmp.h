#include <stdint.h>

typedef struct {
    uint16_t bfType;       // Signature "BM" (0x4D42)
    uint32_t bfSize;       // File size in bytes
    uint16_t bfReserved1;  // Reserved, must be 0
    uint16_t bfReserved2;  // Reserved, must be 0
    uint32_t bfOffBits;    // Offset to pixel array
} BMPFileHeader;

typedef struct {
    uint32_t biSize;           // DIB header size (40 bytes for BITMAPINFOHEADER)
    int32_t biWidth;           // Width in pixels
    int32_t biHeight;          // Height in pixels
    uint16_t biPlanes;         // Number of color planes (must be 1)
    uint16_t biBitCount;       // Bits per pixel (24 for RGB)
    uint32_t biCompression;    // Compression type (0 = uncompressed)
    uint32_t biSizeImage;      // Image data size (may be 0 if uncompressed)
    int32_t biXPelsPerMeter;   // Horizontal resolution (pixels per meter)
    int32_t biYPelsPerMeter;   // Vertical resolution (pixels per meter)
    uint32_t biClrUsed;        // Colors in color table (0 for 24-bit)
    uint32_t biClrImportant;   // Important colors (0 = all are important)
} BMPInfoHeader;
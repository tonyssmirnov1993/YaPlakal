#include "bmp_image.h"
#include "pack_defines.h"

#include <fstream>
#include <iostream>

using namespace std;

namespace img_lib {
    static const int CLR_COUNT = 3;
    static const int PADDING = 4;
    static const uint16_t BF_T = 0x4D42;
    // функция вычисления отступа по ширине
    static int GetBMPStride(int w) {
        return PADDING * ((w * CLR_COUNT + CLR_COUNT) / PADDING);
    }

    PACKED_STRUCT_BEGIN BitmapFileHeader{
        // поля заголовка Bitmap File Header
        uint16_t bfType = BF_T;
        uint32_t bfSize = {};
        uint32_t bfReserved = 0;
        uint32_t bfOffBits = 54;
    }
    PACKED_STRUCT_END

    PACKED_STRUCT_BEGIN BitmapInfoHeader{
        // поля заголовка Bitmap Info Header
        uint32_t biSize = 40;
        int32_t biWidth = {};
        int32_t biHeight = {};
        uint16_t biPlanes = 1;
        uint16_t biBitCount = 24;
        uint32_t biCompression = 0;
        uint32_t biSizeImage = {};
        int32_t biXPelsPerMeter = 11811;
        int32_t biYPelsPerMeter = 11811;
        int32_t biClrUsed = 0;
        int32_t biClrImportant = 0x1000000;
    }
    PACKED_STRUCT_END

    bool SaveBMP(const Path& file, const Image& image) {

    const int stride = GetBMPStride(image.GetWidth());

    BitmapFileHeader file_header;
    BitmapInfoHeader info_header;

    file_header.bfSize = file_header.bfOffBits +  GetBMPStride(image.GetWidth()) * image.GetHeight();
    info_header.biWidth = image.GetWidth();
    info_header.biHeight = image.GetHeight();
    info_header.biSizeImage = GetBMPStride(image.GetWidth()) * image.GetHeight();

    ofstream out(file, ios::binary);
    if (!out.is_open()) { cout << "Error open file"; }
    out.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    out.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    vector<char> buff(stride);

        for (int y = image.GetHeight() - 1; y >= 0; --y) {
            const Color* line = image.GetLine(y);
            for (int x = 0; x < image.GetWidth(); ++x) {
                buff[x * 3 + 0] = static_cast<char>(line[x].b);
                buff[x * 3 + 1] = static_cast<char>(line[x].g);
                buff[x * 3 + 2] = static_cast<char>(line[x].r);
            }
            out.write(reinterpret_cast<const char*>(buff.data()), stride);
        }

        return out.good();
    }

    // напишите эту функцию
    Image LoadBMP(const Path& file) {
        ifstream ifs(file, ios::binary);
        if (!ifs.is_open()) {
            return {};
        }

        BitmapFileHeader file_header;
        BitmapInfoHeader info_header;

        if (!ifs.read(reinterpret_cast<char*>(&file_header), sizeof(BitmapFileHeader))) {
            return {};
        }
        if (!ifs.read(reinterpret_cast<char*>(&info_header), sizeof(BitmapInfoHeader))) {
            return {};
        }

        if (file_header.bfType != BF_T) {
            return {};
        }

        int w = info_header.biWidth;
        int h = info_header.biHeight;
        int stride = GetBMPStride(w);

        Image result(w, h, Color::Black());
        std::vector<char> buff(stride);

        for (int y = result.GetHeight() - 1; y >= 0; --y) {
            Color* line = result.GetLine(y);
            ifs.read(buff.data(), stride);

            for (int x = 0; x != w; ++x) {
                line[x].b = static_cast<byte>(buff[x * 3 + 0]);
                line[x].g = static_cast<byte>(buff[x * 3 + 1]);
                line[x].r = static_cast<byte>(buff[x * 3 + 2]);
            }
        }
        return result;
    }
}// namespace img_lib
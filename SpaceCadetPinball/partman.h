#pragma once

struct zmap_header_type;
struct gdrv_bitmap8;

enum class bmp8Flags : unsigned char
{
    RawBmpUnaligned = 1 << 0,
    DibBitmap = 1 << 1,
    Spliced = 1 << 2,
};

#pragma pack(push, 1)
struct datFileHeader
{
    char FileSignature[21];
    char AppName[50];
    char Description[100];
    int FileSize;
    unsigned short NumberOfGroups;
    int SizeOfBody;
    unsigned short Unknown;
};

struct dat8BitBmpHeader
{
    uint8_t Resolution;
    int16_t Width;
    int16_t Height;
    int16_t XPosition;
    int16_t YPosition;
    int Size;
    bmp8Flags Flags;

    bool IsFlagSet(bmp8Flags flag) const
    {
        return static_cast<char>(Flags) & static_cast<char>(flag);
    }
};

struct dat16BitBmpHeader
{
    int16_t Width;
    int16_t Height;
    int16_t Stride;
    int Unknown0;
    int16_t Unknown1_0;
    int16_t Unknown1_1;
};
#pragma pack(pop)

static_assert(sizeof(dat8BitBmpHeader) == 14, "Wrong size of dat8BitBmpHeader");
static_assert(sizeof(datFileHeader) == 183, "Wrong size of datFileHeader");
static_assert(sizeof(dat16BitBmpHeader) == 14, "Wrong size of zmap_header_type");

class partman
{
public:
    static class DatFile *load_records(LPCSTR lpFileName, bool fullTiltMode);

private:
    static short _field_size[];

    static uint8_t LRead8(FILE *file)
    {
        uint8_t Buffer{};
        fread(&Buffer, 1, sizeof(uint8_t), file);
        return Buffer;
    }

    static uint16_t LRead16(FILE *file)
    {
        uint16_t Buffer{};
        fread(&Buffer, 1, sizeof(uint16_t), file);
        return __builtin_bswap16(Buffer);
    }

    static uint32_t LRead32(FILE *file)
    {
        uint32_t Buffer{};
        fread(&Buffer, 1, sizeof(uint32_t), file);
        return __builtin_bswap32(Buffer);
    }

    static datFileHeader LReadDatFileHeader(FILE *file)
    {
        datFileHeader Buffer{};

        fread(&Buffer, 1, sizeof Buffer, file);
        Buffer.FileSize = __builtin_bswap32(Buffer.FileSize);
        Buffer.NumberOfGroups = __builtin_bswap16(Buffer.NumberOfGroups);
        Buffer.SizeOfBody = __builtin_bswap32(Buffer.SizeOfBody);
        Buffer.Unknown = __builtin_bswap16(Buffer.Unknown);

        return Buffer;
    }

    static dat8BitBmpHeader LReadDat8BitBmpHeader(FILE *file)
    {
        dat8BitBmpHeader Buffer{};
        Buffer.Resolution = LRead8(file);
        Buffer.Width = LRead16(file);
        Buffer.Height = LRead16(file);
        Buffer.XPosition = LRead16(file);
        Buffer.YPosition = LRead16(file);
        Buffer.Size = LRead32(file);
        Buffer.Flags = static_cast<bmp8Flags>(LRead8(file));

        return Buffer;
    }

    static dat16BitBmpHeader LReadDat16BitBmpHeader(FILE *file)
    {
        dat16BitBmpHeader Buffer{};
        Buffer.Width = LRead16(file);
        Buffer.Height = LRead16(file);
        Buffer.Stride = LRead16(file);
        Buffer.Unknown0 = LRead32(file);
        Buffer.Unknown1_0 = LRead16(file);
        Buffer.Unknown1_1 = LRead16(file);

        return Buffer;
    }
};

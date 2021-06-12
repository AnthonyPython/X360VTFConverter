#include <iostream>
#if not defined (_WIN32)
#include <byteswap.h>
#endif
#include <stdint.h>

enum ImageFormat 
{
	IMAGE_FORMAT_UNKNOWN  = -1,
	IMAGE_FORMAT_RGBA8888 = 0, 
	IMAGE_FORMAT_ABGR8888, 
	IMAGE_FORMAT_RGB888, 
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565, 
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,

	// Depth-stencil texture formats for shadow depth mapping
	IMAGE_FORMAT_NV_DST16,		// 
	IMAGE_FORMAT_NV_DST24,		//
	IMAGE_FORMAT_NV_INTZ,		// Vendor-specific depth-stencil texture
	IMAGE_FORMAT_NV_RAWZ,		// formats for shadow depth mapping 
	IMAGE_FORMAT_ATI_DST16,		// 
	IMAGE_FORMAT_ATI_DST24,		//
	IMAGE_FORMAT_NV_NULL,		// Dummy format which takes no video memory

	// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

#if defined( _X360 )
	// Depth-stencil texture formats
	IMAGE_FORMAT_X360_DST16,
	IMAGE_FORMAT_X360_DST24,
	IMAGE_FORMAT_X360_DST24F,
	// supporting these specific formats as non-tiled for procedural cpu access
	IMAGE_FORMAT_LINEAR_BGRX8888,
	IMAGE_FORMAT_LINEAR_RGBA8888,
	IMAGE_FORMAT_LINEAR_ABGR8888,
	IMAGE_FORMAT_LINEAR_ARGB8888,
	IMAGE_FORMAT_LINEAR_BGRA8888,
	IMAGE_FORMAT_LINEAR_RGB888,
	IMAGE_FORMAT_LINEAR_BGR888,
	IMAGE_FORMAT_LINEAR_BGRX5551,
	IMAGE_FORMAT_LINEAR_I8,
	IMAGE_FORMAT_LINEAR_RGBA16161616,

	IMAGE_FORMAT_LE_BGRX8888,
	IMAGE_FORMAT_LE_BGRA8888,
#endif

	NUM_IMAGE_FORMATS
};

enum CompiledVtfFlags
{
	// flags from the *.txt config file
	TEXTUREFLAGS_POINTSAMPLE	               = 0x00000001,
	TEXTUREFLAGS_TRILINEAR		               = 0x00000002,
	TEXTUREFLAGS_CLAMPS			               = 0x00000004,
	TEXTUREFLAGS_CLAMPT			               = 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC	               = 0x00000010,
	TEXTUREFLAGS_HINT_DXT5		               = 0x00000020,
	TEXTUREFLAGS_SRGB						   = 0x00000040,
	TEXTUREFLAGS_NORMAL			               = 0x00000080,
	TEXTUREFLAGS_NOMIP			               = 0x00000100,
	TEXTUREFLAGS_NOLOD			               = 0x00000200,
	TEXTUREFLAGS_ALL_MIPS			           = 0x00000400,
	TEXTUREFLAGS_PROCEDURAL		               = 0x00000800,
	
	// These are automatically generated by vtex from the texture data.
	TEXTUREFLAGS_ONEBITALPHA	               = 0x00001000,
	TEXTUREFLAGS_EIGHTBITALPHA	               = 0x00002000,

	// newer flags from the *.txt config file
	TEXTUREFLAGS_ENVMAP			               = 0x00004000,
	TEXTUREFLAGS_RENDERTARGET	               = 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET	           = 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE               = 0x00020000,
	TEXTUREFLAGS_SINGLECOPY		               = 0x00040000,
	
		TEXTUREFLAGS_UNUSED_00080000		   = 0x00080000,
		TEXTUREFLAGS_UNUSED_00100000		   = 0x00100000,
		TEXTUREFLAGS_UNUSED_00200000           = 0x00200000,
		TEXTUREFLAGS_UNUSED_00400000           = 0x00400000,

	TEXTUREFLAGS_NODEPTHBUFFER                 = 0x00800000,

		TEXTUREFLAGS_UNUSED_01000000           = 0x01000000,

	TEXTUREFLAGS_CLAMPU                        = 0x02000000,

	TEXTUREFLAGS_VERTEXTEXTURE                 = 0x04000000,					// Useable as a vertex texture

	TEXTUREFLAGS_SSBUMP                        = 0x08000000,
					
		TEXTUREFLAGS_UNUSED_10000000           = 0x10000000,

	// Clamp to border color on all texture coordinates
	TEXTUREFLAGS_BORDER						   = 0x20000000,

		TEXTUREFLAGS_UNUSED_40000000		   = 0x40000000,
		TEXTUREFLAGS_UNUSED_80000000		   = 0x80000000,
};

#pragma pack(1)


struct VTFFileBaseHeader_t
{
	char fileTypeString[4]; // "VTF" Valve texture file
	int version[2]; 		// version[0].version[1]
	int headerSize;
};

struct VectorAligned
{
	unsigned char pad[4];
	float x, y, z;
};

struct Vector
{
	float x, y, z;
};

struct VTFFileHeaderV7_1_t : public VTFFileBaseHeader_t 
{
	unsigned short	width;
	unsigned short	height;
	unsigned int	flags;
	unsigned short	numFrames;
	unsigned short	startFrame;

	// must manually align in order to maintain pack(1) expected layout with existing binaries
	char			pad1[4];
	Vector			reflectivity;
	char			pad2[4];

	float			bumpScale;
	ImageFormat		imageFormat;
	unsigned char	numMipLevels;
	ImageFormat		lowResImageFormat;
	unsigned char	lowResImageWidth;
	unsigned char	lowResImageHeight;
	
	unsigned char	pad3[1];
};

struct VTFFileHeaderV7_2_t : public VTFFileHeaderV7_1_t
{

	unsigned short depth;
};

typedef unsigned int uint32;
typedef unsigned char uint8;


#define BYTE_POS( byteVal, shft )	uint32( uint32(uint8(byteVal)) << uint8(shft * 8) )
#if !defined( _X360 )
#define MK_VTF_RSRC_ID(a, b, c)		uint32( BYTE_POS(a, 0) | BYTE_POS(b, 1) | BYTE_POS(c, 2) )
#define MK_VTF_RSRCF(d)				BYTE_POS(d, 3)
#else
#define MK_VTF_RSRC_ID(a, b, c)		uint32( BYTE_POS(a, 3) | BYTE_POS(b, 2) | BYTE_POS(c, 1) )
#define MK_VTF_RSRCF(d)				BYTE_POS(d, 0)
#endif

// Special section for stock resources types
enum ResourceEntryType
{
	// Legacy stock resources, readin/writing are handled differently (i.e. they do not have the length tag word!)
	VTF_LEGACY_RSRC_LOW_RES_IMAGE	= MK_VTF_RSRC_ID( 0x01, 0, 0 ),	// Low-res image data
	VTF_LEGACY_RSRC_IMAGE			= MK_VTF_RSRC_ID( 0x30, 0, 0 ),	// Image data

	// New extended resource
	VTF_RSRC_SHEET = MK_VTF_RSRC_ID( 0x10, 0, 0 ),			// Sheet data
};

// Bytes with special meaning when set in a resource type
enum ResourceEntryTypeFlag
{
	RSRCF_HAS_NO_DATA_CHUNK	= MK_VTF_RSRCF( 0x02 ),	// Resource doesn't have a corresponding data chunk
	RSRCF_MASK				= MK_VTF_RSRCF( 0xFF )	// Mask for all the flags
};

// Header details constants
enum HeaderDetails
{
	MAX_RSRC_DICTIONARY_ENTRIES = 32,		// Max number of resources in dictionary
	MAX_X360_RSRC_DICTIONARY_ENTRIES = 4,	// 360 needs this to be slim, otherwise preload size suffers
};

struct ResourceEntryInfo
{
	union
	{ 
		unsigned int	eType;		// Use MK_VTF_??? macros to be endian compliant with the type
		unsigned char	chTypeBytes[4];
	};
	unsigned int		resData;	// Resource data or offset from the beginning of the file
};

struct VTFFileHeaderV7_3_t : public VTFFileHeaderV7_2_t
{

	char			pad4[3];
	unsigned int	numResources;

#if defined( _X360 ) || defined( POSIX )
	// must manually align in order to maintain pack(1) expected layout with existing binaries
	char			pad5[8];
#endif
	
	// AFTER THE IMPLICIT PADDING CAUSED BY THE COMPILER....
	// *** followed by *** ResourceEntryInfo resources[0];
	// Array of resource entry infos sorted ascending by type
};

#define VTF_X360_MAJOR_VERSION	0x0360
#define VTF_X360_MINOR_VERSION	8
struct VTFFileHeaderX360_t : public VTFFileBaseHeader_t 
{
	unsigned int	flags;
	unsigned short	width;					// actual width of data in file
	unsigned short	height;					// actual height of data in file
	unsigned short	depth;					// actual depth of data in file
	unsigned short	numFrames;
	unsigned short	preloadDataSize;		// exact size of preload data (may extend into image!)
	unsigned char	mipSkipCount;			// used to resconstruct mapping dimensions
	unsigned char	numResources;
	Vector			reflectivity;			// Resides on 16 byte boundary!
	float			bumpScale;
	ImageFormat		imageFormat;
	unsigned char	lowResImageSample[4];
	unsigned int	compressedSize;

	// *** followed by *** ResourceEntryInfo resources[0];
};

#pragma pack()

float byteswap_float(float value)
{
	int converted_to_int = *(int *)&value;
	int swapped = ((converted_to_int>>24)&0xff) | // move byte 3 to byte 0
                    ((converted_to_int<<8)&0xff0000) | // move byte 1 to byte 2
                    ((converted_to_int>>8)&0xff00) | // move byte 2 to byte 1
                    ((converted_to_int<<24)&0xff000000); // byte 0 to byte 3
	
	return *(float *)&swapped;
}

#if defined (_WIN32)
int bswap_32(int value)
{
	int swapped = ((value>>24)&0xff) | // move byte 3 to byte 0
                    ((value<<8)&0xff0000) | // move byte 1 to byte 2
                    ((value>>8)&0xff00) | // move byte 2 to byte 1
                    ((value<<24)&0xff000000); // byte 0 to byte 3
	
	return swapped;
}
#endif

#if defined (_WIN32)
uint16_t bswap_16(uint16_t value)
{
	return (value >> 8) |(value << 8);
}
#endif

int main(int argc, char **argv) 
{
    if (argc < 3)
        return 1;
    
	FILE *pFile = fopen(argv[1], "rb");
	if (!pFile)
		return 1;
	
	fseek(pFile, 0, SEEK_END);
	
	size_t iFileSize = ftell(pFile);
	
	fseek(pFile, 0, SEEK_SET);
	
	char *pBuffer = (char *)malloc(iFileSize);
	fread(pBuffer, 1, iFileSize, pFile);
	fclose(pFile);
	
	VTFFileHeaderX360_t *pHdr = (VTFFileHeaderX360_t *)pBuffer;
	
	pHdr->version[0] = bswap_32(pHdr->version[0]);
	pHdr->version[1] = bswap_32(pHdr->version[1]);
	pHdr->headerSize = bswap_32(pHdr->headerSize);
	
	pHdr->flags = bswap_32(pHdr->flags);
	pHdr->width = bswap_16(pHdr->width);
	pHdr->height = bswap_16(pHdr->height);
	pHdr->depth = bswap_16(pHdr->depth);
	pHdr->numFrames = bswap_16(pHdr->numFrames);
	pHdr->preloadDataSize = bswap_16(pHdr->preloadDataSize);
	
	pHdr->reflectivity.x = byteswap_float(pHdr->reflectivity.x);
	pHdr->reflectivity.y = byteswap_float(pHdr->reflectivity.y);
	pHdr->reflectivity.z = byteswap_float(pHdr->reflectivity.z);
	
	pHdr->bumpScale = byteswap_float(pHdr->bumpScale);
	pHdr->imageFormat = (ImageFormat)bswap_32(pHdr->imageFormat);
	pHdr->compressedSize = bswap_32(pHdr->compressedSize);
	
	if (pHdr->version[0] == VTF_X360_MAJOR_VERSION && pHdr->version[1] == VTF_X360_MINOR_VERSION)
	{
		// Convert to a 7.1 VTF
		VTFFileHeaderV7_1_t newHeader;
		newHeader.fileTypeString[0] = 'V';
		newHeader.fileTypeString[1] = 'T';
		newHeader.fileTypeString[2] = 'F';
		newHeader.fileTypeString[3] = '\0';
		
		newHeader.version[0] = 7;
		newHeader.version[1] = 1;
		
		newHeader.headerSize = sizeof(VTFFileHeaderV7_1_t);
		
		
		// VTF 7.1 members.
		newHeader.width = pHdr->width;
		newHeader.height = pHdr->height;
		newHeader.flags = pHdr->flags;
		newHeader.numFrames = pHdr->numFrames;
		newHeader.startFrame = 0; // Doesn't exist in x360 version.
		
		newHeader.reflectivity = pHdr->reflectivity;
		newHeader.bumpScale = pHdr->bumpScale;
		newHeader.imageFormat = pHdr->imageFormat;
		
		int nMipMapCalculation = 1;
		
		if (!(pHdr->flags & TEXTUREFLAGS_NOMIP))
		{
			int iSizeMipmap = (newHeader.width < newHeader.height) ? newHeader.width : newHeader.height;
			for (int i = 0;;i++)
			{
				if (iSizeMipmap > 1)
				{
					iSizeMipmap = iSizeMipmap >> 1;
					nMipMapCalculation++;
				}
				else
				{
					break;
				}
			}
		}
		
		newHeader.numMipLevels = nMipMapCalculation; // Doesn't exist in x360 version.
		newHeader.lowResImageFormat = pHdr->imageFormat; // Doesn't exist in x360 version.
		newHeader.lowResImageWidth = 0; // Doesn't exist in x360 version.
		newHeader.lowResImageHeight = 0; // Doesn't exist in x360 version.
		
		newHeader.pad1[0] = 0;
		newHeader.pad1[1] = 0;
		newHeader.pad1[2] = 0;
		newHeader.pad1[3] = 0;
		
		newHeader.pad2[0] = 0;
		newHeader.pad2[1] = 0;
		newHeader.pad2[2] = 0;
		newHeader.pad2[3] = 0;
		
		newHeader.pad3[0] = 0;
		
		// ----------------------------------------------------------------------------------
		
		pFile = fopen(argv[2], "wb");
		fwrite(&newHeader, 1, sizeof(VTFFileHeaderV7_1_t), pFile);
		
		for (int i = 0; i < pHdr->numResources; i++)
		{
			ResourceEntryInfo *pResourceEntryInfo = (ResourceEntryInfo *)(pBuffer + sizeof(VTFFileHeaderX360_t) + (sizeof(ResourceEntryInfo) * i));
			pResourceEntryInfo->resData = bswap_32(pResourceEntryInfo->resData);
		}
		
		for (int i = 0; i < pHdr->numResources; i++)
		{
			ResourceEntryInfo *pResourceEntryInfo = (ResourceEntryInfo *)(pBuffer + sizeof(VTFFileHeaderX360_t) + (sizeof(ResourceEntryInfo) * i));
			
			unsigned int iPixelDataSize;
			if (pHdr->numResources == 1)
			{
				iPixelDataSize = iFileSize - pResourceEntryInfo->resData;
			}

			// Convert from big endian to little endian pixel data.
			for (int i = 0; i < iPixelDataSize; i += 2)
			{
				short *pInt = (short *)(pBuffer + pResourceEntryInfo->resData + i);
				*pInt = bswap_16(*pInt);
			}
			
			fwrite(pBuffer + pResourceEntryInfo->resData, 1, iPixelDataSize, pFile);
		}
		
		fclose(pFile);
	}
}
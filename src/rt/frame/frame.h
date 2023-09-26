/* FILE NAME   : frame.h
 * PURPOSE     : Ray Tracing project.
 *               Frame buffer module.
 * PROGRAMMER  : AU3
 * LAST UPDATE : 01.08.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __frame_h_
#define __frame_h_

#include "../../def.h"
#include <fstream>

#pragma pack(push, 1)
#include <TGAHEAD.H>
#pragma pack(pop)

/* Project namespace */
namespace nirt
{
  class frame
  {
  private:
    DWORD *Pixels = nullptr; // Frame buffer pixels
  public:
    INT W = 0, H = 0;        // Frame size

    /* Default constructor */
    frame( VOID )
    {
    } /* End of 'frame' function */

    /* Copy constructor.
     * ARGUMENTS:
     *   - frame to copy:
     *       const frame &Fr;
     */
    frame( const frame &Fr )
    {
      if (Pixels != nullptr)
        delete[] Pixels;
      W = Fr.W;
      H = Fr.H;
      Pixels = new DWORD[W * H];
      memcpy(Pixels, Fr.Pixels, W * H * 4);
    } /* End of 'frame' constructor */

    VOID Clear( VOID )
    {
      if (Pixels != nullptr)
        memset(Pixels, 0, W * H * 4);
    }

    /* Operator = function. 
     * ARGUMENTS:
     *   - frame to equal:
     *       const frame &Fr; 
     * RETURNS: None.
     */
    VOID operator = ( const frame &Fr )
    {
      if (Pixels != nullptr)
        delete[] Pixels;
      W = Fr.W;
      H = Fr.H;
      Pixels = new DWORD[W * H];
      memcpy(Pixels, Fr.Pixels, W * H * 4);
    } /* End of 'operator =' function */

    /* Destructor */
    ~frame( VOID )
    {
      if (Pixels != nullptr)
        delete[] Pixels, Pixels = nullptr;
      W = H = 0;
    } /* End of 'frame' destructor */

    /* Resize frame function.
     * ARGUMENTS:
     *   - new size:
     *       INT NewW, NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      W = NewW * 0.96;
      H = NewH * 0.96;

      if (Pixels != nullptr)
        delete[] Pixels;
      Pixels = new DWORD[W * H];
      ZeroMemory(Pixels, 4 * W * H);
    } /* End of 'Resize' function */

    /* Put pixel to frame function.
     * ARGUMENTS: 
     *   - coordinates to put:
     *       INT X, Y;
     *   - color to put:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( INT X, INT Y, DWORD Color )
    {
      // Clipping
      if (X < 0 || Y < 0 || X >= W || Y >= H)
        return;

      // Set color
      Pixels[Y * W + X] = Color;
    } /* End of 'PutPixel' function */

    /* Draw function.
     * ARGUMENTS:
     *   - device context to draw:
     *       HDC hDC;
     *   - coordinates to draw;
     *       INT X, Y;
     * RETURNS: None.
     */
    VOID Draw( HDC hDC, INT X = 0, INT Y = 0 )
    {
      BITMAPINFOHEADER bih;

      bih.biSize = sizeof(BITMAPINFOHEADER);
      bih.biBitCount = 32;
      bih.biPlanes = 1;
      bih.biWidth = W;
      bih.biHeight = -H;
      bih.biSizeImage = W * H * 4;
      bih.biCompression = BI_RGB;
      bih.biClrUsed = 0;
      bih.biClrImportant = 0;
      bih.biXPelsPerMeter = 30;
      bih.biYPelsPerMeter = 30;

      for (INT i = 0; i < W; i++)
      {
        PutPixel(i, 0, 0xFF8000);
        PutPixel(i, 1, 0xFF8000);
        PutPixel(i, 2, 0xFF8000);
        PutPixel(i, H - 1, 0xFF8000);
        PutPixel(i, H - 2, 0xFF8000);
        PutPixel(i, H - 3, 0xFF8000);
      }
      for (INT i = 0; i < H; i++)
      {
        PutPixel(0, i, 0xFF8000);
        PutPixel(1, i, 0xFF8000);
        PutPixel(2, i, 0xFF8000);
        PutPixel(W - 1, i, 0xFF8000);
        PutPixel(W - 2, i, 0xFF8000);
        PutPixel(W - 3, i, 0xFF8000);
      }
      SetStretchBltMode(hDC, COLORONCOLOR);
      StretchDIBits(hDC, X, Y, W, H, 0, 0, W, H, Pixels, 
        (BITMAPINFO *)&bih, DIB_RGB_COLORS, SRCCOPY);
    } /* End of 'Draw' function */

    /* Save image to BMP function.
     * ARGUMENTS:
     *   - save file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL SaveBMP( const std::string &FileName )
    {
      BITMAPFILEHEADER bmf;
      BITMAPINFOHEADER bmi;

      /* Fill file headers */
      UINT bpl = ((W * 3 + 3) >> 2) << 2;
      bmf.bfType = 'B' | ('M' << 8);
      bmf.bfSize = sizeof(bmf) + sizeof(bmi) + H * bpl;
      bmf.bfReserved1 = bmf.bfReserved2 = 0;
      bmf.bfOffBits = sizeof(bmf) + sizeof(bmi);

      bmi.biSize = sizeof(bmi);
      bmi.biWidth = W;
      bmi.biHeight = H;
      bmi.biBitCount = 24;
      bmi.biPlanes = 1;
      bmi.biSizeImage = H * bpl;
      bmi.biCompression = BI_RGB;
      bmi.biXPelsPerMeter = bmi.biYPelsPerMeter = 1;
      bmi.biClrImportant = bmi.biClrUsed = 0;

      std::ofstream f(FileName, std::ios_base::binary);
      f.write((CHAR *)&bmf, sizeof(bmf)).
        write((CHAR *)&bmi, sizeof(bmi));

      /* Write image color data */
      BYTE *buf = new BYTE[bpl];
      for (INT row = H - 1; row >= 0; row--)
      {
        for (INT x = 0; x < W; x++)
        {
          buf[x * 3 + 0] = Pixels[row * W + x] & 0xFF;
          buf[x * 3 + 1] = (Pixels[row * W + x] >> 8) & 0xFF;
          buf[x * 3 + 2] = (Pixels[row * W + x] >> 16) & 0xFF;
        }
        f.write((CHAR *)buf, bpl);
      }
      delete[] buf;
      return TRUE;
    } /* End of 'SaveBMP' function */

    /* Save image to TGA function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID SaveTGA( VOID )
    {
      tgaFILEHEADER fh;
      tgaFILEFOOTER ff;
      tgaEXTHEADER eh;
      CHAR FileName[1000];
      SYSTEMTIME st;

      srand(clock());
      GetLocalTime(&st);
      sprintf(FileName, "SHOTS/ND4_RT_%d_%02d_%02d_%02d_%02d_%02d_%03d_%d.tga",
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
        st.wMilliseconds, rand() % 3000);

      std::ofstream f(FileName, std::ios_base::binary);

      fh.X = fh.Y = 0;
      fh.Width = W;
      fh.Height = H;
      fh.ImageType = 2;
      fh.BitsPerPixel = 24;
      fh.PaletteEntrySize = 0;
      fh.PaletteSize = 0;
      fh.PaletteStart = 0;
      fh.IDLength = (BYTE)strlen("(c) Computer Graphics Support Group of 30 Phys-Math Lyceum");
      fh.ColorMapType = 0;
      fh.ImageDescr = 32;

      ff.DeveloperOffset = 0;
      ff.ExtensionOffset = sizeof(tgaFILEHEADER) + sizeof("(c) Computer Graphics Support Group of 30 Phys-Math Lyceum") + W * H * 4;
      strcpy(ff.Signature, TGA_EXT_SIGNATURE);

      eh.Size = sizeof(tgaEXTHEADER);
      strcpy(eh.AuthorName, "ND4");
      strcpy(eh.AuthorComment, "Ray Tracing project");
      eh.StampYear = st.wYear;
      eh.StampMonth = st.wMonth;
      eh.StampDay = st.wDay;
      eh.StampHour = st.wHour;
      eh.StampMinute = st.wMinute;
      eh.StampSecond = st.wSecond;
      strcpy(eh.JobName, "Ray Tracing sample");
      eh.JobHour = 0;
      eh.JobMinute = 0;
      eh.JobSecond = 30;
      strcpy(eh.SoftwareID, "Proc: Intel(R) Core(TM) i5-4590");
      eh.VersionNumber = 1;
      eh.VersionLetter = 'a';
      eh.KeyColor = 0;
      eh.PixelDenominator = 1;
      eh.PixelNumerator = 1;
      eh.GammaNumerator = 1;
      eh.GammaDenominator = 1;
      eh.AttributeType = 0;

      f.write((CHAR *)&fh, sizeof(fh));
      f.write("(c) Computer Graphics Support Group of 30 Phys-Math Lyceum", fh.IDLength);
      for (INT y = 0; y < H; y++)
        for (INT x = 0; x < W; x++)
          f.write((CHAR *)&Pixels[y * W + x], 3);
      f.write((CHAR *)&eh, sizeof(eh));
      f.write((CHAR *)&ff, sizeof(ff));
    } /* End of 'SaveTGA' function */

    /* To RGB function.
     * ARGUMENTS:
     *   - RGB values:
     *       FLT R, G, B
     * RETURNS: (DWORD) Color
     */
    static DWORD toRGB( FLT R, FLT G, FLT B )
    {
      DWORD Color = RGB(mth::Clamp(B * 255.0, 0.0, 255.0), 
                        mth::Clamp(G * 255.0, 0.0, 255.0), 
                        mth::Clamp(R * 255.0, 0.0, 255.0));
      return Color;
    }
  }; /* End of 'frame' class */
} /* End of 'nirt' namespace */

#endif /* __frame_h_ */

/* END OF 'frame.h' FILE */
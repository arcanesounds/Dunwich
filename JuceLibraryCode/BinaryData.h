/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   small_knob_png;
    const int            small_knob_pngSize = 10678266;

    extern const char*   bgon_png;
    const int            bgon_pngSize = 2118298;

    extern const char*   bgoff_png;
    const int            bgoff_pngSize = 2093502;

    extern const char*   switch3_png;
    const int            switch3_pngSize = 185409;

    extern const char*   switch2_png;
    const int            switch2_pngSize = 243700;

    extern const char*   switch_png;
    const int            switch_pngSize = 244512;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}

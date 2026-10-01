#pragma once

// gl2d includes <stb_truetype/stb_truetype.h>, because upstream gl2d vendors each
// third-party library in its own folder. The nothings/stb repository keeps every
// header side by side, so this forwarding header makes both spellings work:
//   <stb_truetype.h>            -> dependencies/stb/stb_truetype.h
//   <stb_truetype/stb_truetype.h>  -> this file

#include <stb_truetype.h>

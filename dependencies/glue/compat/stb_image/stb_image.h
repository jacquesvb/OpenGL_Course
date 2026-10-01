#pragma once

// gl2d includes <stb_image/stb_image.h>, because upstream gl2d vendors each
// third-party library in its own folder. The nothings/stb repository keeps every
// header side by side, so this forwarding header makes both spellings work:
//   <stb_image.h>            -> dependencies/stb/stb_image.h
//   <stb_image/stb_image.h>  -> this file

#include <stb_image.h>

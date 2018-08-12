#pragma once

/**
 * Macro for marking functions as having public visibility.
 * Ported from folly/CPortability.h
 */
#ifndef __GNUC_PREREQ
#if defined __GNUC__ && defined __GNUC_MINOR__
#define __GNUC_PREREQ(maj, min) \
  ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#define __GNUC_PREREQ(maj, min) 0
#endif
#endif

#ifdef _WIN32
# if defined(torch_EXPORTS)
#  define TORCH_API __declspec(dllexport)
# else
#  define TORCH_API __declspec(dllimport)
# endif
#elif defined(__GNUC__)
# if defined(torch_EXPORTS)
#  if __GNUC_PREREQ(4, 9)
#   define TORCH_API [[gnu::visibility("default")]]
#  else
#   define TORCH_API __attribute__((__visibility__("default")))
#  endif
# else
#  define TORCH_API
# endif
#else
# define TORCH_API
#endif

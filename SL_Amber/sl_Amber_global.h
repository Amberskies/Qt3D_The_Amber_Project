#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SL_AMBER_LIB)
#  define SL_AMBER_EXPORT Q_DECL_EXPORT
# else
#  define SL_AMBER_EXPORT Q_DECL_IMPORT
# endif
#else
# define SL_GRAPHICS_EXPORT
#endif

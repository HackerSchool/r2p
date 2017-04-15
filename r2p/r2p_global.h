#ifndef R2P_GLOBAL_H
#define R2P_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(R2P_LIBRARY)
#  define R2PSHARED_EXPORT Q_DECL_EXPORT
#else
#  define R2PSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // R2P_GLOBAL_H

#ifndef RECEIPT_GLOBAL_H
#define RECEIPT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RECEIPT_LIBRARY)
#  define RECEIPT_EXPORT Q_DECL_EXPORT
#else
#  define RECEIPT_EXPORT Q_DECL_IMPORT
#endif

#endif // RECEIPT_GLOBAL_H

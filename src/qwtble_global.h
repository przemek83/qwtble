#pragma once

#include <QtCore/qglobal.h>

#if defined(QWTBLE_LIBRARY)
#define QWTBLE_EXPORT Q_DECL_EXPORT
#else
#define QWTBLE_EXPORT Q_DECL_IMPORT
#endif

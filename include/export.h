#ifndef SMALLPROJECTS_EXPORT_H
#define SMALLPROJECTS_EXPORT_H

#if !defined(LEVELDB_EXPORT)

#if defined(LEVELDB_SHARED_LIBRARY)
#if defined(OS_WIN)

#if defined(LEVELDB_COMPILE_LIBRARY)
#define LEVELDB_EXPORT  __declspec(dllexport)
#else
#define LEVELDB_EXPORT  __declspec(dllimport)
#endif // defined(LEVELDB_COMPILE_LIBRARY)

#else // defined(OS_WIN)
#if defined(LEVELDB_COMPILE_LIBRARY)
#define LEVELDB_EXPORT __attribute__((visibility("default")))
#else
#define LEVELDB_EXPORT
#endif
#endif // defined(OS_WIN)

#else // defined(LEVELDB_SHARED_LIBRARY)
#define LEVELDB_EXPORT
#endif

#endif // !defined(LEVELDB_EXPORT)

#endif //SMALLPROJECTS_EXPORT_H

#include <gio/gio.h>

#if defined (__ELF__) && ( __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6))
# define SECTION __attribute__ ((section (".gresource.datetime_window"), aligned (8)))
#else
# define SECTION
#endif

static const SECTION union { const guint8 data[908]; const double alignment; void * const ptr;}  datetime_window_resource_data = { {
  0x47, 0x56, 0x61, 0x72, 0x69, 0x61, 0x6e, 0x74, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x28, 0x06, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 
  0xeb, 0x66, 0x1e, 0x03, 0x05, 0x00, 0x00, 0x00, 
  0xc8, 0x00, 0x00, 0x00, 0x07, 0x00, 0x4c, 0x00, 
  0xd0, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00, 
  0x69, 0x82, 0x2f, 0x58, 0x00, 0x00, 0x00, 0x00, 
  0xd4, 0x00, 0x00, 0x00, 0x12, 0x00, 0x76, 0x00, 
  0xe8, 0x00, 0x00, 0x00, 0x63, 0x03, 0x00, 0x00, 
  0xd4, 0xb5, 0x02, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0x63, 0x03, 0x00, 0x00, 0x01, 0x00, 0x4c, 0x00, 
  0x64, 0x03, 0x00, 0x00, 0x68, 0x03, 0x00, 0x00, 
  0x51, 0x55, 0xd5, 0xbc, 0x04, 0x00, 0x00, 0x00, 
  0x68, 0x03, 0x00, 0x00, 0x08, 0x00, 0x4c, 0x00, 
  0x70, 0x03, 0x00, 0x00, 0x74, 0x03, 0x00, 0x00, 
  0x60, 0xab, 0x78, 0x7c, 0x02, 0x00, 0x00, 0x00, 
  0x74, 0x03, 0x00, 0x00, 0x03, 0x00, 0x4c, 0x00, 
  0x78, 0x03, 0x00, 0x00, 0x7c, 0x03, 0x00, 0x00, 
  0x2d, 0xc8, 0xf5, 0xa0, 0x03, 0x00, 0x00, 0x00, 
  0x7c, 0x03, 0x00, 0x00, 0x09, 0x00, 0x4c, 0x00, 
  0x88, 0x03, 0x00, 0x00, 0x8c, 0x03, 0x00, 0x00, 
  0x70, 0x6c, 0x75, 0x67, 0x69, 0x6e, 0x2f, 0x00, 
  0x01, 0x00, 0x00, 0x00, 0x64, 0x61, 0x74, 0x65, 
  0x74, 0x69, 0x6d, 0x65, 0x2d, 0x77, 0x69, 0x6e, 
  0x64, 0x6f, 0x77, 0x2e, 0x75, 0x69, 0x00, 0x00, 
  0x6b, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76, 0x65, 
  0x72, 0x73, 0x69, 0x6f, 0x6e, 0x3d, 0x22, 0x31, 
  0x2e, 0x30, 0x22, 0x20, 0x65, 0x6e, 0x63, 0x6f, 
  0x64, 0x69, 0x6e, 0x67, 0x3d, 0x22, 0x55, 0x54, 
  0x46, 0x2d, 0x38, 0x22, 0x3f, 0x3e, 0x0a, 0x3c, 
  0x21, 0x2d, 0x2d, 0x20, 0x47, 0x65, 0x6e, 0x65, 
  0x72, 0x61, 0x74, 0x65, 0x64, 0x20, 0x77, 0x69, 
  0x74, 0x68, 0x20, 0x67, 0x6c, 0x61, 0x64, 0x65, 
  0x20, 0x33, 0x2e, 0x31, 0x38, 0x2e, 0x33, 0x20, 
  0x2d, 0x2d, 0x3e, 0x0a, 0x3c, 0x69, 0x6e, 0x74, 
  0x65, 0x72, 0x66, 0x61, 0x63, 0x65, 0x3e, 0x3c, 
  0x72, 0x65, 0x71, 0x75, 0x69, 0x72, 0x65, 0x73, 
  0x20, 0x6c, 0x69, 0x62, 0x3d, 0x22, 0x67, 0x74, 
  0x6b, 0x2b, 0x22, 0x20, 0x76, 0x65, 0x72, 0x73, 
  0x69, 0x6f, 0x6e, 0x3d, 0x22, 0x33, 0x2e, 0x31, 
  0x32, 0x22, 0x2f, 0x3e, 0x3c, 0x6f, 0x62, 0x6a, 
  0x65, 0x63, 0x74, 0x20, 0x63, 0x6c, 0x61, 0x73, 
  0x73, 0x3d, 0x22, 0x47, 0x74, 0x6b, 0x57, 0x69, 
  0x6e, 0x64, 0x6f, 0x77, 0x22, 0x20, 0x69, 0x64, 
  0x3d, 0x22, 0x64, 0x61, 0x74, 0x65, 0x74, 0x69, 
  0x6d, 0x65, 0x2d, 0x77, 0x69, 0x6e, 0x64, 0x6f, 
  0x77, 0x22, 0x3e, 0x3c, 0x70, 0x72, 0x6f, 0x70, 
  0x65, 0x72, 0x74, 0x79, 0x20, 0x6e, 0x61, 0x6d, 
  0x65, 0x3d, 0x22, 0x77, 0x69, 0x64, 0x74, 0x68, 
  0x5f, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 
  0x22, 0x3e, 0x32, 0x35, 0x36, 0x3c, 0x2f, 0x70, 
  0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 0x79, 0x3e, 
  0x3c, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 
  0x79, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x3d, 0x22, 
  0x63, 0x61, 0x6e, 0x5f, 0x66, 0x6f, 0x63, 0x75, 
  0x73, 0x22, 0x3e, 0x46, 0x61, 0x6c, 0x73, 0x65, 
  0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 
  0x74, 0x79, 0x3e, 0x3c, 0x70, 0x72, 0x6f, 0x70, 
  0x65, 0x72, 0x74, 0x79, 0x20, 0x6e, 0x61, 0x6d, 
  0x65, 0x3d, 0x22, 0x62, 0x6f, 0x72, 0x64, 0x65, 
  0x72, 0x5f, 0x77, 0x69, 0x64, 0x74, 0x68, 0x22, 
  0x3e, 0x36, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x70, 
  0x65, 0x72, 0x74, 0x79, 0x3e, 0x3c, 0x70, 0x72, 
  0x6f, 0x70, 0x65, 0x72, 0x74, 0x79, 0x20, 0x6e, 
  0x61, 0x6d, 0x65, 0x3d, 0x22, 0x72, 0x65, 0x73, 
  0x69, 0x7a, 0x61, 0x62, 0x6c, 0x65, 0x22, 0x3e, 
  0x46, 0x61, 0x6c, 0x73, 0x65, 0x3c, 0x2f, 0x70, 
  0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 0x79, 0x3e, 
  0x3c, 0x63, 0x68, 0x69, 0x6c, 0x64, 0x3e, 0x3c, 
  0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x20, 0x63, 
  0x6c, 0x61, 0x73, 0x73, 0x3d, 0x22, 0x47, 0x74, 
  0x6b, 0x43, 0x61, 0x6c, 0x65, 0x6e, 0x64, 0x61, 
  0x72, 0x22, 0x20, 0x69, 0x64, 0x3d, 0x22, 0x63, 
  0x61, 0x6c, 0x65, 0x6e, 0x64, 0x61, 0x72, 0x22, 
  0x3e, 0x3c, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 
  0x74, 0x79, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x3d, 
  0x22, 0x76, 0x69, 0x73, 0x69, 0x62, 0x6c, 0x65, 
  0x22, 0x3e, 0x54, 0x72, 0x75, 0x65, 0x3c, 0x2f, 
  0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 0x79, 
  0x3e, 0x3c, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 
  0x74, 0x79, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x3d, 
  0x22, 0x63, 0x61, 0x6e, 0x5f, 0x66, 0x6f, 0x63, 
  0x75, 0x73, 0x22, 0x3e, 0x54, 0x72, 0x75, 0x65, 
  0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 
  0x74, 0x79, 0x3e, 0x3c, 0x70, 0x72, 0x6f, 0x70, 
  0x65, 0x72, 0x74, 0x79, 0x20, 0x6e, 0x61, 0x6d, 
  0x65, 0x3d, 0x22, 0x79, 0x65, 0x61, 0x72, 0x22, 
  0x3e, 0x32, 0x30, 0x31, 0x36, 0x3c, 0x2f, 0x70, 
  0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 0x79, 0x3e, 
  0x3c, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 0x74, 
  0x79, 0x20, 0x6e, 0x61, 0x6d, 0x65, 0x3d, 0x22, 
  0x6d, 0x6f, 0x6e, 0x74, 0x68, 0x22, 0x3e, 0x39, 
  0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x70, 0x65, 0x72, 
  0x74, 0x79, 0x3e, 0x3c, 0x70, 0x72, 0x6f, 0x70, 
  0x65, 0x72, 0x74, 0x79, 0x20, 0x6e, 0x61, 0x6d, 
  0x65, 0x3d, 0x22, 0x64, 0x61, 0x79, 0x22, 0x3e, 
  0x34, 0x3c, 0x2f, 0x70, 0x72, 0x6f, 0x70, 0x65, 
  0x72, 0x74, 0x79, 0x3e, 0x3c, 0x2f, 0x6f, 0x62, 
  0x6a, 0x65, 0x63, 0x74, 0x3e, 0x3c, 0x2f, 0x63, 
  0x68, 0x69, 0x6c, 0x64, 0x3e, 0x3c, 0x2f, 0x6f, 
  0x62, 0x6a, 0x65, 0x63, 0x74, 0x3e, 0x3c, 0x2f, 
  0x69, 0x6e, 0x74, 0x65, 0x72, 0x66, 0x61, 0x63, 
  0x65, 0x3e, 0x0a, 0x00, 0x00, 0x28, 0x75, 0x75, 
  0x61, 0x79, 0x29, 0x2f, 0x04, 0x00, 0x00, 0x00, 
  0x67, 0x6f, 0x6f, 0x72, 0x6f, 0x6f, 0x6d, 0x2f, 
  0x05, 0x00, 0x00, 0x00, 0x6b, 0x72, 0x2f, 0x00, 
  0x03, 0x00, 0x00, 0x00, 0x64, 0x61, 0x74, 0x65, 
  0x74, 0x69, 0x6d, 0x65, 0x2f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
} };

static GStaticResource static_resource = { datetime_window_resource_data.data, sizeof (datetime_window_resource_data.data), NULL, NULL, NULL };
extern GResource *datetime_window_get_resource (void);
GResource *datetime_window_get_resource (void)
{
  return g_static_resource_get_resource (&static_resource);
}
/*
  If G_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a sane way, including e.g. on library unload. If not you're on
  your own.

  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):

  #ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  G_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }

*/

#if  __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func (void);
#define G_DEFINE_DESTRUCTOR(_func) static void __attribute__((destructor)) _func (void);

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __pragma(section(".CRT$XCU",read)) \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined (_MSC_VER)

#define G_HAS_CONSTRUCTORS 1

/* Pre Visual studio 2008 must use #pragma section */
#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _wrapper(void) { _func(); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func ## _wrapper;

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  section(".CRT$XCU",read)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void); \
  static int _func ## _constructor(void) { atexit (_func); return 0; } \
  __declspec(allocate(".CRT$XCU")) static int (* _array ## _func)(void) = _func ## _constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define G_HAS_CONSTRUCTORS 1

#define G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA 1

#define G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
  init(_func)
#define G_DEFINE_CONSTRUCTOR(_func) \
  static void _func(void);

#define G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
  fini(_func)
#define G_DEFINE_DESTRUCTOR(_func) \
  static void _func(void);

#else

/* constructors not supported for this compiler */

#endif


#ifdef G_HAS_CONSTRUCTORS

#ifdef G_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(resource_constructor)
#endif
G_DEFINE_CONSTRUCTOR(resource_constructor)
#ifdef G_DEFINE_DESTRUCTOR_NEEDS_PRAGMA
#pragma G_DEFINE_DESTRUCTOR_PRAGMA_ARGS(resource_destructor)
#endif
G_DEFINE_DESTRUCTOR(resource_destructor)

#else
#warning "Constructor not supported on this compiler, linking in resources will not work"
#endif

static void resource_constructor (void)
{
  g_static_resource_init (&static_resource);
}

static void resource_destructor (void)
{
  g_static_resource_fini (&static_resource);
}


// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl NODEAPP_Configurator
// ------------------------------
#ifndef NODEAPP_CONFIGURATOR_EXPORT_H
#define NODEAPP_CONFIGURATOR_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (NODEAPP_CONFIGURATOR_HAS_DLL)
#  define NODEAPP_CONFIGURATOR_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && NODEAPP_CONFIGURATOR_HAS_DLL */

#if !defined (NODEAPP_CONFIGURATOR_HAS_DLL)
#  define NODEAPP_CONFIGURATOR_HAS_DLL 1
#endif /* ! NODEAPP_CONFIGURATOR_HAS_DLL */

#if defined (NODEAPP_CONFIGURATOR_HAS_DLL) && (NODEAPP_CONFIGURATOR_HAS_DLL == 1)
#  if defined (NODEAPP_CONFIGURATOR_BUILD_DLL)
#    define NODEAPP_Configurator_Export ACE_Proper_Export_Flag
#    define NODEAPP_CONFIGURATOR_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define NODEAPP_CONFIGURATOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* NODEAPP_CONFIGURATOR_BUILD_DLL */
#    define NODEAPP_Configurator_Export ACE_Proper_Import_Flag
#    define NODEAPP_CONFIGURATOR_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define NODEAPP_CONFIGURATOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* NODEAPP_CONFIGURATOR_BUILD_DLL */
#else /* NODEAPP_CONFIGURATOR_HAS_DLL == 1 */
#  define NODEAPP_Configurator_Export
#  define NODEAPP_CONFIGURATOR_SINGLETON_DECLARATION(T)
#  define NODEAPP_CONFIGURATOR_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* NODEAPP_CONFIGURATOR_HAS_DLL == 1 */

// Set NODEAPP_CONFIGURATOR_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (NODEAPP_CONFIGURATOR_NTRACE)
#  if (ACE_NTRACE == 1)
#    define NODEAPP_CONFIGURATOR_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define NODEAPP_CONFIGURATOR_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !NODEAPP_CONFIGURATOR_NTRACE */

#if (NODEAPP_CONFIGURATOR_NTRACE == 1)
#  define NODEAPP_CONFIGURATOR_TRACE(X)
#else /* (NODEAPP_CONFIGURATOR_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define NODEAPP_CONFIGURATOR_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (NODEAPP_CONFIGURATOR_NTRACE == 1) */

#endif /* NODEAPP_CONFIGURATOR_EXPORT_H */

// End of auto generated file.

/* Copyright (C) 2011-2014 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SAMPGDK_CORE_H
#define SAMPGDK_CORE_H

#include <stdarg.h>

#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/sdk.h>

/**
 * \defgroup core      Core
 * \defgroup interop   Interop
 * \defgroup version   Version
 * \defgroup sdk       SA-MP SDK
 * \defgroup natives   SA-MP Natives
 * \defgroup callbacks SA-MP Callbacks
 */

/**
 * \addtogroup core
 * @{
 */

/**
 * \brief Returns supported SDK version.
 *
 * This function should be called from Supports():
 *
 * \code
 * PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
 *   return sampgdk_Supports() | SUPPORTS_PROCESS_TICK;
 * }
 * \endcode
 *
 * \returns SUPPORTS_VERSION.
 */
SAMPGDK_API(unsigned int, sampgdk_Supports(void));

/**
 * \brief Gets plugin handle by address.
 *
 * \returns The plugin handle or NULL if failed.
 */
SAMPGDK_API(void *, sampgdk_GetPluginHandle(void *address));

/**
 * \brief Initializes the library.
 *
 * This function should be called when the plugin is loaded,
 * e.g. from Load():
 *
 * \code
 * PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
 *   ...
 *   return sampgdk_Load(plugin, ppData);
 * }
 * \endcode
 *
 * \param plugin The plugin handle obtained with sampgdk_GetPluginHandle().
 * \param ppData A pointer to the SA-MP plugin data passed to Load().
 *
 * \returns Returns \c true on success and \c false otherwise.
 *
 * \see sampgdk_Unload()
 * \see sampgdk_GetPluginHandle()
 */
SAMPGDK_API(bool, sampgdk_Load(void *plugin, void **ppData));

/**
 * \brief Performs the final cleanup.
 *
 * This function should be called when the plugin is unloaded,
 * e.g. from Unload():
 *
 * \code
 * PLUGIN_EXPORT void PLUGIN_CALL Unload() {
 *   ...
 *   sampgdk_Unload(plugin);
 * }
 * \endcode
 *
 * \param plugin The plugin handle obtained with sampgdk_GetPluginHandle().
 *
 * \see sampgdk_Load()
 * \see sampgdk_GetPluginHandle()
 */
SAMPGDK_API(void, sampgdk_Unload(void *plugin));

/**
 * \brief Processes timers created by the specified plugin.
 *
 * This function should be called from ProcessTick():
 *
 * \code
 * PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
 *   sampgdk_ProcessTick(plugin);
 * }
 * \endcode
 *
 * \param plugin The plugin handle obtained with sampgdk_GetPluginHandle().
 *
 * \see sampgdk_GetPluginHandle()
 */
SAMPGDK_API(void, sampgdk_ProcessTick(void *plugin));

/**
 * \brief Prints a message to the server log.
 *
 * \note The resulting message cannot be longer than 1024 characters.
 *
 * \param format A printf-like format string.
 * \param ... Further arguments to logprintf().
 *
 * \see sampgdk_vlogprintf()
 */
SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...));

/**
 * \brief Prints a message to the server log.
 *
 * This function is identical to sampgdk_logprintf() but takes a
 * \c va_list instead of a variable number of arguments.
 *
 * \param format A printf-like format string.
 * \param args Further arguments to logprintf().
 *
 * \see sampgdk_logprintf()
 */
SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args));

/** @} */

#ifdef __cplusplus

/// \brief Main namespace.
namespace sampgdk {

/**
 * \addtogroup core
 * @{
 */

/// \brief C++ wrapper around sampgdk_Supports().
inline unsigned int Supports() {
  return sampgdk_Supports();
}

/// \brief C++ wrapper around sampgdk_GetPluginHandle().
inline void *GetPluginHandle(void *address) {
  return sampgdk_GetPluginHandle(address);
}

/// \brief Gets current plugin handle.
inline void *GetCurrentPluginHandle() {
  static void *handle = sampgdk_GetPluginHandle((void *)&::Load);
  return handle;
}

/// \brief C++ wrapper around sampgdk_Load().
inline bool Load(void *plugin, void **ppData) {
  return sampgdk_Load(plugin, ppData);
}

/// \brief C++ wrapper around sampgdk_Load().
inline bool Load(void **ppData) {
  return sampgdk_Load(GetCurrentPluginHandle(), ppData);
}

/// \brief C++ wrapper around sampgdk_Unload().
inline void Unload(void *plugin) {
  sampgdk_Unload(plugin);
}

/// \brief C++ wrapper around sampgdk_Unload().
inline void Unload() {
  sampgdk_Unload(GetCurrentPluginHandle());
}

/// \brief C++ wrapper around sampgdk_ProcessTick().
inline void ProcessTick(void *plugin) {
  sampgdk_ProcessTick(plugin);
}

/// \brief C++ wrapper around sampgdk_ProcessTick().
inline void ProcessTick() {
  sampgdk_ProcessTick(GetCurrentPluginHandle());
}

/// \brief C++ wrapper around sampgdk_logprintf().
inline void logprintf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  sampgdk_vlogprintf(format, args);
  va_end(args);
}

/// \brief C++ wrapper around sampgdk_vlogprintf().
inline void vlogprintf(const char *format, va_list args) {
  sampgdk_vlogprintf(format, args);
}

/** @} */

} // namespace sampgdk

#endif /* __cplusplus */

#endif /* !SAMPGDK_CORE_H */

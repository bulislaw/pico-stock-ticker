#pragma once

#include "pico/stdlib.h"

/** Sends a preconfigured HTTP GET request using TLS
 *
 * This is not a generic HTTP client, the functionality is limited to what I need. If reply doesn't fit into the buffer,
 * it will be truncated and the remaining bytes will be discarded.
 *
 * This function is not thread safe.
 *
 * This function will block until the request is completed or timeout.
 *
 * Currently it allocates memory on heap for the full body of HTTP request.
 *
 * @param[in] server The server to send the request to
 * @param[in] path The path to send the request to
 * @param[in] cert TLS certificate, if NULL certificate is not checked
 * @param[in] cert_len TLS certificate's len
 * @param[out] buf The buffer to store the response; NULL terminated
 * @param[in] buf_len The size of the buffer
 * @return The number of bytes received if positive or negative error
 */
int https_get(const char *server, const char *path, const uint8_t *cert, size_t cert_len, char *buf, size_t buf_len);
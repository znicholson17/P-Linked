#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the socket client.
 */
void socket_client_init(void);

/**
 * @brief Start the socket client task.
 */
void socket_client_start(void);

#ifdef __cplusplus
}
#endif

#endif


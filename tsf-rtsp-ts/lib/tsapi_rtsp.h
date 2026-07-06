/* SPDX-License-Identifier: MIT */
/* Copyright (C) 2026 Interpretica, Unipessoal Lda. All rights reserved. */
/** @file
 * @brief Suite helpers: an agent and an RPC server on it, which tapi_rtsp
 *        drives.
 * @author Maxim Menshikov <maxim.menshikov@interpretica.io>
 */
#ifndef __TSAPI_RTSP_H__
#define __TSAPI_RTSP_H__
#include "rcf_rpc.h"
#include "te_errno.h"
#ifdef __cplusplus
extern "C" {
#endif
/** The agent this suite works on. */
#define TSAPI_RTSP_TA   "Agt_A"
/** What a test needs to talk to the agent. */
typedef struct tsapi_rtsp_session {
    const char *ta;           /**< Agent name. */
    rcf_rpc_server *pco;      /**< RPC server on it - what tapi_rtsp takes. */
} tsapi_rtsp_session;
/** Open a session: an RPC server on the agent. */
extern te_errno tsapi_rtsp_session_init(tsapi_rtsp_session *session,
                                        const char *name);
/** Close a session. */
extern void tsapi_rtsp_session_fini(tsapi_rtsp_session *session);
#ifdef __cplusplus
}
#endif
#endif /* !__TSAPI_RTSP_H__ */

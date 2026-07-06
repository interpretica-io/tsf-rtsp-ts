/** @file
 * @brief RTSP Group
 *
 * OPTIONS then DESCRIBE a configured RTSP endpoint. The endpoint is the
 * test's to supply (env TSF_RTSP_URI, e.g. rtsp://host:554/stream); with
 * none configured the test skips cleanly - a host with no RTSP server to
 * point at is not a failure. It asserts the control path runs and the
 * OPTIONS reply is sane, not a particular stream.
 *
 * Copyright (C) 2026 Interpretica Unipessoal Lda
 */
#define TE_TEST_NAME    "rtsp/probe"
#include "te_config.h"
#include <stdlib.h>
#include "tapi_test.h"
#include "te_string.h"
#include "tapi_rtsp.h"
#include "tsapi_rtsp.h"
int
main(int argc, char **argv)
{
    tsapi_rtsp_session sess = {0};
    tapi_rtsp_reply reply;
    bool reply_ready = false;
    const char *uri;

    TEST_START;

    uri = getenv("TSF_RTSP_URI");
    if (uri == NULL || uri[0] == '\0')
        TEST_SKIP("Set TSF_RTSP_URI (e.g. rtsp://host:554/stream) to point "
                  "at an endpoint");

    TEST_STEP("Open a session to the agent");
    CHECK_RC(tsapi_rtsp_session_init(&sess, "pco_rtsp_probe"));

    TEST_STEP("OPTIONS %s", uri);
    CHECK_RC(tapi_rtsp_options(sess.pco, uri, &reply));
    reply_ready = true;
    RING("OPTIONS -> %d; Server: %s; Public: %s", reply.status,
         reply.server != NULL ? reply.server : "?",
         reply.public_methods != NULL ? reply.public_methods : "?");
    if (reply.status < 100 || reply.status >= 600)
        TEST_VERDICT("OPTIONS returned an implausible status %d",
                     reply.status);
    tapi_rtsp_reply_free(&reply);
    reply_ready = false;

    TEST_STEP("DESCRIBE %s", uri);
    if (tapi_rtsp_describe(sess.pco, uri, &reply) == 0)
    {
        reply_ready = true;
        RING("DESCRIBE -> %d; Content-Type: %s; %zu-byte body", reply.status,
             reply.content_type != NULL ? reply.content_type : "?",
             reply.body != NULL ? strlen(reply.body) : (size_t)0);
        tapi_rtsp_reply_free(&reply);
        reply_ready = false;
    }

    TEST_SUCCESS;

cleanup:
    if (reply_ready)
        tapi_rtsp_reply_free(&reply);
    tsapi_rtsp_session_fini(&sess);
    TEST_END;
}

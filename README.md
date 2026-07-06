# tsf-rtsp-ts

A Test Environment suite exercising
[tsf-rtsp](https://github.com/interpretica-io/tsf-rtsp) (`tapi_rtsp`) from
the agent it runs on — RTSP control (OPTIONS + DESCRIBE) over libcurl.

| Test | What it checks |
|---|---|
| `probe` | OPTIONS logs the server's `Public` method set and `Server` header and returns a plausible status; DESCRIBE logs the status and SDP content-type. Control only — no media streamed. |

The endpoint is supplied via **env `TSF_RTSP_URI`** (e.g.
`rtsp://host:554/stream`); with none set the test **skips cleanly**, so a
bare run is green.

## Running it

```bash
./scripts/run.sh guess --cfg=localhost        # native (agent on this host)
./scripts/run.sh docker guess --cfg=localhost # in the build container
```
Needs `test-environment` as a sibling and libcurl with its dev headers
(the Dockerfile installs `libcurl4-openssl-dev`).

## Status

Written alongside tsf-rtsp; the module's libcurl RTSP usage was
syntax-checked against real headers. First native build on lasirena is
the end-to-end verification.

## Quick guide for AI coding agents working on SNIPS

Short contract
- Inputs: small, focused edits or feature requests (files under `firmware/`, `docs/`, `resources/`, top-level README).
- Outputs: minimal, working changes (buildable firmware where applicable) and a short verification step (build or linter result).
- Error modes: missing hardware details, unavailable test rigs, or private secrets — report and propose alternatives.

Essential repository overview (big picture)
- Purpose: Embedded LoRa mesh + positioning system. See `README.md` for architecture and role definitions (Anchors, Relay, Mobile).
- Major components:
  - `firmware/ESP32S3_LoRa/` — PlatformIO Arduino project (env: `seeed_xiao_esp32s3`, libs: RadioLib/LoRa).
  - `firmware/ARD_Lora/` — PlatformIO Arduino project (env: `uno_r4_minima`).
  - `docs/` — conceptual, protocol and hardware docs; good source for design rationale and expected behaviour.

Developer workflows & concrete commands (PowerShell / CI)
- Local build (PlatformIO CLI installed):
  - Build ESP32 firmware: `pio run -e seeed_xiao_esp32s3` from `firmware/ESP32S3_LoRa`.
  - Build Arduino Uno R4 firmware: `pio run -e uno_r4_minima` from `firmware/ARD_Lora`.
  - Upload (device attached): `pio run -e <env> -t upload`.
- In VS Code prefer PlatformIO extension (open the firmware folder as a project or use PlatformIO sidebar).
- Tests: firmware folders include `test/` README placeholders — no automated tests currently; if adding tests, follow PlatformIO unit testing conventions.

Project-specific patterns & conventions
- Firmware uses Arduino sketch structure: `src/main.cpp` with `setup()` and `loop()`; put board-specific bindings and radio initialisation in `firmware/*/src/`.
- Add library dependencies in `platformio.ini` using `lib_deps` (example: `RadioLib` and `LoRa` in `ESP32S3_LoRa/platformio.ini`).
- Platform-specific env names are authoritative — use those exact environment ids when running `pio run -e`.

Integration points & external dependencies
- LoRa libraries referenced in `platformio.ini` (RadioLib, sandeepmistry's LoRa). Ensure new code uses those APIs or adds compatible lib_deps.
- Hardware behaviour (timing, TDMA) is documented in `docs/` and must be respected when changing message formats or scheduling code.

Examples of safe, useful edits
- Fix a compile error in `firmware/*/src/*.cpp` and demonstrate success by running `pio run -e <env>` and reporting the build log.
- Add a `lib_deps` entry to `platformio.ini` and run a rebuild to confirm no new dependency issues.
- Update protocol documentation in `docs/protocol/` and provide a short code-change summary linking to the modified files.

What not to assume
- No physical devices available for runtime testing: prefer compile-time validation and clear instructions for manual testing.
- CI workflows are minimal/no-op currently; do not assume an existing automated build for firmware unless you add it.

Key files to reference while working
- `README.md` — project overview and architecture (high-level requirements)
- `docs/conceptual/overview.md` — design rationale and protocol expectations
- `firmware/ESP32S3_LoRa/platformio.ini` and `firmware/ESP32S3_LoRa/src/main.cpp`
- `firmware/ARD_Lora/platformio.ini` and `firmware/ARD_Lora/src/main.cpp`

If something is unclear
- Ask a short clarifying question specifying which hardware, which env, and whether you should prefer compile-time-only changes or modify docs/tests as well.

Please review this guidance and tell me if you'd like me to add: CI build steps for PlatformIO, a template PR checklist, or examples for adding PlatformIO unit tests.

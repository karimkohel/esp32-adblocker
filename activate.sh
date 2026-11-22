#!/usr/bin/env bash

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

conda activate "$PROJECT_DIR/.conda-env"
export PLATFORMIO_CORE_DIR="$PROJECT_DIR/.pio-core"

echo "✅ ESP32 development environment activated!"
